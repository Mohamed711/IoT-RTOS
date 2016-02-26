/*
 * i2c_test.h
 *
 *  Created on: Feb 2, 2016
 *      Author: 350g1
 */

#ifndef I2C_TEST_H_
#define I2C_TEST_H_

#include <stdint.h>

void initI2C0(void);
uint8_t readI2C0(uint16_t device_address, uint16_t device_register);
void writeI2C0(uint16_t device_address, uint8_t device_data);

void I2CSendString(uint32_t slave_addr, char array[]);



#endif /* I2C_TEST_H_ */
