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

#ifndef ADC_H
#define ADC_H

#include <stdbool.h>
#include <stdint.h>
#include "ADC_CFG.h"

#include <avr/interrupt.h>
#include <util/delay.h>


 

extern void adcInit(uint8_t voltage_ref_sel , bool enable_interrupt , uint8_t trigger , uint8_t channel ,uint32_t u32MaxFreq );
	
extern void adcOff(void);
extern uint16_t adcResult_u16();
extern uint8_t  adcResult_u8();
typedef struct
{
	uint32_t u32TempFreq;
	uint8_t u8RegVal;
}ADC_CLK_Rate;

extern const ADC_CLK_Rate adc_clk[PRESCALAR_NUM];


#endif