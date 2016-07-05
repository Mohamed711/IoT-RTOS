/******************************************************************************
 *	RTOS V 0.0.0 - Copyright (C) 2016
 *  Computer and systems department
 *  Ain Shams University
 *  
 *  All rights reserved
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the redistributions of the
 *  source code must retain the above copyright notice, and this condition.
 * 
 * 	FreeRTOS V8.2.3 - Copyright (C) 2015 Real Time Engineers Ltd.
 *
 * 	This version is a modified and enhanced version of the queue module
 * 	in the freeRTOS distribution.
 *****************************************************************************/

#include <stdint.h>
#include <stdlib.h>

#include "../RTOS.h"
#include "ipc.h"
#include "ipc_trace.h"
#include "../Scheduler/queue.h"
#include "../Scheduler/ReSched.h"
#include "../MMU/mmu.h"
#include "../Scheduler/Process.h"

extern bool wakefromSleep;	


/****************************************************************************
*
* Definition of the queue used in the inter-process communcation.
* Items are transferred to the queue by copy not by reference.
*
*****************************************************************************/
typedef struct QueueDefinition
{
	int8_t *pcHead;								/* Points to the beginning of the queue storage area. */
	int8_t *pcTail;								/* Points to the byte at the end of the queue storage area. */
	int8_t *pcWriteTo;						/* Points to the free next place in the storage area. */
	int8_t *pcReadFrom;						/* Points to the last place that a queued item was read from when the structure is used as a queue. */

	volatile UBaseType_t uxMessagesWaiting;	/* The number of items currently in the queue. */
	UBaseType_t uxLength;					/* The length of the queue defined as the number of items it will hold, not the number of bytes. */
	UBaseType_t uxItemSize;				/* The size of each items that the queue will hold. */
	
	qid xTasksWaitingToSend;		/* Queue Number of tasks waiting to send */
	qid xTasksWaitingToReceive;	/* Queue Number of tasks waiting to receive */

}Queue_t;


/****************************************************************************
*
* Static functions prototypes.
*
*****************************************************************************/
static BaseType_t prvIsQueueEmpty( const Queue_t *pxQueue );
static BaseType_t prvIsQueueFull( const Queue_t *pxQueue );
static BaseType_t prvCopyDataToQueue( Queue_t * const pxQueue, const void *pvItemToQueue, const BaseType_t xPosition );
static void prvCopyDataFromQueue( Queue_t * const pxQueue, void * const pvBuffer );


/****************************************************************************
*	Function Number 1
*
*	The function's purpose is to create a new queue.
*
*	\param uxQueueLength			The number of items of the queue.
*	\param uxItemSize				  The size of the item.
*
* \return QueueHandle_t to the created queue
*
*****************************************************************************/
QueueHandle_t IPC_xQueueGenericCreate( const UBaseType_t uxQueueLength, const UBaseType_t uxItemSize )
{
	Queue_t *pxNewQueue;
	size_t xQueueSizeInBytes;
	QueueHandle_t xReturn = NULL;

	configASSERT( ( uxQueueLength > ( UBaseType_t ) 0 ) && ( uxItemSize > ( UBaseType_t ) 0 ) );

	/* The queue is one byte longer than asked for to make wrap checking
	easier/faster. */
	xQueueSizeInBytes = ( size_t ) ( uxQueueLength * uxItemSize ) + ( size_t ) 1;


	/* Allocate the new queue structure and storage area. */
	pxNewQueue = ( Queue_t * ) pvPortMalloc( sizeof( Queue_t ) + xQueueSizeInBytes );

	if( pxNewQueue != NULL )
	{

		/* Jump past the queue structure to find the location of the queue
		storage area. */
		pxNewQueue->pcHead = ( ( int8_t * ) pxNewQueue ) + sizeof( Queue_t );


		/* Initialize the queue members as described above where the queue type
		is defined. */
		pxNewQueue->uxLength = uxQueueLength;
		pxNewQueue->uxItemSize = uxItemSize;
		( void ) IPC_xQueueGenericReset( pxNewQueue, IPC_RESET_NEW_QUEUE );

		traceQUEUE_CREATE( pxNewQueue );
		xReturn = pxNewQueue;
	}
	else
	{
		mtCOVERAGE_TEST_MARKER();
	}

	configASSERT( xReturn );

	return xReturn;
}


