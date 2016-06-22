/*
 * HAL_UART.c
 *
 * Created: 2/20/2016 3:09:12 PM
 *  Author: Mark
 */ 

#include "HAL_UART.h"
#include "USART.h"

void HAL_UART_Init(UART_InitTypeDef* uart)
{
	uartInit(uart);
}

void HAL_UART_Send(UART_HandleTypeDef* uart)
{
	uartSend(uart->Tx);
}

void HAL_UART_Receive(UART_HandleTypeDef* uart)
{
	uart->Rx= uartReceive();
}