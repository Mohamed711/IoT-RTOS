/*
 * ADC_test_2.c
 *
 * Created: 31-Jan-16 7:10:09 PM
 *  Author: nada
 */ 

#include <util/delay.h>
#include <avr/interrupt.h>
#include "HAL_ADC_AVR.h"
int main(void)
{
	
	
	uint16_t result;
	DDRA &=(~(0xFF));
	
	
	
	DDRC |=0xFF;
	DDRD |=0xFF;
	
	ADC_InitTypeDef handle;
	handle.channel=ch_ADC0;
	handle.enable_interrupt= false;
	handle.trigger=Free_Running_mode;
	handle.voltage_ref_sel=Internal_Voltage_Reference;
	handle.u32MaxFreq=75000000UL;
	ADC_handle_typedef res;
	res.return_result=0x00;
	HAL_ADC_Init(&handle);
    while(1)
    {
      
	    
	 HAL_ADC_read(&res);
	   
	 result =res.return_result;
	 
	 PORTC =(result &0xFF);
	 PORTD =((result)>>8);
	
	
	
    }


}