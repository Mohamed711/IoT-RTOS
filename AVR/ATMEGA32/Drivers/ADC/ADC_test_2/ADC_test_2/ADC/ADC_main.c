/*
 * ADC_test_2.c
 *
 * Created: 31-Jan-16 7:10:09 PM
 *  Author: nada
 */ 


#include <avr/io.h>
#include "ADC.h"
#include "ADC_CFG.h" 

int main(void)
{
	u16 result;
	DDRA &=(~(1<<PA0));
	DDRC |=0xFF;
	DDRD |=0xFF;
	
    while(1)
    {
		
       adc_init() ;
	   result=  ADC_u8_result();
		 
	 
	 PORTC =(result&0xFF);
	 PORTD =((result)>>8);
	 u16 i;
	 for(i=0;i<10;i++)
	 {
	 for(i=0;i<100;i++){;}
	 
     }
	
	
}
adc_off();

	}