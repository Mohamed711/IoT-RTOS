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
#define PR_FREE 0 		/* Process table entry is unused */
#define PR_CURR 1 		/* Process is currently running */
#define PR_READY 2 		/* Process is on ready queue */
#define PR_RECV 3 		/* Process waiting for message */
#define PR_SLEEP 4 		/* Process is sleeping */
#define PR_SUSP 5 		/* Process is suspended */
#define PR_WAIT 6 		/* Process is on semaphore queue */
#define PR_RECTIM 7 	/* Process is receiving with timeout */

/* Miscellaneous process definitions */
#define PNMLEN 16 		/* Length of process "name" */
#define NULLPROC 0 		/* ID of the null process */

#define	NULLSTK	100		/* stack size for null process	*/

#define NULLCH 0 		/* Null Character to mark the end of the process' name */

/* Process initialization constants */
#define INITPRIO 20 	/* Initial process priority */
#define INITRET userret /* Address to which process returns */
#define INITSTK 100 	/* Initial process stack size */
#define MINSTK	10  	/* Minimum stack size */

 struct procent {                /* Entry in the process table           */
	void (*processFunction)(void);
	 uint32_t returnValue;
	uint16_t prstate;         /* Process state: PR_CURR, etc.         */
	uint32_t   prprio;         /* Process priority                     */
	char    *prstkptr;      /* Saved stack pointer                  */
	char    *prstkbase;     /* Base of run time stack               */
	uint16_t  prstklen;       /* Stack length in bytes                */
	char    prname[PNMLEN]; /* Process name                         */
}; 

pid32 pocessGetPid();
pid32 processNewPid();
pid32 processCreate(void *funcaddr, uint32_t ssize, pri16 priority, char *name);
sysCall processTerminate(pid32 pid);
sysCall	processSetReady(pid32 pid);
pri16 processResume(pid32 pid);
sysCall	processSuspend(pid32 pid);
void processSuspendAll(void);
void processResumeAll(void);
sysCall	processWaiting(pid32 pid);
char * stackinit(char* stackpointer, void *func(), uint32_t ssize);
sysCall processKill();

#endif

