#include "Timer_TivaC.h"

typedef struct{

} Timer_InitTypeDef;

typedef struct{
	Timer_InitTypeDef  instance;
	uint32_t timeInMillis;
	FnPtr timeoutFn;

} Timer_HandleTypeDef;

void HAL_Timer_Init(Timer_InitTypeDef * timer);
void HAL_Timer_Start(Timer_HandleTypeDef * timer);
void HAL_Timer_Delay(Timer_HandleTypeDef * timer);
void HAL_Timer_Stop(Timer_HandleTypeDef * timer);
