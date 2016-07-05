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
#include "nullProcess.h"
#include "contextSwitch.h"
unsigned int lrReg;		/*the value of the link register in case there was an interrupt*/
static volatile uint32_t time;				/*time used for the timer*/

uint32_t	clktime;		/* current time in secs since boot	*/
qid16		sleepq;			/* queue for sleeping processes		*/
uint32_t 	ctr1000;
int32_t		slnonempty;		/* nonzero if sleepq is nonempty	*/
int32_t		*sltop;			/* ptr to key in first item on sleepq	*/
uint32_t	preempt;		/* preemption counter			*/

extern pid32 currpid;
extern struct procent proctab[NPROC];		  /* table of processes */
extern qid16 readylist;

/*Inline code to check process ID (assumes interrupts are disabled) */
#define isbadpid(x) ( ((pid32)(x) < 0) || \
((pid32)(x) >= NPROC) || \
(proctab[(x)].prstate == PR_FREE))


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
sysCall	Scheduler_insertd(pid32	pid,  qid16	q, int32_t	key)
{
	pid32	next;			/* Runs through the delta list	*/
	pid32	prev;			/* Follows next through the list*/

	if (isbadqid(q) || isbadpid(pid))
	{
		return SYSERR;
	}

	prev = queuehead(q);
	next = queuetab[queuehead(q)].qnext;

	while ((next != queuetail(q)) && (queuetab[next].qkey <= key))
	{
		key -= queuetab[next].qkey;
		prev = next;
		next = queuetab[next].qnext;
	}

	/* Insert new node between prev and next nodes */

	queuetab[pid].qnext = next;
	queuetab[pid].qprev = prev;
	queuetab[pid].qkey = key;
	queuetab[prev].qnext = pid;
	queuetab[next].qprev = pid;

	if (next != queuetail(q))
	{
		queuetab[next].qkey -= key;
		
	}
	
	time = queuetab[firstid(sleepq)].qkey;
	Timer_New(Scheduler_clkhandler, time);

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
volatile uint16_t tempAddress;
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

	if (Scheduler_insertd(currpid, sleepq, delay) == SYSERR)
	{
		return SYSERR;
	}

	proctab[currpid].prstate = PR_sleep;

	tempAddress=Scheduler_nullProc;
	TempPointer_L=tempAddress;
	TempPointer_H=tempAddress>>8;
	SetReturnAddress();
	asm volatile ("ret");
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
sysCall	Scheduler_unsleep(pid32 pid)
{
	struct	procent	*prptr;		/* Ptr to process' table entry	*/
	pid32	pidnext;		/* ID of process on sleep queue	*/
										/*   that follows the process	
										/*   which is being removed	*/
	if (isbadpid(pid))
	{
		return SYSERR;
	}

	/* Verify that candidate process is on the sleep queue */
	prptr = &proctab[pid];

	if ((prptr->prstate!=PR_sleep) && (prptr->prstate!=PR_RECTIM))
	{
		return SYSERR;
	}

	/* Increment delay of next process if such a process exists */
	pidnext = queuetab[pid].qnext;
	if (pidnext < NPROC)
	{
		queuetab[pidnext].qkey += queuetab[pid].qkey;
	}
	getitem(pid);			/* Unlink process from queue */
	
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
	pid32 pid;
	uint32_t i =0;
		pid = dequeue(sleepq);
		insert(pid, readylist, proctab[pid].prprio);
	if (!isempty(sleepq))
	{
		time = queuetab[firstid(sleepq)].qkey;
		Timer_New(Scheduler_clkhandler, time);
	}
	else
	{
		Timer_New(Scheduler_clkhandler, 1000000);
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
	if(!isempty(sleepq))
	{
		/* Decrement the delay for the first process on the */
		/* sleep queue, and awaken if the count reaches zero */
		if (queuetab[firstid(sleepq)].qkey - time  <=0)
		{
			Scheduler_wakeup();
		}
	}
	
}

/******************************************************************************
*
*	The function's purpose is to handle the clock interrupt
*
* 	\return none
*
*****************************************************************************/
void Timer_New(FnPtr clkhandler, uint32_t time)
{
	
	Timer_InitTypeDef timerInit;

	Timer_HandleTypeDef  timerHandle;
	timerHandle.timeInMillis=time;
	timerHandle.timeoutFn = clkhandler;

	timerinit(&timerInit);
	timerstart(&timerHandle);
}	