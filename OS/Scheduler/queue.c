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

struct queueEntry queueTab[NQENT];

#if ( PARTIALLY_BLOCKING_ENABLE == 0x01 )
	struct sleepingEntry sleepTab[NPROC+2]; /* the two entries for the sleeping queue */
#endif

/******************************************************************************
*
*	The function's purpose is insert a process at the tail of a queue
*
*	\param processId			ID of process to insert
*	\param queueId			ID of queue to use
*
* 	\return pdPASS if the process is enqueued successfully
* 	or pdFAIL in case of failure
*
*****************************************************************************/
sysCall enqueue(pid processId, qid queueId)
{
	qid tail, prev;          /* Tail & previous node indexes */
	if (isBadQid(queueId) || isbadpid(processId))
	{
	  	return pdFAIL;
	}
	tail = queueTail(queueId);
	prev = queueTab[tail].qprev;
	queueTab[processId].qnext  = tail;    /* Insert just before tail node */
	queueTab[processId].qprev  = prev;
	queueTab[prev].qnext = processId;
	queueTab[tail].qprev = processId;
	return pdPASS;
}

/******************************************************************************
*
*	The function's purpose is to remove and return the first process on a list
*
*	\param queueId			ID of queue to use
*
* 	\return the pid of the inserted process
*
*****************************************************************************/
pid dequeue(qid queueId)
{
	pid processId;                    /* ID of process removed */
	if (isBadQid(queueId))
	{
		return pdFAIL;
	}
	else if (isEmpty(queueId))
	{
		return errQUEUE_EMPTY;
	}
	processId = firstId(queueId);
	getItem(processId);
	return processId;
}

/******************************************************************************
*
*	The function's purpose is to insert a process in a queue
*	making sure it's in the right place
*
*	\param processId			ID of the process to be inserted
*	\param queueId				ID of queue to use
*	\param entryPriority		The priority of the process in the queue
*
* 	\return pdFAIL if there's an error, pdPASS if there's no error
*
*****************************************************************************/
sysCall	insert( pid processId, qid queueId, queuePriority entryPriority )
{
	qid	curr;			/* Runs through items in a queue */
	qid	prev;			/* Holds previous node index	*/

	if (isBadQid(queueId) || isbadpid(processId))
	{
		return pdFAIL;
	}

	curr = firstId(queueId);
	while (queueTab[curr].qPriority > entryPriority)
	{
		curr = queueTab[curr].qnext;
	}

	/* Insert process between curr node and previous node */

	prev = queueTab[curr].qprev;	/* Get index of previous node */
	queueTab[processId].qnext = curr;
	queueTab[processId].qprev = prev;
	queueTab[processId].qPriority = entryPriority;

	queueTab[prev].qnext = processId;
	queueTab[curr].qprev = processId;

	return pdPASS;
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
	static qid queueId = NPROC-2; 	/* Next list in queuetab to use */
	queueId += 2;

	if (isBadQid(queueId))
	{ /* Check for table overflow */
		return (qid)pdFAIL;
	}

	/* Initialize head and tail nodes to form an empty queue */
	queueTab[queueHead(queueId)].qnext = queueTail(queueId);
	queueTab[queueTail(queueId)].qprev = queueHead(queueId);

	queueTab[queueHead(queueId)].qPriority = MAXKEY;
	queueTab[queueTail(queueId)].qPriority = MINKEY;

	return queueId;
}


/******************************************************************************
*
*	The function's purpose is to remove a specific process
*
*	\param processId	    	ID of process to be removed
*
* 	\return pdPASS if the process is removed
*
*****************************************************************************/
sysCall getItem(pid processId)
{
		qid prev, next;
		next = queueTab[processId].qnext;  /* Following node in list  */
		prev = queueTab[processId].qprev;  /* Previous node in list   */
		queueTab[prev].qnext = next;
		queueTab[next].qprev = prev;
		return pdPASS;
}


