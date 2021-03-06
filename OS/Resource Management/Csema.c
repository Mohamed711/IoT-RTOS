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

#include "Resource Management.h"
#include "../Scheduler/Process.h"

extern pid currpid;


int8_t Csema_init( Csema *sema, int8_t count )
{
	if(sema==NULL)
	{
		return SYSERR;
	}

	sema->count =count;
	int16_t nq =newqueue();
	if(nq==SYSERR)
		return SYSERR;
	else
	{
		sema->queue=nq;
		return OK;
	}

}

int8_t Csema_delete( Csema *sema )
{
	if(sema==NULL)
		{
			return SYSERR;
		}

	int32_t pid;
	while(pid=dequeue(sema->queue)!=SYSERR)
	{
		Scheduler_processResume(pid);
	}
	return OK;

}

int8_t Csema_wait(Csema *sema)
{
	if(sema==NULL)
		{
			return SYSERR;
		}

	//DisableInterrupt();

	if( sema->count >0)
	{
		sema->count--;
		//EnableInterrupt();
		return OK;

	}
	else
	{
		enqueue(currpid,sema->queue);
		Scheduler_processWaiting(currpid);

		//EnbleInterrupt();
		return OK;
	}
}



int8_t Csema_signal(Csema *sema)
{
	if(sema==NULL)
		{
			return SYSERR;
		}
	//DisableInterrupt();
	if(isEmpty(sema->queue))
	{
		sema->count++;
		//EnableInterrupt();
		return OK;
	}
	else
	{
		int32_t pid=dequeue(sema->queue);
		Scheduler_processSetReady(pid);

		//EnableInterrupt();
		return OK;
	}
}

