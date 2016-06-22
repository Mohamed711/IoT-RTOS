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

#define IPC_CFG_H

/* the basetype must be defined some where */
typedef int8_t BaseType_t ;		// signed basetype is the base datatype
typedef uint8_t TickType_t ;	// ticktype is a structure for the tick
typedef uint8_t UBaseType_t ; 	// unsigned basetype is important datatype used
typedef uint8_t TimeOut_t;  	// do not know want to know more about it

#define configASSERT(x)			// configAssert check the condition x is true or return the file and line number
#define taskENTER_CRITICAL()	// enable critical section
#define taskEXIT_CRITICAL()		// disable critical section
#define pdTRUE	0x01			// true return
#define pdFALSE	0x00			// false return
#define pdPASS	0x01			// return value that the function carried out correctly
#define pdFAIL 	0x00			// return fail
#define mtCOVERAGE_TEST_MARKER()// just an empty for the else part of the if statement
#define PRIVILEGED_FUNCTION		// to the memory protection unit
#define configUSE_PREEMPTION 0	// config the scheduler to be preemptive or cooperative
#define portYIELD_WITHIN_API()	// check for the tasks to take the higher priority one
#define errQUEUE_FULL	0x00	// error value indicates that the queue is full
#define errQUEUE_EMPTY 	0x00	// error the queue is empty
#define configUSE_QUEUE_LOCKS 1	// configure the locks

#ifndef traceQUEUE_CREATE
	#define traceQUEUE_CREATE( pxNewQueue )
#endif

#ifndef traceQUEUE_CREATE_FAILED
	#define traceQUEUE_CREATE_FAILED( ucQueueType )
#endif

#ifndef traceQUEUE_SEND
	#define traceQUEUE_SEND( pxQueue )
#endif

#ifndef traceQUEUE_SEND_FAILED
	#define traceQUEUE_SEND_FAILED( pxQueue )
#endif

#ifndef traceQUEUE_RECEIVE
	#define traceQUEUE_RECEIVE( pxQueue )
#endif

#ifndef traceQUEUE_PEEK
	#define traceQUEUE_PEEK( pxQueue )
#endif

#ifndef traceQUEUE_PEEK_FROM_ISR
	#define traceQUEUE_PEEK_FROM_ISR( pxQueue )
#endif

#ifndef traceQUEUE_RECEIVE_FAILED
	#define traceQUEUE_RECEIVE_FAILED( pxQueue )
#endif

#ifndef traceQUEUE_SEND_FROM_ISR
	#define traceQUEUE_SEND_FROM_ISR( pxQueue )
#endif

#ifndef traceQUEUE_SEND_FROM_ISR_FAILED
	#define traceQUEUE_SEND_FROM_ISR_FAILED( pxQueue )
#endif

#ifndef traceQUEUE_RECEIVE_FROM_ISR
	#define traceQUEUE_RECEIVE_FROM_ISR( pxQueue )
#endif

#ifndef traceQUEUE_RECEIVE_FROM_ISR_FAILED
	#define traceQUEUE_RECEIVE_FROM_ISR_FAILED( pxQueue )
#endif

#ifndef traceQUEUE_PEEK_FROM_ISR_FAILED
	#define traceQUEUE_PEEK_FROM_ISR_FAILED( pxQueue )
#endif

#ifndef traceQUEUE_DELETE
	#define traceQUEUE_DELETE( pxQueue )
#endif

