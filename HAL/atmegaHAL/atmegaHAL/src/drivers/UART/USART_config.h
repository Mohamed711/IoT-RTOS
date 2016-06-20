/*
 * USART_config.h
 *
 * Created: 2/4/2016 2:49:13 PM
 *  Author: Mark
 */ 


#ifndef USART_CONFIG_H_
#define USART_CONFIG_H_

#include <stdint.h>

void uartDisable();
void uartDisableRx();
void uartDisableTx();
void uartEnable();
void uartEnableRx();
void uartEnableTx();
void uartDisableInterrupt();
void uartEnableInterrupt();
void uartEnableInterruptRx();

#endif /* USART_CONFIG_H_ */