/*
 * HAL_UART.c
 *
 * Created: 2/20/2016 3:09:12 PM
 *  Author: Mark
 */ 

#include "HAL_UART.h"
#include "USART.h"
#include "return_Errors.h"

uint16_t HAL_comm_UART_Initialize(HAL_Comm_UART_ConfigStruct_t* HAL_uartInitConfig)
{
	comm_UART_Initialize(HAL_uartInitConfig);
	return SUCCESS;
}

uint16_t HAL_comm_UART_Send(HAL_Comm_UART_HandleTypeDefStruct_t* HAL_transmitChar)
{
	comm_UART_Send(HAL_transmitChar->transmit_char);
	return SUCCESS;
}

uint16_t HAL_comm_UART_Receive(void *receiveChar)
{
	
	uint16_t temp;
	if (comm_UART_Receive(&temp))
	{
		return FAIL;
	}
	else
	{
		*(uint16_t*)receiveChar = temp;
		return SUCCESS;
	}	
}