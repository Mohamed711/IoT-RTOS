
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
	
#define timerinit(x) timer0Init1ms()
#define timerdelay(x) timer0Delay1ms(x.timeInMillis, x.timeoutFn)
#define timerstart(x) timer0Start(x.timeInMillis, x.timeoutFn)
#define timerstop(x) timer0Stop()

#endif /* HAL_H_ */