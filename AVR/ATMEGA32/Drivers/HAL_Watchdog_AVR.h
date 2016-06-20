/*
 * HAL_Watchdog_AVR.h
 *
 * Created: 21/2/2016 12:58:18 AM
 *  Author: Karen-pc
 */ 
#include "GPIO.h"
#include "Watchdog.h"

typedef struct 
{
	uint8_t timeout2;
	} watchdog_EnableTypeDef;
	
void HAL_WDT_Enable(watchdog_EnableTypeDef * watchdogen);

void HAL_Watchdog_Init();

void HAL_Watchdog_Disable();

void HAL_Watchdog_Reset();

	