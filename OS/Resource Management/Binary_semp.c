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

#include <stdio.h>
#include "Resource_Management.h"
#include "../RTOS.h"
#include "../Scheduler/ReSched.h"
#include "../MMU/mmu.h"
#include "../Scheduler/Process.h"

extern bool wakefromSleep;

uint16_t binarySemaphore_Initialize(binarySemaphoreStruct_t *pBsemaphore)
{
	
	if(pBsemaphore==NULL)
	{
		return RM_NULLPTR;
	}
	
	
		qid Bsemaphore_newqueue= newqueue();
		
	pBsemaphore->Bsemaphore_queue =Bsemaphore_newqueue;
	pBsemaphore->Bsemaphore_count=1;
	
}

uint16_t binarySemaphore_Wait (binarySemaphoreStruct_t *pBsemaphore)
{
	if (pBsemaphore->Bsemaphore_count == 0)
	{ 
		uint16_t enqueue_return= insert(Scheduler_processGetPid() /*current process*/,pBsemaphore->Bsemaphore_queue,proctab[Scheduler_processGetPid()].prprio);
		if(enqueue_return ==pdFAIL)
		{
			return RM_ENQUEUE;
		}
		
		
		/*pri16*/ /*sysCall suspend_return =*/ Scheduler_processWaiting(Scheduler_processGetPid());
		_RESCHEDULE_;
		
		
	}
	else if(pBsemaphore->Bsemaphore_count==1)
	{
		pBsemaphore->Bsemaphore_count=0;
	}
}
uint16_t binarySemaphore_Signal(binarySemaphoreStruct_t *pBsemaphore)
{
	
	if (!isEmpty(pBsemaphore->Bsemaphore_queue))
	{
		pid processid= dequeue(pBsemaphore->Bsemaphore_queue);
		Scheduler_processSetReady(processid /*curent process id  */);
		_RESCHEDULE_;
	}
	else if(isEmpty(pBsemaphore->Bsemaphore_queue))
	{
		pBsemaphore->Bsemaphore_count=1;
	}
}


uint16_t binarySemaphore_Delete (binarySemaphoreStruct_t *pBsemaphore )
{
	if(pBsemaphore==NULL)
	{
		return RM_NULLPTR;
	}

	pid processid;
	while(processid=dequeue(pBsemaphore->Bsemaphore_queue)!=errQUEUE_EMPTY)
	{
		Scheduler_processSetReady(processid);
		_RESCHEDULE_;
	}
	return SUCCESS;

}