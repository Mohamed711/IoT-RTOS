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
#ifndef HAL_UART_H_
#define HAL_UART_H_

#include "uart.h"
#include <stdint.h>

typedef struct {

	uint32_t BaseAddress;
	uint32_t BaudRate;
	uint32_t Parity;
	uint32_t stopBit;
	uint32_t Wlen;
	uint32_t clock;


}Uart_InitTypeDef;

typedef struct {
	Uart_InitTypeDef init;
	unsigned char Tx;

}Uart_HandleTypeDef;

/*****************************************************************************
*
* Prototypes for the APIs.
*
******************************************************************************/
void uartinit (Uart_InitTypeDef * uart);
void uartsend (Uart_HandleTypeDef * uart);
int32_t uartreceive (Uart_HandleTypeDef * uart);


#endif /* HAL_UART_H_ */
