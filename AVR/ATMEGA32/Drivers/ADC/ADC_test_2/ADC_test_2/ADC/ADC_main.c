/*
 * ADC_test_2.c
 *
 * Created: 31-Jan-16 7:10:09 PM
 *  Author: nada
 */ 

#include <util/delay.h>
#include <avr/io.h>
#include "ADC.h"
#include "ADC_CFG.h" 
#include "HAL_ADC_AVR.h"
int main(void)
{
	
	
	u16 result;
	DDRA &=(~(0xFF));
	
	
	
	DDRC |=0xFF;
	DDRD |=0xFF;
	
	ADC_InitTypeDef handle;
	handle.channel=0x00;
	handle.enable_interrupt= true;
	handle.trigger=0x00;
	handle.voltage_ref_sel=0x00;
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