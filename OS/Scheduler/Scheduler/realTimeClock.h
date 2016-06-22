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

#ifndef TIMER_H_
#define TIMER_H_

#include "headers.h"

u32	clktime;	/* current time in secs since boot	*/
qid16	sleepq;		/* queue for sleeping processes		*/
u32 ctr1000;
s32	slnonempty;	/* nonzero if sleepq is nonempty	*/
s32	*sltop;		/* ptr to key in first item on sleepq	*/
u32	preempt;	/* preemption counter			*/

sysCall	insertd(pid32 pid, qid16 q,s32 key);
sysCall	yield(void);
sysCall	sleep(s32 delay);
sysCall	sleepms(s32	delay);
sysCall	unsleep(pid32 pid);
void wakeup(void);
void clkhandler(void);
void clkinit(void);

#endif /* TIMER_H_ */
