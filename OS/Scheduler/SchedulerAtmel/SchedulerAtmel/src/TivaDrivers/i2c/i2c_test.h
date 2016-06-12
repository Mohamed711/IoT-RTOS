/*
 * i2c_test.h
 *
 *  Created on: Feb 2, 2016
 *      Author: 350g1
 */

#ifndef I2C_TEST_H_
#define I2C_TEST_H_

#include <stdint.h>

void initMasterI2C(uint32_t baseAddress);
uint8_t MasterReceive(uint32_t baseAddress, uint8_t slaveAddress);
void MasterSend(uint32_t baseAddress, uint8_t slaveAddress, uint8_t data);
void initSlaveI2C(uint32_t baseAddress, uint8_t SlaveAddr);
uint8_t SlaveReceive(uint32_t baseAddress, uint8_t SlaveAddr);
void SlaveSend(uint32_t baseAddress, uint8_t data, uint8_t SlaveAddr);




void I2CSendString(uint32_t slave_addr, char array[]);


void MasterSendTest();
void MasterReceiveTest();

void SlaveSendTest();
void SlaveReceiveTest();


#endif /* I2C_TEST_H_ */
