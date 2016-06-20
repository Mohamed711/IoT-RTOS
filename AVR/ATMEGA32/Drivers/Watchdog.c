/*
 * WATCHDOG.c
 *
 * Created: 2/2/2016 5:25:38 PM
 *  Author: Karen-pc
 */ 
#include "Watchdog.h"
#include "Watchdog_cfg.h"
#include <avr/interrupt.h>
#include <avr/io.h>

/********************************
*disables watchdog after a reset
********************************/
void watchdogInit(void)
{
	MCUCSR_Reg = 0;
	watchdogDisable();
	return;
}
/*************************************************
* Enable watchdog timer and set the timeout value 
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

/* reset watchdog */
void watchdogReset()
{
	WDR();
}

/*******************************************************
* disable watchdog by Writing logical one to WDCE and WDE
********************************************************/
void watchdogDisable()
{   
	watchdogReset(); 
	WDTCR_Reg |= ( 1 << WDT_En) | ( 1 << WDT_TurnOFF_Enable) ;
	WDTCR_Reg = 0x00;
}