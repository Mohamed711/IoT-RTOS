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


void TimerInit (void);

u8 timer0_Read();

void delay1ms(u16 delay);

//void delay1us(u16 delay);

u8 timer0_readOVFFlag();

u8 timer0_readCMPFlag();


#endif /* TIMERCOUNTER0_H_ */