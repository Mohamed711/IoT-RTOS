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
#include "GPIO.h"

void SPI_Init(void);
//void SPI_SlaveInit(void);
void SPI_MasterTransmit(u8 data);	//for both with and without interrupt
void SPI_SlaveTransmit(u8 data);	//with interrupt
void SPI_MasterReceive();			//with interrupt
void SPI_SlaveReceive();			//without interrupt
void SPI_Tranceiver(u8 data);		//for Master and Slave with and without interrupt
void initInterrupt();
ISR(INT1_vect);//for master receiving
ISR(SPI_STC_vect); //for receiving of slave

//void SPI_SlaveReceive ();





#endif /* SPI_H_ */