/******************************************************************************
*	OurOS V 0.0.0 - Copyright (C) 2016
*  Computer and systems department
*  Ain Shams University
*
*  All rights reserved
*
*  VISIT http://www.OurRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*  Redistributions of source code must retain the above copyright
*  notice, this list of conditions and the following disclaimer.
*
*  Redistributions in binary form must reproduce the above copyright
*  notice, this list of conditions and the following disclaimer in the
*  documentation and/or other materials provided with the
*  distribution.
*****************************************************************************/

#include "HAL_I2C_TivaC.h"
#include <stdint.h>
#include <stdbool.h>
#include "i2c.h"

#include "../inc/hw_i2c.h"
#include "../inc/hw_memmap.h"
#include "../inc/hw_types.h"
#include "../inc/hw_gpio.h"

#include "../sysctl/sysctl.h"
#include "../gpio/gpio.h"
#include "../pin_map/pin_map.h"
#include "../uart/uart.h"

/******************************************************************************
*
*	The function's purpose is to initialize the i2c as a master
*
*	\param i2c		pointer to structure that contains all the data needed
*					to initialize the i2c as a master
*
* 	\return none
*
*****************************************************************************/
void i2cmasterinit(I2C_InitTypeDef * i2c)
{
	uint32_t baseAddress = i2c->baseAddress;

	if (baseAddress == I2C0_BASE)
	{
		/*enable I2C module*/
		SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);

		/*reset I2C module*/
		SysCtlPeripheralReset(SYSCTL_PERIPH_I2C0);

		/*enable GPIO peripheral that contains I2C*/
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

		/*Configure the pin muxing for I2C0 functions on port B2 and B3.*/
		GPIOPinConfigure(GPIO_PB2_I2C0SCL);
		GPIOPinConfigure(GPIO_PB3_I2C0SDA);

		/*Select the I2C function for these pins.*/
		GPIOPinTypeI2CSCL(GPIO_PORTB_BASE, GPIO_PIN_2);
		GPIOPinTypeI2C(GPIO_PORTB_BASE, GPIO_PIN_3);

		/*Enable and initialize the I2C0 master module.  Use the system clock for
		the I2C0 module.  The last parameter sets the I2C data transfer rate.
		If false the data rate is set to 100kbps and if true the data rate will
		be set to 400kbps.*/
			I2CMasterInitExpClk(I2C0_BASE, SysCtlClockGet(), false);

		/*clear I2C FIFOs*/
		HWREG(I2C0_BASE + I2C_O_FIFOCTL) = 80008000;
	}

	else if (baseAddress == I2C1_BASE)
	{
		/*enable I2C module*/
		SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C1);

		/*reset I2C module*/
		SysCtlPeripheralReset(SYSCTL_PERIPH_I2C1);

		/*enable GPIO peripheral that contains I2C*/
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

		/*Configure the pin muxing for I2C0 functions on port B2 and B3.*/
		GPIOPinConfigure(GPIO_PA6_I2C1SCL);
		GPIOPinConfigure(GPIO_PA7_I2C1SDA);

		/*Select the I2C function for these pins.*/
		GPIOPinTypeI2CSCL(GPIO_PORTA_BASE, GPIO_PIN_6);
		GPIOPinTypeI2C(GPIO_PORTA_BASE, GPIO_PIN_7);

		/*Enable and initialize the I2C0 master module.  Use the system clock for
		the I2C0 module.  The last parameter sets the I2C data transfer rate.
		If false the data rate is set to 100kbps and if true the data rate will
		be set to 400kbps.*/
		I2CMasterInitExpClk(I2C1_BASE, SysCtlClockGet(), false);

		/*clear I2C FIFOs*/
		HWREG(I2C1_BASE + I2C_O_FIFOCTL) = 80008000;
	}


	else if (baseAddress == I2C2_BASE)
	{
		/*enable I2C module*/
		SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C2);

		/*reset I2C module*/
		SysCtlPeripheralReset(SYSCTL_PERIPH_I2C2);

		/*enable GPIO peripheral that contains I2C*/
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);

		/*Configure the pin muxing for I2C0 functions on port B2 and B3.*/
		GPIOPinConfigure(GPIO_PE4_I2C2SCL);
		GPIOPinConfigure(GPIO_PE5_I2C2SDA);

		/*Select the I2C function for these pins.*/
		GPIOPinTypeI2CSCL(GPIO_PORTE_BASE, GPIO_PIN_4);
		GPIOPinTypeI2C(GPIO_PORTE_BASE, GPIO_PIN_5);

		/*Enable and initialize the I2C0 master module.  Use the system clock for
		the I2C0 module.  The last parameter sets the I2C data transfer rate.
		If false the data rate is set to 100kbps and if true the data rate will
		be set to 400kbps.*/
		I2CMasterInitExpClk(I2C2_BASE, SysCtlClockGet(), false);

		/*clear I2C FIFOs*/
		HWREG(I2C2_BASE + I2C_O_FIFOCTL) = 80008000;
	}


	else if (baseAddress == I2C3_BASE)
	{
		/*enable I2C module*/
		SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C3);

		/*reset I2C module*/
		SysCtlPeripheralReset(SYSCTL_PERIPH_I2C3);

		/*enable GPIO peripheral that contains I2C*/
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);

		/*Configure the pin muxing for I2C0 functions on port B2 and B3.*/
		GPIOPinConfigure(GPIO_PD0_I2C3SCL);
		GPIOPinConfigure(GPIO_PD1_I2C3SDA);

		/*Select the I2C function for these pins.*/
		GPIOPinTypeI2CSCL(GPIO_PORTD_BASE, GPIO_PIN_0);
		GPIOPinTypeI2C(GPIO_PORTD_BASE, GPIO_PIN_1);

		/*Enable and initialize the I2C0 master module.  Use the system clock for
		the I2C0 module.  The last parameter sets the I2C data transfer rate.
		If false the data rate is set to 100kbps and if true the data rate will
		be set to 400kbps.*/
		I2CMasterInitExpClk(I2C3_BASE, SysCtlClockGet(), false);

		/*clear I2C FIFOs*/
		HWREG(I2C3_BASE + I2C_O_FIFOCTL) = 80008000;
	}
}

