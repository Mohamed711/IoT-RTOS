/*
 * I2C.c
 *
 * Created: 2/4/2016 2:00:25 PM
 *  Author: sameh
 */ 

#include <stdint.h>
#include "I2C.h"
#include "I2C_cfg.h"
//#include "I2C_Lcfg.h"

#define F_CPU   8000000UL

/********************************************************
I2C Master Initialization								*
it initialize the kite as the master					*
it takes 1 parameter ClockRate							*
*********************************************************/
void masterInit(uint16_t ClockRate)
{
	TWBR_REG = ((F_CPU/ClockRate) - 16)/2;
	TWCR_REG = (1<<TWEN); /* Enable I2C */
	TWSR_REG = 0x00;  /* prescaler set to 1 (option) */
	/*****Start*****/
	TWCR_REG = (1<<TWINT) | (1<<TWEN) | (1<<TWSTA); /* start condition */
	while(!(TWCR_REG & (1<<TWINT)));  /* check start condition */
}

/********************************************************
I2C Master Transmit										*
the master send a data to the salve						*
it takes 2 parameters x & y	(char)						*
x -> slave address , y-> data needed to be transmitted	*
*********************************************************/
void masterTransmit(char x,char y)
{
	TWDR_REG = x;  /* slave address */
	TWCR_REG = (1<<TWINT) | (1<<TWEN); /* Enable I2C and clear interrupt */
	while(!(TWCR_REG & (1<<TWINT))); /* write succeeded with TWDR empty */
	
	TWDR_REG = y;  /* data itself */
	TWCR_REG = (1<<TWINT) | (1<<TWEN); /* Enable I2C and clear interrupt */
	while(!(TWCR_REG & (1<<TWINT))); /* write succeeded with TWDR empty */
}

/****************************************************
I2C Master Receive									*
this function master receive data from the slave	*
it doesn't take any parameters						*
it return data (char)								*
*****************************************************/
char masterReceive()
{
	TWCR_REG = (1<<TWEN) | (1<<TWINT); /* enable I2C and clear interrupt */
	while(!(TWCR_REG & (1<<TWINT))); /* read succeeded with all data received */
	return TWDR_REG;
}

/************************************************
Slave Initialization							*	
it initialize the kite as the slave				*
it takes 1 parameter which is the slave address	* 
 ************************************************/
void slaveInit(uint8_t address)
{
	TWBR_REG=1;
	/* Setting up the SCL frequency by writing a value in TWBR */
	TWSR_REG|=(0<<TWPS1)|(0<<TWPS0);
	TWAR_REG=address;
	/* The first seven bits indicate the slave address */
	TWCR_REG|=(1<<TWINT)|(1<<TWEN)|(1<<TWEA)|(0<<TWSTA)|(0<<TWSTO);
	/* Enabling Acknowledge function */
	while (!(TWCR_REG & (1<<TWINT)));
	/*Wait for the interrupt to be cleared as it will indicate the successful reception */
	while(TWCR_REG&(0xF8)!=(0x60));
	/* Checking if the self-address+W has been received and ACK has been sent */
	
}

/************************************************************
Slave Transmit												*
this function transmit data from slave						*
it takes 1 parameter "write_data" which is the data needed	*
to be transmitted from the slave							*
*************************************************************/
void slaveTransmit(char write_data)
{
	/* Fill TWDR register with the data to be sent */
	TWDR_REG= write_data;
	/* Enable TWI, Clear TWI interrupt flag */
	TWCR_REG= (1<<TWEN)|(1<<TWINT);
	/* Wait for the acknowledgment */
	//while((TWSR & 0xF8) != 0xB8); /* 0xC0 for NACK */
}

/****************************************************
Slave Receive										*
this function the slave receive data				*
it doesn't take any parameters						*
it return data received at the slave side (char)	*
*****************************************************/
char slaveReceive(void)
{
	char recv_data;
	/* Clear TWI interrupt flag,Get acknowledgment, Enable TWI */
	TWCR_REG= (1<<TWINT)|(1<<TWEA)|(1<<TWEN);
	/* Wait for TWINT flag */
	while (!(TWCR_REG & (1<<TWINT)));
	/* Wait for acknowledgment */
	while((TWSR_REG & 0xF8)!=0x80);/* 0x88 for NACK */
	/* Get value from TWDR */
	recv_data=TWDR_REG;
	/* send the receive value on PORTB */
	return recv_data;
}