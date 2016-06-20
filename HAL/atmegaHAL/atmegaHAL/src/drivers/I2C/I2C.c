
#include <stdint.h>
#include "I2C.h"
#include "I2C_cfg.h"
//#include "I2C_Lcfg.h"

#define F_CPU   8000000UL

/*******************************************************
*	I2C Master Initialization							
*	it initialize the kite as the master				
*														
*	\param	ClockRate									
*														
*	\return	none										
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
*	I2C Master Transmit										
*	the master send a data to the salve		
*				
*	\param x	slave address 
*	\param y	data needed to be transmitted	
*
*	\return		none
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
*	I2C Master Receive									
*	this function master receive data from the slave	
*
*	\return	Received char								
*****************************************************/
char masterReceive()
{
	TWCR_REG = (1<<TWEN) | (1<<TWINT); /* enable I2C and clear interrupt */
	while(!(TWCR_REG & (1<<TWINT))); /* read succeeded with all data received */
	return TWDR_REG;
}

/************************************************
*	Slave Initialization							
*	it initialize the kite as the slave				
*
*	\param address the slave address	
*
*	\return	none
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
*	Slave Transmit												
*	this function transmit data from slave						

*	\param write_data	data needed to be to be transmitted from the slave		

*	\return	none			
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
*	Slave Receive										
*	this function the slave receive data				
*
*	\return	data received at the slave side (char)	
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