/****************************************************************************
*	Function Number 2
*
*	The function's purpose is to reset a queue by resetting its parameters
* to the default values.
*
*	The function is called either for a new queue to reset all the parameters
* to the default values or for an existing queue.
*
* In case of the function is called to reset an existing queue, the function 
* checks if any tasks are waiting to send to the queue to activate them.

*	\param xQueue						Pointer to the queue.
*	\param xNewQueue				Indicate if it's a new queue or not.
*
* \return SUCCESS if there's no error.
*
*****************************************************************************/
BaseType_t IPC_xQueueGenericReset( QueueHandle_t xQueue, BaseType_t xNewQueue )
{
	Queue_t * const pxQueue = ( Queue_t * ) xQueue;
	
	configASSERT( pxQueue );

	EnterCriticalSection();
	{
		pxQueue->pcTail = pxQueue->pcHead + ( pxQueue->uxLength * pxQueue->uxItemSize );
		pxQueue->pcReadFrom = pxQueue->pcTail - pxQueue->uxItemSize;
		pxQueue->uxMessagesWaiting = ( UBaseType_t ) 0U;
		pxQueue->pcWriteTo = pxQueue->pcHead;

		if( xNewQueue == IPC_RESET_EXISTING_QUEUE )
		{
			/* Resetting an already existing queue */
			/* If there are tasks blocked waiting to read from the queue, then
			the tasks will remain blocked as after this function exits the queue
			will still be empty.  If there are tasks blocked waiting to write to
			the queue, then one should be unblocked as after this function exits
			it will be possible to write to it. */

			if( nonEmpty( pxQueue->xTasksWaitingToSend ) )
			{
				pid ProcessId = dequeue( pxQueue->xTasksWaitingToSend );
				Scheduler_processSetReady( ProcessId );
				wakefromSleep = false;
				IntTrigger(INT_TIMER0A);
			}
			else
			{
				mtCOVERAGE_TEST_MARKER();
			}
		}
		else
		{
			pxQueue->xTasksWaitingToSend = ( qid ) newqueue();
			pxQueue->xTasksWaitingToReceive = ( qid ) newqueue();
		}
	}
	ExitCriticalSection();

	return SUCCESS;
}


/****************************************************************************
*	Function Number 3
*
*	The function's purpose is to send data to a specific queue.
* 
*	\param xQueue								Pointer to the queue.
*	\param pvItemToQueue				Pointer to the item to be transferred to the queue.
* \param xSleepTime						Sleeping time to wait on the queue if it is full.
* \param xCopyPosition				Position where the item will be deposited.
*
* \return SUCCESS if there's no error.
*
*****************************************************************************/

BaseType_t IPC_xQueueGenericSend( QueueHandle_t xQueue, const void * const pvItemToQueue, _delay_ms xSleepTime, const BaseType_t xCopyPosition )
{
	Queue_t * const pxQueue = ( Queue_t * ) xQueue;

	configASSERT( pxQueue );

	for(;;)
	{
		EnterCriticalSection();
		{
			if( pxQueue->uxMessagesWaiting < pxQueue->uxLength )
			{
				traceQUEUE_SEND( pxQueue );
				prvCopyDataToQueue( pxQueue, pvItemToQueue, xCopyPosition );

				/* If there was a task waiting for data to arrive on the
				queue then unblock it now. */
				if( nonEmpty ( pxQueue->xTasksWaitingToReceive ) )
				{
					pid ProcessId = dequeue( pxQueue->xTasksWaitingToReceive );
					Scheduler_processSetReady( ProcessId );
				}
				else
				{
					mtCOVERAGE_TEST_MARKER();
				}
				ExitCriticalSection();
				return SUCCESS;
			}
			else
			{
				if( xSleepTime == IPC_NO_SLEEP )
				{
					ExitCriticalSection();
					return errQUEUE_FULL;
				}
				else
				{
					traceBLOCKING_ON_QUEUE_SEND( pxQueue );
					insert( Scheduler_processGetPid() , pxQueue->xTasksWaitingToSend , proctab[Scheduler_processGetPid()].prprio );
					if ( xSleepTime != IPC_WAIT_FOREVER )
					{
						Scheduler_insertd( Scheduler_processGetPid(), sleepingList, xSleepTime );
					}
					else
					{
						mtCOVERAGE_TEST_MARKER();
					}
					
					wakefromSleep = false;
					IntTrigger(INT_TIMER0A);

					if ( prvIsQueueFull( pxQueue ) == pdTRUE )
					{
						ExitCriticalSection();
						return errQUEUE_FULL;
					}
					else
					{
						mtCOVERAGE_TEST_MARKER();
						// remove my self from the sleep queue
					}
				}
			}
		}
		ExitCriticalSection();
	}
}


