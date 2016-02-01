

#ifndef ADC_H
#define ADC_H
#include "StdTypes.h"
//setup values
#define ADC_REF 1 //adc reference voltage (see adc_init function for reference)
#define ADC_PRESCALER 128 //adc prescaler (2, 4, 8, 16, 32, 64, 128)
#define ADC_JUSTIFY 'R' //adc justify ('L' or 'R')
//#define ADC_TRIGGERON 0 //adc trigger (1 on - 0 off)
#define ADC_REFRES 1024 //reference resolution used for conversions

#define channel 0 

//functions
//extern void adc_setchannel(uint8_t channel);
//extern uint16_t adc_read(uint8_t channel);
//extern uint16_t adc_readsel(void);
extern void adc_init(void);
//extern double acd_getrealvref(void);
//extern long adc_getresistence(uint16_t adcread, uint16_t adcbalanceresistor);
//extern double adc_getvoltage(uint16_t adcread, double adcvref);
//extern unsigned int adc_emafilter(unsigned int newvalue, unsigned int value);
extern s16 ADC_u16_result(void);
#endif