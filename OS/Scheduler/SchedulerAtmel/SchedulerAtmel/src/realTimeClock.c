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

#include "headers.h"
//#include "AvrDrivers/Timer/HAL_Timer_AVR.h"
extern reSched();

/******************************************************************************
*
*	The function's purpose is to insert a processes in the sleep queue
*	and calculate it's new key
*
*	\param pid				process's ID
*	\param q				ID of the queue
*	\param key				delay from now (in ms.)
*	\param *name			The Process' name (for debugging)
*
* 	\return 0 if there's an error, -1 if there's no error
*
*****************************************************************************/
sysCall	insertd(  pid32	pid,  qid16	q, s32	key)
{
	s32	next;			/* Runs through the delta list	*/
	s32	prev;			/* Follows next through the list*/

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

	return OK;
}

/******************************************************************************
*
*	The function's purpose is to call the reSched function
*
* 	\return 0 if there's an error, -1 if there's no error
*
*****************************************************************************/
sysCall	yield(void)
{
	//intmask	mask;			/* Saved interrupt mask		*/
	//mask = disable();
	reSched();
	//restore(mask);
	return OK;
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
sysCall	sleep(s32 delay)
{
	if ( (delay < 0) || (delay > MAXSECONDS) )
	{
		return SYSERR;
	}
	sleepms(1000*delay);
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
sysCall	sleepms(s32	delay)
{
	//intmask	mask;			/* Saved interrupt mask		*/

	if (delay < 0)
	{
		return SYSERR;
	}

	if (delay == 0)
	{
		yield();
		return OK;
	}

	/* Delay calling process */

	//mask = disable();
	if (insertd(currpid, sleepq, delay) == SYSERR)
	{
		//restore(mask);
		return SYSERR;
	}

	proctab[currpid].prstate = PR_SLEEP;
	reSched();
	//restore(mask);
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
sysCall	unsleep(pid32 pid)
{
	//intmask	mask;			/* Saved interrupt mask		*/
     struct	procent	*prptr;		/* Ptr to process' table entry	*/

     pid32	pidnext;		/* ID of process on sleep queue	*/
							/*   that follows the process	*/
							/*   which is being removed	*/

	//mask = disable();

	if (isbadpid(pid))
	{
		//restore(mask);
		return SYSERR;
	}

	/* Verify that candidate process is on the sleep queue */

	prptr = &proctab[pid];

	if ((prptr->prstate!=PR_SLEEP) && (prptr->prstate!=PR_RECTIM))
	{
		//restore(mask);
		return SYSERR;
	}

	/* Increment delay of next process if such a process exists */

	pidnext = queuetab[pid].qnext;
	if (pidnext < NPROC)
	{
		queuetab[pidnext].qkey += queuetab[pid].qkey;
	}

	getitem(pid);			/* Unlink process from queue */
	//restore(mask);
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
void wakeup(void)
{
	/* Awaken all processes that have no more time to sleep */

	//resched_cntl(DEFER_START);
	while (nonempty(sleepq) && (firstkey(sleepq) <= 0))
	{
		processSetReady(dequeue(sleepq));
	}
	reSched();
	//resched_cntl(DEFER_STOP);
	return;
}

/******************************************************************************
*
*	The function's purpose is to handle the clock interrupt
*
* 	\return none
*
*****************************************************************************/
void clkhandler(void)
{
	static u32 count1000 = 1000; /* Count to 1000 ms */
	/* Decrement the ms counter, and see if a second has passed */
	if((--count1000) <= 0)
	{
		/* One second has passed, so increment seconds count */
		clktime++;
		/* Reset the local ms counter for the next second */
		count1000 = 1000;
	}
	/* Handle sleeping processes if any exist */
	if(!isempty(sleepq))
	{
		/* Decrement the delay for the first process on the */
		/* sleep queue, and awaken if the count reaches zero */
		if((--queuetab[firstid(sleepq)].qkey) <= 0)
		{
			wakeup();
		}
	}
	/* Decrement the preemption counter, and reschedule when the */
	/* remaining time reaches zero */

	if((--preempt) <= 0)
	{
		preempt = QUANTUM;
		reSched();
	}
}

/******************************************************************************
*
*	The function's purpose is to initialize the clock
*
* 	\return none
*
*****************************************************************************/
void clkinit(void)
{

	/* Allocate a queue to hold the delta list of sleeping processes*/
	sleepq = newqueue();
	/* Initialize the preemption count */
	preempt = QUANTUM;
	/* Initialize the time since boot to zero */
	clktime = 0;

	//Timer_InitTypeDef timerInit;

	Timer_HandleTypeDef  timerHandle;
	//timerHandle.timeInMillis=1000;
	timerHandle.timeoutFn = clkhandler;

	//HAL_Timer_Init(&timerInit);
	HAL_Timer_1ms(&timerHandle);


	return;
}