/****************************************************************************
*	Function Number 4
*
*	The function's purpose is to receive data from a given queue.
*
*	\param xQueue							Pointer to the queue.
*	\param pvBuffer						Pointer to where the item will be copied.
* \param xSleepTime					Sleeping time to wait on the queue if it is empty.
* \param xJustPeeking				If reading without consuming is required.
*
* \return SUCCESS if there's no error
*
*****************************************************************************/
BaseType_t IPC_xQueueGenericReceive( QueueHandle_t xQueue, void * const pvBuffer, _delay_ms xSleepTime, const BaseType_t xJustPeeking )
{
	int8_t *pcOriginalReadPosition;
	Queue_t * const pxQueue = ( Queue_t * ) xQueue;

	configASSERT( pxQueue );

	for( ;; )
	{
		EnterCriticalSection();
		{
			if( pxQueue->uxMessagesWaiting > ( UBaseType_t ) 0 )
			{
				/* Remember our read position in case we are just peeking. */
				pcOriginalReadPosition = pxQueue->pcReadFrom;

				prvCopyDataFromQueue( pxQueue, pvBuffer );

				if( xJustPeeking == IPC_RECEIVE_WITH_CONSUMING )
				{
					traceQUEUE_RECEIVE( pxQueue );

					/* Data is actually being removed (not just peeked). */
					--( pxQueue->uxMessagesWaiting );

					if( nonEmpty( pxQueue -> xTasksWaitingToSend ) )
					{
						pid ProcessId = dequeue( pxQueue->xTasksWaitingToSend );
						Scheduler_processSetReady( ProcessId );
						wakefromSleep = false;
						IntTrigger(INT_TIMER0A);
					}
					else
					{
						mtCOVERAGE_TEST_MARKER();
					}
				}
				else
				{
					traceQUEUE_PEEK( pxQueue );

					pxQueue->pcReadFrom = pcOriginalReadPosition;

					if( nonEmpty ( pxQueue->xTasksWaitingToReceive ) )
					{
						pid ProcessId = dequeue( pxQueue->xTasksWaitingToReceive );
						Scheduler_processSetReady( ProcessId );
						wakefromSleep = false;
						IntTrigger(INT_TIMER0A);
					}
					else
					{
						mtCOVERAGE_TEST_MARKER();
					}
				}
				ExitCriticalSection();
				return SUCCESS;
			}
			else
			{
				if( xSleepTime ==  IPC_NO_SLEEP )
				{
					ExitCriticalSection();
					traceQUEUE_RECEIVE_FAILED( pxQueue );
					return errQUEUE_EMPTY;
				}
				else
				{
					insert( Scheduler_processGetPid() , pxQueue->xTasksWaitingToReceive , proctab[Scheduler_processGetPid()].prprio );
					
					if ( xSleepTime != IPC_WAIT_FOREVER )
					{
						Scheduler_insertd( Scheduler_processGetPid(), sleepingList, xSleepTime );
					}
					else
					{
						mtCOVERAGE_TEST_MARKER();
					}
					
					wakefromSleep = false;
					IntTrigger(INT_TIMER0A);

					if ( prvIsQueueEmpty( pxQueue ) == pdTRUE )
					{
						ExitCriticalSection();
						return errQUEUE_EMPTY;
					}
					else
					{
						mtCOVERAGE_TEST_MARKER();
						// remove it from the sleeping queue
					}
				}
			}
		}
	ExitCriticalSection();
	}
}


/****************************************************************************
*	Function Number 5
*
*	The function's purpose is to return the number of messages 
* in the queue
*
*	\param xQueue						Pointer to the queue of messages
*
* \return uxReturn				The number of messages in the queue
*
*****************************************************************************/

