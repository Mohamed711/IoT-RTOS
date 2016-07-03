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
#include "drivers/timer/HAL_Timer_TivaC.h"
#include "tivaHAL.h"
#include "drivers/interrupt/interrupt.h"
#include "../../OS/RTOS.h"
#include "../../OS/Scheduler/Process.h"
#include "drivers/timer/timer.h"
#include "../../User_Config.h"

extern unsigned int lrReg;
extern pid32 currpid;
extern struct procent proctab[NPROC];
#define MAIN_RETURN 0xFFFFFFF9  //Tells the handler to return using the MSP
#define THREAD_RETURN 0xFFFFFFFD //Tells the handler to return using the PSP

extern bool wakefromSleep;

void ISRos(void)
{
	if (proctab[currpid].prstate != PR_FREE)
	{
		saveContext(proctab[currpid].prstkptr);
		proctab[currpid].prstkptr = (void*)get_PSP();
	}
	uint32_t* mainStk = (void*)get_MSP();

	TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
	
	if (wakefromSleep) 
		Scheduler_clkhandler();
	wakefromSleep = true;

	pid32 nwPiD = Scheduler_reSchedule();
	
		*((uint32_t*)mainStk) = THREAD_RETURN;
		set_PSP((uint32_t)proctab[nwPiD].prstkptr);
	loadContext(proctab[nwPiD].prstkptr);
}

void Timer_New(FnPtr timeoutFn, uint32_t time)
{
		uint32_t ui32Period;

		SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
		GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);

		SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
		TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);

		ui32Period = time * 80000;
		TimerLoadSet(TIMER0_BASE, TIMER_A, ui32Period -1);
		TimerIntRegister(TIMER0_BASE, TIMER_A, ISRos);
		IntEnable(INT_TIMER0A);
		TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
		IntMasterEnable();
		TimerEnable(TIMER0_BASE, TIMER_A);

}
