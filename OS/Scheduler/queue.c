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

struct processEntry procEntry[NPROC];		  /* table of processes */
pid queueTab[NQENT];

#if ( PARTIALLY_BLOCKING_ENABLE == 0x01 )
	struct sleepingEntry sleepTab[NPROC];
#endif


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
		return INVALID_QUEUE;
	}
	else if (isEmpty(queueId))
	{
		return errQUEUE_EMPTY;
	}
	processId = firstId(queueId);
	queueTab[queueId] = procEntry[processId].qnext;
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
	pid	curr;			/* Runs through items in a queue */
	pid	prev;			/* Holds previous node index	*/

	if ( isBadQid(queueId) || isbadpid(processId) )
	{
		return pdFAIL;
	}
	else if ( isEmpty(queueId) )
	{
		queueTab[queueId] = processId;
		procEntry[processId].qprev = NULL_ENTRY;
		procEntry[processId].qnext = NULL_ENTRY;
	}
	else
	{
		curr = firstId(queueId);
		while (procEntry[curr].procPriority >= entryPriority)
		{
			if (procEntry[curr].qnext == NULL_ENTRY)
			{
				procEntry[processId].qnext = NULL_ENTRY;
				procEntry[processId].qprev = curr;
				procEntry[curr].qnext= processId;
				return pdPASS;
			}
			curr = procEntry[curr].qnext;
		}
		prev = procEntry[curr].qprev;	/* Get index of previous node */
		procEntry[processId].qnext = curr;
		procEntry[processId].qprev = prev;
		procEntry[curr].qprev = processId;

		if ( prev == NULL_ENTRY )
		{
			queueTab[queueId] = processId;
		}
		else
		{
			procEntry[prev].qnext = processId;
		}
	}

	procEntry[processId].procPriority = entryPriority;
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
	static qid queueId = 0; 	/* Next list in queuetab to use */
	qid xReturn;

	/* Check for table overflow */
	if (isBadQid(queueId))
	{
		return INVALID_QUEUE;
	}

	/* Initialize head and tail nodes to form an empty queue */
	queueTab[queueId] = NULL_ENTRY;

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
sysCall getItem(pid processId, qid queueId)
{
	pid prev, next;
	next = procEntry[processId].qnext;  /* Following node in list  */
	prev = procEntry[processId].qprev;  /* Previous node in list   */

	if ( prev == NULL_ENTRY )
	{
		queueTab[queueId] = next;
	}
	else
	{
		procEntry[prev].qnext = next;
	}

	if ( next != NULL_ENTRY )
	{
		procEntry[next].qprev = prev;
	}
	return pdPASS;
}


#if ( PARTIALLY_BLOCKING_ENABLE == 0x01 )
	pid dequeueSleep()
	{
		pid processId;                    /* ID of process removed */

		if (isBadQid(sleepingList))
		{
			return INVALID_QUEUE;
		}
		else if (isEmpty(sleepingList))
		{
			return errQUEUE_EMPTY;
		}
		processId = firstId(sleepingList);
		queueTab[sleepingList] = sleepTab[processId].sleepingNext;
		return processId;
	}
#endif



#if ( PARTIALLY_BLOCKING_ENABLE == 0x01 )
	sysCall	insertSleep (pid processId, queuePriority entryPriority )
	{
		pid	curr;			/* Runs through items in a queue */
		pid	prev;			/* Holds previous node index	*/

		if ( isBadQid(sleepingList) || isbadpid(processId) )
		{
			return pdFAIL;
		}
		else if ( isEmpty(sleepingList) )
		{
			queueTab[sleepingList] = processId;
			sleepTab[processId].sleepingPrevious = NULL_ENTRY;
			sleepTab[processId].sleepingNext = NULL_ENTRY;
		}
		else
		{
			curr = firstId(sleepingList);
			while (procEntry[curr].procPriority >= entryPriority)
			{
				if (procEntry[curr].qnext == NULL_ENTRY)
				{
					sleepTab[processId].sleepingNext = NULL_ENTRY;
					sleepTab[processId].sleepingPrevious = curr;
					sleepTab[curr].sleepingNext= processId;
					return pdPASS;
				}
				curr = sleepTab[curr].sleepingNext;
			}
			prev = sleepTab[curr].sleepingPrevious;	/* Get index of previous node */
			sleepTab[processId].sleepingNext = curr;
			sleepTab[processId].sleepingPrevious = prev;
			sleepTab[curr].sleepingPrevious = processId;

			if ( prev == NULL_ENTRY )
			{
				queueTab[sleepingList] = processId;
			}
			else
			{
				sleepTab[prev].sleepingNext = processId;
			}
		}
		sleepTab[processId].sleeping = entryPriority;
	return pdPASS;
	}
#endif



#if ( PARTIALLY_BLOCKING_ENABLE == 0x01 )
	sysCall getItemFromSleep(pid processId)
	{
		pid prev, next;
		next = sleepTab[processId].sleepingNext;  /* Following node in list  */
		prev = sleepTab[processId].sleepingPrevious;  /* Previous node in list   */

		if ( prev == NULL_ENTRY )
		{
			queueTab[sleepingList] = next;
		}
		else
		{
			sleepTab[prev].sleepingNext = next;
		}

		if ( next != NULL_ENTRY )
		{
			sleepTab[next].sleepingPrevious = prev;
		}
		return pdPASS;
	}
#endif
