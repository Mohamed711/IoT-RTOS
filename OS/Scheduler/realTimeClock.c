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

#include "queue.h"
#include "reSched.h"
#include "realTimeClock.h"
#include "Process.h"
#include "../RTOS.h"

extern bool wakefromSleep;
unsigned int lrReg;		/*the value of the link register in case there was an interrupt*/
uint32_t time;				/*time used for the timer*/

uint32_t	clktime;		/* current time in secs since boot	*/
uint32_t 	ctr1000;
int32_t		slnonEmpty;		/* nonzero if sleepq is nonEmpty	*/
int32_t		*sltop;			/* ptr to key in first item on sleepq	*/
uint32_t	preempt;		/* preemption counter			*/

/******************************************************************************
*
*	The function's purpose is to insert a processes in the sleep queue
*	and calculate it's new key
*
*	\param pid				process's ID
*	\param q				ID of the queue
*	\param key				delay from now (in ms.)
*
* 	\return 0 if there's an error, -1 if there's no error
*
*****************************************************************************/
sysCall	Scheduler_insertd(pid	processId,  qid	queueId, queuePriority	key)
{
	qid	next;			/* Runs through the delta list	*/
	qid	prev;			/* Follows next through the list*/

	if (isBadQid(queueId) || isbadpid(processId))
	{
		return SYSERR;
	}

	prev = queueHead(queueId);
	next = queueTab[queueHead(queueId)].qnext;

	while ((next != queueTail(queueId)) && (queueTab[next].qPriority <= key))
	{
		key -= queueTab[next].qPriority;
		prev = next;
		next = queueTab[next].qnext;
	}

	/* Insert new node between prev and next nodes */

	queueTab[processId].qnext = next;
	queueTab[processId].qprev = prev;
	queueTab[processId].qPriority = key;
	queueTab[prev].qnext = processId;
	queueTab[next].qprev = processId;

	if (next != queueTail(queueId))
	{
		queueTab[next].qPriority -= key;
	}
	
	time = queueTab[firstId(sleepingList)].qPriority;
	Timer_New(Scheduler_clkhandler, time+2);

}

/******************************************************************************
*
*	The function's purpose is to make a delay in seconds
*
*	\param delay		time to delay in seconds
*
* 	\return system call
*
*****************************************************************************/
sysCall	Scheduler_sleep(int32_t delay)
{
	if ( (delay < 0) || (delay > MAXSECONDS) )
	{
		return SYSERR;
	}
	Scheduler_sleepms(1000*delay);
	return OK;
}

/******************************************************************************
*
*	The function's purpose is to make a delay in milliseconds
*
*	\param delay		time to delay in seconds
*
* 	\return 0 if there's an error, -1 if there's no error
*
*****************************************************************************/
sysCall	Scheduler_sleepms(int32_t	delay)
{
	if (delay < 0)
	{
		return SYSERR;
	}

	if (delay == 0)
	{
		return OK;
	}

	/* Delay calling process */

	if (Scheduler_insertd(currpid, sleepingList, delay) == SYSERR)
	{
		return SYSERR;
	}

	proctab[currpid].prstate = PR_sleep;
	wakefromSleep = false;
	IntTrigger(INT_TIMER0A);
	return OK;
}

/******************************************************************************
*
*	The function's purpose is to remove a process from the sleeping queue
*
*	\param pid		the process's ID
*
* 	\return 0 if there's an error, -1 if there's no error
*
*****************************************************************************/
sysCall	Scheduler_unsleep(pid processId)
{
	struct	procent	*prptr;		/* Ptr to process' table entry	*/
	qid	pidnext;		/* ID of process on sleep queue	*/
										/*   that follows the process	
										/*   which is being removed	*/
	if (isbadpid(processId))
	{
		return SYSERR;
	}

	/* Verify that candidate process is on the sleep queue */
	prptr = &proctab[processId];

	if ((prptr->prstate!=PR_sleep) && (prptr->prstate!=PR_RECTIM))
	{
		return SYSERR;
	}
if (processId == queueHead(sleepingList))
	{
		time = queueTab[firstId(sleepingList)].qPriority;
		Timer_New(Scheduler_clkhandler, time+2);
	}
	getItem(processId);			/* Unlink process from queue */
	
	Scheduler_processSetReady(processId);
	
	if (!isEmpty(sleepingList))
	{
		time = queueTab[firstId(sleepingList)].qPriority;
		Timer_New(Scheduler_clkhandler, time);
	}
	else
	{
		Timer_New(Scheduler_clkhandler, 10000000000);
		//TimerDisable(TIMER0_BASE, TIMER_A);
	}
	
	wakefromSleep = false;
	IntTrigger(INT_TIMER0A);
	return OK;
}

/******************************************************************************
*
*	The function's purpose is awake all processes that have
*	no more time to sleep
*
* 	\return none
*
*****************************************************************************/
void Scheduler_wakeup(void)
{
	/* Awaken all processes that have no more time to sleep */
	pid processId;
	uint32_t i =0;
		processId = dequeue(sleepingList);
		insert(processId, readyList, proctab[processId].prprio);
	if (!isEmpty(sleepingList))
	{
		time = queueTab[firstId(sleepingList)].qPriority;
		Timer_New(Scheduler_clkhandler, time);
	}
	else
	{
		Timer_New(Scheduler_clkhandler, 100000000);
	}
	return;
}

/******************************************************************************
*
*	The function's purpose is to handle the clock interrupt
*
* 	\return none
*
*****************************************************************************/
void Scheduler_clkhandler(void)
{

	/* Handle sleeping processes if any exist */
	if(!isEmpty(sleepingList))
	{
		/* Decrement the delay for the first process on the */
		/* sleep queue, and awaken if the count reaches zero */
		if (queueTab[firstId(sleepingList)].qPriority - time  <=0)
		{
			Scheduler_wakeup();
		}
	}
	
}