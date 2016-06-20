/*
 * CFile1.c
 *
 * Created: 21/2/2016 12:57:26 AM
 *  Author: Karen-pc
 */ 
#include "HAL_Watchdog_AVR.h"

void HAL_Watchdog_Init()
{
	watchdogInit();
}

void HAL_Watchdog_Enable(watchdog_EnableTypeDef * watchdogen)
{
	watchdogEnable(watchdogen->timeout2);
}

void HAL_Watchdog_Disable()
{
	
	watchdogDisable();
}

void HAL_Watchdog_Reset()
{
	watchdogReset();
}