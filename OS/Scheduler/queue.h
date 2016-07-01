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
#ifndef QUEUE_H_
#define QUEUE_H_

#include "../RTOS.h"

/******************************************************************************
* NOTES BY MOHAMED AHMED
* 1) Change name of empty it can be used in other module
* 2) Datatypes of the module must be all changed according to the architecture
* UBaseType to fit with the 8_bit 16_bit and 32_bit architecture
* 3) Capitalize the letters of the functions getItem, queueHead(), isEmpty()
* 4) getFirst & gitLast is it better to use firstId(q) and lastId(q)
* to be passed to the function so you don't have to declare a variable head
* or tail.
* 5) getFirst && getLast a valid qid need to be checked
* 6) dequeue function: no need to check for valid qid and empty as you called
* already getFirst() which do that already
* 7) All of this functions are carried out from an interrupt or ordinary
* function what if they are interrupted ??! by a higher priority interrupt
* or by interrupt in case of oridnary function.
* 8) Inserting a process is O(n) think of another way to make it log(n)
* 9) if we succeed to build a prescheduler to count number of processes
* and queues then checking the qid and queue is full and these have to be
* deleted
* 10) For the queue entries, the key has no use
* in case of head: the prev has no use
* in case of tail: the next has no use
* so making a structure for them decrease the memory for 4*Word per queue
* 11) A function to initialize the default queues suspended, ready, ...
* is missing and the processes entries.
* 12) check if insertion in the readylist then rescheduling
* 13) when inserting a process in a queue you should change its state automatically
* 14) you should hashDefine of all processes to change their states or be responsible
* for changing the state
* 15) isempty and nonempty are not working in a right way
*****************************************************************************/

/* The attributes of each process in a queue */
struct processEntry {               /* One per process plus two per list    */
		_delay_ms sleeping;			/* sleeping time */
        pid sleepingNext;			/* next process in the sleeping queue */
        pid sleepingPrevious;		/* previous process in the sleeping queue */
	    pid procPriority;         	/* Key on which the queue is ordered    */
        pid qnext;        			/* Index of next process or tail        */
        pid qprev; 					/* Index of previous process or head    */
};

/* The attributes of each queue */
struct queueEntry {
	pid firstProcess;
	pid lastProcess;
};

extern qid readyList;
extern qid suspendedList;
extern qid sleepingList;

extern struct processEntry procTab[];
extern struct queueEntry queueTab[];

/* Inline queue manipulation functions */
#define firstId(queueId)      		( queueTab[queueId].firstProcess )
#define lastId(queueId)       		( queueTab[queueId].lastProcess )
#define isEmpty(queueId)      		( firstId(queueId) == NULL_ENTRY )
#define nonEmpty(queueId)     		( firstId(queueId) != NULL_ENTRY )
#define firstPriority(queueId)     	( queueTab[firstId(q)].procPriority )
#define lastPriority(queueId)      	( queueTab[ lastId(q)].procPriority )

#define firstSleepingId()			( firstId(sleepingList) )
#define lastSleepingId()			( lastId(sleepingList) )
#define firstSleepingTime()			( processEntry[firstId(sleepingList)].sleeping )
#define lastSleepingTime()			( processEntry[lastId(sleepingList)].sleeping )

#define firstReadyId()				( firstId(readyList) )
#define lastReadyId()				( lastId(readyList) )

/* Inline to check queue id assumes interrupts are disabled */
/* One number is reserved to be returned in case of errors */
#define isBadQid(queueId)    				( (qid)(queueId) >= (NQENT-1) )

#define NULL_ENTRY 					( (pid)0xFFFFFFFF )
#define INVALID_QUEUE				( (qid)0xFFFFFFFF )

pid dequeue(qid queueId);
sysCall enqueue(pid processId,qid queueId );
sysCall	insert(pid processId, qid queueId, pid key);
qid newqueue(void);

#endif
