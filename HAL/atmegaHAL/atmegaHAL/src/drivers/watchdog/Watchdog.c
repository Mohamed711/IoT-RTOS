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

#include "Watchdog.h"
#include "Watchdog_cfg.h"
#include <avr/interrupt.h>
#include <avr/io.h>

/********************************
*	disables watchdog after a reset
*
*	\return none
********************************/
void watchdogInit(void)
{
	MCUCSR_Reg = 0;
	watchdogDisable();
	return;
}
/*************************************************
*	Enable watchdog timer and set the timeout value 
*
*	\return none
*************************************************/
void watchdogEnable(uint8_t Timeout)
{
	/* disable interrupts */
	cli();
	WDTCR_Reg =	0x00;
	WDTCR_Reg |=  Timeout;
	WDTCR_Reg = ( 1 << WDT_En);
	/* Enable global interrupts */
	sei();
}

/*******************************************************
*	reset the watchdog
*
*	\return none
********************************************************/
void watchdogReset()
{
	WDR();
}

/*******************************************************
*	disable watchdog by Writing logical one to WDCE and WDE
*
*	\return none
********************************************************/
void watchdogDisable()
{   
	watchdogReset(); 
	WDTCR_Reg |= ( 1 << WDT_En) | ( 1 << WDT_TurnOFF_Enable) ;
	WDTCR_Reg = 0x00;
}