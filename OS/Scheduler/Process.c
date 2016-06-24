
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

#include "Process.h"
#include "queue.h"
#include "ReSched.h"
#include "realTimeClock.h"
#include "../MMU/mmu.h"

pid32 currpid;
extern struct procent proctab[NPROC];		  /* table of processes */
extern qid16 readylist;
extern qid16 suspendedlist;

/******************************************************************************
*
*	The function's purpose is to get the pid of the current process
*
*	the function returns the value of the current pid
*
* 	\return the pid
*
*****************************************************************************/
pid32 pocessGetPid()
{
	return currpid;
}

/******************************************************************************
*
*	The function's purpose is to get a new pid for the newly created process
*
*	get a new pid, by looping through the process table to check if there's a 
*	a free spot, if yes, it'll return the first available pid
*
* 	\return the pid
*
*****************************************************************************/
pid32 processNewPid(void)
{
	uint32_t i; /* Iterate through all processes*/
	static pid32 nextpid = 1; /* Position in table to try or */
	/* one beyond end of table */
	/* Check all NPROC slots */
	for (i = 0; i < NPROC; i++) {
		nextpid %= NPROC; /* Wrap around to beginning */
		if (proctab[nextpid].prstate == PR_FREE) {
			return nextpid++;
		}
		else {
			nextpid++;
		}
	}
	return (pid32)SYSERR;
}

/******************************************************************************
*
*	The function's purpose is to create a new process
*
*	\param *funcAddr		Address of the function
*	\param ssize			Stack size in words
*	\param priority			Process' priority
*	\param *name			The Process' name (for debugging)
*
*	Creating a new process so it can be used later ?
*
* 	\return the pid of the created process
*
*****************************************************************************/
pid32 processCreate(void *funcAddr, uint32_t ssize, pri16 priority, char *name)
{
	pid32 pid; /* Stores new process id */
	struct procent *prptr; /* Pointer to process table entry */
	int32_t i;
	uint32_t *saddr;

	if (ssize < MINSTK)
	ssize = MINSTK;
	
	pid = processNewPid();
	saddr= (uint32_t *)pvPortMalloc(ssize);

	if ((priority < 1) || pid == (pid32)SYSERR || saddr == (uint32_t *)SYSERR)
	{
		return (pid32)SYSERR;
	}
	prptr = &proctab[pid];

	/* Initialize process table entry for new process */
	prptr->processFunction = funcAddr;
	prptr->prstate = PR_SUSP; /* Initial state is suspended */
	prptr->prprio = priority;
	prptr->prstkbase = (char *)saddr;
	prptr->prstklen = ssize;
	prptr->prname[PNMLEN - 1] = NULLCH;
	for (i = 0; i < PNMLEN - 1 && (prptr->prname[i] = name[i]) != NULLCH; i++)
	{
		;
	}

	return pid;
}

/******************************************************************************
*
*	The function's purpose is to terminate a  process
*
*	\param pid			Process' pid
*
*	removing the process from the process table, by looking for its pid
*	then changing its status to free
*
* 	\return 0 if there's an error, -1 if there's no error
*
*****************************************************************************/
sysCall processTerminate(pid32 pid)
{
	struct procent *prptr; /* Ptr to process’ table entry */
	//uint32_t i; /* Index into descriptors */

	if (isbadpid(pid) || (pid == NULLPROC)
		|| ((prptr = &proctab[pid])->prstate) == PR_FREE) {
		return SYSERR;
	}
	//if (--prcount <= 1) { /* Last user process completes */
		//xdone(); //lsa mt3mltsh 
	

	switch (prptr->prstate) {
	case PR_CURR:
		prptr->prstate = PR_FREE; /* Suicide */
		reSched();
	case PR_SLEEP:
	case PR_RECTIM:
		unsleep(pid);
		prptr->prstate = PR_FREE;
		break;
	case PR_WAIT:
		//semtab[prptr->prsem].scount++;
		/* Fall through */
	case PR_READY:
		getitem(pid); /* Remove from queue */
		prptr->prstate = PR_FREE;
		break;
		/* Fall through */
	default:
		prptr->prstate = PR_FREE;
	}
	return OK;
}

/******************************************************************************
*
*	The function's purpose is to set the status of a new process to ready
*
*	\param pid				the process's ID
*
* 	\return 0 if there's an error, -1 if there's no error
*
*****************************************************************************/
sysCall	processSetReady(uint32_t pid)
{
	register struct procent *prptr; //optimazation for fast memory access

	if (isbadpid(pid))
	{
		return SYSERR;
	}

	/* Set process state to indicate ready and add to ready list */
	prptr = &proctab[pid];
	prptr->prstate = PR_READY;
	insert(pid, readylist, prptr->prprio);
	reSched();

return OK;
}

