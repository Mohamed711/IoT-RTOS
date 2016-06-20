#ifndef HAL_I2C_TIVAC_H_
#define HAL_I2C_TIVAC_H_

#include <stdint.h>
#include <stdbool.h>
#include "i2c_test.h"


typedef struct {
	bool type;		//if type = 0  -> master
	uint8_t slaveAddress1;
	uint8_t slaveAddress2;
	uint16_t clockRate;
	uint32_t baseAddress;
} I2C_InitTypeDef;

typedef struct {
	I2C_InitTypeDef instance;
	uint8_t slaveAddress;
	uint8_t Txdata;
	uint8_t Rxdata;
} I2C_HandleTypeDef;

void HAL_I2C_Init(I2C_InitTypeDef * i2c);
void HAL_I2C_Master_Transmit(I2C_HandleTypeDef *i2c);
void HAL_I2C_Master_Receive(I2C_HandleTypeDef *i2c);
void HAL_I2C_Slave_Transmit(I2C_HandleTypeDef *i2c);
void HAL_I2C_Slave_Receive(I2C_HandleTypeDef *i2c);



#endif /* HAL_I2C_TIVAC_H_ */
