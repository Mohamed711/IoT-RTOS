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


#include <string.h>
extern pid32 currpid;
uint32_t prcount;

/******************************************************************************
*
*	The function's purpose is to initialie the null Process
*
* 	\return none
*
*****************************************************************************/
void Scheduler_initializenullProcess()
{
	proctab[0].processFunction = Scheduler_nullProc;
	proctab[0].prstate = PR_CURR;
	proctab[0].prprio = 0;
	strncpy(proctab[0].prname, "prnull", 7);
	
	proctab[0].prstkbase = (char*)pvPortMalloc(100);  
	proctab[0].prstkptr = Scheduler_stackInitialization(proctab[0].prstkbase , Scheduler_nullProc, 100);
	currpid = 0;
}

void initializeUART( Uart_InitTypeDef *initConf,uint32_t BaseAddress )
{
	
	initConf->BaudRate=9600;
	initConf->Parity= UART_CONFIG_PAR_NONE;
	initConf->Wlen=UART_CONFIG_WLEN_8;
	initConf->stopBit=UART_CONFIG_STOP_ONE;
	initConf->BaseAddress=BaseAddress;
	initConf->clock=SysCtlClockGet();

	uartinit(initConf);

}