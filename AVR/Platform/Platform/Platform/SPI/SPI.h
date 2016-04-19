/*
 * SPI.h
 *
 * Created: 2/11/2016 12:47:30 AM
 *  Author: ZIKO
 */ 


#ifndef SPI_H_
#define SPI_H_

#include <avr/io.h>
#include "avr/interrupt.h"
//#include "DIO.h"
#include "HAL_SPI_AVR.h"

void SPI_Init(u32 u32MaxFreq, u8 u8Mode, u8 u8DataOrder);
void SPI_InterruptInit();
void SPI_Transmit(u8 data);	//for both with and without interrupt
//void SPI_SlaveTransmit(u8 data);	//with interrupt
u8 SPI_SlaveReceive();			//without interrupt
u8 SPI_Tranceiver(u8 data);		//for Master and Slave with and without interrupt
//u8 Data_Received();
extern volatile u8 SPI_DATA ;
#endif /* SPI_H_ */