UBaseType_t IPC_uxQueueMessagesWaiting( const QueueHandle_t xQueue )
{
UBaseType_t uxReturn;

	configASSERT( xQueue );

	EnterCriticalSection();
	{
		uxReturn = ( ( Queue_t * ) xQueue )->uxMessagesWaiting;
	}
	ExitCriticalSection();

	return uxReturn;
}

/****************************************************************************
*	Function Number 6
*
*	The function's purpose is to return the number of free spaces 
* in the queue
*
*	\param xQueue						Pointer to the queue of messages
*
* \return uxReturn				The number of free spaces in the queue
*
*****************************************************************************/

UBaseType_t IPC_uxQueueSpacesAvailable( const QueueHandle_t xQueue )
{
	UBaseType_t uxReturn;
	Queue_t *pxQueue;

	pxQueue = ( Queue_t * ) xQueue;
	configASSERT( pxQueue );

	EnterCriticalSection();
	{
		uxReturn = pxQueue->uxLength - pxQueue->uxMessagesWaiting;
	}
	ExitCriticalSection();

	return uxReturn;
}

/****************************************************************************
*	Function Number 7
*
*	The function's purpose is to return the number of messages 
* in the queue to be called from a critical section or from 
* an ISR.
*
*	\param xQueue						Pointer to the queue of messages
*
* \return uxReturn				The number of messages in the queue
*
*****************************************************************************/

UBaseType_t IPC_uxQueueMessagesWaitingFromISR( const QueueHandle_t xQueue )
{
UBaseType_t uxReturn;

	configASSERT( xQueue );

	uxReturn = ( ( Queue_t * ) xQueue )->uxMessagesWaiting;

	return uxReturn;
} 

/****************************************************************************
*	Function Number 8
*
*	The function's purpose is to check if the queue is empty.
*
*	\param pxQueue						Pointer to the queue of messages
*
* \return xReturn						pdTRUE if the queue is empty, pdFALSE otherwise
*
*****************************************************************************/


static BaseType_t prvIsQueueEmpty( const Queue_t *pxQueue )
{
BaseType_t xReturn;

	EnterCriticalSection();
	{
		if( pxQueue->uxMessagesWaiting == ( UBaseType_t )  0 )
		{
			xReturn = pdTRUE;
		}
		else
		{
			xReturn = pdFALSE;
		}
	}
	ExitCriticalSection();

	return xReturn;
}

/****************************************************************************
*	Function Number 9
*
*	The function's purpose is to check if the queue is empty.
*
*	\param xQueue						Pointer to the queue of messages
*
* \return xReturn					pdTRUE if the queue is empty, pdFALSE otherwise
*
*****************************************************************************/

BaseType_t IPC_xQueueIsQueueEmptyFromISR( const QueueHandle_t xQueue )
{
BaseType_t xReturn;

	configASSERT( xQueue );
	if( ( ( Queue_t * ) xQueue )->uxMessagesWaiting == ( UBaseType_t ) 0 )
	{
		xReturn = pdTRUE;
	}
	else
	{
		xReturn = pdFALSE;
	}

	return xReturn;
} 

/****************************************************************************
*	Function Number 10
*
*	The function's purpose is to check if the queue is full.
*
*	\param pxQueue						Pointer to the queue of messages
*
* \return xReturn						pdTRUE if the queue is full, pdFALSE otherwise
*
*****************************************************************************/

static BaseType_t prvIsQueueFull( const Queue_t *pxQueue )
{
BaseType_t xReturn;

	EnterCriticalSection();
	{
		if( pxQueue->uxMessagesWaiting == pxQueue->uxLength )
		{
			xReturn = pdTRUE;
		}
		else
		{
			xReturn = pdFALSE;
		}
	}
	ExitCriticalSection();

	return xReturn;
}

/****************************************************************************
*	Function Number 11
*
*	The function's purpose is to check if the queue is full.
*
* The function is to be called from a critical section or from
* an ISR.
*
*	\param pxQueue						Pointer to the queue of messages
*
* \return xReturn						pdTRUE if the queue is full, pdFALSE otherwise
*
*****************************************************************************/

