
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

I2C_InitTypeDef *i2cy;
I2C_HandleTypeDef *i2cz;

#define i2cmasterinit(x) i2cy = x; masterInit(i2cy->clock)
#define i2cslaveinit(x) i2cy = x; slaveInit(i2cy->SlaveAddress)
#define i2cmastersend(x) i2cz = x; masterTransmit(i2cz->slaveAddress ,i2cz->Txdata)
#define i2cmasterreceive(x)  masterReceive(); i2cz = x
#define i2cslavetsend(x) i2cz = x; slaveTransmit(i2cz->Txdata)
#define i2cslavereceive(x)  slaveReceive(); i2cz = x

#endif /* HAL_I2C_AVR_H_ */