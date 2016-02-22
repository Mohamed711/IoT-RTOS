/*
 * _8_bit_TimerCounter0.h
 *
 * Created: 1/31/2016 4:29:54 PM
 *  Author: Dell Ultrabook
 */ 


#ifndef TIMERCOUNTER0_H_
#define TIMERCOUNTER0_H_
#include <stdint.h>
#include "StdTypes.h"
//#include "HAL.h"

typedef void (*FnPtr)(void);

void HAL_Timer_Init1ms ();

u8 timer0_Read();

//void delay1ms(u16 delay);
void HAL_Timer_delay1ms(u16 delay, FnPtr delayFn);
void HAL_Timer_Start (u16 millis, FnPtr timeoutFn);

//void delay1us(u16 delay);

u8 timer0_readOVFFlag();

void trial_fn();
u8 timer0_readCMPFlag();


#endif /* TIMERCOUNTER0_H_ */