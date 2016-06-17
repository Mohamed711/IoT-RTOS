/*
 * TimerCounter0_8_bit_.c
 *
 * Created: 1/31/2016 4:26:26 PM
 *  Author: Heba Rady
 */ 


#include <avr/io.h>
#include "GPIO.h"
#include "8-bit_TimerCounter0.h"
#include "HAL_Timer_AVR.h"

void trial_fnON()
{
	GPIO_WritePort(PC,0x01,0x01);
}

void trial_fnOFF()
{
	GPIO_WritePort(PC,0x00,0x01);
}
static uint8_t state = 0x01;
void toggle ()
{
	state = state ^0x01;
	GPIO_WritePort(PC,state,0x01);
}


int main(void)
{
	
	GPIO_InitPortDirection(PC,0x01,0x01);
	
	Timer_InitTypeDef timerInit;
	Timer_HandleTypeDef timerHandle;
	timerHandle.millis = 1000;
	
	
	HAL_Timer_Init(&timerInit);
	
    while(1)
    {	
		
		timerHandle.timeoutFn = toggle;
		/*timerHandle.timeoutFn = trial_fnON;*/
		HAL_Timer_Start(&timerHandle);
		/*HAL_Timer_Delay(&timerHandle);*/
		
		
    }
}


