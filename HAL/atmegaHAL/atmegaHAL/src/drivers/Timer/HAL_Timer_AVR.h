
#include "8-bit_TimerCounter0.h"


#ifndef HAL_H_
#define HAL_H_

typedef struct {
	
	
	}Timer_InitTypeDef;
	
typedef struct {
	
	Timer_InitTypeDef instance ;
	uint16_t millis; 
	FnPtr timeoutFn;

	
	}Timer_HandleTypeDef;

void HAL_Timer_Init(Timer_InitTypeDef * timer);
void HAL_Timer_Delay(Timer_HandleTypeDef * timer);
void HAL_Timer_Start (Timer_HandleTypeDef * timer);
void HAL_Timer_Stop(Timer_HandleTypeDef * timer); 



#endif /* HAL_H_ */