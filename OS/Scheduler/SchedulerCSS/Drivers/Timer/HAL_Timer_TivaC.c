#include <stdint.h>
#include <stdbool.h>
//#include "Timer_HAL.h"
#include "HAL_Timer_TivaC.h"


void HAL_Timer_Init(Timer_InitTypeDef * timer)
{
	Timer_Init();
}
void HAL_Timer_Start(Timer_HandleTypeDef * timer)
{
	Timer_Start(timer->timeInMillis,timer->timeoutFn);
}
void HAL_Timer_Delay(Timer_HandleTypeDef * timer)
{
	Timer_Delay(timer->timeInMillis);
}
void HAL_Timer_Stop(Timer_HandleTypeDef * timer)
{
	Timer_Stop();
}
void HAL_Timer_1ms(Timer_HandleTypeDef* timer)
{
	Timer_New(timer->timeoutFn);
}
