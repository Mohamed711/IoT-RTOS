
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

#define i2cmasterinit(x) masterInit(x.clock)
#define i2cslaveinit(x) slaveInit(x.SlaveAddress)
#define i2cmastersend(x) masterTransmit(x.slaveAddress ,x.Txdata)
#define i2cmasterreceive(x) masterReceive()
#define i2cslavetsend(x) slaveTransmit(x.Txdata)
#define i2cslavereceive(x) slaveReceive()

#endif /* HAL_I2C_AVR_H_ */