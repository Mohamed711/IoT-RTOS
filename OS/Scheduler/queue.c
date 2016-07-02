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

#include <stdint.h>
#include "queue.h"
#include "Process.h"

qid16 readylist;
qid16 suspendedlist;

extern struct procent proctab[NPROC];		  /* table of processes */
/*Inline code to check process ID (assumes interrupts are disabled) */
#define isbadpid(x) ( ((pid32)(x) < 0) || \
((pid32)(x) >= NPROC) || \
(proctab[(x)].prstate == PR_FREE))
/******************************************************************************
*
*	The function's purpose is insert a process at the tail of a queue
*
*	\param pid			ID of process to insert
*	\param q			ID of queue to use
*
*	Creating a new process so it can be used later ?
*
* 	\return the pid of the inserted process
*
*****************************************************************************/
pid32 enqueue(pid32 pid, qid16 q)
{
	int16_t   tail, prev;             /* Tail & previous node indexes */
    if (isbadqid(q) || isbadpid(pid))
    {
    	return SYSERR;
    }
	tail = queuetail(q);
	prev = queuetab[tail].qprev;
	queuetab[pid].qnext  = tail;    /* Insert just before tail node */
	queuetab[pid].qprev  = prev;
	queuetab[prev].qnext = pid;
	queuetab[tail].qprev = pid;
 	return pid;
}

/******************************************************************************
*
*	The function's purpose is to remove and return the first process on a list
*
*	\param q			ID of queue to use
*
*	Creating a new process so it can be used later ?
*
* 	\return the pid of the inserted process
*
*****************************************************************************/
pid32 dequeue(qid16 q)
{
	pid32   pid;                    /* ID of process removed        */
	if (isbadqid(q))
	{
		return SYSERR;
	}
	else if (isempty(q))
	{
		return EMPTY;
	}
	pid = getfirst(q);
	queuetab[pid].qprev = EMPTY;
	queuetab[pid].qnext = EMPTY;
	return pid;
}

/******************************************************************************
*
*	The function's purpose is to insert a process in a queue
*	making sure it's in the right place
*
*	\param pid			ID of the process to be inserted
*	\param q			ID of queue to use
*	\param key			the key used to sort the processes in the queue
*
* 	\return 0 if there's an error, -1 if there's no error
*
*****************************************************************************/
sysCall	insert(pid32 pid, qid16 q, int32_t key)
{
	int16_t	curr;			/* Runs through items in a queue*/
	int16_t	prev;			/* Holds previous node index	*/

	if (isbadqid(q) || isbadpid(pid))
	{
		return SYSERR;
	}

	curr = firstid(q);
	while (queuetab[curr].qkey > key)
	{
		curr = queuetab[curr].qnext;
	}

	/* Insert process between curr node and previous node */

	prev = queuetab[curr].qprev;	/* Get index of previous node	*/
	queuetab[pid].qnext = curr;
	queuetab[pid].qprev = prev;
	queuetab[pid].qkey = key;
	queuetab[prev].qnext = pid;
	queuetab[curr].qprev = pid;
	return OK;
}

/******************************************************************************
*
*	The function's purpose is to create a new queue
*
* 	\return the ID of the newly created queue
*
*****************************************************************************/
qid16 newqueue(void)
{
	static qid16 nextqid = NPROC; /* Next list in queuetab to use */
	qid16 q; /* ID of allocated queue */
	q = nextqid;

	if (q > NQENT)
	{ /* Check for table overflow */
		return (qid16)SYSERR;
	}

	nextqid += 2; /* Increment index for next call*/

	/* Initialize head and tail nodes to form an empty queue */
	queuetab[queuehead(q)].qnext = queuetail(q);
	queuetab[queuehead(q)].qprev = EMPTY;
	queuetab[queuehead(q)].qkey = MAXKEY;
	queuetab[queuetail(q)].qnext = EMPTY;
	queuetab[queuetail(q)].qprev = queuehead(q);
	queuetab[queuetail(q)].qkey = MINKEY;
	return q;
}


/******************************************************************************
*
*	The function's purpose is to remove a specific process
*
*	\param pid			ID of process to be removed
*
* 	\return the removed process's ID
*
*****************************************************************************/
pid32 getitem(pid32 pid)
{
	pid32   prev, next;
	next = queuetab[pid].qnext;  /* Following node in list  */
	prev = queuetab[pid].qprev;  /* Previous node in list   */
	queuetab[prev].qnext = next;
	queuetab[next].qprev = prev;
	return pid;
}

/******************************************************************************
*
*	The function's purpose is to remove the first process
*	in a specefic queue
*
*	\param q			ID of queue to use
*
* 	\return the removed process's ID
*
*****************************************************************************/
pid32 getfirst(qid16 q)
{
	pid32  head;
	if (isempty(q))
	{
		return EMPTY;
	}
	head = queuehead(q);
	return getitem(queuetab[head].qnext);
}

/******************************************************************************
*
*	The function's purpose is to remove the last process
*	in a specefic queue
*
*	\param q			ID of queue to use
*
* 	\return the removed process's ID
*
*****************************************************************************/
pid32 getlast(qid16 q)
{
	int16_t tail;
	if (isempty(q))
	{
		return EMPTY;
	}
	tail = queuetail(q);
	return getitem(queuetab[tail].qprev);
}
