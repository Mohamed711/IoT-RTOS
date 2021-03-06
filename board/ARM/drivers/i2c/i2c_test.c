#include <stdint.h>
#include <stdbool.h>
#include "i2c_test.h"
#include "i2c.h"

#include "../uart/uart.h"
#include "../uart/HAL_UART.h"

#include "../inc/hw_i2c.h"
#include "../inc/hw_memmap.h"
#include "../inc/hw_types.h"
#include "../inc/hw_gpio.h"

#include "../sysctl/sysctl.h"
#include "../gpio/gpio.h"
#include "../pin_map/pin_map.h"


/******************************************************************************
*
*	The function's purpose is to initialize the i2c as a master
*
*	\param baseAddress		 the base address of the needed i2c
*
* 	\return none
*
*****************************************************************************/
void i2cMasterInit(uint32_t baseAddress)
{
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
*	The function's purpose is to receive a char using the i2c as a master
*
*	\param baseAddress			the base address of the needed i2c
*	\param slaveAddress			the slave address that's gonna send the char
*
* 	\return the received character
*
*****************************************************************************/
uint8_t i2cMasterReceive(uint32_t baseAddress, uint8_t slaveAddress)
{
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
*	The function's purpose is to send a char using the i2c as a master
*
*	\param baseAddress			the base address of the needed i2c
*	\param slaveAddress			the slave address that's gonna send the char
*	\param data					the data needed to be sent
*
* 	\return none
*
*****************************************************************************/
void i2cMasterSend(uint32_t baseAddress, uint8_t slaveAddress,  uint8_t data)
{
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
*	The function's purpose is to send a string using the i2c as a master
*
*	\param slaveAddress			the slave address that's gonna send the char
*	\param array[]				the string needed to be sent
*
* 	\return none
*
*****************************************************************************/
void I2CSendString(uint32_t slave_addr, char array[])
{
    /*Tell the master module what address it will place on the bus when
    communicating with the slave.*/
    I2CMasterSlaveAddrSet(I2C0_BASE, slave_addr, false);

    /*put data to be sent into FIFO*/
    I2CMasterDataPut(I2C0_BASE, array[0]);

    /*if there is only one argument, we only need to use the
    single send I2C function*/
    if(array[1] == '\0')
    {
        /*Initiate send of data from the MCU*/
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_SEND);

        /*Wait until MCU is done transferring.*/
        while(I2CMasterBusy(I2C0_BASE));
    }

    /*otherwise, we start transmission of multiple bytes on the I2C bus*/
    else
    {
        /*Initiate send of data from the MCU*/
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_START);

        /*Wait until MCU is done transferring.*/
        while(I2CMasterBusy(I2C0_BASE));

        //initialize index into array*/
        uint8_t i = 1;

        /*send num_of_args-2 pieces of data, using the
        BURST_SEND_CONT command of the I2C module*/
        while(array[i + 1] != '\0')
        {
            /*put next piece of data into I2C FIFO*/
            I2CMasterDataPut(I2C0_BASE, array[i++]);

            /*send next data that was just placed into FIFO*/
            I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_CONT);

            /*Wait until MCU is done transferring.*/
            while(I2CMasterBusy(I2C0_BASE));
        }

        /*put last piece of data into I2C FIFO*/
        I2CMasterDataPut(I2C0_BASE, array[i]);

        /*send next data that was just placed into FIFO*/
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);

        /*Wait until MCU is done transferring.*/
        while(I2CMasterBusy(I2C0_BASE));
    }
}

/******************************************************************************
*
*	The function's purpose is to initialize the i2c as a slave
*
*	\param baseAddress			the base address of the needed i2c
*	\param slaveAddress			the slave address that's gonna send the char
*
* 	\return none
*
*****************************************************************************/
void i2cSlaveInit(uint32_t baseAddress, uint8_t SlaveAddr)
{
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
*	The function's purpose is to receive a char using the i2c as a slave
*
*	\param baseAddress			the base address of the needed i2c
*	\param slaveAddress			the slave address that's gonna send the char
*
* 	\return the received character
*
*****************************************************************************/
uint8_t i2cSlaveReceive(uint32_t baseAddress, uint8_t SlaveAddr)
{
	//I2CSlaveInit(baseAddress, SlaveAddr);
	/*wait till the master sends some data*/
	while(!(I2CSlaveStatus(baseAddress) & I2C_SLAVE_ACT_RREQ));
	return I2CSlaveDataGet(baseAddress);
}

/******************************************************************************
*
*	The function's purpose is to send a char using the i2c as a master
*
*	\param baseAddress			the base address of the needed i2c
*	\param sata					the data needed to be sent
*	\param slaveAddress			the slave address that's gonna send the char
*
* 	\return none
*
*****************************************************************************/
void i2cSlaveSend(uint32_t baseAddress, uint8_t data, uint8_t SlaveAddr)
{
	//I2CSlaveInit(baseAddress, SlaveAddr);
	/*wait till the master requests some data*/
	while(!(I2CSlaveStatus(baseAddress) & I2C_SLAVE_ACT_TREQ));
	I2CSlaveDataPut(baseAddress, data);
}


void MasterSendTest()
{
	//first, initializing the i2c0 module
	i2cMasterInit(I2C0_BASE);

	//for sending just one char
	i2cMasterSend(I2C0_BASE, 4, 'a');

	//for sending a string
	char st [5] = {'a', 'b', 'c', 'd', 'e'};
	I2CSendString(4, st);
}
void MasterReceiveTest()
{
	//UART0 Configuration
	SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	GPIOPinConfigure(GPIO_PA0_U0RX);
	GPIOPinConfigure(GPIO_PA1_U0TX);
	GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
	UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
	(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));


	//first, initializing the i2c0 module
	i2cMasterInit(I2C0_BASE);

	//receiving  a character from the slave then displaying it using the UART
	uint8_t x = i2cMasterReceive(I2C0_BASE,4);
	UARTCharPut(UART0_BASE, x);
}

void SlaveSendTest()
{
	//initializing the slave
	i2cSlaveInit( I2C0_BASE, 4);

	//Sends a '0' to the master
	i2cSlaveSend(I2C0_BASE, '0', 4);

	//delay
	SysCtlDelay(20000);

	//then sends a '1' to the master
	i2cSlaveSend(I2C0_BASE, '1', 4);

}
void SlaveReceiveTest()
{
	//UART0 Configuration
	SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	GPIOPinConfigure(GPIO_PA0_U0RX);
	GPIOPinConfigure(GPIO_PA1_U0TX);
	GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
	UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
	(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

	//initializing the slave
	i2cSlaveInit(I2C0_BASE, 4);

	//receiving  a character then displaying it using the UART
	char x = i2cSlaveReceive(I2C0_BASE, 4);
	UARTCharPut(UART0_BASE, x);
}
