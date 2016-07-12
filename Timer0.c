/*
 * Timer0.c
 *
 * Created: 9/23/2015 4:55:03 PM
 *  Author: alaa
 */ 

#include <avr/io.h>
#include "Timer0.h"

// ATmega32 at 8MHz
// Initialize TCNT to 1us
// Input: none
// Output: none
void Timer_Init (void){
	TCCR2 = 0x02;	// Normal Mode, Set pre-scaler at 8
}

// Input: delay time in 1us units
// Output: none
void Timer_Wait (uint16_t cycles) {
	TCNT2 = 0;
	uint16_t i;
	for (i = 0 ; i < (cycles / 256) ; i++)
		while (TCNT2 < 255)
			;
	while (TCNT2 <= cycles % 256)
		;
}

// Input: delay time in 1ms units
// Output: none
void Timer_Wait1ms (unsigned short delay){
	unsigned long i;	for (i = 0; i < (4 * delay); i++)		Timer_Wait(250);}

