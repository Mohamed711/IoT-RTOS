/******************************************************************************
 *	OurOS V 0.0.0 - Copyright (C) 2016 
 *  Computer and systems department
 *  Ain Shams University
 *  
 *  All rights reserved
 *
 *  VISIT http://www.OurRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 * 
 *  Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 * 
 *  Redistributions in binary form must reproduce the above copyright
 *  notice, this list of conditions and the following disclaimer in the
 *  documentation and/or other materials provided with the  
 *  distribution.
 *****************************************************************************/

#include <stdint.h>
#include <stdlib.h>

// include of the task header file which can be used to transfer the task between modules
#include "ipc_cfg.h"
#include "ipc.h"

/* Constants used with the xRxLock and xTxLock structure members. */
#define queueUNLOCKED					( ( BaseType_t ) -1 )
#define queueLOCKED_UNMODIFIED			( ( BaseType_t ) 0 )

#if( configUSE_PREEMPTION == 0 )
	/* If the cooperative scheduler is being used then a yield should not be
	performed just because a higher priority task has been woken. */
	#define queueYIELD_IF_USING_PREEMPTION()
#else
	#define queueYIELD_IF_USING_PREEMPTION() portYIELD_WITHIN_API()
#endif



/*
 * Definition of the queue used by the scheduler.
 * Items are queued by copy, not reference.
 */
typedef struct QueueDefinition
{
	int8_t *pcHead;					/*< Points to the beginning of the queue storage area. */
	int8_t *pcTail;					/*< Points to the byte at the end of the queue storage area.  Once more byte is allocated than necessary to store the queue items, this is used as a marker. */
	int8_t *pcWriteTo;				/*< Points to the free next place in the storage area. */
	int8_t *pcReadFrom;			/*< Points to the last place that a queued item was read from when the structure is used as a queue. */


// Two lists of processes one for the tasks waiting to send and other waiting to receive
/// LOOK HERE ///
	uint32_t xTasksWaitingToSend[5];
	uint32_t xTasksWaitingToReceive[5];
//	List_t xTasksWaitingToSend;		/*< List of tasks that are blocked waiting to post onto this queue.  Stored in priority order. */
//	List_t xTasksWaitingToReceive;	/*< List of tasks that are blocked waiting to read from this queue.  Stored in priority order. */

	volatile UBaseType_t uxMessagesWaiting;/*< The number of items currently in the queue. */
	UBaseType_t uxLength;			/*< The length of the queue defined as the number of items it will hold, not the number of bytes. */
	UBaseType_t uxItemSize;			/*< The size of each items that the queue will hold. */

#if (configUSE_QUEUE_LOCKS == 1)
	volatile BaseType_t xRxLock;	/*< Stores the number of items received from the queue (removed from the queue) while the queue was locked.  Set to queueUNLOCKED when the queue is not locked. */
	volatile BaseType_t xTxLock;	/*< Stores the number of items transmitted to the queue (added to the queue) while the queue was locked.  Set to queueUNLOCKED when the queue is not locked. */
#endif

} Queue_t;


/*-----------------------------------------------------------*/

/*
 * Unlocks a queue locked by a call to prvLockQueue.  Locking a queue does not
 * prevent an ISR from adding or removing items to the queue, but does prevent
 * an ISR from removing tasks from the queue event lists.  If an ISR finds a
 * queue is locked it will instead increment the appropriate queue lock count
 * to indicate that a task may require unblocking.  When the queue in unlocked
 * these lock counts are inspected, and the appropriate action taken.
 */
static void prvUnlockQueue( Queue_t * const pxQueue );

/*
 * Uses a critical section to determine if there is any data in a queue.
 *
 * @return pdTRUE if the queue contains no items, otherwise pdFALSE.
 */
static BaseType_t prvIsQueueEmpty( const Queue_t *pxQueue );

/*
 * Uses a critical section to determine if there is any space in a queue.
 *
 * @return pdTRUE if there is no space, otherwise pdFALSE;
 */
static BaseType_t prvIsQueueFull( const Queue_t *pxQueue );

/*
 * Copies an item into the queue, either at the front of the queue or the
 * back of the queue.
 */
static BaseType_t prvCopyDataToQueue( Queue_t * const pxQueue, const void *pvItemToQueue, const BaseType_t xPosition );

/*
 * Copies an item out of a queue.
 */
static void prvCopyDataFromQueue( Queue_t * const pxQueue, void * const pvBuffer );


