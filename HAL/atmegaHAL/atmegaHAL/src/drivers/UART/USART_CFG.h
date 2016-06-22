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

#ifndef USART_CFG_H_
#define USART_CFG_H_

#include <stdint.h>

#define UCSRA_REG *((uint8_t volatile *const)0x2B)
#define UCSRB_REG *((uint8_t volatile *const)0x2A)
#define UCSRC_REG *((uint8_t volatile *const)0x40)
#define UBRRH_REG *((uint8_t volatile *const)0x40)
#define UBRRL_REG *((uint8_t volatile *const)0x29)
#define UDR_REG   *((uint8_t volatile *const)0x2C)

#define UCSRC_SELECT	0x80
#define UBRR_SELECT	0x00

#define DATA_BIT_5	0x00
#define DATA_BIT_6	0x02
#define DATA_BIT_7	0x04
#define DATA_BIT_8	0x06

#define STOP_BIT_1	0x00
#define STOP_BIT_2	0x08

#define UDR_ENABLE	0x20
#define	RXC_RECEIVE_COMPLETE	0x80

#define PARITY_DISABLE	0x00
#define PARITY_EVEN	0x20
#define PARITY_ODD	0x30

#define U2X_ENABLE 0x02
#define U2X_DISABLE 0x00

#endif /* USART_CFG_H_ */