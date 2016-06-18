/*
 * I2C_CONFIG.h
 *
 * Created: 2/4/2016 3:11:10 PM
 *  Author: sameh
 */ 

#ifndef I2C_CONFIG_H_
#define I2C_CONFIG_H_

#include "StdTypes.h"

typedef struct
{
	u16 ubrr;
	
} I2C_CONFIG;

extern const I2C_CONFIG I2C_initConfig;
#endif /* I2C_CONFIG_H_ */