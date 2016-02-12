/*
 * Slave.h
 *
 * Created: 2/1/2016 7:50:16 AM
 *  Author: ZIKO
 */ 


#ifndef SLAVE_H_
#define SLAVE_H_


#include <avr/io.h>
#include "avr/interrupt.h"
#include "GPIO.h"

void SPI_SlaveInit(void);
//unsigned char SPI_MasterReceive(void);
void SPI_SlaveTransmit (u8);
void SPI_SlaveTranceiver (u8 data);
void SPI_SlaveReceive();
//void initInterrupt();
ISR(SPI_STC_vect);




#endif /* SLAVE_H_ */