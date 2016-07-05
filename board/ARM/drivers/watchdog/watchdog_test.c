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

#include <stdint.h>
#include <stdbool.h>
#include "watchdog.h"
#include "../inc/hw_memmap.h"
#include "watchdog_test.h"


/*****************************************************************************
*
* Registers of the port clock and the data register for portF
*
******************************************************************************/
#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400253FC))
#define SYSCTL_RCGCWD_R         (*((volatile unsigned long *)0x400FE600))


/*****************************************************************************
*
* static functions prototype.
*
******************************************************************************/
static void delay(uint32_t delay);


/*****************************************************************************
*
* watchdog timer interrupt function.
*.
* This function is the function called by the interrupt of the
* watchdog timer.
* It makes the RGB LED to be white then yellow.
*
* \return None.
******************************************************************************/
void watchDogInterrupt_Test()
{
	WatchdogIntClear(WATCHDOG0_BASE);
	GPIO_PORTF_DATA_R = 0x0E;
	delay(1000);
	GPIO_PORTF_DATA_R = 0x0A;
	delay(1000);
}


/*****************************************************************************
*
* Reset test of the watchdog timer.
*
* This function test the reset of the watchdog timer.
* The RGB LED will be blue at the begining then it will be white
* if a reset takes place it will be blue again as it starts from the begining
*
* \return None.
******************************************************************************/
void WDT_Reset_Test()
{
	SYSCTL_RCGCWD_R |= 0x01;
	delay(1000);
	GPIO_PORTF_DATA_R = 0x04;
	delay(1000);
	WatchdogReloadSet(WATCHDOG0_BASE,0x01000000);
	WatchdogResetEnable(WATCHDOG0_BASE);
	WatchdogEnable(WATCHDOG0_BASE);

	while (1)
	{
		GPIO_PORTF_DATA_R = 0x0E;
		delay(1000);
	}
}


/*****************************************************************************
*
* Interrupt test of the watchdog timer.
*
* This function tests the interrupt of the watchdog timer.
* The RGB LED will be blue then the interrupt function is carried
* out to change it.
*
* \return None.
******************************************************************************/
void WDT_INT_Test()
{
	SYSCTL_RCGCWD_R |= 0x01;
	GPIO_PORTF_DATA_R = 0x04;
	delay(1000);
	WatchdogReloadSet(WATCHDOG0_BASE,0x10000000);
	WatchdogIntRegister(WATCHDOG0_BASE,watchDogInterrupt_Test);
	WatchdogEnable(WATCHDOG0_BASE);
}


/*****************************************************************************
*
* Initialize the watchdog timer.
*
* This function is the ordinary operation of watchdog timer.
* The watchdog timer is reloaded before resetting the timer or generating
* an interrupt.
* The RGB LED will be blue then will be yellow.
*
* \return None.
******************************************************************************/
void WDT_ON_Test()
{
	SYSCTL_RCGCWD_R |= 0x01;
	GPIO_PORTF_DATA_R = 0x04;
	delay(1000);
	GPIO_PORTF_DATA_R = 0x0A;
	delay(1000);
	WatchdogReloadSet(WATCHDOG0_BASE,0x00100000);
	WatchdogEnable(WATCHDOG0_BASE);

	while (1)
	{
		WatchdogReloadSet(WATCHDOG0_BASE,0x00100000);
		delay(1000);
	}
}

/*****************************************************************************
*
* Software delay.
*
* \param delay the amount to be delayed.
*
* This function is a software delay function.
*
* \return None.
******************************************************************************/

void delay(uint32_t delay)
{
	uint32_t i,j;
	for (i = 0 ; i < delay ; i++)
	{
		for (j = 0; j < 1000 ; j++)
		{
		}
	}
}
