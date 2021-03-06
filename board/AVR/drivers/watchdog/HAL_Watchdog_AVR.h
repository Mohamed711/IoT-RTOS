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
#include "../GPIO/GPIO.h"
#include "Watchdog.h"
#include "../../../../User_Config.h"

typedef struct 
{
	uint8_t timeout2;
}WDT_InitTypeDef;
	

/*****************************************************************************
*
* Prototypes for the APIs.
*
******************************************************************************/
#if (FAST_HAL == 1)
	#define WDT_Enable(watchdogen)	watchdogEnable(*(watchdogen).timeout2);
	#define WDT_Init()			watchdogInit()
	#define WDT_Disable()		watchdogDisable()
	#define WDT_Reset()			watchdogReset()
#else
	void WDT_Enable(WDT_InitTypeDef * watchdogen);
	void WDT_Init();
	void WDT_Disable();
	void WDT_Reset();
#endif
	
