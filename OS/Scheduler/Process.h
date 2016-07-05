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
#ifndef PROCESS_H_
#define PROCESS_H_

#include <stdint.h>
#include "../RTOS.h"

/* Process state constants */
#define PR_FREE 0 								/* Process table entry is unused */
#define PR_CURR 1 								/* Process is currently running */
#define PR_READY 2 								/* Process is on ready queue */
#define PR_RECV 3 		/* Process waiting for message */
#define PR_sleep 4 		/* Process is sleeping */
#define PR_SUSP 5 		/* Process is suspended */
#define PR_WAIT 6 		/* Process is on semaphore queue */
#define PR_RECTIM 7 	/* Process is receiving with timeout */

/* Miscellaneous process definitions */
#define PNMLEN 16 		/* Length of process "name" */
#define nullProc 0 		/* ID of the null process */

#define	NULLSTK	100		/* stack size for null process	*/

#define NULLCH 0 		/* Null Character to mark the end of the process' name */

/* Process initialization constants */
#define INITPRIO 20 	/* Initial process priority */
#define INITRET userret /* Address to which process returns */
#define INITSTK 100 	/* Initial process stack size */
#define MINSTK	10  	/* Minimum stack size */

 struct procent
 {
	 uint8_t	*prstkptr;      /* Saved stack pointer                  */
	 uint8_t 	*Regstkptr;     /* Base of run time stack               */
	 volatile uint16_t returnValue;
	 void (*processFunction)(void);
	 uint16_t 	prstate;        /* Process state: PR_CURR, etc.         */
	 uint32_t 	prprio;         /* Process priority                     */
	 uint8_t 	*prstkbase;     /* Base of run time stack               */

	 uint16_t 	prstklen;       /* Stack length in bytes                */
	 char     	prname[PNMLEN]; /* Process name                         */
	 uint16_t 	prparent;       /* ID of the creating process           */
 };
extern pid32 currpid;
pid32 Scheduler_processGetPid();
pid32 Scheduler_processNewPid();
pid32 Scheduler_processCreate(void *funcaddr, uint32_t ssize, pri16 priority, char *name);
sysCall Scheduler_processTerminate(pid32 pid);
sysCall	Scheduler_processSetReady(pid32 pid);
pri16 Scheduler_processResume(pid32 pid);
sysCall	Scheduler_processSuspend(pid32 pid);
void Scheduler_processSuspendAll(void);
void Scheduler_processResumeAll(void);
sysCall	Scheduler_processWaiting(pid32 pid);
char * Scheduler_stackInitialization(char* stackpointer, void *func(), uint32_t ssize);
sysCall Scheduler_processKill();

#endif

