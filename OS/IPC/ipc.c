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

	UBaseType_t xTasksWaitingToSend;		/* Queue Number of tasks waiting to send */
	UBaseType_t xTasksWaitingToReceive;	/* Queue Number of tasks waiting to receive */

	volatile UBaseType_t uxMessagesWaiting;	/* The number of items currently in the queue. */
	UBaseType_t uxLength;					/* The length of the queue defined as the number of items it will hold, not the number of bytes. */
	UBaseType_t uxItemSize;				/* The size of each items that the queue will hold. */

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
*	The function is called either for a new queue to reset all the parameters
* to the default values or for an existing queue.
*
* In case of the function is called to reset an existing queue, the function 
* checks if any tasks are waiting to send to the queue to activate them.

*	\param xQueue			ID of the process to be inserted
*	\param xNewQueue				ID of queue to use
*
* \return pdFAIL if there's an error, pdPASS if there's no error
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
	xQueueSizeInBytes = ( size_t ) ( uxQueueLength * uxItemSize ) + ( size_t ) 1; /*lint !e961 MISRA exception as the casts are only redundant for some ports. */


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
		( void ) IPC_xQueueGenericReset( pxNewQueue, pdTRUE );

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

*	\param xQueue			ID of the process to be inserted
*	\param xNewQueue				ID of queue to use
*
* \return pdFAIL if there's an error, pdPASS if there's no error
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

		if( xNewQueue == pdFALSE )
		{
			/* Resetting an already existing queue */
			/* If there are tasks blocked waiting to read from the queue, then
			the tasks will remain blocked as after this function exits the queue
			will still be empty.  If there are tasks blocked waiting to write to
			the queue, then one should be unblocked as after this function exits
			it will be possible to write to it. */

			if( isEmpty( pxQueue->xTasksWaitingToSend ) == pdFALSE )
			{
				pid ProcessId = dequeue( pxQueue->xTasksWaitingToSend );
				insert( ProcessId , readyList , proctab[ProcessId].prprio );
				proctab[ProcessId].prstate = PR_READY;
		    	queueYIELD_IF_USING_PREEMPTION();
			}
			else
			{
				mtCOVERAGE_TEST_MARKER();
			}
		}
		else
		{
			pxQueue->xTasksWaitingToSend = ( UBaseType_t ) newqueue();
			pxQueue->xTasksWaitingToReceive = ( UBaseType_t ) newqueue();
		}
	}
	ExitCriticalSection();

	/* A value is returned for calling semantic consistency with previous
	versions. */
	return pdPASS;
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

*	\param xQueue			ID of the process to be inserted
*	\param xNewQueue				ID of queue to use
*
* \return pdFAIL if there's an error, pdPASS if there's no error
*
*****************************************************************************/

