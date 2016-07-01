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
struct ProcessEntry {               /* One per process plus two per list    */
		_delay_ms sleeping;			/* sleeping time */
        pid sleepingNext;			/* next process in the sleeping queue */
        pid sleepingPrevious;		/* previous process in the sleeping queue */
	    pid procPriority;         	/* Key on which the queue is ordered    */
        pid qnext;        			/* Index of next process or tail        */
        pid qprev; 					/* Index of previous process or head    */
};

/* The union isn't a ANSCI C standard but here we use it as only one parameter is required */
/* The attributes of each queue */
union QueueEntry {
	pid firstNode;
	pid lastNode;
};

extern qid readyList;
extern qid suspendedList;

extern struct ProcessEntry queuetab[];


/* Inline queue manipulation functions */
#define queueHead(q)    (q)
#define queueTail(q)    ((q) + 1)
#define firstId(q)      (queuetab[queuehead(q)].qnext)
#define lastId(q)       (queuetab[queuetail(q)].qprev)
#define isEmpty(q)      (firstid(q) >= NPROC)
#define nonEmpty(q)     (firstid(q) < NPROC)
#define firstKey(q)     (queuetab[firstid(q)].qkey)
#define lastKey(q)      (queuetab[ lastid(q)].qkey)

/* Inline to check queue id assumes interrupts are disabled */
#define isbadqid(x)     ( (int32_t)(x) >= NQENT )


pid dequeue(qid queueId);
sysCall enqueue(pid processId,qid queueId );
sysCall	insert(pid processId, qid queueId, pid key);
qid newqueue(void);

#endif
