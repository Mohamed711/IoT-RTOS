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
} HAL_Comm_UART_ConfigStruct_t;

typedef struct
{
	uint8_t transmit_char;
} HAL_Comm_UART_HandleTypeDefStruct_t;

typedef unsigned char HAL_DataType;

uint16_t HAL_comm_UART_Initialize(HAL_Comm_UART_ConfigStruct_t* HAL_uartInitConfig);
uint16_t HAL_comm_UART_Send(HAL_Comm_UART_HandleTypeDefStruct_t* HAL_transmitChar);
uint16_t HAL_comm_UART_Receive(void *receiveChar);

#endif /* HAL_UART_H_ */