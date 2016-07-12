/*
 * Timer0.h
 *
 * Created: 9/23/2015 4:55:03 PM
 *  Author: alaa
 */ 


#ifndef TIMER0_H_
#define TIMER0_H_
#include "RTOS_Headers.h"

void Timer_Init (void);
void Timer_Wait (uint16_t cycles);
void Timer_Wait1ms (unsigned short delay);



#endif /* TIMER0_H_ */