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
#ifndef HAL_TIMER_
#define HAL_TIMER_

#include <stdint.h>
typedef void (*FnPtr)(void);

typedef struct Timer_InitTypeDef{
	uint32_t baseAddress;
}Timer_InitTypeDef;

typedef struct Timer_HandleTypeDef{
	Timer_InitTypeDef  instance;
	uint32_t timeInMillis;
	FnPtr timeoutFn;
} Timer_HandleTypeDef;

/*****************************************************************************
*
* Prototypes for the APIs.
*
******************************************************************************/
void timerinit(Timer_InitTypeDef * timer);
void timerstart(Timer_HandleTypeDef * timer);
void timerstart(Timer_HandleTypeDef * timer);
void timerstop(Timer_HandleTypeDef * timer);

void Timer_New(FnPtr timeoutFn, uint32_t time);

#endif
