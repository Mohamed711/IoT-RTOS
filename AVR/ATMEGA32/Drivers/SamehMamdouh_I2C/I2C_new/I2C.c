/*
 * I2C.c
 *
 * Created: 2/4/2016 2:00:25 PM
 *  Author: sameh
 */ 


#include <avr/io.h>
#include "I2C.h"
#include "I2C_cfg.h"
//#include "I2C_Lcfg.h"

#define F_CPU   8000000UL

/*I2C Initialization*/
void master_init(uint16_t ClockRate)
{
	//TWBR = 0x62;  // baud rate is set by calculating the TWBR (option)
	//TWBR = ((F_CPU/I2C_initConfig.ubrr) - 16)/2;
	TWBR_REG = ((F_CPU/ClockRate) - 16)/2;
	TWCR_REG = (1<<TWEN); // Enable I2C
	TWSR_REG = 0x00;  // prescaler set to 1 (option)
	/*****Start*****/
	TWCR_REG = (1<<TWINT) | (1<<TWEN) | (1<<TWSTA); //start condition
	while(!(TWCR_REG & (1<<TWINT)));  //check start condition
}

/*I2C master transmit*/
void master_transmit(char x,char y)
{
	TWDR_REG = x;  //slave address
	TWCR_REG = (1<<TWINT) | (1<<TWEN); //Enable I2C and clear interrupt
	while(!(TWCR_REG & (1<<TWINT))); //write succeeded with TWDR empty
	
	TWDR_REG = y;  //data itself
	TWCR_REG = (1<<TWINT) | (1<<TWEN); //Enable I2C and clear interrupt
	while(!(TWCR_REG & (1<<TWINT))); //write succeeded with TWDR empty
}

/*I2C Read*/
char master_receive()
{
	TWCR_REG = (1<<TWEN) | (1<<TWINT); // enable I2C and clear interrupt
	while(!(TWCR_REG & (1<<TWINT))); //read succeeded with all data received
	return TWDR_REG;
}

// Function to initialize slave
void slave_init(uint8_t address)
{
	TWBR_REG=1;
	//Setting up the SCL frequency by writing a value in TWBR
	TWSR_REG|=(0<<TWPS1)|(0<<TWPS0);
	//Fscl=     Fcpu/(16+2*(TWBR)*(4^TWPS))
	TWAR_REG=address;
	//The first seven bits indicate the slave address
	TWCR_REG|=(1<<TWINT)|(1<<TWEN)|(1<<TWEA)|(0<<TWSTA)|(0<<TWSTO);
	//Enabling Acknowledge function
	while (!(TWCR_REG & (1<<TWINT)));
	//Wait for the interrupt to be cleared as it will indicate the successful reception
	while(TWCR_REG&(0xF8)!=(0x60));
	//Checking if the self-address+W has been received and ACK has been sent
	
}

void slave_transmit(char write_data) // Function to write data
{
	// Fill TWDR register with the data to be sent
	TWDR_REG= write_data;
	// Enable TWI, Clear TWI interrupt flag
	TWCR_REG= (1<<TWEN)|(1<<TWINT);
	// Wait for the acknowledgement
	//while((TWSR & 0xF8) != 0xB8); //0xC0 for NACK
}

char slave_receive(void)
{
	char recv_data;
	// Clear TWI interrupt flag,Get acknowledgement, Enable TWI
	TWCR_REG= (1<<TWINT)|(1<<TWEA)|(1<<TWEN);
	// Wait for TWINT flag
	while (!(TWCR_REG & (1<<TWINT)));
	// Wait for acknowledgement
	while((TWSR_REG & 0xF8)!=0x80);//0x88 for NACK
	// Get value from TWDR
	recv_data=TWDR_REG;
	// send the receive value on PORTB
	//PORTB=recv_data; //i don't know if shall i put that in main or not
	return recv_data;
}


/*
uint8_t TWIGetStatus(void)
{
	uint8_t status;
	//mask status
	status = TWSR & 0xF8;
	return status;
}
*/

/*

void i2c_init_old()
{
	//TWBR = 0x62;  // baud rate is set by calculating the TWBR (option)
	TWBR = ((F_CPU/I2C_initConfig.ubrr) - 16)/2;
	//TWBR = ((F_CPU/ClockRate) - 16)/2;
	TWCR = (1<<TWEN); // Enable I2C
	TWSR = 0x00;  // prescaler set to 1 (option)
}

char i2c_read_ACK()
{
	TWCR = (1<<TWEN) | (1<<TWINT) | (1<<TWEA); // enable I2C and clear interrupt
	while(!(TWCR & (1<<TWINT))); //read succeeded with all data received
	return TWDR;
}
//Function to match the slave address and slave direction bit(read)
void TWI_match_read_slave(void)
{
	// Loop till correct acknoledgement have been received
	while((TWSR & 0xF8)!= 0x60)
	{
		// Get acknowlegement, Enable TWI, Clear TWI interrupt flag
		TWCR=(1<<TWEA)|(1<<TWEN)|(1<<TWINT);
		// Wait for TWINT flag
		while (!(TWCR & (1<<TWINT)));
	}
}
// Function to match the slave address and slave
void TWI_match_write_slave(void)//direction bit(write)
{
	// Loop till correct acknowledgement have been received
	while((TWSR & 0xF8)!= 0xA8)
	{
		// Get acknowledgment, Enable TWI, Clear TWI interrupt flag
		TWCR=(1<<TWEA)|(1<<TWEN)|(1<<TWINT);
		while (!(TWCR & (1<<TWINT)));  // Wait for TWINT flag
	}
}
// I2C start condition 
void i2c_start()
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTA); //start condition
	while(!(TWCR & (1<<TWINT)));  //check start condition
	
}
//I2C Stop
void i2c_stop()
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
}
//I2C Restart
void i2c_restart()
{
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	while(!(TWCR & (1<<TWINT)));  //check start condition
}
//I2C master transmit
void i2c_master_transmit(char x,char y)
{
	i2c_write(x);//slave address
	i2c_write(y);//data
}
// I2C write
void i2c_write(char x)
{
	TWDR = x;  //put value in I2C data reg
	TWCR = (1<<TWINT) | (1<<TWEN); //Enable I2C and clear interrupt
	while(!(TWCR & (1<<TWINT))); //write succeeded with TWDR empty
}	
*/