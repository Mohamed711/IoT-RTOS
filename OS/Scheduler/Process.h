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

/******************************************************************************
* NOTES BY MOHAMED AHMED
* 1) NULLCH ? null character is \0 not zero and its placed automatically by
* the compiler in case of string "___"
* 2) userret ? I can't understand the process return
* 3) Number of processed given by the user is N, and you make N-1 proceses
* not N as 0 is the null process isn't counted by the user
* 4) what is a device descriptor ?
* 5) process states are better to be defined as enum
* 6) Difference between stack pointer and base runtime stack
* 7) void pointer to parameters to be passed to the task function in the
* process table
* 8) The datatypes of the process parameters to BaseType
* 9) ProcessNewPid() I think we should avoid division so if condition is
* better than division
* 10) ProcessCreate() saddr is better a void pointer
* 11) ProcessCreate() wrong casting in saddr cating (char *) into uint16 !!
* 12) ProcessCreate() for loop to copy !! very complex implemntation use memcpy
* 13) Function documentations SYSERR is -1 not 0
* write correct documentation
* 14) processNewPid() if its not used anywhere else declare it as static
* 15) processTerminate() a break is required in the switch statement for the
* first case
* 16) Processterminate() semaphore_wait A removing it from the queue waiting
* on the semaphore, signal it, and set the process to be free
* 17) ProcessTerminate() if making process free is common between all cases
* and can come first then make it above the switch case
* 18) ProcessResume() mesh fahem el comments deh kolha
* 19) ProcessResume() hya leeh btrg3 priority
* 20) ProcessSuspend() tyb mahe if elseif w else SYSERROR
* 21) ProcessSuspend() add_it to the suspended list w mwdo3 el priority brdo
* 22) ProcessWaiting() documentation
* 23) ProcessSuspendAll() mesh el mfrod mesh 3la el ready bs !
* 24) ProcessResumeAll() mesh el mfrod kol wa7da trg3 el state bt3tha
* 25) ProcessWaiting() return priority laken el function return syscall which
* is boolean
* 26) ProcessWaiting() feeling no difference between it and ready make just
* one function a more general one passing the queue i want to move my process
* to w 5las
*****************************************************************************/

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

 struct procent {                /* Entry in the process table           */
	void (*processFunction)(void);
	char    *prstkptr;      /* Saved stack pointer                  */
	char    *prstkbase;     /* Base of run time stack               */
	uint32_t returnValue;
	uint32_t   prprio;         /* Process priority                     */
	uint16_t prstate;         /* Process state: PR_CURR, etc.         */
	uint16_t  prstklen;       /* Stack length in bytes                */
	char    prname[PNMLEN]; /* Process name                         */
}; 

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