/*-----------------------------------------------------------*/

/*
 * Macro to mark a queue as locked.  Locking a queue prevents an ISR from
 * accessing the queue event lists.
 */
#define prvLockQueue( pxQueue )								\
	taskENTER_CRITICAL();									\
	{														\
		if( ( pxQueue )->xRxLock == queueUNLOCKED )			\
		{													\
			( pxQueue )->xRxLock = queueLOCKED_UNMODIFIED;	\
		}													\
		if( ( pxQueue )->xTxLock == queueUNLOCKED )			\
		{													\
			( pxQueue )->xTxLock = queueLOCKED_UNMODIFIED;	\
		}													\
	}														\
	taskEXIT_CRITICAL()
/*-----------------------------------------------------------*/

BaseType_t xQueueGenericReset( QueueHandle_t xQueue, BaseType_t xNewQueue )
{
Queue_t * const pxQueue = ( Queue_t * ) xQueue;

	configASSERT( pxQueue );

	taskENTER_CRITICAL();
	{
		pxQueue->pcTail = pxQueue->pcHead + ( pxQueue->uxLength * pxQueue->uxItemSize );
		pxQueue->uxMessagesWaiting = ( UBaseType_t ) 0U;
		pxQueue->pcWriteTo = pxQueue->pcHead;
		pxQueue->pcReadFrom = pxQueue->pcHead + ( ( pxQueue->uxLength - ( UBaseType_t ) 1U ) * pxQueue->uxItemSize );

#if (configUSE_QUEUE_LOCKS == 1)
		pxQueue->xRxLock = queueUNLOCKED;
		pxQueue->xTxLock = queueUNLOCKED;
#endif

		if( xNewQueue == pdFALSE )
		{
			/* If there are tasks blocked waiting to read from the queue, then
			the tasks will remain blocked as after this function exits the queue
			will still be empty.  If there are tasks blocked waiting to write to
			the queue, then one should be unblocked as after this function exits
			it will be possible to write to it. */

			// check for the list of waiting to send tasks is empty
			// check list is empty
			/// LOOK HERE ///
			// check if the sending state is empty
			if( /* listLIST_IS_EMPTY( &(  pxQueue->xTasksWaitingToSend  ) ) */ pdTRUE == pdFALSE )
			{
				// remove a process from waiting to send on the queue as you reset the queue so its empty
				if( /* xTaskRemoveFromEventList( &( pxQueue->xTasksWaitingToSend  ) ) */ pdTRUE == pdTRUE )
				{
					// check in case of preemption if it has high priority
					queueYIELD_IF_USING_PREEMPTION();
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
		else
		{
			/* Ensure the event queues start in the correct state. */
			// make two lists for tasks, one waiting to send and the other is waiting to receive
			//	vListInitialise( &( pxQueue->xTasksWaitingToSend ) );
			//	vListInitialise( &( pxQueue->xTasksWaitingToReceive ) );
			/// LOOK HERE ///
			// create two queues by newqueue which return the number
			// save the address or the number of queues in the datastructure itself
		}
	}
	taskEXIT_CRITICAL();

	/* A value is returned for calling semantic consistency with previous
	versions. */
	return pdPASS;
}
/*-----------------------------------------------------------*/

QueueHandle_t xQueueGenericCreate( const UBaseType_t uxQueueLength, const UBaseType_t uxItemSize )
{
Queue_t *pxNewQueue;
size_t xQueueSizeInBytes;
QueueHandle_t xReturn = NULL;

	configASSERT( ( uxQueueLength > ( UBaseType_t ) 0 ) && ( uxItemSize > ( UBaseType_t ) 0 ) );


	/* The queue is one byte longer than asked for to make wrap checking
	easier/faster. */
	xQueueSizeInBytes = ( size_t ) ( uxQueueLength * uxItemSize ) + ( size_t ) 1; /*lint !e961 MISRA exception as the casts are only redundant for some ports. */


	/* Allocate the new queue structure and storage area. */
	// reserve the amount in memory for the queue
	/// LOOK HERE ///
	pxNewQueue = (Queue_t * ) malloc( sizeof ( Queue_t ) + xQueueSizeInBytes );
	//	pxNewQueue = ( Queue_t * ) pvPortMalloc( sizeof( Queue_t ) + xQueueSizeInBytes );

	if( pxNewQueue != NULL )
	{

		/* Jump past the queue structure to find the location of the queue
		storage area. */
		pxNewQueue->pcHead = ( ( int8_t * ) pxNewQueue ) + sizeof( Queue_t );


		/* Initialise the queue members as described above where the queue type
		is defined. */
		pxNewQueue->uxLength = uxQueueLength;
		pxNewQueue->uxItemSize = uxItemSize;
		( void ) xQueueGenericReset( pxNewQueue, pdTRUE );

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
/*-----------------------------------------------------------*/

BaseType_t xQueueGenericSend( QueueHandle_t xQueue, const void * const pvItemToQueue, TickType_t xTicksToWait, const BaseType_t xCopyPosition )
{
	BaseType_t xEntryTimeSet = pdFALSE;
	TimeOut_t xTimeOut;
	Queue_t * const pxQueue = ( Queue_t * ) xQueue;

			configASSERT( pxQueue );
			configASSERT( !( ( pvItemToQueue == NULL ) && ( pxQueue->uxItemSize != ( UBaseType_t ) 0U ) ) );

			for( ;; )
			{
				taskENTER_CRITICAL();
				{
					/* Is there room on the queue now?  To be running we must be
					the highest priority task wanting to access the queue. */
					if( pxQueue->uxMessagesWaiting < pxQueue->uxLength )
					{
						// trace queue have to search about this sentence
						// traceQUEUE_SEND( pxQueue );
						prvCopyDataToQueue( pxQueue, pvItemToQueue, xCopyPosition );

						/* If there was a task waiting for data to arrive on the
						queue then unblock it now. */
						// look for waiting tasks to receive
						if( /* listLIST_IS_EMPTY( &( pxQueue->xTasksWaitingToReceive ) ) */ pdTRUE == pdFALSE )
						{
							// wake up a task
							if( /* xTaskRemoveFromEventList( &( pxQueue->xTasksWaitingToReceive ) )*/ pdFALSE == pdTRUE )
							{
								/* The unblocked task has a priority higher than
								our own so yield immediately. */
								portYIELD_WITHIN_API();
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

						taskEXIT_CRITICAL();
						return pdPASS;
					}
					else
					{
						if( xTicksToWait == ( TickType_t ) 0 )
						{
							taskEXIT_CRITICAL();
							return errQUEUE_FULL;
						}
						else if( xEntryTimeSet == pdFALSE )
						{
							// initialize the time variable with the required value
							// vTaskSetTimeOutState( &xTimeOut );
							xEntryTimeSet = pdTRUE;
						}
					}
				}
				taskEXIT_CRITICAL();

				taskENTER_CRITICAL();
				{
					if( /* xTaskCheckForTimeOut( &xTimeOut, &xTicksToWait ) */ pdTRUE == pdFALSE )
					{
						if( prvIsQueueFull( pxQueue ) != pdFALSE )
						{
							// traceQueue sentence
							//traceBLOCKING_ON_QUEUE_SEND( pxQueue );
							// add the task to the waiting to send with a specific time
							// vTaskPlaceOnEventList( &( pxQueue->xTasksWaitingToSend ), xTicksToWait );
							portYIELD_WITHIN_API();
						}
						else
						{
							mtCOVERAGE_TEST_MARKER();
						}
					}
					else
					{
						taskEXIT_CRITICAL();
						// traceQUEUE_SEND_FAILED( pxQueue );
						return errQUEUE_FULL;
					}
				}
				taskEXIT_CRITICAL();
			}
}

/*-----------------------------------------------------------*/

BaseType_t xQueueGenericReceive( QueueHandle_t xQueue, void * const pvBuffer, TickType_t xTicksToWait, const BaseType_t xJustPeeking )
{
	BaseType_t xEntryTimeSet = pdFALSE;
		TimeOut_t xTimeOut;
		int8_t *pcOriginalReadPosition;
		Queue_t * const pxQueue = ( Queue_t * ) xQueue;

			configASSERT( pxQueue );
			configASSERT( !( ( pvBuffer == NULL ) && ( pxQueue->uxItemSize != ( UBaseType_t ) 0U ) ) );

			for( ;; )
			{
				taskENTER_CRITICAL();
				{
					if( pxQueue->uxMessagesWaiting > ( UBaseType_t ) 0 )
					{
						/* Remember our read position in case we are just peeking. */
						pcOriginalReadPosition = pxQueue->pcReadFrom;

						prvCopyDataFromQueue( pxQueue, pvBuffer );

						if( xJustPeeking == pdFALSE )
						{
							// the trace of the queue
							//traceQUEUE_RECEIVE( pxQueue );

							/* Data is actually being removed (not just peeked). */
							--( pxQueue->uxMessagesWaiting );

							// check for tasks waiting to send
							if(/* listLIST_IS_EMPTY( &( pxQueue->xTasksWaitingToSend ) ) */ pdTRUE == pdFALSE )
							{
								// remove a task from the waiting to send list
								if( /* xTaskRemoveFromEventList( &( pxQueue->xTasksWaitingToSend ) ) */ pdFALSE == pdTRUE )
								{
									portYIELD_WITHIN_API();
								}
								else
								{
									mtCOVERAGE_TEST_MARKER();
								}
							}
						}
						else
						{
							// trace sentence
							//traceQUEUE_PEEK( pxQueue );

							/* The data is not being removed, so reset our read
							pointer. */
							pxQueue->pcReadFrom = pcOriginalReadPosition;

							/* The data is being left in the queue, so see if there are
							any other tasks waiting for the data. */
							// check for other tasks waiting to receive
							if( /* listLIST_IS_EMPTY( &( pxQueue->xTasksWaitingToReceive ) ) */ pdTRUE == pdFALSE )
							{
								/* Tasks that are removed from the event list will get added to
								the pending ready list as the scheduler is still suspended. */
								// get the task that is waiting to receive
								if( /* xTaskRemoveFromEventList( &( pxQueue->xTasksWaitingToReceive ) )*/  pdTRUE != pdFALSE )
								{
									/* The task waiting has a higher priority than this task. */
									portYIELD_WITHIN_API();
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

						taskEXIT_CRITICAL();
						return pdPASS;
					}
					else
					{
						if( xTicksToWait == ( TickType_t ) 0 )
						{
							taskEXIT_CRITICAL();
							// trace Queue
							// traceQUEUE_RECEIVE_FAILED( pxQueue );
							return errQUEUE_EMPTY;
						}
						else if( xEntryTimeSet == pdFALSE )
						{
							// config the timeout
							//vTaskSetTimeOutState( &xTimeOut );
							xEntryTimeSet = pdTRUE;
						}
					}
				}
				taskEXIT_CRITICAL();

				taskENTER_CRITICAL();
				{
					// compare if the timeout has passed
					if( /* xTaskCheckForTimeOut( &xTimeOut, &xTicksToWait )*/ pdTRUE == pdFALSE )
					{
						if( prvIsQueueEmpty( pxQueue ) != pdFALSE )
						{
							// trace sentence
							//traceBLOCKING_ON_QUEUE_RECEIVE( pxQueue );
							// add a task to the list of waiting to receive
							// vTaskPlaceOnEventList( &( pxQueue->xTasksWaitingToReceive ), xTicksToWait );
							portYIELD_WITHIN_API();
						}
						else
						{
							mtCOVERAGE_TEST_MARKER();
						}
					}
					else
					{
						taskEXIT_CRITICAL();
						// trace Queue
						// traceQUEUE_RECEIVE_FAILED( pxQueue );
						return errQUEUE_EMPTY;
					}
				}
				taskEXIT_CRITICAL();
			}
}

/*-----------------------------------------------------------*/

UBaseType_t uxQueueMessagesWaiting( const QueueHandle_t xQueue )
{
UBaseType_t uxReturn;

	configASSERT( xQueue );

	taskENTER_CRITICAL();
	{
		uxReturn = ( ( Queue_t * ) xQueue )->uxMessagesWaiting;
	}
	taskEXIT_CRITICAL();

	return uxReturn;
} /*lint !e818 Pointer cannot be declared const as xQueue is a typedef not pointer. */
/*-----------------------------------------------------------*/

UBaseType_t uxQueueSpacesAvailable( const QueueHandle_t xQueue )
{
UBaseType_t uxReturn;
Queue_t *pxQueue;

	pxQueue = ( Queue_t * ) xQueue;
	configASSERT( pxQueue );

	taskENTER_CRITICAL();
	{
		uxReturn = pxQueue->uxLength - pxQueue->uxMessagesWaiting;
	}
	taskEXIT_CRITICAL();

	return uxReturn;
} /*lint !e818 Pointer cannot be declared const as xQueue is a typedef not pointer. */
/*-----------------------------------------------------------*/

UBaseType_t uxQueueMessagesWaitingFromISR( const QueueHandle_t xQueue )
{
UBaseType_t uxReturn;

	configASSERT( xQueue );

	uxReturn = ( ( Queue_t * ) xQueue )->uxMessagesWaiting;

	return uxReturn;
} /*lint !e818 Pointer cannot be declared const as xQueue is a typedef not pointer. */
/*-----------------------------------------------------------*/


static BaseType_t prvIsQueueEmpty( const Queue_t *pxQueue )
{
BaseType_t xReturn;

	taskENTER_CRITICAL();
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
	taskEXIT_CRITICAL();

	return xReturn;
}
/*-----------------------------------------------------------*/

BaseType_t xQueueIsQueueEmptyFromISR( const QueueHandle_t xQueue )
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
/*-----------------------------------------------------------*/

static BaseType_t prvIsQueueFull( const Queue_t *pxQueue )
{
BaseType_t xReturn;

	taskENTER_CRITICAL();
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
	taskEXIT_CRITICAL();

	return xReturn;
}
/*-----------------------------------------------------------*/

BaseType_t xQueueIsQueueFullFromISR( const QueueHandle_t xQueue )
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
} /*lint !e818 xQueue could not be pointer to const because it is a typedef. */
/*-----------------------------------------------------------*/

void vQueueDelete( QueueHandle_t xQueue )
{
Queue_t * const pxQueue = ( Queue_t * ) xQueue;

	configASSERT( pxQueue );

	// what is trace queue delete ?
	// where are these tracings ?
	// traceQUEUE_DELETE( pxQueue );
	// free the part of the pxQueue
	// vPortFree( pxQueue );
}

/*-----------------------------------------------------------*/

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
/*-----------------------------------------------------------*/

static void prvCopyDataFromQueue( Queue_t * const pxQueue, void * const pvBuffer )
{
	if( pxQueue->uxItemSize != ( UBaseType_t ) 0 )
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
}
/*-----------------------------------------------------------*/


static void prvUnlockQueue( Queue_t * const pxQueue )
{
	/* THIS FUNCTION MUST BE CALLED WITH THE SCHEDULER SUSPENDED. */

	/* The lock counts contains the number of extra data items placed or
	removed from the queue while the queue was locked.  When a queue is
	locked items can be added or removed, but the event lists cannot be
	updated. */
	taskENTER_CRITICAL();
	{
		/* See if data was added to the queue while it was locked. */
		while( pxQueue->xTxLock > queueLOCKED_UNMODIFIED )
		{
			/* Data was posted while the queue was locked.  Are any tasks
			blocked waiting for data to become available? */
			{
				/* Tasks that are removed from the event list will get added to
				the pending ready list as the scheduler is still suspended. */

				// check the list of tasks waiting to receive on the queue
				if( /* listLIST_IS_EMPTY( &( pxQueue->xTasksWaitingToReceive ) ) */ pdTRUE == pdFALSE )
				{
					// remove task from waiting list to receive
					if( /* xTaskRemoveFromEventList( &( pxQueue->xTasksWaitingToReceive ) )*/ pdTRUE != pdFALSE )
					{
						/* The task waiting has a higher priority so record that a
						context	switch is required. */
						// make the higher priority task to run
						// vTaskMissedYield();
					}
					else
					{
						mtCOVERAGE_TEST_MARKER();
					}
				}
				else
				{
					break;
				}
			}
			--( pxQueue->xTxLock );
		}

		pxQueue->xTxLock = queueUNLOCKED;
	}
	taskEXIT_CRITICAL();

	/* Do the same for the Rx lock. */
	taskENTER_CRITICAL();
	{
		while( pxQueue->xRxLock > queueLOCKED_UNMODIFIED )
		{
			// check the tasks on the waiting list to send
			if(/* listLIST_IS_EMPTY( &( pxQueue->xTasksWaitingToSend ) ) */ pdTRUE == pdFALSE )
			{
				if(/* xTaskRemoveFromEventList( &( pxQueue->xTasksWaitingToSend ) ) */ pdTRUE != pdFALSE )
				{
					// invoke the highest priority task to run
					// vTaskMissedYield();
				}
				else
				{
					mtCOVERAGE_TEST_MARKER();
				}

				--( pxQueue->xRxLock );
			}
			else
			{
				break;
			}
		}

		pxQueue->xRxLock = queueUNLOCKED;
	}
	taskEXIT_CRITICAL();
}
/*-----------------------------------------------------------*/

