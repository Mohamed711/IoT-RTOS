/*
 * HAL_i2c_AVR.h
 *
 * Created: 2/20/2016 2:59:24 PM
 *  Author: sameh
 */ 

#ifndef HAL_I2C_AVR_H_
#define HAL_I2C_AVR_H_
//#include "StdTypes.h"
#include <stdint.h>
#include <stdbool.h>

typedef struct
{
	bool type; /* if type = 0 -> Master , if type =1 -> Slave */
	uint16_t clock;
	uint8_t SlaveAddress;	
	} I2C_InitTypeDef ;

typedef struct
{
	uint8_t slaveAddress;
	uint8_t Txdata;
	uint8_t Rxdata;
	} I2C_HandleTypeDef;


void HAL_I2C_Init(I2C_InitTypeDef *i2c);
void HAL_I2C_Master_Transmit(I2C_HandleTypeDef *i2c);
uint8_t  HAL_I2C_Master_Receive(I2C_HandleTypeDef *i2c);
void HAL_I2C_Slave_Transmit(I2C_HandleTypeDef *i2c);
uint8_t  HAL_I2C_Slave_Receive(I2C_HandleTypeDef *i2c);//


#endif /* HAL_I2C_AVR_H_ */