/*
 * I2C_CONFIG.h
 *
 * Created: 2/4/2016 3:11:10 PM
 *  Author: sameh
 */ 

#ifndef I2C_CFG_H_
#define I2C_CFG_H_

#include "StdTypes.h"

/* TWI stands for "Two Wire Interface" or "TWI Was I2C(tm)" */
#define TWBR *((u8 volatile *const)0x20)
#define TWSR *((u8 volatile *const)0x21)
#define TWAR *((u8 volatile *const)0x22)
#define TWDR *((u8 volatile *const)0x23)
#define TWCR *((u8 volatile *const)0x56)

/* TWCR */
#define TWINT   7
#define TWEA    6
#define TWSTA   5
#define TWSTO   4
#define TWWC    3
#define TWEN    2
/* bit 1 reserved */
#define TWIE    0


/* TWAR */
#define TWA6    7
#define TWA5    6
#define TWA4    5
#define TWA3    4
#define TWA2    3
#define TWA1    2
#define TWA0    1
#define TWGCE   0

/* TWSR */
#define TWS7    7
#define TWS6    6
#define TWS5    5
#define TWS4    4
#define TWS3    3
/* bit 2 reserved */
#define TWPS1   1
#define TWPS0   0




#endif /* I2C_CFG_H_ */