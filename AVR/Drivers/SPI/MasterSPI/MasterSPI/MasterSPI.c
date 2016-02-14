

//#include <avr/io.h>
//#include "GPIO.h"
#include "Master.h"
//#include <avr/interrupt.h>
extern volatile u8 data1;
int main(void)
{
	
	//data= 0x05;
	//DDRA= 0xFF;
	SPI_MasterInit();
	initInterrupt();
	while(1)
	{
		//SPI_MasterTransmit(8);
		//SPI_MasterTransmit(7);
	}
}