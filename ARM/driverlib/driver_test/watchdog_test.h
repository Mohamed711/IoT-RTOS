/*
 * watchdog_test.h
 *
 *  Created on: Jan 31, 2016
 *      Author: mido4
 */

#ifndef DRIVERS_WATCHDOG_WATCHDOG_TEST_H_
#define DRIVERS_WATCHDOG_WATCHDOG_TEST_H_

void delay();
void watchDogInterrupt();	// function called when an interrupt
void WDT_ResetTest();
void WDT_INTTest();
void WDT_ON();

#endif /* DRIVERS_WATCHDOG_WATCHDOG_TEST_H_ */
