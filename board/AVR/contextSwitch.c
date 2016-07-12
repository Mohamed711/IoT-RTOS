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
#include "../../OS/Scheduler/Process.h"
#include "../../OS/Scheduler/queue.h"
#include "../../OS/Scheduler/contextSwitch.h"
#include "../../RTOS_Headers.h"

volatile uint16_t tempAddress;
volatile uint16_t savedAddress;
extern struct procent proctab[NPROC];		  /* table of processes */
#include "avr/interrupt.h"
void Scheduler_contextSwitch()
{
		
		SaveMainStakpointer();
		savedAddress=(TempPointer_H<<8)|(TempPointer_L);
		
		//tempAddress=proctab[0].Regstkptr;
		//TempPointer_L=tempAddress;
		//TempPointer_H=tempAddress>>8;
		//SetMainStakpointer();
		//
		//saveContext();
		//proctab[0].Regstkptr=(TempPointer_H<<8)|(TempPointer_L);
		
		tempAddress=proctab[currpid].Regstkptr;
		TempPointer_L=tempAddress;
		TempPointer_H=tempAddress>>8;
		SetMainStakpointer();
		
		restoreContext();
		proctab[currpid].Regstkptr=(TempPointer_H<<8)|(TempPointer_L);
		tempAddress=proctab[currpid].prstkptr;
		TempPointer_L=tempAddress;
		TempPointer_H=tempAddress>>8;
		SetMainStakpointer();
		sei();
		tempAddress=proctab[currpid].returnValue;
		TempPointer_L=tempAddress;
		TempPointer_H=tempAddress>>8;
		jumptoPC();
		
		
		
		//tempAddress=proctab[0].Regstkptr;
		//TempPointer_L=tempAddress;
		//TempPointer_H=tempAddress>>8;
		//SetMainStakpointer();
		//
		//restoreContext();
		//proctab[0].Regstkptr=(TempPointer_H<<8)|(TempPointer_L);
		TempPointer_L=savedAddress;
		TempPointer_H=savedAddress>>8;
		SetMainStakpointer();
		
	
}