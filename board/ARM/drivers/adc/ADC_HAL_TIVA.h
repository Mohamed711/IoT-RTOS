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

#ifndef DRIVERS_ADC_ADC_HAL_TIVA_H_
#define DRIVERS_ADC_ADC_HAL_TIVA_H_


typedef struct
{
	uint32_t ADCn;
	uint8_t seq;
	uint32_t ADC_TRIGGER;
	uint32_t prio;
	uint32_t steps;
	uint32_t src;
	bool diff;
}ADC_InitTypeDef;

typedef struct
{

}ADC_HandleTypeDef;

/*****************************************************************************
*
* Prototypes for the APIs.
*
******************************************************************************/
void ADC_Init(ADC_InitTypeDef *adc);
uint32_t ADC_Read(ADC_InitTypeDef *adc);
//void ADC_Off();


#endif /* DRIVERS_ADC_ADC_HAL_TIVA_H_ */
