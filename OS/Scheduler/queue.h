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


#if ( PARTIALLY_BLOCKING_ENABLE == 0x01 )
	struct sleepingEntry {
		_delay_ms sleeping;			/* sleeping time */
		pid sleepingNext;			/* next process in the sleeping queue */
		pid sleepingPrevious;		/* previous process in the sleeping queue */
	};
	extern struct sleepingEntry sleepTab[];
#endif

/* The attributes of each process in a queue */
struct processEntry {               /* One per process plus two per list    */
	queuePriority procPriority;     /* Key on which the queue is ordered    */
    pid qnext;        				/* Index of next process or tail        */
    pid qprev; 						/* Index of previous process or head    */
};

extern struct processEntry procEntry[];

extern qid readyList;
extern qid suspendedList;
extern qid sleepingList;
extern pid queueTab[];

/* Inline queue manipulation functions */
#define firstId(queueId)      		( queueTab[queueId] )
#define isEmpty(queueId)      		( firstId(queueId) == NULL_ENTRY )
#define nonEmpty(queueId)     		( firstId(queueId) != NULL_ENTRY )

/* Inline to check queue id assumes interrupts are disabled */
/* One number is reserved to be returned in case of errors */
#define isBadQid(queueId)    		( (qid)(queueId) >= (NQENT-1) )

#define NULL_ENTRY 					( (pid)0xFFFFFFFF )
#define INVALID_QUEUE				( (qid)0xFFFFFFFF )


pid dequeue(qid queueId);
sysCall	insert( pid processId, qid queueId, queuePriority entryPriority );
sysCall getItem(pid processId, qid queueId);
qid newqueue(void);

#if ( PARTIALLY_BLOCKING_ENABLE == 0x00 )
	#define dequeueSleep()							dequeue(sleepingList)
	#define insertSleep(processId, SleepingTime)  	insert( processId, sleepingList, SleepingTime )
	#define getItemFromSleep(processId)				getItem(processId,sleepingList)
#else	
	pid dequeueSleep();
	sysCall	insertSleep (pid processId, queuePriority entryPriority );
	sysCall getItemFromSleep(pid processId);
#endif


#endif
