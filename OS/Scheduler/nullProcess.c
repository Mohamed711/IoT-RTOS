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
#include "nullProcess.h"
#include "Process.h"
#include "queue.h"
#include "reSched.h"
#include "../RTOS.h"
#include "contextSwitch.h"
extern unsigned int lrReg;
extern pid32 currpid;
extern uint32_t prcount;
extern struct procent proctab[NPROC];
extern qid16 readylist;

volatile uint16_t tempAddress;
volatile uint16_t savedAddress;
void Scheduler_nullProc()
{
	
	while (1)
		{
				if (prcount !=0)
				{
					if (currpid != 0)
					{
						//SaveMainStakpointer();
						//savedAddress=(TempPointer_H<<8)|(TempPointer_L);
						//
						//proctab[currpid].prstkptr=savedAddress;
						//
						//tempAddress=proctab[currpid].Regstkptr;
						//TempPointer_L=tempAddress;
						//TempPointer_H=tempAddress>>8;
						//SetMainStakpointer();
						//
						//saveContext();
						//
						//
						//TempPointer_L=savedAddress;
						//TempPointer_H=savedAddress>>8;
						//SetMainStakpointer();
						insert(currpid, readylist, proctab[currpid].prprio);
					}
					currpid = 0;
					Scheduler_reSchedule();
					
				}
	}
}
