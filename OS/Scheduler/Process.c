
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
#include "reSched.h"
#include "realTimeClock.h"
#include "../MMU/mmu.h"

pid32 currpid;
extern struct procent proctab[NPROC];		  /* table of processes */
extern qid16 readylist;
extern qid16 suspendedlist;
extern uint32_t prcount;

/*Inline code to check process ID (assumes interrupts are disabled) */
#define isbadpid(x) ( ((pid32)(x) < 0) || \
((pid32)(x) >= NPROC) || \
(proctab[(x)].prstate == PR_FREE))

#define INITIAL_XPSR                (0x01000000)
#define STACK_MARKER                (0x77777777)
/******************************************************************************
*
*	The function's purpose is to get the pid of the current process
*
*	the function returns the value of the current pid
*
* 	\return the pid
*
*****************************************************************************/
pid32 Scheduler_processGetPid()
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
pid32 Scheduler_processNewPid(void)
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
pid32 Scheduler_processCreate(void *funcAddr, uint32_t ssize, pri16 priority, char *name)
{
	pid32 pid; /* Stores new process id */
	struct procent *prptr; /* Pointer to process table entry */
	int32_t i;
	char *saddr;

	if (ssize < MINSTK)
	ssize = MINSTK;
	
	pid = Scheduler_processNewPid();
	saddr= (char*)pvPortMalloc(ssize);

	if ((priority < 1) || pid == (pid32)SYSERR || saddr == (char *)SYSERR)
	{
		return (pid32)SYSERR;
	}
	prcount++;
	prptr = &proctab[pid];

	/* Initialize process table entry for new process */
	prptr->processFunction = funcAddr;
	prptr->prstate = PR_SUSP; /* Initial state is suspended */
	prptr->prprio = priority;
	prptr->prstkbase = (char*)saddr;
	prptr->prstklen = ssize;
	prptr->prname[PNMLEN - 1] = NULLCH;
	for (i = 0; i < PNMLEN - 1 && (prptr->prname[i] = name[i]) != NULLCH; i++)
	{
		;
	}

	prptr->prstkptr = Scheduler_stackInitialization(saddr , funcAddr, ssize);
	prptr->returnValue = (uint32_t)funcAddr;
	
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
sysCall Scheduler_processTerminate(pid32 pid)
{
	struct procent *prptr; /* Ptr to process’ table entry */
	//u32 i; /* Index into descriptors */

	if (isbadpid(pid) || (pid == nullProc)
		|| ((prptr = &proctab[pid])->prstate) == PR_FREE) {
		return SYSERR;
	}
	//if (--prcount <= 1) { /* Last user process completes */
		//xdone(); //lsa mt3mltsh 
	

	switch (prptr->prstate) {
	case PR_CURR:
		prptr->prstate = PR_FREE; /* Suicide */
	break;
	case PR_sleep:
	case PR_RECTIM:
		Scheduler_unsleep(pid);
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
	prcount--;

	currpid =0;
	getitem(0);
	proctab[0].prstate = PR_CURR;
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
sysCall	Scheduler_processSetReady(pid32 pid)
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
pri16 Scheduler_processResume(pid32 pid)
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
	
	Scheduler_processSetReady(pid);
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
sysCall	Scheduler_processSuspend(pid32 pid) 		/* ID of process to suspend	*/
{
	//intmask	mask;			/* Saved interrupt mask		*/
	struct	procent *prptr;		/* Ptr to process' table entry	*/
	pri16	prio;			/* Priority to return		*/

	//mask = disable();
	if (isbadpid(pid) || (pid == nullProc))
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
	}
	prio = prptr->prprio;
	//restore(mask);
	return prio;
}

sysCall	Scheduler_processWaiting(pid32 pid) 		/* ID of process waiting for semaphore	*/
{
	//intmask	mask;			/* Saved interrupt mask		*/
	struct	procent *prptr;		/* Ptr to process' table entry	*/
	pri16	prio;			/* Priority to return		*/

	//mask = disable();
	if (isbadpid(pid) || (pid == nullProc))
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
void Scheduler_processSuspendAll(void) 		
{	
	while(nonempty(readylist))
	{
		
		pid32 pid=getfirst(readylist);
		Scheduler_processSuspend(pid);
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
void Scheduler_processResumeAll(void)
{
	while(nonempty(suspendedlist))
	{
		pid32 pid=getfirst(suspendedlist);
		Scheduler_processResume(pid);
	}
}

char * Scheduler_stackInitialization(char* stackpointer, void *func(), uint32_t ssize)
{

	/*to go to the stack's top*/
	 uint32_t *stk ;
	 stk = (uint32_t *)((uintptr_t)stackpointer + ssize);

	    /* adjust to 32 bit boundary by clearing the last two bits in the address */
	    stk = (uint32_t *)(((uint32_t)stk) & ~((uint32_t)0x3));

	    /* stack start marker */
	    stk--;
	    *stk = STACK_MARKER;
	    /* make sure the stack is double word aligned (8 bytes) */
	     /* This is required in order to conform with Procedure Call Standard for the
	      * ARMÂ® Architecture (AAPCS) */
	     /* http://infocenter.arm.com/help/topic/com.arm.doc.ihi0042e/IHI0042E_aapcs.pdf */
	     if (((uint32_t) stk & 0x7) != 0) {
	         /* add a single word padding */
	         --stk;
	         *stk = ~((uint32_t)STACK_MARKER);
	     }
			 
			 /*FPU*/
			  stk--;
    *stk = (unsigned int) 0;
    

    /* S0 - S15 */
    
    for (int i = 15; i >= 0; i--) 
	  {
        stk--;
        *stk = i;
		}

	     /* xPSR - initial status register */
	         stk--;
	         *stk = (uint32_t)INITIAL_XPSR;
	         /* pc - initial program counter value := thread entry function */
	         stk--;
	         *stk = (uint32_t)func;
	         /* lr - contains the return address when the thread exits */
	         stk--;
	         *stk = (uint32_t)Scheduler_processKill;
	         /* r12 */
	         stk--;
	         *stk = 0;
	         /* r3 - r1 */
	         uint32_t i;
	         for ( i = 3; i >= 1; i--) {
	             stk--;
	             *stk = i;
	         }
	         /* r0 - contains the thread function parameter */
	        stk--;
	         *stk = 0;

	         /* r11 - r4 */
	         for (i = 11; i >= 4; i--) {
	             stk--;
	             *stk = i;
	         }
	             return (char*) stk;

}
sysCall Scheduler_processKill()
{
	Scheduler_processTerminate(currpid);
	return OK;
}