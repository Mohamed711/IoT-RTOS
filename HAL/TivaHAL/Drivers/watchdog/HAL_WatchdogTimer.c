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

#include "../inc/tm4c123gh6pge.h"
#include "HAL_WatchdogTimer.h"
#include "watchdog.h"


/*****************************************************************************
*
* Initialize the watchdog timer.
*
* \param wdt is a structure of WDT_HandleTypeDef which contains all the
* parameters to initialize the watchdog timer.
*
* This function enables the watchdog clock,
* set the reload value,
* set the type of the required interrupt,
* Enable\Disable the reset mode,
* Enable\Disable lock the registers,
* Enable\Disable the stall mode,
* Enable\Disable the interrupt.
*
* \return None.
******************************************************************************/
void HAL_WDT_Init(WDT_HandleTypeDef * wdt)
{
	HAL_WDT_CLK_ENABLE();
	WatchdogReloadSet(wdt->watchdogBaseAddress , wdt->reloadValue);
	WatchdogIntTypeSet(wdt->watchdogBaseAddress , wdt->interruptType);

	if (wdt->resetEnable == true)
	{
		WatchdogResetEnable(wdt->watchdogBaseAddress);
	}
	else
	{
		WatchdogResetDisable(wdt->watchdogBaseAddress);
	}

	if (wdt->lock == true)
	{
		WatchdogLock(wdt->watchdogBaseAddress);
	}
	else
	{
		WatchdogUnlock(wdt->watchdogBaseAddress);
	}

	if (wdt->stallEnable == true)
	{
		WatchdogStallEnable(wdt->watchdogBaseAddress);
	}
	else
	{
		WatchdogStallDisable(wdt->watchdogBaseAddress);
	}

	if (wdt->interruptEnable)
	{
		WatchdogIntRegister(wdt->watchdogBaseAddress,wdt->pfnHandler);
	}
	else
	{
		WatchdogIntUnregister(wdt->watchdogBaseAddress);
	}


}


/*****************************************************************************
*
* Start the watchdog timer.
*
* \param wdt_base_address which chooses the watchdog timer.
*
* This function starts the watchdog timer.
*
* \return None.
******************************************************************************/
void HAL_WDT_Start(uint32_t wdt_base_address)
{
	WatchdogEnable(wdt_base_address);
}


/*****************************************************************************
*
* Start counting from the reload value.
*
* \param wdt_base_address which chooses the watchdog timer.
*
* This function set the reload value with the value assigned to it before
* Once the reload value is changes the watchdog timer will start from the
* reload value.
*
* \return None.
******************************************************************************/
void HAL_WDT_Refresh(uint32_t wdt_base_address)
{
	WatchdogReloadSet(wdt_base_address,WatchdogReloadGet(wdt_base_address));
}


/*****************************************************************************
*
* State of the watchdog timer.
*
* \param wdt_base_address which chooses the watchdog timer.
*
* This function returns the state of the watchdog if its running
* or not.
*
* \return
* \b true if the watchdog is running
* \b false if its not.
******************************************************************************/
bool HAL_WDT_State(uint32_t wdt_base_address)
{
	return WatchdogRunning(wdt_base_address);
}


/*****************************************************************************
*
* Get the reload value of the watchdog timer.
*
* \param wdt_base_address which chooses the watchdog timer.
*
* This function returns the reload value of the watchdog timer.
*
* \return \uint32_t the reload value of the watchdog timer.
******************************************************************************/
uint32_t HAL_WDT_ReloadGet(uint32_t wdt_base_address)
{
	return WatchdogReloadGet(wdt_base_address);
}


/*****************************************************************************
*
* Get the current value of the watchdog timer.
*
* \param wdt_base_address which chooses the watchdog timer.
*
* This function to return the current value of the watchdog timer.
*
* \return \uint32_t the current value of the watchdog timer.
******************************************************************************/
uint32_t HAL_WDT_ValueGet(uint32_t wdt_base_address)
{
	return WatchdogValueGet(wdt_base_address);
}
