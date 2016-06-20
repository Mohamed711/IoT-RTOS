
#include "8-bit_TimerCounter0.h"
#include "HAL_Timer_AVR.h"

void HAL_Timer_Init(Timer_InitTypeDef * timer)
{
	timer0Init1ms();
}

void HAL_Timer_Delay(Timer_HandleTypeDef * timer)
{
	timer0Delay1ms(timer->millis, timer->timeoutFn);
}
void HAL_Timer_Start (Timer_HandleTypeDef * timer)
{
	timer0Start(timer->millis, timer->timeoutFn);
}
void HAL_Timer_Stop(Timer_HandleTypeDef * timer)
{
	timer0Stop();
}