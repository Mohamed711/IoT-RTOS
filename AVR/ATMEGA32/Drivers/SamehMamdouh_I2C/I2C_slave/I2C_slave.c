/*
 * I2C_slave.c
 *
 * Created: 2/9/2016 1:26:54 PM
 *  Author: sameh
 */ 
//#include <avr/io.h>
#include <util/twi.h>
#include <avr/interrupt.h>

#include "I2C_slave.h"
#include "DIO.h"


// Function to initialize slave
void TWI_init_slave(uint8_t address)
{
		TWBR=1;
		//Setting up the SCL frequency by writing a value in TWBR
		TWSR|=(0<<TWPS1)|(0<<TWPS0);
		//Fscl=     Fcpu/(16+2*(TWBR)*(4^TWPS))
		TWAR=address;
		//The first seven bits indicate the slave address
		TWCR|=(1<<TWINT)|(1<<TWEN)|(1<<TWEA)|(0<<TWSTA)|(0<<TWSTO);
		//Enabling Acknowledge function
		while (!(TWCR & (1<<TWINT)));
		//Wait for the interrupt to be cleared as it will indicate the successful reception
		while(TWCR&(0xF8)!=(0x60));
		//Checking if the self-address+W has been received and ACK has been sent
		
}

void TWI_write_slave(char write_data) // Function to write data
{
	// Fill TWDR register with the data to be sent
	TWDR= write_data;
	// Enable TWI, Clear TWI interrupt flag
	TWCR= (1<<TWEN)|(1<<TWINT);
	// Wait for the acknowledgement
	//while((TWSR & 0xF8) != 0xB8); //0xC0 for NACK
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

char TWI_read_slave(void)
{
	char recv_data;
	// Clear TWI interrupt flag,Get acknowledgement, Enable TWI
	TWCR= (1<<TWINT)|(1<<TWEA)|(1<<TWEN);
	// Wait for TWINT flag
	while (!(TWCR & (1<<TWINT)));
	// Wait for acknowledgement
	while((TWSR & 0xF8)!=0x80);//0x88 for NACK
	// Get value from TWDR
	recv_data=TWDR;
	// send the receive value on PORTB
	//PORTB=recv_data; //i don't know if shall i put that in main or not
	return recv_data;
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