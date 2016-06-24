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

#ifndef WATCHDOG_CFG_H_
#define WATCHDOG_CFG_H_

#define WDR()  __asm__ __volatile__("wdr")

/* Registers */
#define MCUCSR_Reg		*((uint8_t volatile *const)0x54)
#define WDTCR_Reg		*((uint8_t volatile *const)0x41)

/* Bit numbers */
#define WDT_En 0x3
#define WDT_TurnOFF_Enable 0x4

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