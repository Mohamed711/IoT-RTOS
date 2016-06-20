
#ifndef I2C_CONFIG_H_
#define I2C_CONFIG_H_

#include <stdint.h>

typedef struct
{
	uint16_t ubrr;
	
} I2C_CONFIG;

extern const I2C_CONFIG I2C_initConfig;
#endif /* I2C_CONFIG_H_ */