/******************************************************************************
*
*	The function's purpose is to initialize the i2c as a slave
*
*	\param i2c		pointer to structure that contains all the data needed
*					to initialize the i2c as a slave
*
* 	\return none
*
*****************************************************************************/
void i2cslaveinit(I2C_InitTypeDef * i2c)
{
	uint32_t baseAddress = i2c->baseAddress;
	uint32_t SlaveAddr = i2c->slaveAddress1;

	if (baseAddress == I2C0_BASE)
	{
		/*enable I2C module*/
		SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);

		/*reset I2C module*/
		SysCtlPeripheralReset(SYSCTL_PERIPH_I2C0);

		/*enable GPIO peripheral that contains I2C*/
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

		/*Configure the pin muxing for I2C0 functions on port B2 and B3.*/
		GPIOPinConfigure(GPIO_PB2_I2C0SCL);
		GPIOPinConfigure(GPIO_PB3_I2C0SDA);

		/*Select the I2C function for these pins.*/
		GPIOPinTypeI2CSCL(GPIO_PORTB_BASE, GPIO_PIN_2);
		GPIOPinTypeI2C(GPIO_PORTB_BASE, GPIO_PIN_3);
	}

	else if (baseAddress == I2C1_BASE)
	{
		/*enable I2C module*/
		SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C1);

		/*reset I2C module*/
		SysCtlPeripheralReset(SYSCTL_PERIPH_I2C1);

		/*enable GPIO peripheral that contains I2C*/
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

		/*Configure the pin muxing for I2C0 functions on port B2 and B3.*/
		GPIOPinConfigure(GPIO_PA6_I2C1SCL);
		GPIOPinConfigure(GPIO_PA7_I2C1SDA);

		/*Select the I2C function for these pins.*/
		GPIOPinTypeI2CSCL(GPIO_PORTA_BASE, GPIO_PIN_6);
		GPIOPinTypeI2C(GPIO_PORTA_BASE, GPIO_PIN_7);
	}

	else if (baseAddress == I2C2_BASE)
	{
		/*enable I2C module*/
		SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C2);

		/*reset I2C module*/
		SysCtlPeripheralReset(SYSCTL_PERIPH_I2C2);

		/*enable GPIO peripheral that contains I2C*/
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);

		/*Configure the pin muxing for I2C0 functions on port B2 and B3.*/
		GPIOPinConfigure(GPIO_PE4_I2C2SCL);
		GPIOPinConfigure(GPIO_PE5_I2C2SDA);

		/*Select the I2C function for these pins.*/
		GPIOPinTypeI2CSCL(GPIO_PORTE_BASE, GPIO_PIN_4);
		GPIOPinTypeI2C(GPIO_PORTE_BASE, GPIO_PIN_5);
	}

	else if (baseAddress == I2C3_BASE)
	{
		/*enable I2C module*/
		SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C3);

		/*reset I2C module*/
		SysCtlPeripheralReset(SYSCTL_PERIPH_I2C3);

		/*enable GPIO peripheral that contains I2C*/
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);

		/*Configure the pin muxing for I2C0 functions on port B2 and B3.*/
		GPIOPinConfigure(GPIO_PD0_I2C3SCL);
		GPIOPinConfigure(GPIO_PD1_I2C3SDA);

		/*Select the I2C function for these pins.*/
		GPIOPinTypeI2CSCL(GPIO_PORTD_BASE, GPIO_PIN_0);
		GPIOPinTypeI2C(GPIO_PORTD_BASE, GPIO_PIN_1);
	}
	/*sets the i2c slave address*/
	I2CSlaveAddressSet(baseAddress, 0, SlaveAddr);

	I2CSlaveEnable(baseAddress);
}

