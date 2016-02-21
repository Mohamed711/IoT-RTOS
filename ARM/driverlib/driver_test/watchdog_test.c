/*
 * watchdog_test.c
 *
 *  Created on: Jan 31, 2016
 *      Author: mido4
 */

#include <stdint.h>
#include <stdbool.h>
#include "driverlib/watchdog.h"
#include "inc/hw_memmap.h"
#include "watchdog_test.h"

#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400253FC))
#define SYSCTL_RCGCWD_R         (*((volatile unsigned long *)0x400FE600))

/*
 *  The function is a busy waiting delay according to the
 *  x value
 */
void static delay(uint32_t x)
{
	uint32_t i,j;
	for (i = 0 ; i < x ; i++)
	{
		for (j = 0; j < 1000 ; j++)
		{
		}
	}
}

/*
 * watchdog interrupt function
 * the function make the RGB LED to
 * be white then yellow
 */
void watchDogInterrupt()
{
	WatchdogIntClear(WATCHDOG0_BASE);
	GPIO_PORTF_DATA_R = 0x0E;
	delay(1000);
	GPIO_PORTF_DATA_R = 0x0A;
	delay(1000);
}

/*
 * The RGB color is blue at the beginning
 * then will be white till the reset takes place
 */
void WDT_ResetTest()
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

/*
 * The function tests generating a regular interrupt by
 * the watchdog timer
 * At first the RGB will be blue
 * then the interrupt will change it
 */
void WDT_INTTest()
{
	SYSCTL_RCGCWD_R |= 0x01;
	GPIO_PORTF_DATA_R = 0x04;
	delay(1000);
	WatchdogReloadSet(WATCHDOG0_BASE,0x10000000);
	WatchdogIntRegister(WATCHDOG0_BASE,watchDogInterrupt);
	WatchdogEnable(WATCHDOG0_BASE);
}

/*
 * The function is the ordinary operation of the watchdog timer
 */
void WDT_ON()
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


// Color    LED(s) PortF
// dark     ---    0
// red      R--    0x02
// blue     --B    0x04
// green    -G-    0x08
// yellow   RG-    0x0A
// sky blue -GB    0x0C
// white    RGB    0x0E
// pink     R-B    0x06

