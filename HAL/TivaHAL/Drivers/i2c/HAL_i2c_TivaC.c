#include "HAL_I2C_TivaC.h"
//#include "i2c_test.h"

void HAL_I2C_Init(I2C_InitTypeDef * i2c)
{
	if (i2c->type==0)
	{
		i2cMasterInit(i2c->baseAddress);
	}
	else if (i2c->type==1)
	{
		i2cSlaveInit (i2c->baseAddress, i2c->slaveAddress1);
	}
}
void HAL_I2C_Master_Transmit(I2C_HandleTypeDef *i2c)
{
	i2cMasterSend(i2c->instance.baseAddress, i2c->slaveAddress, i2c->Txdata);
}
void HAL_I2C_Master_Receive(I2C_HandleTypeDef *i2c)
{
	i2c->Rxdata = i2cMasterReceive(i2c->instance.baseAddress, i2c->slaveAddress);
}
void HAL_I2C_Slave_Transmit(I2C_HandleTypeDef *i2c)
{
	i2cSlaveSend(i2c->instance.baseAddress, i2c->Txdata, i2c->slaveAddress);
}
void HAL_I2C_Slave_Receive(I2C_HandleTypeDef *i2c)
{
	i2c->Rxdata = i2cSlaveReceive(i2c->instance.baseAddress, i2c->slaveAddress);
}
