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

#include "Resource Management.h"
#include "../Scheduler/Process.h"

extern pid32 currpid;

void vid_Binary_semp_Bsem_wait (Bsem_t *S)
{
	if (S->count == 0)
	{ 
		enqueue(currpid /*current process*/,S->Bsem_queue);
		
		/*pri16*/ /*sysCall suspend_return =*/ Scheduler_processWaiting(currpid);
	}
	else if(S->count==1)
	{
		S->count=0;
	}
}
void vid_Binary_semp_Bsem_signal(Bsem_t *S)
{
	
	if (!isEmpty(S->Bsem_queue))
	{
		int32_t processid= dequeue(S->Bsem_queue);

		Scheduler_processSetReady(processid /*curent process id  */);
	}
	else if(isEmpty(S->Bsem_queue))
	{
		S->count=1;
	}
}
