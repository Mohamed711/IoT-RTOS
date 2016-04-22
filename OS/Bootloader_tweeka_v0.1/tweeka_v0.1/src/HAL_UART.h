/*
 * HAL_UART.h
 *
 * Created: 2/20/2016 3:09:34 PM
 *  Author: Mark
 */ 


#ifndef HAL_UART_H_
#define HAL_UART_H_

typedef unsigned char HAL_DataType;

void HAL_UART_Init();
void HAL_UART_Transmit(HAL_DataType transmit_char);
HAL_DataType HAL_UART_Receive();

#endif /* HAL_UART_H_ */