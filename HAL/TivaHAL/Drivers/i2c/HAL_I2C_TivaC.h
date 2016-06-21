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
#ifndef HAL_I2C_TIVAC_H_
#define HAL_I2C_TIVAC_H_

#include <stdint.h>
#include <stdbool.h>
//#include "i2c_test.h"


typedef struct {
	uint8_t slaveAddress1;
	uint32_t baseAddress;
} I2C_InitTypeDef;

typedef struct {
	I2C_InitTypeDef instance;
	uint8_t slaveAddress;
	uint8_t Txdata;
} I2C_HandleTypeDef;

/*****************************************************************************
*
* Prototypes for the APIs.
*
******************************************************************************/
void i2cmasterinit(I2C_InitTypeDef * i2c);
void i2cslaveinit(I2C_InitTypeDef * i2c);
void i2cmastersend(I2C_HandleTypeDef *i2c);
uint8_t i2cmasterreceive(I2C_HandleTypeDef *i2c);
void i2cslavesend(I2C_HandleTypeDef *i2c);
uint8_t i2cslavereceive(I2C_HandleTypeDef *i2c);



#endif /* HAL_I2C_TIVAC_H_ */
