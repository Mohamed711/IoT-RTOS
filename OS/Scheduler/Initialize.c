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

#include "../RTOS.h"
#include "../MMU/mmu.h"
#include "realTimeClock.h"
#include "Process.h"
#include "queue.h"
#include "nullProcess.h"
#include "Initialize.h"
#include <string.h>

struct procent proctab[NPROC];		  /* table of processes */
struct qentry queuetab[NQENT];        /* Table of process queues */
extern pid32 currpid;
uint32_t prcount;
#ifdef AVR

uint8_t* InitializeStack(portSTACK_TYPE *saddr)
{
		/* Place a few bytes of known values on the bottom of the stack. 
	This is just useful for debugging. */
	*saddr = 0x11;
	saddr--;
	*saddr = 0x22;
	saddr--;
	*saddr = 0x33;
	saddr--;
	/* Next simulate the stack as if after a call to portSAVE_CONTEXT().  
	portSAVE_CONTEXT places the flags on the stack immediately after r0
	to ensure the interrupts get disabled as soon as possible, and so ensuring
	the stack use is minimal should a context switch interrupt occur. */
	*saddr = ( uint8_t ) 0x00;	/* R0 */
	saddr--;
	*saddr = portFLAGS_INT_ENABLED; /* SREG */
	saddr--;


	/* Now the remaining registers.   The compiler expects R1 to be 0. */
	*saddr = ( uint8_t ) 0x00;	/* R1 */
	saddr--;
	*saddr = ( uint8_t ) 0x02;	/* R2 */
	saddr--;
	*saddr = ( uint8_t ) 0x03;	/* R3 */
	saddr--;
	*saddr = ( uint8_t ) 0x04;	/* R4 */
	saddr--;
	*saddr = ( uint8_t ) 0x05;	/* R5 */
	saddr--;
	*saddr = ( uint8_t ) 0x06;	/* R6 */
	saddr--;
	*saddr = ( uint8_t ) 0x07;	/* R7 */
	saddr--;
	*saddr = ( uint8_t ) 0x08;	/* R8 */
	saddr--;
	*saddr = ( uint8_t ) 0x09;	/* R9 */
	saddr--;
	*saddr = ( uint8_t ) 0x10;	/* R10 */
	saddr--;
	*saddr = ( uint8_t ) 0x11;	/* R11 */
	saddr--;
	*saddr = ( uint8_t ) 0x12;	/* R12 */
	saddr--;
	*saddr = ( uint8_t ) 0x13;	/* R13 */
	saddr--;
	*saddr = ( uint8_t ) 0x14;	/* R14 */
	saddr--;
	*saddr = ( uint8_t ) 0x15;	/* R15 */
	saddr--;
	*saddr = ( uint8_t ) 0x16;	/* R16 */
	saddr--;
	*saddr = ( uint8_t ) 0x17;	/* R17 */
	saddr--;
	*saddr = ( uint8_t ) 0x18;	/* R18 */
	saddr--;
	*saddr = ( uint8_t ) 0x19;	/* R19 */
	saddr--;
	*saddr = ( uint8_t ) 0x20;	/* R20 */
	saddr--;
	*saddr = ( uint8_t ) 0x21;	/* R21 */
	saddr--;
	*saddr = ( uint8_t ) 0x22;	/* R22 */
	saddr--;
	*saddr = ( uint8_t ) 0x23;	/* R23 */
	saddr--;

	*saddr = ( uint8_t ) 0x24;	/* R24 */
	saddr--;
	*saddr = ( uint8_t ) 0x25;	/* R25 */
	saddr--;
	*saddr = ( uint8_t ) 0x26;	/* R26 X */
	saddr--;
	*saddr = ( uint8_t ) 0x27;	/* R27 */
	saddr--;
	*saddr = ( uint8_t ) 0x28;	/* R28 Y */
	saddr--;
	*saddr = ( uint8_t ) 0x29;	/* R29 */
	saddr--;
	*saddr = ( uint8_t ) 0x30;	/* R30 Z */
	saddr--;
	*saddr = ( uint8_t ) 0x031;	/* R31 */
	saddr--;
	return saddr;
}
#endif

/******************************************************************************
*
*	The function's purpose is to initialie the null Process
*
* 	\return none
*
*****************************************************************************/
void Scheduler_initializenullProcess()
{
	volatile uint8_t *saddr;
	proctab[0].processFunction = Scheduler_nullProc;
	proctab[0].returnValue=Scheduler_nullProc;
	proctab[0].prstate = PR_CURR;
	proctab[0].prprio = 0;
	strncpy(proctab[0].prname, "prnull", 7);
	saddr = (uint8_t *)pvPortMalloc(100);  
	proctab[0].prstkbase=saddr+100;
	proctab[0].prstklen=100;
	
	proctab[0].prstkptr=(uint8_t *)(saddr+100-36);
	proctab[0].Regstkptr=(uint8_t *)(saddr+100);
	InitializeStack(proctab[0].prstkbase);
	currpid = 0;
}

/*
void initializeUART( Uart_InitTypeDef *initConf,uint32_t BaseAddress )
{
	
	initConf->BaudRate=115200;
	initConf->Parity= UART_CONFIG_PAR_NONE;
	initConf->Wlen=UART_CONFIG_WLEN_8;
	initConf->stopBit=UART_CONFIG_STOP_ONE;
	initConf->BaseAddress=BaseAddress;
	initConf->clock=SysCtlClockGet();

	uartinit(initConf);

}*/