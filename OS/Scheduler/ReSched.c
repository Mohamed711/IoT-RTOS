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
#include "headers.h"

/******************************************************************************
*
*	The function's purpose is to reschedule the processes
*
*	By getting the head of the ready queue, the new process' state is then 
*	changed to 'running' state 
*
* 	\return none
*
*****************************************************************************/
void reSched(void) /* Assumes interrupts are disabled */
{

	struct procent *ptnew; /* Ptr to table entry for new process */

	currpid = dequeue(readylist);
	ptnew = &proctab[currpid];
	ptnew->prstate = PR_CURR;

	return;
}