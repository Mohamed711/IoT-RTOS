/*
 * TimerCounter0_8_bit_.c
 *
 * Created: 1/31/2016 4:26:26 PM
 *  Author: Dell Ultrabook
 */ 


#include <avr/io.h>
#include "GPIO.h"
#include "8-bit_TimerCounter0.h"

int main(void)
{
	GPIO_InitPortDirection(PD,0xFF,0x01);
    while(1)
    {	
		GPIO_WritePort(PD,0x01,0x01); 
		//delay_CTC_milli(100);
		//delay_us(1000000);
		delay_ms(2000);
		GPIO_WritePort(PD,0x00,0x01);
		//delay_CTC_milli(100);
		delay_ms(2000);
    }
}