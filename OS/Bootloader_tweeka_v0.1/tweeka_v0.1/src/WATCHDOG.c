/*
 * WATCHDOG.c
 *
 * Created: 2/2/2016 5:25:38 PM
 *  Author: Karen-pc
 */ 
#include "WATCHDOG.h"
#include "WATCHDOG_CFG.h"

#include <avr/wdt.h>
#include <avr/io.h>

void WDT_Enable(u8 Timeout)
{
	//DIO_InitPortDirection(PC,0xF0,0xF0);
	//DIO_WritePort(PC, 0xF0,0xF0);
	WDTCR_Reg =	0x00;
	WDTCR_Reg |= Timeout;
	WDTCR_Reg = ( 1 << WDT_En);
	
}


void WDT_Disable()
{
	WDR();
	WDTCR_Reg = ( 1 << WDT_En) | ( 1 << WDT_TurnOFF_Enable) ;
	WDTCR_Reg = 0x00;
}