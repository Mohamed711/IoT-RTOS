

//#include <avr/io.h>
//#include "GPIO.h"
#include "Master.h"
//#include <avr/interrupt.h>
extern volatile u8 data1;
int main(void)
{
	
	SPI_MasterInit();
	//initInterrupt();
	//sei();
	//int data1=0x08;
	while(1)
	{
		SPI_MasterTransmit(16);
		SPI_MasterTranceiver(8);
		SPI_MasterTranceiver(7);
	}
}