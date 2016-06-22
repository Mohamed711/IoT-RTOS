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
#ifndef HAL_ADC_AVR_H_
#define HAL_ADC_AVR_H_

#include "ADC.h"

typedef struct
{
	uint8_t voltage_ref_sel ;
	uint8_t channel;
	uint8_t trigger;
    bool enable_interrupt;
	uint32_t u32MaxFreq;
	
}ADC_InitTypeDef;

typedef struct
{
	
}ADC_HandleTypeDef;

#define ADC_Init(x) adcInit( (*x).voltage_ref_sel, (*x).enable_interrupt, (*x).trigger, (*x).channel, (*x).u32MaxFreq )
#define ADC_Read(x) adcResult_u16();
#define ADC_Off() 	adcOff()

#endif /* HAL_ADC_AVR_H_ */
