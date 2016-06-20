#include <stdint.h>
#include <stdbool.h>
#include "HAL_Timer_TivaC.h"


void HAL_TIMER_Init(Timer_InitTypeDef * timer)
{
	timerInit();
}
void HAL_TIMER_Start(Timer_HandleTypeDef * timer)
{
	timerStart(timer->timeInMillis,timer->timeoutFn);
}
void HAL_TIMER_Delay(Timer_HandleTypeDef * timer)
{
	timerDelay(timer->timeInMillis);
}
void HAL_TIMER_Stop(Timer_HandleTypeDef * timer)
{
	timerStop();
}
