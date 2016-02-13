/*
 * I2C_Slave.c
 *
 * Created: 2/9/2016 1:24:09 PM
 *  Author: sameh
 */ 


#include <avr/io.h>
#include "I2C_slave.h"
#include "DIO.h"
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>

unsigned char write_data,recv_data;
int main(void)
{
	//DIO_InitPortDirection(0x01,0xFF,0xFF);
	//DIO_InitPortDirection(0x02,0x00,0xFF);
	DDRB=0xFF;
	//PORTB=0x01;
	//TWI_init_slave(0x40); // Function to initialize slave
	TWI_init_slave(0x41);
	while(1)
	{
		//Function to match the slave address and slave direction bit(read)
		//TWI_match_read_slave();
		// Function to read data
		//recv_data=TWI_read_slave();
		//PORTB=recv_data;
		// Togglem the receive data
		//write_data=~recv_data;
		//PORTB=write_data;
		//Function to match the slave address and slave direction bit(write)
		//TWI_match_write_slave();
		// Function to write data
		TWI_write_slave(0x88);
	}
}