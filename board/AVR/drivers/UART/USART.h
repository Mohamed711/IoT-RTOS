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

#ifndef USART_H_
#define USART_H_
#include <avr/io.h>
#include <stdint.h>
#include "HAL_UART.h"

volatile uint8_t value;

void uartInit(uint32_t Baud, uint8_t DataBits, uint8_t StopBits, uint8_t Parity, uint8_t EnableInterrupt, uint8_t U2X_State);
void uartSend(unsigned char x);
unsigned char uartReceive(void);

#endif /* USART_H_ */