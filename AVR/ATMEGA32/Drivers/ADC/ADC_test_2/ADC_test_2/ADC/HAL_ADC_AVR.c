/*
 * HAL_ADC_AVR.c
 *
 * Created: 20-Feb-16 4:17:07 PM
 *  Author: nada
 */ 



#include "HAL_ADC_AVR.h"


void HAL_ADC_read(ADC_handle_typedef * adc)
{
	adc->return_result = ADC_u16_result();
}
//void HAL_ADC_OFF(void);

void HAL_ADC_Init(ADC_InitTypeDef *adc)
{
adc_init( adc->voltage_ref_sel , adc->enable_interrupt , adc->trigger ,  adc->channel , adc->u32MaxFreq ) ;

}


