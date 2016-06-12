/*
 * _8_bit_TimerCounter0.h
 *
 * Created: 1/31/2016 4:29:54 PM
 *  Author: Dell Ultrabook
 */ 


#ifndef TIMERCOUNTER0_H_
#define TIMERCOUNTER0_H_
#include <stdint.h>
#include "../../std.h"
//#include "HAL.h"

typedef void (*FnPtr)(void);

void Timer0_Init1ms ();

u8 timer0_Read();

//void delay1ms(u16 delay);
void Timer0_delay1ms(u16 millis, FnPtr timeoutFn);
void Timer0_Start (u16 millis, FnPtr timeoutFn);

//void delay1us(u16 delay);

u8 timer0_readOVFFlag();

void trial_fn();
u8 timer0_readCMPFlag();
void Timer0_stop();
void timer_new(FnPtr timeoutFn);


#endif /* TIMERCOUNTER0_H_ */