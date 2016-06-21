/******************************************************************************
 *	OurOS V 0.0.0 - Copyright (C) 2016
 *  Computer and systems department
 *  Ain Shams University
 *
 *  All rights reserved
 *
 *  VISIT http://www.OurRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *
 *  Redistributions in binary form must reproduce the above copyright
 *  notice, this list of conditions and the following disclaimer in the
 *  documentation and/or other materials provided with the
 *  distribution.
 *****************************************************************************/


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