BaseType_t IPC_xQueueGenericSend( QueueHandle_t xQueue, const void * const pvItemToQueue, _delay_ms xSleepTime, const BaseType_t xCopyPosition )
{
	Queue_t * const pxQueue = ( Queue_t * ) xQueue;

	configASSERT( pxQueue );
	configASSERT( !( ( pvItemToQueue == NULL ) && ( pxQueue->uxItemSize != ( UBaseType_t ) 0U ) ) );

	for(;;)
	{
		EnterCriticalSection();
		{
			/* Is there room on the queue now?  To be running we must be
			the highest priority task wanting to access the queue. */
			if( pxQueue->uxMessagesWaiting < pxQueue->uxLength )
			{
				traceQUEUE_SEND( pxQueue );
				prvCopyDataToQueue( pxQueue, pvItemToQueue, xCopyPosition );

				/* If there was a task waiting for data to arrive on the
				queue then unblock it now. */
				if( isEmpty ( pxQueue->xTasksWaitingToReceive ) == pdFALSE )
				{
					pid ProcessId = dequeue( pxQueue->xTasksWaitingToReceive );
					insert( ProcessId , readyList , proctab[ProcessId].prprio );
					proctab[ProcessId].prstate = PR_READY;
					queueYIELD_IF_USING_PREEMPTION();
				}
				else
				{
					mtCOVERAGE_TEST_MARKER();
				}
				ExitCriticalSection();
				return pdPASS;
			}
			else
			{
				if( delay == 0 )
				{
					ExitCriticalSection();
					return errQUEUE_FULL;
				}
				else
				{
					traceBLOCKING_ON_QUEUE_SEND( pxQueue );
					insert( Scheduler_processGetPid() , pxQueue->xTasksWaitingToSend , proctab[Scheduler_processGetPid()].prprio );
					// insert it also in the sleeping queue
					proctab[Scheduler_processGetPid()].prstate = PR_WAIT;
					queueYIELD_IF_USING_PREEMPTION();

					if ( prvIsQueueFull( pxQueue ) == pdTRUE )
					{
						ExitCriticalSection();
						return errQUEUE_FULL;
					}
					else
					{
						mtCOVERAGE_TEST_MARKER();
					}
				}
			}
		}
		ExitCriticalSection();
	}
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

*	\param xQueue			ID of the process to be inserted
*	\param xNewQueue				ID of queue to use
*
* \return pdFAIL if there's an error, pdPASS if there's no error
*
*****************************************************************************/
BaseType_t IPC_xQueueGenericReceive( QueueHandle_t xQueue, void * const pvBuffer, _delay_ms xSleepTime, const BaseType_t xJustPeeking )
{
	int8_t *pcOriginalReadPosition;
	Queue_t * const pxQueue = ( Queue_t * ) xQueue;

	configASSERT( pxQueue );
	configASSERT( !( ( pvBuffer == NULL ) && ( pxQueue->uxItemSize != ( UBaseType_t ) 0U ) ) );

	for( ;; )
	{
		EnterCriticalSection();
		{
			if( pxQueue->uxMessagesWaiting > ( UBaseType_t ) 0 )
			{
				/* Remember our read position in case we are just peeking. */
				pcOriginalReadPosition = pxQueue->pcReadFrom;

				prvCopyDataFromQueue( pxQueue, pvBuffer );

				if( xJustPeeking == pdFALSE )
				{
					traceQUEUE_RECEIVE( pxQueue );

					/* Data is actually being removed (not just peeked). */
					--( pxQueue->uxMessagesWaiting );

					// check for tasks waiting to send
					if( isEmpty( pxQueue -> xTasksWaitingToSend ) == pdFALSE )
					{
						pid ProcessId = dequeue( pxQueue->xTasksWaitingToSend );
						insert( ProcessId , readyList , proctab[ProcessId].prprio );
						proctab[ProcessId].prstate = PR_READY;
						queueYIELD_IF_USING_PREEMPTION();
					}
					else
					{
						mtCOVERAGE_TEST_MARKER();
					}
				}
				else
				{
					traceQUEUE_PEEK( pxQueue );
					/* The data is not being removed, so reset our read
						pointer. */
					pxQueue->pcReadFrom = pcOriginalReadPosition;

					/* The data is being left in the queue, so see if there are
					any other tasks waiting for the data. */
					// check for other tasks waiting to receive
					if( isEmpty ( pxQueue->xTasksWaitingToReceive ) == pdFALSE )
					{
						pid ProcessId = dequeue( pxQueue->xTasksWaitingToReceive );
						insert( ProcessId , readyList , proctab[ProcessId].prprio );
						proctab[ProcessId].prstate = PR_READY;
						queueYIELD_IF_USING_PREEMPTION();
					}
					else
					{
						mtCOVERAGE_TEST_MARKER();
					}
				}
				ExitCriticalSection();
				return pdPASS;
			}
			else
			{
				if( delay ==  0 )
				{
					ExitCriticalSection();
					traceQUEUE_RECEIVE_FAILED( pxQueue );
					return errQUEUE_EMPTY;
				}
				else
				{
					insert( Scheduler_processGetPid() , pxQueue->xTasksWaitingToReceive , proctab[Scheduler_processGetPid()].prprio );
					proctab[Scheduler_processGetPid()].prstate = PR_WAIT;
					queueYIELD_IF_USING_PREEMPTION();

					if ( prvIsQueueEmpty( pxQueue ) == pdTRUE )
					{
						ExitCriticalSection();
						return errQUEUE_EMPTY;
					}
					else
					{
						mtCOVERAGE_TEST_MARKER();
					}
				}
			}
		}
	ExitCriticalSection();
	}
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

*	\param xQueue			ID of the process to be inserted
*	\param xNewQueue				ID of queue to use
*
* \return pdFAIL if there's an error, pdPASS if there's no error
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

*	\param xQueue			ID of the process to be inserted
*	\param xNewQueue				ID of queue to use
*
* \return pdFAIL if there's an error, pdPASS if there's no error
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
} /*lint !e818 Pointer cannot be declared const as xQueue is a typedef not pointer. */

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

*	\param xQueue			ID of the process to be inserted
*	\param xNewQueue				ID of queue to use
*
* \return pdFAIL if there's an error, pdPASS if there's no error
*
*****************************************************************************/

UBaseType_t IPC_uxQueueMessagesWaitingFromISR( const QueueHandle_t xQueue )
{
UBaseType_t uxReturn;

	configASSERT( xQueue );

	uxReturn = ( ( Queue_t * ) xQueue )->uxMessagesWaiting;

	return uxReturn;
} /*lint !e818 Pointer cannot be declared const as xQueue is a typedef not pointer. */

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

*	\param xQueue			ID of the process to be inserted
*	\param xNewQueue				ID of queue to use
*
* \return pdFAIL if there's an error, pdPASS if there's no error
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

*	\param xQueue			ID of the process to be inserted
*	\param xNewQueue				ID of queue to use
*
* \return pdFAIL if there's an error, pdPASS if there's no error
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
} /*lint !e818 xQueue could not be pointer to const because it is a typedef. */

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

