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

countingSemaphoreStruct_t *semaphore_array[5];
uint8_t semaphore_array_index=0;


uint16_t countingSemaphore_Initialize( countingSemaphoreStruct_t *pCSemaphore, int8_t initCount )
{
	if(pCSemaphore==NULL)
	{
		return RM_NULLPTR;
	}
	if(initCount>255)
	{
		return RM_OVERFLOW;
	}
	if(semaphore_array_index<5)
	{
	semaphore_array[semaphore_array_index]=pCSemaphore;
	semaphore_array_index++;
	}
	else
	{
		return RM_FULLBUFFER;
	}
	pCSemaphore->count =initCount;
	qid nq =newqueue();
	
		pCSemaphore->queue=nq;
		return SUCCESS;
}

uint16_t countinSemaphore_Delete( countingSemaphoreStruct_t *pCSemaphore )
{
	if(pCSemaphore==NULL)
		{
			return RM_NULLPTR;
		}

	pid p;
	while(p=dequeue(pCSemaphore->queue)!=errQUEUE_EMPTY)
	{
		Scheduler_processSetReady(p);
    _RESCHEDULE_;
	}
	return SUCCESS;

}

uint16_t countingSemaphore_Wait(countingSemaphoreStruct_t *pCSemaphore)
{
	if(pCSemaphore==NULL)
		{
			return RM_NULLPTR;
		}
	//DisableInterrupt();

	if( pCSemaphore->count >0)
	{
		pCSemaphore->count--;
		//EnableInterrupt();
		return SUCCESS;

	}
	else
	{
		uint16_t enqueue_return=insert(Scheduler_processGetPid(),pCSemaphore->queue,proctab[Scheduler_processGetPid()].prprio);
		if(enqueue_return==pdFAIL)
		{
			return RM_ENQUEUE;
		}

		Scheduler_processWaiting(Scheduler_processGetPid());
		_RESCHEDULE_;
		//EnbleInterrupt();
		return SUCCESS;
	}
}

uint16_t countingSemaphore_WaitTimed(countingSemaphoreStruct_t *pCSemaphore, uint32_t timeout)
{
	if(pCSemaphore==NULL)
		{
			return RM_NULLPTR;
		}

	//DisableInterrupt();

	if( pCSemaphore->count >0)
	{
		pCSemaphore->count--;
		//EnableInterrupt();
		return SUCCESS;

	}
	else
	{
		Scheduler_processWaiting(Scheduler_processGetPid());
		Scheduler_sleep(timeout);
		_RESCHEDULE_;
		//EnbleInterrupt();
		return SUCCESS;
	}
}



uint16_t countingSemaphore_Signal(countingSemaphoreStruct_t *pCSemaphore)
{
	if(pCSemaphore==NULL)
		{
			return RM_NULLPTR;
		}
	//DisableInterrupt();
	if(isEmpty(pCSemaphore->queue))
	{
		pCSemaphore->count++;
		//EnableInterrupt();
		return SUCCESS;
	}
	else
	{
		pid p=dequeue(pCSemaphore->queue);

		Scheduler_processSetReady(p);
		_RESCHEDULE_;
		//EnableInterrupt();
		return SUCCESS;
	}
}

