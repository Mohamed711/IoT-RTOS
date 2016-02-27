/*
 * HAL.h
 *
 * Created: 20-Feb-16 4:36:05 PM
 *  Author: Dell Ultrabook
 */ 
#include "8-bit_TimerCounter0.h"


#ifndef HAL_H_
#define HAL_H_

typedef struct {
	
	
	}Timer_InitTypeDef;
	
typedef struct {
	
	Timer_InitTypeDef instance ;
	u16 millis; 
	FnPtr timeoutFn;

	
	}Timer_HandleTypeDef;

void HAL_Timer_Init(Timer_InitTypeDef * timer);
void HAL_Timer_Delay(Timer_HandleTypeDef * timer);
void HAL_Timer_Start (Timer_HandleTypeDef * timer);
void HAL_Timer_stop(Timer_HandleTypeDef * timer); 



#endif /* HAL_H_ */