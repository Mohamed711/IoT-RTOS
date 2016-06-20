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
/*****************************************************************************
*
* Enable the watchdog timer clock.
*
******************************************************************************/
#define HAL_WDT_CLK_ENABLE()	(SYSCTL_RCGCWD_R |= 0x01)


/*****************************************************************************
*
* Parameters to be passed for the initialization of the watchdog timer.
*
******************************************************************************/
typedef struct WDT_PARAMS
{
	uint32_t watchdogBaseAddress;
	uint32_t reloadValue;
	bool stallEnable;
	bool lock;
	bool resetEnable;
	bool interruptEnable;
	uint32_t interruptType;
	void (*pfnHandler)(void);
}WDT_HandleTypeDef;

/*****************************************************************************
*
* Prototypes for the APIs.
*
******************************************************************************/

void HAL_WDT_Init(WDT_HandleTypeDef * wdt);
void HAL_WDT_Start(uint32_t wdt_base_address);
void HAL_WDT_Refresh(uint32_t wdt_base_address);
bool HAL_WDT_State(uint32_t wdt_base_address);
uint32_t HAL_WDT_ReloadGet(uint32_t wdt_base_address);
uint32_t HAL_WDT_ValueGet(uint32_t wdt_base_address);