/******************************************************************************
*
*	The function's purpose is to send a char using the i2c as a master
*
*	\param i2c		pointer to structure that contains an instance of the
*					initialization structure that includes the base address
*					of the previously intialized i2c and the slave address
*					that's going to receive the data
*
* 	\return none
*
*****************************************************************************/
void i2cmastersend(I2C_HandleTypeDef *i2c)
{
	uint32_t baseAddress = i2c->instance.baseAddress;
	uint32_t slaveAddress = i2c->slaveAddress;
	uint8_t data = i2c->Txdata;

	/*specify that we want to communicate to device address with an intended write to bus*/
	I2CMasterSlaveAddrSet(baseAddress, slaveAddress, false);

	/*register to be read*/
	I2CMasterDataPut(baseAddress, data);

	/*Initiate send of data from the MCU*/
	I2CMasterControl(baseAddress, I2C_MASTER_CMD_SINGLE_SEND);

	/*Wait until MCU is done transferring.*/
	while(I2CMasterBusy(baseAddress));
}

/******************************************************************************
*
*	The function's purpose is to receive a char using the i2c as a master
*
*	\param i2c		pointer to structure that contains an instance of the
*					initialization structure that includes the base address
*					of the previously intialized i2c and the slave address
*					that's going to send the data
*
* 	\return the received character
*
*****************************************************************************/
uint8_t i2cmasterreceive(I2C_HandleTypeDef *i2c)
{
	uint32_t baseAddress = i2c->instance.baseAddress;
	uint32_t slaveAddress = i2c->slaveAddress;

	/*specify that we want to communicate to device address with an intended write to bus*/
	I2CMasterSlaveAddrSet(baseAddress, slaveAddress, false);

	/*the register to be read*/
	I2CMasterDataPut(baseAddress, 0x40020000);

	/*send control byte and register address byte to slave device*/
	I2CMasterControl(baseAddress, I2C_MASTER_CMD_SINGLE_SEND);

	/*wait for MCU to complete send transaction*/
	while(I2CMasterBusy(baseAddress));

	/*read from the specified slave device*/
	I2CMasterSlaveAddrSet(baseAddress, slaveAddress, true);

	/*send control byte and read from the register from the MCU*/
	I2CMasterControl(baseAddress, I2C_MASTER_CMD_SINGLE_RECEIVE);

	/*wait while checking for MCU to complete the transaction*/
	while(I2CMasterBusy(baseAddress));

	/*Get the data from the MCU register and return to caller*/
	return( I2CMasterDataGet(baseAddress));
}

/******************************************************************************
*
*	The function's purpose is to send a char using the i2c as a slave
*
*	\param i2c		pointer to structure that contains an instance of the
*					initialization structure, the slave address that's going to
*					send the data and the data needed to be sent
*
* 	\return none
*
*****************************************************************************/
void i2cslavesend(I2C_HandleTypeDef *i2c)
{
	uint32_t baseAddress = i2c->instance.baseAddress;
	uint8_t data = i2c->Txdata;
	while(!(I2CSlaveStatus(baseAddress) & I2C_SLAVE_ACT_TREQ));
		I2CSlaveDataPut(baseAddress, data);
}

/******************************************************************************
*
*	The function's purpose is to receive a char using the i2c as a slave
*
*	\param i2c		pointer to structure that contains an instance of the
*					initialization structure, the slave address that's going to
*					receive the data and the data needed to be sent
*
* 	\return the received char
*
*****************************************************************************/
uint8_t i2cslavereceive(I2C_HandleTypeDef *i2c)
{
	uint32_t baseAddress = i2c->instance.baseAddress;
	/*wait till the master sends some data*/
	while(!(I2CSlaveStatus(baseAddress) & I2C_SLAVE_ACT_RREQ));
	return I2CSlaveDataGet(baseAddress);
}
