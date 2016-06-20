/*
 * HAL_UART.h
 *
 * Created: 2/20/2016 3:09:34 PM
 *  Author: Mark
 */ 


#ifndef HAL_UART_H_
#define HAL_UART_H_

#include <stdint.h>
#include "USART_CFG.h"

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

void HAL_UART_Init(UART_InitTypeDef* uart);
void HAL_UART_Send(UART_HandleTypeDef* uart);
void HAL_UART_Receive(UART_HandleTypeDef* uart);

#endif /* HAL_UART_H_ */