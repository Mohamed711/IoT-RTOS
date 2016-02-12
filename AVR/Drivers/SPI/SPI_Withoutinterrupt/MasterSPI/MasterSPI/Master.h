

#ifndef MASTER_H_
#define MASTER_H_
#include <avr/io.h>
#include "avr/interrupt.h"
#include "GPIO.h"

void SPI_MasterInit(void);
//unsigned char SPI_MasterReceive(void);
void SPI_MasterTransmit (u8 data);
void SPI_MasterTranceiver (u8 data);

#endif /* MASTER_H_ */