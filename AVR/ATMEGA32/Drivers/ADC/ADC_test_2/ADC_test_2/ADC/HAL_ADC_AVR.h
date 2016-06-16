/*
 * HAL_ADC_AVR.h
 *
 * Created: 20-Feb-16 4:07:24 PM
 *  Author: nada
 */ 


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
	uint16_t return_result;
	
}ADC_handle_typedef;

void HAL_ADC_Init(ADC_InitTypeDef * adc);
void HAL_ADC_read(ADC_handle_typedef *adc);
void HAL_ADC_OFF(void);

#endif /* HAL_ADC_AVR_H_ */