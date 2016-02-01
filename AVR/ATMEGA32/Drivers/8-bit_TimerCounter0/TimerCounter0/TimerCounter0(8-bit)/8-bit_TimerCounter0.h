/*
 * _8_bit_TimerCounter0.h
 *
 * Created: 1/31/2016 4:29:54 PM
 *  Author: Dell Ultrabook
 */ 


#ifndef TIMERCOUNTER0_H_
#define TIMERCOUNTER0_H_
#include <stdint.h>

void TimerCounter0_Init (void);
void TimerCounter0_milliTimeNORMAL (uint8_t time);
uint8_t TimerCounter0_Read();
void delay_NORMAL (void);


#endif /* TIMERCOUNTER0_H_ */