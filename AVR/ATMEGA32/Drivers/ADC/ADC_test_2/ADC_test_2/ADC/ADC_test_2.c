/*
 * ADC_test_2.c
 *
 * Created: 31-Jan-16 7:10:09 PM
 *  Author: nada
 */ 


#include <avr/io.h>
#include "ADC.h"

int main(void)
{
	u16 result;
	DDRA &=(~(1<<PA0));
	DDRC |=0xFF;
	
    while(1)
    {
       adc_init() ;
	 result=  ADC_u16_result();
	 PORTC =result;
    }
}