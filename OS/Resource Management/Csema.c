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

#include "Csema.h"


void Csema_init( Csema *sema, uint8_t count )
{
	sema->count =count;
	sema->queue=newqueue();
}

void Csema_delete( Csema *sema )
{
	int32_t pid;
	while(pid=dequeue(sema->queue)!=SYSERR)
	{
		processResume(pid);
	}
}

void Csema_wait(Csema *sema)
{
	//DisableInterrupt();
	if( sema->count >0)
	{
		sema->count--;
		//EnableInterrupt();
	}
	else
	{
		enqueue(currpid,sema->queue);
		processSuspend(currpid);
		//EnbleInterrupt();
	}
}

void Csema_signal(Csema *sema)
{
	//DisableInterrupt();
	if(isempty(sema->queue))
	{
		sema->count++;
		//EnableInterrupt();
	}
	else
	{
		int32_t pid=dequeue(sema->queue);
		processResume(pid);
		//EnableInterrupt();
	}


}
