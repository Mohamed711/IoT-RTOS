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

#ifndef DRIVERS_WATCHDOG_WATCHDOG_TEST_H_
#define DRIVERS_WATCHDOG_WATCHDOG_TEST_H_

/*****************************************************************************
*
* Prototypes for the APIs.
*
******************************************************************************/
void watchDogInterrupt_Test();	/* function called when the interrupt takes place */
void WDT_Reset_Test();
void WDT_INT_Test();
void WDT_ON_Test();

#endif /* DRIVERS_WATCHDOG_WATCHDOG_TEST_H_ */
