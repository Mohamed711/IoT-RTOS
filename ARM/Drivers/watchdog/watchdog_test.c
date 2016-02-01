/*
 * watchdog_test.c
 *
 *  Created on: Jan 31, 2016
 *      Author: mido4
 */

#include <stdint.h>
#include <stdbool.h>
#include "watchdog.h"
#include "watchdog_test.h"

#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400253FC))
#define SYSCTL_RCGCWD_R         (*((volatile unsigned long *)0x400FE600))

void delay(uint32_t x)
{
	uint32_t i,j;
	for (i = 0 ; i < x ; i++)
	{
		for (j = 0; j < 1000 ; j++)
		{
		}
	}
}

void watchDogInterrupt()
{
	WatchdogIntClear(WATCHDOG0);
	// white then delay
		GPIO_PORTF_DATA_R = 0x0E;
		delay(1000);
		GPIO_PORTF_DATA_R = 0x0A;
		delay(1000);

}

/*
 * The RGB color is black at the begin
 * then will be white till the reset takes place
 */
void WDT_ResetTest()
{
	// Enable watchdog timer 0
	SYSCTL_RCGCWD_R |= 0x01;

	delay(1000);
	// white then delay
	GPIO_PORTF_DATA_R = 0x04;
	delay(1000);

	// reload value
	WatchdogReloadSet(WATCHDOG0,0x01000000);

	// Reset Enable
	WatchdogResetEnable(WATCHDOG0);

	// Enable watchDog timer
	WatchdogEnable(WATCHDOG0);

	while (1)
	{
		// white then delay
		GPIO_PORTF_DATA_R = 0x0E;
		delay(1000);
	}
}

void WDT_INTTest()
{
	// Enable watchdog timer 0
	SYSCTL_RCGCWD_R |= 0x01;

	// white then delay
	GPIO_PORTF_DATA_R = 0x04;
	delay(1000);

	// reload value
	WatchdogReloadSet(WATCHDOG0,0x10000000);

	// Interrupt Enable
	WatchdogIntRegister(WATCHDOG0,watchDogInterrupt);

	// Enable watchDog timer
	WatchdogEnable(WATCHDOG0);

}

void WDT_ON()
{
	// Enable watchdog timer 0
	SYSCTL_RCGCWD_R |= 0x01;

	// white then delay
	GPIO_PORTF_DATA_R = 0x04;
	delay(1000);

	// yellow then delay
	GPIO_PORTF_DATA_R = 0x0A;
	delay(1000);

	// reload value
	WatchdogReloadSet(WATCHDOG0,0x00100000);

	// Enable watchDog timer
	WatchdogEnable(WATCHDOG0);

	while (1)
	{
		WatchdogReloadSet(WATCHDOG0,0x00100000);
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

