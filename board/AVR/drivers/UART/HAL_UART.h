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

#include <stdint.h>
#include "USART_CFG.h"
#include "USART.h"

#define F_CPU 8000000ul

/************************************************************************
* Set the Baud Rate, number of data bits, number of stop bits,
* parity state, Interrupt state, speed state if normal or double speed
************************************************************************/
typedef struct
{
	uint32_t Baud;
	uint8_t DataBits;
	uint8_t StopBits;
	uint8_t Parity;
	uint8_t EnableInterrupt;
	uint8_t U2X_State;
} UART_InitTypeDef;

typedef struct
{
	uint8_t Tx;
	uint8_t Rx;

} UART_HandleTypeDef;

typedef unsigned char HAL_DataType;

#define uartinit(x) uartInit((*x).Baud, (*x).DataBits, (*x).StopBits, (*x).Parity,(*x).EnableInterrupt,(*x).U2X_State)
#define uartsend(x) uartSend((*x).Tx)
#define uartreceive(x)  uartReceive()

#endif /* HAL_UART_H_ */