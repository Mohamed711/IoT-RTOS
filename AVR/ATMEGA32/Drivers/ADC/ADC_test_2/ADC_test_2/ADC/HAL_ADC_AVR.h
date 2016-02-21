/*
 * HAL_ADC_AVR.h
 *
 * Created: 20-Feb-16 4:07:24 PM
 *  Author: nada
 */ 


#ifndef HAL_ADC_AVR_H_
#define HAL_ADC_AVR_H_
#include "StdTypes.h"
#include "ADC_CFG.h"
#include "ADC.h"
typedef struct
{
	u8 voltage_ref_sel ;
	u8 channel;
	u8 trigger;
    u8 enable_interrupt;
	u32 u32MaxFreq;
	
}ADC_InitTypeDef;

typedef struct
{
	u16 return_result;
	
}ADC_handle_typedef;



void HAL_ADC_Init(ADC_InitTypeDef * adc);
void HAL_ADC_read(ADC_handle_typedef *adc);
//void HAL_ADC_OFF(void);

#endif /* HAL_ADC_AVR_H_ */