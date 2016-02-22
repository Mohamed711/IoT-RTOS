/*
 * TimerCounter0_8_bit_.c
 *
 * Created: 1/31/2016 4:26:26 PM
 *  Author: Dell Ultrabook
 */ 


#include <avr/io.h>
#include "GPIO.h"
#include "8-bit_TimerCounter0.h"

void trial_fnON()
{
	GPIO_WritePort(PC,0x01,0x01);
}

void trial_fnOFF()
{
	GPIO_WritePort(PC,0x00,0x01);
}

int main(void)
{
	GPIO_InitPortDirection(PC,0x01,0x01);
	//TimerInit();
	HAL_Timer_Init1ms();
	//HAL_Timer_Start (1000, trial_fnON);
	//trial_fnOFF();
	//HAL_Timer_Start (1000, trial_fnON);
    while(1)
    {	
		//HAL_Timer_Start(1000,trial_fnON);
		//int x=0;
		HAL_Timer_delay1ms(1000,trial_fnON);
		HAL_Timer_Init1ms(1000,trial_fnOFF);
		HAL_Timer_delay1ms(1000,trial_fnON);
		//GPIO_InitPortDirection(PC,0x2,0x02);
		//GPIO_WritePort(PC,0x00,0x01);
		//delay1ms(1000,trial_fnON);
		
		//delay1ms(1000,trial_fnON);
		//HAL_Timer_Start (1000, trial_fnON);
		//HAL_Timer_Start (1000, trial_fnOFF);
		//GPIO_WritePort(PC,0x00,0x01);
		//trial_fnOFF();
		//HAL_Timer_Start(1000,trial_fnOFF);
		//GPIO_WritePort(PC,0x01,0x01); 
		////delay_ms(1);
		//delay1ms(100);
		//GPIO_WritePort(PC,0x00,0x01);
		////delay_ms(1);
		//delay1ms(100);
    }
}


