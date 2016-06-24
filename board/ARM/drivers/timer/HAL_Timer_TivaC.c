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
#include "HAL_Timer_TivaC.h"
#include <stdint.h>
#include <stdbool.h>
#include "../inc/tm4c123gh6pge.h"
#include "../inc/hw_memmap.h"
#include "../inc/hw_types.h"
#include "../sysctl/sysctl.h"
#include "../interrupt/interrupt.h"
#include "../gpio/gpio.h"
#include "timer.h"

volatile static uint32_t millis=0;
volatile uint32_t max_millis;
volatile FnPtr function;
volatile static bool delayFlag=false;

static void ISR(void)
{
	TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
	millis++;
	if(delayFlag==false)
	{
		if(millis==max_millis)
		{
			function();
			millis = 0;
		}
	}
}

/******************************************************************************
  *
  *	Initializes the timer
  *
  *	You have to call this function before using the timer
  *
  * \return none
  *
  *****************************************************************************/
void timerinit(Timer_InitTypeDef * timer)
{
	uint32_t period=40000;
	SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
	TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
	TimerLoadSet(TIMER0_BASE, TIMER_A, period-1);
	TimerIntRegister(TIMER0_BASE, TIMER_A, ISR);
	IntEnable(INT_TIMER0A);
	TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
	IntMasterEnable();
}

/******************************************************************************
  *
  *	Start the timer
  *
  *	\param	timer is a pointer to structure that contains the timeInMillis
  *			which is the time in miliseconds and timeoutFn which is the function
  *			that executes when the time is out.
  *
  *	This function takes a time in milliseconds and after this time is out it starts
  *	executing the function that timeoutFn points to
  *
  * \return none
  *
  *****************************************************************************/
void timerstart(Timer_HandleTypeDef * timer)
{
	uint32_t timeInMillis = timer->timeInMillis;
	FnPtr timeoutFn = timer->timeoutFn;

	delayFlag=false;
	millis=0;
	function = timeoutFn;
	max_millis=timeInMillis;
	TimerEnable(TIMER0_BASE, TIMER_A);

}

/******************************************************************************
  *
  *	Makes a delay
  *
  *	\param 	timer which is a pointer to a structure which contains the
  *			timeInMillis which is the time in miliseconds
  *
  * \return none
  *
  *****************************************************************************/
void timerdelay(Timer_HandleTypeDef * timer)
{
	uint32_t timeInMillis = timer->timeInMillis;

	delayFlag=true;
	millis=0;
	max_millis=timeInMillis;
	TimerEnable(TIMER0_BASE, TIMER_A);
	while(millis<max_millis);
}

/******************************************************************************
  *
  *	Stops the timer
  *
  * \return none
  *
  *****************************************************************************/
void timerstop(Timer_HandleTypeDef * timer)
{
	TimerDisable(TIMER0_BASE, TIMER_A);
}
