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
#ifndef SPI_CONFIG_H_
#define SPI_CONFIG_H_

 #include <stdint.h>
 #include <stdbool.h>

/* SPI Registers */
#define SPCR_REG		*((uint8_t volatile *const)0x2D)
#define SPDR_REG		*((uint8_t volatile *const)0x2F)
#define SPSR_REG		*((uint8_t volatile *const)0x2E)
#define GICR_REG		*((uint8_t volatile *const)0x5B)
#define MCUCR_REG		*((uint8_t volatile *const)0x55)

/*for interrupt */
#define INT_1 0x80
#define ISC_10 0x04
#define ISC_11 0x08
#define SPIF_0 0x80
/*SCK rate for Mater*/
#define PRESCALAR_NUM	0x07

/* clock polarity and clock phase setup */
#define u8MODE_0		0x00		// Sample (Rising) Setup (Falling) 
#define u8MODE_1		0x04		// Setup (Rising) Sample (Falling)
#define u8MODE_2		0x08		//Sample (Falling) Setup (Rising) 
#define u8MODE_3		0x0C		//Setup (Falling) Sample (Rising)

/*enable master or slave*/
#define SPI_MASTER_EN	0x10
#define SPI_SLAVE_EN	0x00

/*Data order*/
#define u8DOR_MSB		0x00
#define u8DOR_LSB		0x20

#define SPI_INT_EN		0x80		/*Enable execution of SPI interrupt */
#define SPI_EN			0x40		/*SPI Enabled*/
#define SPI_INT_Disable		0x00


//#define SPI_INT_FL		0x80		//SPI Interrupt Flag 
#define SPI_DOUBLE_SP	0x01		/*Double SPI Speed Bit for Master */

#define Master_Or_Slave			SPI_SLAVE_EN
#define ENABLE_INTERRUPT_OR_NOT SPI_INT_Disable

#endif /* SPI_CONFIG_H_ */