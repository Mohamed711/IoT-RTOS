

#ifndef ADC_H
#define ADC_H
#include "StdTypes.h"
//setup values
//#define ADC_REF 1 //adc reference voltage (see adc_init function for reference)
#define ADC_PRESCALER 128 //adc prescaler (2, 4, 8, 16, 32, 64, 128)
#define ADC_JUSTIFY 'R' //adc justify ('L' or 'R')

//#define ADC_REFRES 1024 //reference resolution used for conversions

//channel
#define channel_ADC0 0b00000
#define channel_ADC1 0b00001
#define channel_ADC2 0b00010
#define channel_ADC3 0b00011
#define channel_ADC4 0b00100
#define channel_ADC5 0b00101
#define channel_ADC6 0b00110
#define channel_ADC7 0b00111



extern void adc_init(void);

extern s16 ADC_u16_result(u8 channel);
#endif