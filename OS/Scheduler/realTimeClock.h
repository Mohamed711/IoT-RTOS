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

uint32_t	clktime;	/* current time in secs since boot	*/
qid16	sleepq;		/* queue for sleeping processes		*/
uint32_t ctr1000;
int32_t	slnonempty;	/* nonzero if sleepq is nonempty	*/
int32_t	*sltop;		/* ptr to key in first item on sleepq	*/
uint32_t	preempt;	/* preemption counter			*/

sysCall	insertd(pid32 pid, qid16 q,int32_t key);
sysCall	yield(void);
sysCall	sleep(int32_t delay);
sysCall	sleepms(int32_t	delay);
sysCall	unsleep(pid32 pid);
void wakeup(void);
void clkhandler(void);
void clkinit(void);

#endif /* TIMER_H_ */
