/*
 * HAL_Watchdog_AVR.h
 *
 * Created: 21/2/2016 12:58:18 AM
 *  Author: Karen-pc
 */ 
#include "../GPIO/GPIO.h"
#include "Watchdog.h"

typedef struct 
{
	uint8_t timeout2;
	} WDT_InitTypeDef;
	
void HAL_WDT_Enable(WDT_InitTypeDef * watchdogen);

void HAL_Watchdog_Init();

void HAL_Watchdog_Disable();

void HAL_Watchdog_Reset();

	