#ifndef I2C_TEST_H_
#define I2C_TEST_H_

#include <stdint.h>

void i2cMasterInit(uint32_t baseAddress);
uint8_t i2cMasterReceive(uint32_t baseAddress, uint8_t slaveAddress);
void i2cMasterSend(uint32_t baseAddress, uint8_t slaveAddress, uint8_t data);
void i2cSlaveInit(uint32_t baseAddress, uint8_t SlaveAddr);
uint8_t i2cSlaveReceive(uint32_t baseAddress, uint8_t SlaveAddr);
void i2cSlaveSend(uint32_t baseAddress, uint8_t data, uint8_t SlaveAddr);




void I2CSendString(uint32_t slave_addr, char array[]);


void MasterSendTest();
void MasterReceiveTest();

void SlaveSendTest();
void SlaveReceiveTest();


#endif /* I2C_TEST_H_ */
