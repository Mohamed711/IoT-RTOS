

#ifndef ADC_H
#define ADC_H

#include <stdbool.h>
#include <stdint.h>
#include "ADC_CFG.h"

#include <avr/interrupt.h>
#include <util/delay.h>


 

extern void adcInit(uint8_t voltage_ref_sel , bool enable_interrupt , uint8_t trigger , uint8_t channel ,uint32_t u32MaxFreq );
	
extern void adcOff(void);
extern uint16_t adcResult_u16();
extern uint8_t  adcResult_u8();
typedef struct
{
	uint32_t u32TempFreq;
	uint8_t u8RegVal;
}CLK_Rate;

extern const CLK_Rate clk[PRESCALAR_NUM];


#endif