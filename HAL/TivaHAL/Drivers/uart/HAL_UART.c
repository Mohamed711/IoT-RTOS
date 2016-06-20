
#include "HAL_UART.h"

void HAL_UART_Init (Uart_InitTypeDef * uart)
{
	initialize(uart->BaseAddress);
	uartConfigSetExpClk(uart->BaseAddress, uart->clock, uart->BaudRate,
	(uart->Wlen | uart->stopBit| uart->Parity));
}
void HAL_UART_Send (Uart_HandleTypeDef * uart)
{
	uartSend(uart->init.BaseAddress,uart->Tx );
}
void HAL_UART_Receive (Uart_HandleTypeDef * uart)
{
	uart->Rx=uartReceive(uart->init.BaseAddress);
}



