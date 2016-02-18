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
	GPIO_InitPortDirection(PC,0x01,0x01);
	TimerInit();
    while(1)
    {	
		GPIO_WritePort(PC,0x01,0x01); 
		//delay_ms(1);
		delay1ms(100);
		GPIO_WritePort(PC,0x00,0x01);
		//delay_ms(1);
		delay1ms(100);
    }
}