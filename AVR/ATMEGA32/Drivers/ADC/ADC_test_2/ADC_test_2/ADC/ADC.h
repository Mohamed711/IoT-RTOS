

#ifndef ADC_H
#define ADC_H
#include "StdTypes.h"
#define ADC_JUSTIFY 'R' //adc justify ('L' or 'R')


extern void adc_init(void);

extern s16 ADC_u16_result(u8 channel);
#endif