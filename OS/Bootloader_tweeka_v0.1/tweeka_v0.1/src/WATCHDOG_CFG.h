/*
 * WATCHDOG_CFG.h
 *
 * Created: 2/2/2016 5:27:49 PM
 *  Author: Karen-pc
 */ 
#ifndef WATCHDOG_CFG_H_
#define WATCHDOG_CFG_H_

#define WDR()  __asm__ __volatile__("wdr")

/* Registers */
#define MCUCSR_Reg		*((u8 volatile *const)0x54)
#define WDTCR_Reg		*((u8 volatile *const)0x41)

#define WDT_En 0x08
#define WDT_TurnOFF_Enable 0x10

/* Time out */
#define WDT_16_3MS	0x00
#define WDT_32_5MS	0x01
#define WDT_65_MS	0x02
#define WDT_130MS	0x03
#define WDT_260MS	0x04
#define WDT_520MS	0x05
#define WDT_1S		0x06
#define WDT_2_1S	0x07

#endif