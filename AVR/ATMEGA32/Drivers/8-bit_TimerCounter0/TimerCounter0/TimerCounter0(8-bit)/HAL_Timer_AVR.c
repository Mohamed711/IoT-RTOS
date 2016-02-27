/*
 * Timer_HAL_AVR.c
 *
 * Created: 27-Feb-16 5:22:19 PM
 *  Author: Dell Ultrabook
 */ 

#include "8-bit_TimerCounter0.h"
#include "HAL_Timer_AVR.h"

void HAL_Timer_Init(Timer_InitTypeDef * timer)
{
	Timer0_Init1ms();
}

void HAL_Timer_Delay(Timer_HandleTypeDef * timer)
{
	Timer0_delay1ms(timer->millis, timer->timeoutFn);
}
void HAL_Timer_Start (Timer_HandleTypeDef * timer)
{
	Timer0_Start(timer->millis, timer->timeoutFn);
}
void HAL_Timer_stop(Timer_HandleTypeDef * timer)
{
	Timer0_stop();
}