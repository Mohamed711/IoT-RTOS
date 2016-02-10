

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
	int data1=0x08;
	while(1)
	{
		SPI_MasterTransmit(8);
		data1= 0x7;
		SPI_MasterTransmit(7);
		// for(int i=0;i<10;i++){}
	}
}