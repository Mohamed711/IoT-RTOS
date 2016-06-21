
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

ADC_InitTypeDef *adcy;
ADC_HandleTypeDef *adcz;

#define adcinit(x) adcy = x; adcInit( adcy->voltage_ref_sel , adcy->enable_interrupt , adcy->trigger ,  adcy->channel , adcy->u32MaxFreq)
#define adcread(x)  adcResult_u16(); adcz = x
#define adcoff() adcOff()

#endif /* HAL_ADC_AVR_H_ */