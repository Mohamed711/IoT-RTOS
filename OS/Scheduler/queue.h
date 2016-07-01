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
* 9) if we succeed to build a preScheduler to count number of processes
* and queues then checking the qid and queue is full and these have to be
* deleted
* 10) For the queue entries, the key has no use
* in case of head: the prev has no use
* in case of tail: the next has no use
* so making a structure for them decrease the memory for 4*Word per queue
* 11) A function to initialize the default queues suspended, ready, ...
* is missing and the processes entries.
*****************************************************************************/

#define EMPTY   (-1)            /* Null value for qnext or qprev index  */
#define MAXKEY  0x7FFFFFFF      /* Max key that can be stored in queue  */
#define MINKEY  (-1)      		/* Min key that can be stored in queue  */

struct  qentry  {               /* One per process plus two per list    */
	    int32_t   qkey;         /* Key on which the queue is ordered    */
        int16_t   qnext;        /* Index of next process or tail        */
        int16_t   qprev;        /* Index of previous process or head    */
};

extern struct qentry queuetab[];

/* Inline queue manipulation functions */
#define queuehead(q)    (q)
#define queuetail(q)    ((q) + 1)
#define firstid(q)      (queuetab[queuehead(q)].qnext)
#define lastid(q)       (queuetab[queuetail(q)].qprev)
#define isempty(q)      (firstid(q) >= NPROC)
#define nonempty(q)     (firstid(q) < NPROC)
#define firstkey(q)     (queuetab[firstid(q)].qkey)
#define lastkey(q)      (queuetab[ lastid(q)].qkey)

/* Inline to check queue id assumes interrupts are disabled */
#define isbadqid(x)     (((int32_t)(x) < 0) || (int32_t)(x) >= NQENT-1)


pid32 dequeue(qid16 q);
pid32 enqueue(pid32 pid, qid16 q );
sysCall	insert(pid32 pid, qid16 q, int32_t key);
qid16 newqueue(void);

pid32 getitem(pid32 pid);
pid32 getfirst(qid16 q);
pid32 getlast(qid16 q);



#endif