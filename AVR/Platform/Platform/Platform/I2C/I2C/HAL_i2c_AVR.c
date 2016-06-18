/*
 * HAL_i2c_AVR.c
 *
 * Created: 2/20/2016 2:59:01 PM
 *  Author: sameh
 */ 
#include "HAL_i2c_AVR.h"
#include "I2C.h"


void HAL_I2C_Init(I2C_InitTypeDef *i2c)
{
	if(i2c->type == 0) /* master */
	{
		masterInit(i2c->clock);
	}
	else if(i2c->type == 1) /* slave */
	{
		slaveInit(i2c->SlaveAddress);
	}
}

void HAL_I2C_Master_Transmit(I2C_HandleTypeDef *i2c)
{
	masterTransmit(i2c->slaveAddress ,i2c->Txdata);
}

void HAL_I2C_Master_Receive(I2C_HandleTypeDef *i2c)
{
	i2c->Rxdata = masterReceive();	
}

void HAL_I2C_Slave_Transmit(I2C_HandleTypeDef *i2c)
{
	slaveTransmit(i2c->Txdata);
}

void HAL_I2C_Slave_Receive(I2C_HandleTypeDef *i2c)
{
	i2c->Rxdata = slaveReceive();
}
