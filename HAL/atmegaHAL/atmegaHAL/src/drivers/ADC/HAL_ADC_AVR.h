
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
	
}ADC_handle_typedef;

#define adcinit(x) adcInit( x.voltage_ref_sel , x.enable_interrupt , x.trigger ,  x.channel , x.u32MaxFreq)
#define adcread(x) adcResult_u16()
#define adcoff() adcOff()

#endif /* HAL_ADC_AVR_H_ */