/*
 * HAL_UART.h
 *
 * Created: 2/20/2016 3:09:34 PM
 *  Author: Mark
 */ 


#ifndef HAL_UART_H_
#define HAL_UART_H_

#include "StdTypes.h"

typedef unsigned char HAL_DataType;

typedef struct
{
	u32 Baud;
	u8 DataBits;
	u8 StopBits;
	u8 Parity;
	u8 EnableInterrupt;
	u8 U2X_State;
} USART_CONFIG;

typedef struct
{
	u8 transmit_char;
}UART_HandleTypeDef;

//extern const USART_CONFIG usart_init_config;
//extern const UART_HandleTypeDef UartHandle;

void HAL_UART_Init(USART_CONFIG* HAL_usart_init_config);
void HAL_UART_Transmit(UART_HandleTypeDef* HAL_transmit_char);
HAL_DataType HAL_UART_Receive();

#endif /* HAL_UART_H_ */