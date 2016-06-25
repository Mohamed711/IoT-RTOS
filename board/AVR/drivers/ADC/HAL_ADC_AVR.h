/*
 * HAL_ADC_AVR.h
 *
 * Created: 20-Feb-16 4:07:24 PM
 *  Author: nada
 */ 


#ifndef HAL_ADC_AVR_H_
#define HAL_ADC_AVR_H_

#include "ADC.h"


#define ADC_DEFAULT_VALUES {Internal_Voltage_Reference,false,Free_Running_mode,ch_ADC0,75000000UL}


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
	uint16_t return_result;
	
}ADC_HandleTypeDef;

//void HAL_ADC_Init(ADC_InitTypeDef * adc);
//void HAL_ADC_read(ADC_HandleTypeDef *adc);
//void HAL_ADC_OFF(void);

#define ADC_Init(x) adcInit( (*x).voltage_ref_sel, (*x).enable_interrupt, (*x).trigger, (*x).channel, (*x).u32MaxFreq )
#define ADC_Read(x) adcResult_u16(   (*x).return_result );
#define ADC_Off() 	adcOff()


#endif /* HAL_ADC_AVR_H_ */