/******************************************************************************
*
*	The function's purpose is to insert a process at the tail of the sleeping
*	queue
*
*	\param processId			ID of process to insert
*
* 	\return pdPASS if the process is enqueued successfully
* 	or pdFAIL in case of failure
*
*****************************************************************************/
#if ( PARTIALLY_BLOCKING_ENABLE == 0x01 )
	sysCall enqueueSleep(pid processId)
	{
		qid tail, prev;          /* Tail & previous node indexes */
		if (isbadpid(processId))
		{
			return pdFAIL;
		}
		tail = queueTail(sleepingList);
		prev = sleepTab[tail].qprev;
		sleepTab[processId].qnext  = tail;    /* Insert just before tail node */
		sleepTab[processId].qprev  = prev;
		sleepTab[prev].qnext = processId;
		sleepTab[tail].qprev = processId;
		return pdPASS;
	}
#endif

/******************************************************************************
*
*	The function's purpose is to remove and return the first process on a list
*
* 	\return the pid of the inserted process
*
*****************************************************************************/
#if ( PARTIALLY_BLOCKING_ENABLE == 0x01 )
	pid dequeueSleep()
	{
		pid processId;                    /* ID of process removed */

		if (isEmpty(sleepingList))
		{
			return errQUEUE_EMPTY;
		}
		processId = firstId(sleepingList);
		getItem(processId);
		return processId;
	}
#endif

/******************************************************************************
*
*	The function's purpose is to insert a process in a queue
*	making sure it's in the right place
*
*	\param processId			ID of the process to be inserted
*	\param entryPriority		The priority of the process in the queue
*
* 	\return pdFAIL if there's an error, pdPASS if there's no error
*
*****************************************************************************/
#if ( PARTIALLY_BLOCKING_ENABLE == 0x01 )
	sysCall	insertSleep (pid processId, queuePriority entryPriority )
	{
		qid	curr;			/* Runs through items in a queue */
		qid	prev;			/* Holds previous node index	*/

		if (isbadpid(processId))
		{
			return pdFAIL;
		}

		curr = firstId(sleepingList);
		while (sleepTab[curr].sleeping > entryPriority)
		{
			curr = sleepTab[curr].qnext;
		}

		/* Insert process between curr node and previous node */

		prev = sleepTab[curr].qprev;	/* Get index of previous node */
		sleepTab[processId].qnext = curr;
		sleepTab[processId].qprev = prev;
		sleepTab[processId].sleeping = entryPriority;

		sleepTab[prev].qnext = processId;
		sleepTab[curr].qprev = processId;

		return pdPASS;
	}
#endif

/******************************************************************************
*
*	The function's purpose is to remove a specific process
*
*	\param processId	    	ID of process to be removed
*
* 	\return pdPASS if the process is removed
*
*****************************************************************************/
#if ( PARTIALLY_BLOCKING_ENABLE == 0x01 )
	sysCall getItemFromSleep(pid processId)
	{
		qid prev, next;
		next = sleepTab[processId].qnext;  /* Following node in list  */
		prev = sleepTab[processId].qprev;  /* Previous node in list   */
		sleepTab[prev].qnext = next;
		sleepTab[next].qprev = prev;
		return pdPASS;
	}
#endif

/******************************************************************************
*
*	The function's purpose is to create a sleeping queue
*
* 	\return the ID of the newly created queue
*
*****************************************************************************/
#if ( PARTIALLY_BLOCKING_ENABLE == 0x01 )

	qid newqueue(void)
	{
		static qid queueId = NPROC-2; 	/* Next list in queuetab to use */
		queueId += 2;

		/* Initialize head and tail nodes to form an empty queue */
		sleepTab[queueHead(queueId)].qnext = queueTail(queueId);
		sleepTab[queueTail(queueId)].qprev = queueHead(queueId);

		sleepTab[queueHead(queueId)].qPriority = MAXKEY;
		sleepTab[queueTail(queueId)].qPriority = MINKEY;

		return queueId;
	}

#endif
