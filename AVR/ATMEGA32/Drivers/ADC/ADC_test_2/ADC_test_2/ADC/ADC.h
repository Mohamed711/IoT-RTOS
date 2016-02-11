

#ifndef ADC_H
#define ADC_H
#include "StdTypes.h"
#define ADC_JUSTIFY 'L' //adc justify ('L' or 'R') L for only 8 bit precision 


extern void adc_init(void);
extern void adc_off(void);
extern u16 ADC_u16_result();
extern u8  ADC_u8_result();
#endif