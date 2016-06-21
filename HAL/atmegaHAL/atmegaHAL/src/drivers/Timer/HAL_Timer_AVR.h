
#include "8-bit_TimerCounter0.h"


#ifndef HAL_H_
#define HAL_H_

typedef struct {
	
	
	}Timer_InitTypeDef;
	
typedef struct {
	
	Timer_InitTypeDef instance ;
	uint16_t timeInMillis; 
	FnPtr timeoutFn;

	
	}Timer_HandleTypeDef;
	
Timer_InitTypeDef *timery;
Timer_HandleTypeDef *timerz;
	
#define timerinit(x) timery = x; timer0Init1ms()
#define timerdelay(x) timerz = x; timer0Delay1ms(timerz->timeInMillis, timerz->timeoutFn)
#define timerstart(x) timerz = x; timer0Start(timerz->timeInMillis, timerz->timeoutFn)
#define timerstop(x) timerz = x; timer0Stop()

#endif /* HAL_H_ */