BaseType_t IPC_xQueueIsQueueFullFromISR( const QueueHandle_t xQueue )
{
BaseType_t xReturn;

	configASSERT( xQueue );
	if( ( ( Queue_t * ) xQueue )->uxMessagesWaiting == ( ( Queue_t * ) xQueue )->uxLength )
	{
		xReturn = pdTRUE;
	}
	else
	{
		xReturn = pdFALSE;
	}

	return xReturn;
}

/****************************************************************************
*	Function Number 12
*
*	The function's purpose is to delete a queue.
*
*	\param xQueue							Pointer to the queue of messages
*
* \return Nothing
*
*****************************************************************************/

void IPC_vQueueDelete( QueueHandle_t xQueue )
{
	Queue_t * const pxQueue = ( Queue_t * ) xQueue;

	configASSERT( pxQueue );

	traceQUEUE_DELETE( pxQueue );

	/* Not supported in our OS as its static memory implementation */
	/* vPortFree( pxQueue ); */
}


/****************************************************************************
*	Function Number 13
*
*	The function's purpose is to copy data to the queue.
*
*	\param pxQueue						Pointer to the queue of messages.
* \param pvItemToQueue			Pointer to the data to be copied to the queue.
* \param xPosition					Position of the data on the queue.
*
* \return SUCCESS if there is no error.						
*
*****************************************************************************/

static BaseType_t prvCopyDataToQueue( Queue_t * const pxQueue, const void *pvItemToQueue, const BaseType_t xPosition )
{

	if( xPosition == IPC_queueSEND_TO_BACK )
	{
		( void ) memcpy( ( void * ) pxQueue->pcWriteTo, pvItemToQueue, ( size_t ) pxQueue->uxItemSize ); 
		pxQueue->pcWriteTo += pxQueue->uxItemSize;
		if( pxQueue->pcWriteTo >= pxQueue->pcTail ) 
		{
			pxQueue->pcWriteTo = pxQueue->pcHead;
		}
		else
		{
			mtCOVERAGE_TEST_MARKER();
		}
	}
	else
	{
		( void ) memcpy( ( void * ) pxQueue->pcReadFrom, pvItemToQueue, ( size_t ) pxQueue->uxItemSize );
		pxQueue->pcReadFrom -= pxQueue->uxItemSize;
		if( pxQueue->pcReadFrom < pxQueue->pcHead )
		{
			pxQueue->pcReadFrom = ( pxQueue->pcTail - pxQueue->uxItemSize );
		}
		else
		{
			mtCOVERAGE_TEST_MARKER();
		}

		if( xPosition == IPC_queueOVERWRITE )
		{
			if( pxQueue->uxMessagesWaiting > ( UBaseType_t ) 0 )
			{
				/* An item is not being added but overwritten, so subtract
				one from the recorded number of items in the queue so when
				one is added again below the number of recorded items remains
				correct. */
				--( pxQueue->uxMessagesWaiting );
			}
			else
			{
				mtCOVERAGE_TEST_MARKER();
			}
		}
		else
		{
			mtCOVERAGE_TEST_MARKER();
		}
	}

	++( pxQueue->uxMessagesWaiting );

	return SUCCESS;
}

/****************************************************************************
*	Function Number 14
*
*	The function's purpose is to copy data from a queue to a given buffer.
*
*	\param pxQueue						Pointer to the queue of messages
* \param pvBuffer						Pointer to the buffer 
*
* \return Nothing
*
*****************************************************************************/

static void prvCopyDataFromQueue( Queue_t * const pxQueue, void * const pvBuffer )
{

	pxQueue->pcReadFrom += pxQueue->uxItemSize;
	if( pxQueue->pcReadFrom >= pxQueue->pcTail ) 
	{
		pxQueue->pcReadFrom = pxQueue->pcHead;
	}
	else
	{
		mtCOVERAGE_TEST_MARKER();
	}
	( void ) memcpy( ( void * ) pvBuffer, ( void * ) pxQueue->pcReadFrom, ( size_t ) pxQueue->uxItemSize ); /*lint !e961 !e418 MISRA exception as the casts are only redundant for some ports.  Also previous logic ensures a null pointer can only be passed to memcpy() when the count is 0. */

}


