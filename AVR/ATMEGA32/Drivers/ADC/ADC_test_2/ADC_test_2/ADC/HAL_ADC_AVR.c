


#include "HAL_ADC_AVR.h"


void HAL_ADC_read(ADC_handle_typedef * adc)
{
	adc->return_result = adcResult_u16();
}
void HAL_ADC_OFF(void)
{
	adcOff();
}

void HAL_ADC_Init(ADC_InitTypeDef *adc)
{
adcInit( adc->voltage_ref_sel , adc->enable_interrupt , adc->trigger ,  adc->channel , adc->u32MaxFreq ) ;

}


