/******************************************************************************
 *	OurOS V 0.0.0 - Copyright (C) 2016
 *  Computer and systems department
 *  Ain Shams University
 *
 *  All rights reserved
 *
 *  VISIT http://www.OurRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *
 *  Redistributions in binary form must reproduce the above copyright
 *  notice, this list of conditions and the following disclaimer in the
 *  documentation and/or other materials provided with the
 *  distribution.
 *****************************************************************************/
#ifndef TIMERCOUNTER0_H_
#define TIMERCOUNTER0_H_
#include <stdint.h>
#include <stdbool.h>


#define TimerOS 1

typedef void (*FnPtr)(void);

void timer0Init1ms();

uint8_t timer0Read();

void timer0Delay1ms(uint16_t millis, FnPtr timeoutFn);
void timer0Start (uint16_t millis, FnPtr timeoutFn);


uint8_t timer0ReadOVFFlag();

void trial_fn();
uint8_t timer0ReadCMPFlag();
void timer0Stop();


#endif /* TIMERCOUNTER0_H_ */