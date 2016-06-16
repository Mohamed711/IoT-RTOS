/*
 * ADC_test_2.c
 *
 * Created: 31-Jan-16 7:10:09 PM
 *  Author: nada
 */ 

#include <util/delay.h>

#include "ADC.h"
#include "ADC_CFG.h" 
#include "HAL_ADC_AVR.h"
int main(void)
{
	
	
	uint16_t result;
	DDRA &=(~(0xFF));
	
	
	
	DDRC |=0xFF;
	DDRD |=0xFF;
	
	ADC_InitTypeDef handle;
	handle.channel=ch_ADC0;
	handle.enable_interrupt= true;
	handle.trigger=Free_Running_mode;
	handle.voltage_ref_sel=Internal_2_dot_56V_Voltage_Reference_with_external_cap_at_AREF_pin;
	handle.u32MaxFreq=75000000UL;
	ADC_handle_typedef res;
	res.return_result=0x00;
    while(1)
    {
      
	    HAL_ADC_Init(&handle);
	    HAL_ADC_read(&res);
	   
	    result =res.return_result;
	 
	 PORTC =(result &0xFF);
	 PORTD =((result)>>8);
	
	//_delay_ms(10000);
	
	//PORTD |=0xF0;

	//_delay_ms(10000);
	
}


	}