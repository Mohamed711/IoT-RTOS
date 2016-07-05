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
	
#include "reSched.h"
#include "Process.h"
#include "queue.h"
#include "contextSwitch.h"
#include "../RTOS.h"

extern pid32 currpid;
extern struct procent proctab[NPROC];		  /* table of processes */
extern qid16 readylist;

	
/*******************************************************************************
*
*	The function's purpose is to reSchedule the processes
*
*	By getting the head of the ready queue, the new process' state is then 
*	changed to 'running' state 
*
* 	\return none
*
*****************************************************************************/

void Scheduler_reSchedule(void) /* Assumes interrupts are disabled */
{
	
	volatile struct procent *ptold; /* Ptr to table entry for old process */
	volatile struct procent *ptnew; /* Ptr to table entry for new process */
	ptold = &proctab[currpid];
	
	pid32 oldP = currpid;
	
	if (ptold->prstate == PR_CURR)
	{ 	/* Process remains eligible */
		if (firstkey(readylist)==0)
		{
			return;
		}
		if (ptold->prprio > firstkey(readylist))
		{
			return;
		}
		/* Old process will no longer remain current */
		ptold->prstate = PR_READY;
		insert(currpid, readylist, ptold->prprio);
	}
	currpid = dequeue(readylist);
	ptnew = &proctab[currpid];
	ptnew->prstate = PR_CURR;
Scheduler_contextSwitch();


}
