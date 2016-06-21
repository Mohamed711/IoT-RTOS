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
#ifndef HAL_I2C_AVR_H_
#define HAL_I2C_AVR_H_
#include <stdint.h>
#include <stdbool.h>

typedef struct
{
	uint16_t clock;
	uint8_t SlaveAddress;	
	} I2C_InitTypeDef ;

typedef struct
{
	uint8_t slaveAddress;
	uint8_t Txdata;
	} I2C_HandleTypeDef;

#define i2cmasterinit(x) masterInit((*x).clock)
#define i2cslaveinit(x) slaveInit((*x).SlaveAddress)
#define i2cmastersend(x)  masterTransmit((*x).slaveAddress ,(*x).Txdata)
#define i2cmasterreceive(x)  masterReceive(); 
#define i2cslavetsend(x)  slaveTransmit((*x).Txdata)
#define i2cslavereceive(x)  slaveReceive(); 

#endif /* HAL_I2C_AVR_H_ */