/*
 * HAL_i2c_AVR.c
 *
 * Created: 2/20/2016 2:59:01 PM
 *  Author: sameh
 */ 

#include "HAL_i2c_AVR.h"
#include "I2C.h"
#include "I2C_slave.h"


void HAL_I2C_Init(I2C_InitTypeDef *i2c)
{
	if(i2c->type == 0)//master
	{
		i2c_init(i2c->clock);
		i2c_start();
	}
	else if(i2c->type == 1)
	{
		TWI_init_slave(i2c->SlaveAddress);
	}
}

void HAL_I2C_Master_Transmit(I2C_HandleTypeDef *i2c)
{
	//i2c_master_transmit(i2c->slaveAddress ,i2c->Txdata);
	i2c_write(i2c->slaveAddress);
	i2c_write(i2c->Txdata);
}

void HAL_I2C_Master_Receive(I2C_HandleTypeDef *i2c)
{
	i2c->Rxdata = i2c_read_NACK();	
}

void HAL_I2C_Slave_Transmit(I2C_HandleTypeDef *i2c)
{
	TWI_write_slave(i2c->Txdata);
}

void HAL_I2C_Slave_receive(I2C_HandleTypeDef *i2c)
{
	i2c->Rxdata = TWI_read_slave();
}
