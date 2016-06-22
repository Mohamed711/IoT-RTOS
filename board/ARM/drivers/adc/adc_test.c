/*
 * adc_test.c
 *
 *  Created on: Feb 7, 2016
 *      Author: Mina
 */

#include"adc_test.h"
#include <stdint.h>
#include <stdbool.h>
#include "../inc/hw_memmap.h"
#include "../inc/hw_types.h"
#include "../debug/debug.h"
#include "../sysctl/sysctl.h"
#include"adc.h"

void adctest()
{
uint32_t ui32ADC0Value[4];
volatile uint32_t ui32TempAvg;

//settign up clock
SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);

//choosing adc0
SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);

//sampling rate ,priorty
ADCSequenceConfigure(ADC0_BASE, 1, ADC_TRIGGER_PROCESSOR, 0);
ADCSequenceStepConfigure(ADC0_BASE, 1, 0, ADC_CTL_TS);
ADCSequenceStepConfigure(ADC0_BASE, 1, 1, ADC_CTL_TS);
ADCSequenceStepConfigure(ADC0_BASE, 1, 2, ADC_CTL_TS);
ADCSequenceStepConfigure(ADC0_BASE,1,3,ADC_CTL_TS|ADC_CTL_IE|ADC_CTL_END);

//enabling
ADCSequenceEnable(ADC0_BASE, 1);


while(1)
{
ADCIntClear(ADC0_BASE, 1);
ADCProcessorTrigger(ADC0_BASE, 1);

//busy waiting
while(!ADCIntStatus(ADC0_BASE, 1, false))
{
}

ADCSequenceDataGet(ADC0_BASE, 1, ui32ADC0Value);

ui32TempAvg = (ui32ADC0Value[0] + ui32ADC0Value[1] + ui32ADC0Value[2] + ui32ADC0Value[3] + 2)/4;
ui32TempAvg = (1475 - ((2475 * ui32TempAvg)) / 4096)/10;

}



}
