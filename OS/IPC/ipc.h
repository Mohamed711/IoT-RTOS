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

#ifndef IPC_H_
#define IPC_H_

#ifndef RTOS_H_
	#error "include RTOS.h" must appear in source files before "include ipc.h"
#endif


#ifdef __cplusplus
extern "C" {
#endif


/*
 * Type by which queues are referenced.  For example, a call to xQueueCreate()
 * returns an QueueHandle_t variable that can then be used as a parameter to
 * xQueueSend(), xQueueReceive(), etc.
 */
typedef void * QueueHandle_t;

/* For internal use only. */
#define	queueSEND_TO_BACK		( ( BaseType_t ) 0 )
#define	queueSEND_TO_FRONT		( ( BaseType_t ) 1 )
#define queueOVERWRITE			( ( BaseType_t ) 2 )


/* create a queue */
#define IPC_xQueueCreate( uxQueueLength, uxItemSize ) IPC_xQueueGenericCreate( uxQueueLength, uxItemSize )
QueueHandle_t IPC_xQueueGenericCreate( const UBaseType_t uxQueueLength, const UBaseType_t uxItemSize );


#define IPC_xQueueSendToFront( xQueue, pvItemToQueue, xTicksToWait ) IPC_xQueueGenericSend( ( xQueue ), ( pvItemToQueue ), ( xTicksToWait ), queueSEND_TO_FRONT )
#define IPC_xQueueSendToBack( xQueue, pvItemToQueue, xTicksToWait ) IPC_xQueueGenericSend( ( xQueue ), ( pvItemToQueue ), ( xTicksToWait ), queueSEND_TO_BACK )
#define IPC_xQueueSend( xQueue, pvItemToQueue, xTicksToWait ) IPC_xQueueGenericSend( ( xQueue ), ( pvItemToQueue ), ( xTicksToWait ), queueSEND_TO_BACK )
#define IPC_xQueueOverwrite( xQueue, pvItemToQueue ) IPC_xQueueGenericSend( ( xQueue ), ( pvItemToQueue ), 0, queueOVERWRITE )


BaseType_t IPC_xQueueGenericSend( QueueHandle_t xQueue, const void * const pvItemToQueue, int32_t delay, const BaseType_t xCopyPosition ) ;
#define IPC_xQueuePeek( xQueue, pvBuffer, xTicksToWait ) IPC_xQueueGenericReceive( ( xQueue ), ( pvBuffer ), ( xTicksToWait ), pdTRUE )
BaseType_t IPC_xQueuePeekFromISR( QueueHandle_t xQueue, void * const pvBuffer ) PRIVILEGED_FUNCTION;
#define IPC_xQueueReceive( xQueue, pvBuffer, xTicksToWait ) IPC_xQueueGenericReceive( ( xQueue ), ( pvBuffer ), ( xTicksToWait ), pdFALSE )
BaseType_t IPC_xQueueGenericReceive( QueueHandle_t xQueue, void * const pvBuffer, int32_t delay, const BaseType_t xJustPeek ) ;
UBaseType_t IPC_uxQueueMessagesWaiting( const QueueHandle_t xQueue );
UBaseType_t IPC_uxQueueSpacesAvailable( const QueueHandle_t xQueue );
void IPC_vQueueDelete( QueueHandle_t xQueue ) PRIVILEGED_FUNCTION;
#define IPC_xQueueSendToFrontFromISR( xQueue, pvItemToQueue, pxHigherPriorityTaskWoken ) IPC_xQueueGenericSendFromISR( ( xQueue ), ( pvItemToQueue ), ( pxHigherPriorityTaskWoken ), queueSEND_TO_FRONT )
#define IPC_xQueueSendToBackFromISR( xQueue, pvItemToQueue, pxHigherPriorityTaskWoken ) IPC_xQueueGenericSendFromISR( ( xQueue ), ( pvItemToQueue ), ( pxHigherPriorityTaskWoken ), queueSEND_TO_BACK )
#define IPC_xQueueOverwriteFromISR( xQueue, pvItemToQueue, pxHigherPriorityTaskWoken ) IPC_xQueueGenericSendFromISR( ( xQueue ), ( pvItemToQueue ), ( pxHigherPriorityTaskWoken ), queueOVERWRITE )
#define IPC_xQueueSendFromISR( xQueue, pvItemToQueue, pxHigherPriorityTaskWoken ) IPC_xQueueGenericSendFromISR( ( xQueue ), ( pvItemToQueue ), ( pxHigherPriorityTaskWoken ), queueSEND_TO_BACK )
BaseType_t IPC_xQueueGenericSendFromISR( QueueHandle_t xQueue, const void * const pvItemToQueue, BaseType_t * const pxHigherPriorityTaskWoken, const BaseType_t xCopyPosition );
BaseType_t IPC_xQueueReceiveFromISR( QueueHandle_t xQueue, void * const pvBuffer, BaseType_t * const pxHigherPriorityTaskWoken );

/*
 * Utilities to query queues that are safe to use from an ISR.  These utilities
 * should be used only from witin an ISR, or within a critical section.
 */
BaseType_t IPC_xQueueIsQueueEmptyFromISR( const QueueHandle_t xQueue );
BaseType_t IPC_xQueueIsQueueFullFromISR( const QueueHandle_t xQueue );
UBaseType_t IPC_uxQueueMessagesWaitingFromISR( const QueueHandle_t xQueue );

/*
 * Reset a queue back to its original empty state.  The return value is now
 * obsolete and is always set to pdPASS.
 */
#define IPC_xQueueReset( xQueue ) IPC_xQueueGenericReset( xQueue, pdFALSE )


/* Not public API functions. */
BaseType_t IPC_xQueueGenericReset( QueueHandle_t xQueue, BaseType_t xNewQueue ) PRIVILEGED_FUNCTION;


#ifdef __cplusplus
}
#endif


#endif /* IPC_H_ */


