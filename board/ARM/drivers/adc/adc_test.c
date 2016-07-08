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
/*
 * adc_test.c
 *
 *  Created on: Feb 7, 2016
 *      Author: Mina
 */

#include"adc_test.h"
#include <stdint.h>
#include <stdbool.h>
#include "../inc/hw_memmap.h"
#include "../inc/hw_types.h"
#include "../debug/debug.h"
#include "../sysctl/sysctl.h"
#include"adc.h"









void adctest()
{
uint32_t ui32ADC0Value[4];
volatile uint32_t ui32TempAvg;
ADC_InitTypeDef input;


input.ADCn=SYSCTL_PERIPH_ADC0;
input.seq=1;
input.ADC_TRIGGER=ADC_TRIGGER_PROCESSOR;
input.prio=0;
input.src=ADC_CTL_TS;
input.diff=0;





//settign up clock
SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);




HAL_ADC_Init(&input);

while(1)
{

HAL_ADC_read(&input);

input.ui32ADCnValue/=4;
ui32TempAvg = (1475 - ((2475 * input.ui32ADCnValue)) / 4096)/10;
}



}
