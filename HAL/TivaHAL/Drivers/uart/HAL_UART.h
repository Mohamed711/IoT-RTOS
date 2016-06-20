

#ifndef HAL_UART_H_
#define HAL_UART_H_
#include "uartTest.h"
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
	unsigned char Rx;
	unsigned char Tx;

}Uart_HandleTypeDef;

extern void HAL_UART_Init (Uart_InitTypeDef * uart);
extern void HAL_UART_Send (Uart_HandleTypeDef * uart);
extern void HAL_UART_Receive (Uart_HandleTypeDef * uart);


#endif /* HAL_UART_H_ */