/******************************************************************************
*
*	The function's purpose is to resume a previously suspended process
*
*	\param pid				the process's ID
*
* 	\return the priority of the resumed process
*
*****************************************************************************/
pri16 processResume(pid32 pid)
{
	//intmask	mask;			/* Saved interrupt mask		*/
	struct	procent *prptr;		/* Ptr to process' table entry	*/
	pri16	prio;			/* Priority to return		*/

	//mask = disable();
	/*
	Function disable disables interrupts and returns the previous interrupt status to its caller.
	*/
	if (isbadpid(pid))
	{
	//	restore(mask);
		return (pri16)SYSERR;
	}
	prptr = &proctab[pid];
	if (prptr->prstate != PR_SUSP)
	{
	//	restore(mask);
		return (pri16)SYSERR;
	}
	prio = prptr->prprio;		/* Record priority to return	*/
	
	processSetReady(pid);
	//dequeue(suspendedlist); // lw 3wz a keep track l kol el suspended
	//restore(mask);
	/*
	Function restore reloads an interrupt status from a previously saved value.
	*/
	return prio;
}

/******************************************************************************
*
*	The function's purpose is to set the status of a new process to suspend
*
*	\param pid				the process's ID
*
* 	\return 0 if there's an error, -1 if there's no error
*
*****************************************************************************/
sysCall	processSuspend(pid32 pid) 		/* ID of process to suspend	*/
{
	//intmask	mask;			/* Saved interrupt mask		*/
	struct	procent *prptr;		/* Ptr to process' table entry	*/
	pri16	prio;			/* Priority to return		*/

	//mask = disable();
	if (isbadpid(pid) || (pid == NULLPROC))
	{
	//	restore(mask);
		return SYSERR;
	}

	/* Only suspend a process that is current or ready */

	prptr = &proctab[pid];
	if ((prptr->prstate != PR_CURR) && (prptr->prstate != PR_READY))
	{
	//	restore(mask);
		return SYSERR;
	}
	if (prptr->prstate == PR_READY)
	{
		
		getitem(pid);		    /* Remove a ready process	*/
					    /*   from the ready list	*/
		prptr->prstate = PR_SUSP;
		//enqueue(pid,suspendedlist); //lw 3wzen n keep track lel suspended processes
	}
	else
	{
		prptr->prstate = PR_SUSP;   /* Mark the current process	*/
	//	enqueue(pid,suspendedlist); //lw 3wzen n keep track lel suspended processes
		reSched();		    /*   suspended and resched.	*/
	}
	prio = prptr->prprio;
	//restore(mask);
	return prio;
}

sysCall	processWaiting(pid32 pid) 		/* ID of process waiting for semaphore	*/
{
	//intmask	mask;			/* Saved interrupt mask		*/
	struct	procent *prptr;		/* Ptr to process' table entry	*/
	pri16	prio;			/* Priority to return		*/

	//mask = disable();
	if (isbadpid(pid) || (pid == NULLPROC))
	{
		//	restore(mask);
		return SYSERR;
	}

	/* Only wait a process that is current  */

	prptr = &proctab[pid];
	if (prptr->prstate != PR_CURR)
	{
		//	restore(mask);
		return SYSERR;
	}

	else
	{
		prptr->prstate = PR_WAIT;   /* Mark the current process	*/
		//enqueue(pid,waitinglist); //lw 3wzen n keep track lel suspended processes
		reSched();		    /*   suspended and resched.	*/
	}
	prio = prptr->prprio;
	//restore(mask);
	return prio;
}



/******************************************************************************
*
*	The function's purpose is to suspend all the processes
*
* 	\return none
*
*****************************************************************************/
void processSuspendAll(void) 		
{	
	while(nonempty(readylist))
	{
		
		pid32 pid=getfirst(readylist);
		processSuspend(pid);
		enqueue(pid,suspendedlist);
			
	}
}

/******************************************************************************
*
*	The function's purpose is to resume all the previously suspended processes
*
* 	\return none
*
*****************************************************************************/
void processResumeAll(void)
{
	while(nonempty(suspendedlist))
	{
		pid32 pid=getfirst(suspendedlist);
		processResume(pid);
	}
}
