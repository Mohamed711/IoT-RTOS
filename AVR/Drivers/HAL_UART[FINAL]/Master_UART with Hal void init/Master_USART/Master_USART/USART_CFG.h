/*
 * USART_CFG.h
 *
 * Created: 2/5/2016 3:42:31 PM
 *  Author: Mark
 */ 


#ifndef USART_CFG_H_
#define USART_CFG_H_

#include <stdint.h>

#define UCSRA_REG	UCSRA
#define UCSRB_REG	UCSRB
#define UCSRC_REG	UCSRC
#define UBRRH_REG	UBRRH
#define UBRRL_REG	UBRRL
#define UDR_REG		UDR

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