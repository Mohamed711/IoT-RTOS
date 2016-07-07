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

/****************************************************************************
*
*	Type by which queues are referenced.
* It's used as a parameter to other functions IPC_xQueueSendToFront(), etc
*
*****************************************************************************/
typedef void * QueueHandle_t;

/* For external use by other modules */
#define IPC_NO_SLEEP									( ( _delay_ms ) ( 0x00000000 ) )
#define IPC_WAIT_FOREVER							( ( _delay_ms ) ( 0xFFFFFFFF ) )

/* For internal use only. */
#define	IPC_queueSEND_TO_BACK					( ( BaseType_t ) 0 )
#define	IPC_queueSEND_TO_FRONT				( ( BaseType_t ) 1 )
#define IPC_queueOVERWRITE						( ( BaseType_t ) 2 )
	
#define IPC_RECEIVE_WITH_CONSUMING		( ( BaseType_t ) 0 )
#define IPC_RECEIVE_WITHOUT_CONSUMING	( ( BaseType_t ) 1 )
	
#define IPC_RESET_EXISTING_QUEUE			( ( BaseType_t ) 0 )
#define IPC_RESET_NEW_QUEUE						( ( BaseType_t ) 1 )


/* create a queue */
#define IPC_xQueueCreate( uxQueueLength, uxItemSize ) \
				IPC_xQueueGenericCreate( ( uxQueueLength ), ( uxItemSize ) )


/* send to a queue */
#define IPC_xQueueSendToFront( xQueue, pvItemToQueue, xSleepTime ) \
				IPC_xQueueGenericSend( ( xQueue ), ( pvItemToQueue ), ( xSleepTime ), IPC_queueSEND_TO_FRONT )
				
#define IPC_xQueueSendToBack( xQueue, pvItemToQueue, xSleepTime ) 	\
				IPC_xQueueGenericSend( ( xQueue ), ( pvItemToQueue ), ( xSleepTime ), IPC_queueSEND_TO_BACK )
				
#define IPC_xQueueOverwrite( xQueue, pvItemToQueue ) 	\
				IPC_xQueueGenericSend( ( xQueue ), ( pvItemToQueue ), IPC_NO_SLEEP, IPC_queueOVERWRITE )
				
#define IPC_xQueueSendToFrontFromISR( xQueue, pvItemToQueue, pxHigherPriorityTaskWoken ) \
				IPC_xQueueGenericSendFromISR( ( xQueue ), ( pvItemToQueue ), ( pxHigherPriorityTaskWoken ), IPC_queueSEND_TO_FRONT )
				
#define IPC_xQueueSendToBackFromISR( xQueue, pvItemToQueue, pxHigherPriorityTaskWoken ) \
				IPC_xQueueGenericSendFromISR( ( xQueue ), ( pvItemToQueue ), ( pxHigherPriorityTaskWoken ), IPC_queueSEND_TO_BACK )
				
#define IPC_xQueueOverwriteFromISR( xQueue, pvItemToQueue, pxHigherPriorityTaskWoken ) \
				IPC_xQueueGenericSendFromISR( ( xQueue ), ( pvItemToQueue ), ( pxHigherPriorityTaskWoken ), IPC_queueOVERWRITE )
				

/* receive from a queue */
#define IPC_xQueuePeek( xQueue, pvBuffer, xSleepTime ) \
				IPC_xQueueGenericReceive( ( xQueue ), ( pvBuffer ), ( xSleepTime ), IPC_RECEIVE_WITHOUT_CONSUMING )
				
#define IPC_xQueueReceive( xQueue, pvBuffer, xSleepTime ) \
				IPC_xQueueGenericReceive( ( xQueue ), ( pvBuffer ), ( xSleepTime ), IPC_RECEIVE_WITH_CONSUMING )
				
#define IPC_xQueueReset( xQueue ) \
				IPC_xQueueGenericReset( xQueue, IPC_RESET_EXISTING_QUEUE )


/* create a queue */
QueueHandle_t IPC_xQueueGenericCreate( const UBaseType_t uxQueueLength, const UBaseType_t uxItemSize );


/* reset a queue */
BaseType_t IPC_xQueueGenericReset(  QueueHandle_t xQueue, BaseType_t xNewQueue );


/* send to a queue */
BaseType_t IPC_xQueueGenericSend( QueueHandle_t xQueue, const void * const pvItemToQueue, _delay_ms xSleepTime, const BaseType_t xCopyPosition );
//BaseType_t IPC_xQueueGenericSendFromISR( QueueHandle_t xQueue, const void * const pvItemToQueue, BaseType_t * const pxHigherPriorityTaskWoken, const BaseType_t xCopyPosition );


/* receive from a queue */
BaseType_t IPC_xQueueGenericReceive( QueueHandle_t xQueue, void * const pvBuffer, _delay_ms xSleepTime, const BaseType_t xJustPeek );
//BaseType_t IPC_xQueueReceiveFromISR( QueueHandle_t xQueue, void * const pvBuffer, BaseType_t * const pxHigherPriorityTaskWoken );
//BaseType_t IPC_xQueuePeekFromISR( QueueHandle_t xQueue, void * const pvBuffer );


/* queue utilities */
UBaseType_t IPC_uxQueueMessagesWaiting( const QueueHandle_t xQueue );
UBaseType_t IPC_uxQueueSpacesAvailable( const QueueHandle_t xQueue );
void IPC_vQueueDelete( QueueHandle_t xQueue );
BaseType_t IPC_xQueueIsQueueEmptyFromISR( const QueueHandle_t xQueue );
BaseType_t IPC_xQueueIsQueueFullFromISR( const QueueHandle_t xQueue );
//UBaseType_t IPC_uxQueueMessagesWaitingFromISR( const QueueHandle_t xQueue );


#ifdef __cplusplus
}
#endif


#endif /* IPC_H_ */
