/*
 * SPI_Config.h
 *
 * Created: 2/8/2016 8:48:10 PM
 *  Author: ZIKO
 */ 


#ifndef SPI_CONFIG_H_
#define SPI_CONFIG_H_

#include "StdTypes.h"

// SPI Registers
#define SPCR_REG		*((u8 volatile *const)0x2D)
#define SPDR_REG		*((u8 volatile *const)0x2F)
#define SPSR_REG		*((u8 volatile *const)0x2E)
#define GICR_REG		*((u8 volatile *const)0x5B)
#define MCUCR_REG		*((u8 volatile *const)0x55)

//for interrupt
#define INT_1 0x80
#define ISC_11 0x08
#define ISC_10 0x04
#define SPIF_0 0x80
//SCK rate for Mater
#define PRESCALAR_NUM	0x07

// clock polarity and clock phase setup
#define u8MODE_0		0x00		// Sample (Rising) Setup (Falling) 
#define u8MODE_1		0x04		// Setup (Rising) Sample (Falling)
#define u8MODE_2		0x08		//Sample (Falling) Setup (Rising) 
#define u8MODE_3		0x0C		//Setup (Falling) Sample (Rising)

//enable master or slave
#define SPI_MASTER_EN	0x10
#define SPI_SLAVE_EN	0x00

//Data order
#define u8DOR_MSB		0x00
#define u8DOR_LSB		0x20

#define SPI_INT_EN		0x80		//Enable execution of SPI interrupt 
#define SPI_EN			0x40		//SPI Enabled
#define SPI_INT_Disable		0x00


#define Master_Or_Slave			SPI_SLAVE_EN
#define ENABLE_INTERRUPT_OR_NOT SPI_INT_EN
//#define SPI_INT_FL		0x80		//SPI Interrupt Flag 
#define SPI_DOUBLE_SP	0x01		//?Double SPI Speed Bit for Master



#endif /* SPI_CONFIG_H_ */