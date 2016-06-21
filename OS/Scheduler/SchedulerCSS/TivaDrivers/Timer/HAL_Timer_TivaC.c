#include <stdint.h>
#include <stdbool.h>
#include "HAL_Timer_TivaC.h"


void HAL_Timer_Init(Timer_InitTypeDef * timer)
{
	timerInit();
}
void HAL_Timer_Start(Timer_HandleTypeDef * timer)
{
	timerStart(timer->timeInMillis,timer->timeoutFn);
}
void HAL_Timer_Delay(Timer_HandleTypeDef * timer)
{
	timerDelay(timer->timeInMillis);
}
void HAL_Timer_Stop(Timer_HandleTypeDef * timer)
{
	timerStop();
}

void HAL_Timer_1ms(Timer_HandleTypeDef * timer)
{
	timerInit();
}
