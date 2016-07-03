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
#include "8-bit_TimerCounter0.h"


#ifndef HAL_H_
#define HAL_H_

typedef struct {
	uint32_t i ; 	//DUMMY variable
}Timer_InitTypeDef;
	
typedef struct {	
	Timer_InitTypeDef instance ;
	uint16_t timeInMillis; 
	FnPtr timeoutFn;
}Timer_HandleTypeDef;
	
#define timerinit(x) timer0Init1ms()
#define timerdelay(x) timer0Delay1ms((*x).timeInMillis, (*x).timeoutFn)
#define timerstart(x) timer0Start((*x).timeInMillis, (*x).timeoutFn)
#define timerstop(x)  timer0Stop()

#endif /* HAL_H_ */