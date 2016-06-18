/*
 * HAL_UART.c
 *
 * Created: 2/20/2016 3:09:12 PM
 *  Author: Mark
 */ 

#include "HAL_UART.h"
#include "USART.h"

void HAL_UART_Init(UART_Config* HAL_uartInitConfig)
{
	uartInit(HAL_uartInitConfig);
}

void HAL_UART_Send(UART_HandleTypeDef* HAL_transmitChar)
{
	uartSend(HAL_transmitChar->transmit_char);
}

HAL_DataType HAL_UART_Receive()
{
	return uartReceive();
}