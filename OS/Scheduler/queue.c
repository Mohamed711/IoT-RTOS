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

qid readyList;
qid suspendedList;
qid sleepingList;

struct processEntry procTab[NPROC];		  /* table of processes */
struct queueEntry queueTab[NQENT];

inline static pid getfirst( qid queueId );
inline static pid getitem(pid processId);
inline static pid getlast(qid queueId);

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
sysCall enqueue( pid processId,qid queueId )
{
	pid tail, prev;             /* Tail & previous node indexes */
    if (isBadQid(queueId) || isbadpid(processId))
    {
    	return SYSERR;
    }
	tail = queuetail(queueId);
	prev = queuetab[tail].qprev;
	queueTab[processId].qnext  = tail;    /* Insert just before tail node */
	queueTab[processId].qprev  = prev;
	queueTab[prev].qnext = processId;
	queueTab[tail].qprev = processId;
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
pid dequeue(qid queueId)
{
	int32_t   pid;                    /* ID of process removed */
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
* 	\return SYSERR if there's an error, OK if there's no error
*
*****************************************************************************/
sysCall	insert(pid processId, qid queueId, pid key)
{
	int16_t	curr;			/* Runs through items in a queue */
	int16_t	prev;			/* Holds previous node index	*/

	if (isbadqid(q) || isbadpid(pid))
	{
		return SYSERR;
	}

	curr = firstid(q);
	while (queuetab[curr].qkey >= key)
	{
		curr = queuetab[curr].qnext;
	}

	/* Insert process between curr node and previous node */

	prev = queuetab[curr].qprev;	/* Get index of previous node */
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
qid newqueue(void)
{
	static qid queueId = 0; 	/* Next list in queuetab to use */
	qid xReturn;

	/* Check for table overflow */
	if (isBadQid(queueId))
	{
		return INVALID_QUEUE;
	}

	/* Initialize head and tail nodes to form an empty queue */
	queueTab[queueId].firstProcess = NULL_ENTRY;
	queueTab[queueId].lastProcess = NULL_ENTRY;

	xReturn = queueId;
	queueId++; 				/* Increment index for next call */
	return xReturn;
}


/******************************************************************************
*
*	The function's purpose is to remove a specific process
*
*	\param processId	    	ID of process to be removed
*
* 	\return the removed process's ID
*
*****************************************************************************/
inline static pid getitem(pid processId)
{
	pid prev, next;
	next = procTab[processId].qnext;  /* Following node in list  */
	prev = procTab[processId].qprev;  /* Previous node in list   */
	procTab[prev].qnext = next;
	procTab[next].qprev = prev;
	return processId;
}

/******************************************************************************
*
*	The function's purpose is to remove the first process
*	in a specefic queue
*
*	\param queueId			ID of queue to use
*
* 	\return the removed process's ID
*
*****************************************************************************/
inline static pid getFirst( qid queueId )
{
	if (isEmpty(queueId))
	{
		return errQUEUE_EMPTY;
	}
	return getitem(firstId(queueId));
}

/******************************************************************************
*
*	The function's purpose is to remove the last process
*	in a specefic queue
*
*	\param queueId			ID of queue to use
*
* 	\return the removed process's ID
*
*****************************************************************************/
inline static pid getLast(qid queueId)
{
	if (isEmpty(queueId))
	{
		return errQUEUE_EMPTY;
	}
	return getitem(lastId(queueId));
}
