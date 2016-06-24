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

#ifndef RTOS_H_
#define RTOS_H_


#include <stdint.h>
#include <stdbool.h>

#include "../User_Config.h"

#ifdef ARM
	#include "../board/ARM/drivers/timer/HAL_Timer_TivaC.h"
	#include "../board/ARM/board_config.h"
#endif

#ifdef AVR
	#include "../board/AVR/drivers/Timer/HAL_Timer_AVR.h"
	#include "../board/AVR/board_config.h"
#endif


typedef uint8_t TimeOut_t;
typedef uint8_t TickType_t ;	// ticktype is a structure for the tick
/* the basetype must be defined some where */
typedef int8_t BaseType_t ;		// signed basetype is the base datatype
typedef uint8_t UBaseType_t ; 	// unsigned basetype is important datatype used
typedef int32_t pid32;
typedef uint16_t pri16;
typedef uint32_t sid32;
typedef uint32_t umsg32;
typedef bool bool8;
typedef	uint32_t intmask;
typedef uint16_t qid16;
typedef bool sysCall;

#define configASSERT(x)			// configAssert check the condition x is true or return the file and line number
#define pdTRUE	0x01			// true return
#define pdFALSE	0x00			// false return
#define pdPASS	0x01			// return value that the function carried out correctly
#define pdFAIL 	0x00			// return fail
#define errQUEUE_FULL	0x00	// error value indicates that the queue is full
#define errQUEUE_EMPTY 	0x00	// error the queue is empty
#define mtCOVERAGE_TEST_MARKER()// just an empty for the else part of the if statement
#define PRIVILEGED_FUNCTION		// to the memory protection unit
#define configUSE_PREEMPTION 0	// config the scheduler to be preemptive or cooperative
#define preemptive 0

#define portYIELD_WITHIN_API()	// check for the tasks to take the higher priority one


/* this values to be computed by a separate program isa */
#define NSEM 10
#define NPROC 5
#define NQENT   (NPROC + 4 + NSEM + NSEM)

#define	QUANTUM	2
#define	MAXSECONDS	2147483		/* Max seconds per 32-bit msec	*/

#define OK 1
#define SYSERR -1
#define TIMEOUT 0

#ifndef configUSE_MALLOC_FAILED_HOOK
	#define configUSE_MALLOC_FAILED_HOOK 0
#endif


/*-----------------------------------------*/
/* struct
typedef struct
{
	bool type; //TivaC=0 , Atmega32=1
	uint16_t configTOTAL_HEAP_SIZE;
} Heap_Init;
void heap_init(Heap_Init *size);
*/
/*-----------------------------------------*/

/*portBYTE_ALIGNMENT defined by user but for default value portBYTE_ALIGNMENT=8  need to implement this as structure*/
#if portBYTE_ALIGNMENT == 8
	#define portBYTE_ALIGNMENT_MASK ( 0x0007 )
#endif

#if portBYTE_ALIGNMENT == 4
	#define portBYTE_ALIGNMENT_MASK	( 0x0003 )
#endif

#if portBYTE_ALIGNMENT == 2
	#define portBYTE_ALIGNMENT_MASK	( 0x0001 )
#endif

#if portBYTE_ALIGNMENT == 1
	#define portBYTE_ALIGNMENT_MASK	( 0x0000 )
#endif

#ifndef portBYTE_ALIGNMENT_MASK
	#error "Invalid portBYTE_ALIGNMENT definition"
#endif


#endif
