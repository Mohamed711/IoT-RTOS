

#ifndef ADC_H
#define ADC_H
#include "StdTypes.h"
#include <stdbool.h>
#include "GPIO.h"
#include "ADC_Lcfg.h"
#include "ADC_CFG.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define ADC_JUSTIFY 'R' //adc justify ('L' or 'R') L for only 8 bit precision 
//#define enable_interrupt 

extern void adc_init(u8 voltage_ref_sel , u8 enable_interrupt , u8 trigger , u8 channel ,u32 u32MaxFreq );
	
extern void adc_off(void);
extern u16 ADC_u16_result();
extern u8  ADC_u8_result();

#endif