*	\param xQueue			ID of the process to be inserted
*	\param xNewQueue				ID of queue to use
*
* \return pdFAIL if there's an error, pdPASS if there's no error
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

*	\param xQueue			ID of the process to be inserted
*	\param xNewQueue				ID of queue to use
*
* \return pdFAIL if there's an error, pdPASS if there's no error
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

*	\param xQueue			ID of the process to be inserted
*	\param xNewQueue				ID of queue to use
*
* \return pdFAIL if there's an error, pdPASS if there's no error
*
*****************************************************************************/

void IPC_vQueueDelete( QueueHandle_t xQueue )
{
	//Queue_t * const pxQueue = ( Queue_t * ) xQueue;

	//configASSERT( pxQueue );

	//traceQUEUE_DELETE( pxQueue );

	/// LOOK HERE ///
	// free the part of the pxQueue

	// vPortFree( pxQueue );
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

*	\param xQueue			ID of the process to be inserted
*	\param xNewQueue				ID of queue to use
*
* \return pdFAIL if there's an error, pdPASS if there's no error
*
*****************************************************************************/

static BaseType_t prvCopyDataToQueue( Queue_t * const pxQueue, const void *pvItemToQueue, const BaseType_t xPosition )
{
BaseType_t xReturn = pdFALSE;

	if( xPosition == queueSEND_TO_BACK )
	{
		( void ) memcpy( ( void * ) pxQueue->pcWriteTo, pvItemToQueue, ( size_t ) pxQueue->uxItemSize ); /*lint !e961 !e418 MISRA exception as the casts are only redundant for some ports, plus previous logic ensures a null pointer can only be passed to memcpy() if the copy size is 0. */
		pxQueue->pcWriteTo += pxQueue->uxItemSize;
		if( pxQueue->pcWriteTo >= pxQueue->pcTail ) /*lint !e946 MISRA exception justified as comparison of pointers is the cleanest solution. */
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
		( void ) memcpy( ( void * ) pxQueue->pcReadFrom, pvItemToQueue, ( size_t ) pxQueue->uxItemSize ); /*lint !e961 MISRA exception as the casts are only redundant for some ports. */
		pxQueue->pcReadFrom -= pxQueue->uxItemSize;
		if( pxQueue->pcReadFrom < pxQueue->pcHead ) /*lint !e946 MISRA exception justified as comparison of pointers is the cleanest solution. */
		{
			pxQueue->pcReadFrom = ( pxQueue->pcTail - pxQueue->uxItemSize );
		}
		else
		{
			mtCOVERAGE_TEST_MARKER();
		}

		if( xPosition == queueOVERWRITE )
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

*	\param xQueue			ID of the process to be inserted
*	\param xNewQueue				ID of queue to use
*
* \return pdFAIL if there's an error, pdPASS if there's no error
*
*****************************************************************************/

static void prvCopyDataFromQueue( Queue_t * const pxQueue, void * const pvBuffer )
{

	pxQueue->pcReadFrom += pxQueue->uxItemSize;
	if( pxQueue->pcReadFrom >= pxQueue->pcTail ) /*lint !e946 MISRA exception justified as use of the relational operator is the cleanest solutions. */
	{
		pxQueue->pcReadFrom = pxQueue->pcHead;
	}
	else
	{
		mtCOVERAGE_TEST_MARKER();
	}
	( void ) memcpy( ( void * ) pvBuffer, ( void * ) pxQueue->pcReadFrom, ( size_t ) pxQueue->uxItemSize ); /*lint !e961 !e418 MISRA exception as the casts are only redundant for some ports.  Also previous logic ensures a null pointer can only be passed to memcpy() when the count is 0. */

}


