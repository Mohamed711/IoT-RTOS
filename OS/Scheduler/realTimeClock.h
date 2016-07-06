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

#include <stdint.h>
#include "../RTOS.h"

extern uint32_t time;				/*time used for the timer*/

sysCall	Scheduler_sleep(int32_t delay);
sysCall	Scheduler_sleepms(int32_t	delay);
sysCall	Scheduler_unsleep(pid processId);
void Scheduler_wakeup(void);
void Scheduler_clkhandler(void);

#endif /* TIMER_H_ */
