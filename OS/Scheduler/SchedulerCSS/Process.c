
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
	u32 i; /* Iterate through all processes*/
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
pid32 processCreate(void *funcAddr, u32 ssize, pri16 priority, char *name)
{
	pid32 pid; /* Stores new process id */
	struct procent *prptr; /* Pointer to process table entry */
	s32 i;
	u32 *saddr;

	if (ssize < MINSTK)
		ssize = MINSTK;
	//ssize = (u32)roundmb(ssize);// sameh hy3mlha
	pid = processNewPid();
//	saddr = (u32 *)memoryGetStack(ssize); // sameh hy3mlha

	if ((priority < 1) || pid == (pid32)SYSERR || saddr == (u32 *)SYSERR)
	{
		return (pid32)SYSERR;
	}
	prcount++;
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
	prptr->prsem = -1;
	prptr->prhasmsg = false;

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
	u32 i; /* Index into descriptors */

	if (isbadpid(pid) || (pid == NULLPROC)
		|| ((prptr = &proctab[pid])->prstate) == PR_FREE) {
		return SYSERR;
	}
	if (--prcount <= 1) { /* Last user process completes */
		//xdone(); //lsa mt3mltsh 
	}

//	memoryFreeStack(prptr->prstkbase, prptr->prstklen); //sameh msh hy3mlha

	switch (prptr->prstate) {
	case PR_CURR:
		prptr->prstate = PR_FREE; /* Suicide */
		reSched();
	case PR_SLEEP:
	case PR_RECTIM:
//		unsleep(pid); lsa mt3mltsh
		prptr->prstate = PR_FREE;
		break;
	case PR_WAIT:
		//semtab[prptr->prsem].scount++;
		/* Fall through */
	case PR_READY:
		getitem(pid); /* Remove from queue */
		/* Fall through */
	default:
		prptr->prstate = PR_FREE;
	}
	return OK;
}

/* Index of ready list		*/

sysCall	processSetReady(u32 pid)	/* ID of process to make ready	*/
{
	register struct procent *prptr; //optimazation for fast memory access

	if (isbadpid(pid)) //macro should be defined
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

pri16 processResume(pid32 pid) 		/* ID of process to unsuspend	*/
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
		enqueue(pid,suspendedlist); //lw 3wzen n keep track lel suspended processes
	}
	else
	{
		prptr->prstate = PR_SUSP;   /* Mark the current process	*/
		enqueue(pid,suspendedlist); //lw 3wzen n keep track lel suspended processes
		reSched();		    /*   suspended and resched.	*/
	}
	prio = prptr->prprio;
	//restore(mask);
	return prio;
}
void processSuspendAll(void) 		
{	
	while(nonempty(readylist))
	{
		
		pid32 pid=getfirst(readylist);
		processSuspend(pid);
		enqueue(pid,suspendedlist);
			
	}
}
void processResumeAll(void)
{
	while(nonempty(suspendedlist))
	{
		pid32 pid=getfirst(suspendedlist);
		processResume(pid);
	}
}
