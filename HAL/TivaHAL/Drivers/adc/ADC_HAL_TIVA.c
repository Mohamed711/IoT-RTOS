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
#include"ADC_HAL_TIVA.h"

/******************************************************************************
*
*	The function's purpose is to initialize the adc
*
*	\param i2c		pointer to structure that contains all the data needed
*					to initialize the adc
*
* 	\return none
*
*****************************************************************************/
void adcinit(ADC_InitTypeDef *adc)
{
	uint32_t ADCn_BASE;
	SysCtlPeripheralEnable(adc->ADCn); /*enabling adc periph*/

	switch(adc->ADCn)
	{
	case SYSCTL_PERIPH_ADC0 :
		ADCn_BASE = ADC0_BASE;
		break;
	case SYSCTL_PERIPH_ADC1 :
		ADCn_BASE = ADC1_BASE;
		break;
	}

	ADCSequenceConfigure(ADCn_BASE, adc->seq, adc->ADC_TRIGGER, adc->prio);

	int8_t count;
	adc->steps=4;
	switch (adc->seq)
	{
	case 0: adc->steps=8;
	break;
	case 3: adc->steps=1;
	break;

	}

	for(count=0;count<adc->steps-1 ;++count)
	{
		ADCSequenceStepConfigure(ADCn_BASE, adc->seq, count, adc->src|((1 & adc->diff)<<1));
	}

	ADCSequenceStepConfigure(ADCn_BASE,adc->seq,adc->steps-1,adc->src|ADC_CTL_IE|ADC_CTL_END|((1 & adc->diff)<<1));

	ADCSequenceEnable(ADCn_BASE, adc->seq);
}

/******************************************************************************
*
*	The function's purpose is to read the adc's return value
*
* 	\return none
*
*****************************************************************************/
uint32_t  adcread(ADC_InitTypeDef *adc)
{
	uint32_t ADCn_BASE;
	switch(adc->ADCn)
		{
		case SYSCTL_PERIPH_ADC0 :
			ADCn_BASE = ADC0_BASE;
			break;
		case SYSCTL_PERIPH_ADC1 :
			ADCn_BASE = ADC1_BASE;
			break;
		}

			ADCIntClear(ADCn_BASE,adc->seq);
			ADCProcessorTrigger(ADCn_BASE,adc->seq);

			/*maybe use interrupt*/
			while(!ADCIntStatus(ADCn_BASE, 1, 0))
			{
			}

			uint32_t *ui32ADCnValue;
			uint32_t value;
			ADCSequenceDataGet(ADCn_BASE,adc->seq, ui32ADCnValue);

			value =  (ui32ADCnValue[0] + ui32ADCnValue[1] + ui32ADCnValue[2] + ui32ADCnValue[3] + 2)/4;
			value = (1475 - ((2475 * value)) / 4096)/10;
			return value;
}

/******************************************************************************
*
*	The function's purpose is to turn off the adc
*
* 	\return none
*
*****************************************************************************/
void adcoff()
{
	/*Before using this function, it is highly recommended that the event trigger
	is changed to ADC_TRIGGER_NEVER on all enabled sequencers to prevent the ADC from
	starting after checking the busy status*/

	if(ADCBusy(ADC0_BASE)||ADCBusy(ADC1_BASE))
	{
		return false;
	}
	else
	{
		return true;
	}
}
