#include "atmegaHAL.h"
#include "drivers/DIO/DIO.h"

//SPI TEST
/*
volatile uint8_t SPI_DATA;
SPI_InitTypeDef spi =
{
	2000000UL,
	u8MODE_1,
	u8DOR_MSB
};

void main()
{
	DIO_InitPortDirection(PA,0xFF,0xFF);
	SPI_HandleTypeDef SPIDATA ;
	HAL_SPI_Init( &spi);
	while(1)
	{
		PORTA=HAL_SPI_Receive(&SPIDATA);
		SPIDATA.Txdata=7;
		PORTA=HAL_SPI_Receive(&SPIDATA);
		
		SPIDATA.Txdata=16;
	}
}
*/

//UART TEST

UART_InitTypeDef uart_init_config;
UART_HandleTypeDef uart_handle;
/*
int main(void)
{
	DIO_InitPortDirection(0x00,0xFF,0xFF);
	
	uart_init_config.Baud = 9600;
	uart_init_config.DataBits = DATA_BIT_8;
	uart_init_config.StopBits = STOP_BIT_1;
	uart_init_config.Parity = PARITY_DISABLE;
	uart_init_config.EnableInterrupt = 0;
	uart_init_config.U2X_State = U2X_DISABLE;
	
	uartinit(&uart_init_config);
uart_init_config.Baud = 9600;
uart_init_config.DataBits = DATA_BIT_8;
uart_init_config.StopBits = STOP_BIT_1;
uart_init_config.Parity = PARITY_DISABLE;
uart_init_config.EnableInterrupt = 0;
uart_init_config.U2X_State = U2X_DISABLE;

uartinit(&uart_init_config);
while(1)
{
	unsigned char x;
	x = uartreceive(&uart_handle);
	
	if (x == 'v')
	{
		uart_handle.Tx = 'T';
		uartsend(&uart_handle);
	}
	else
	{
		uart_handle.Tx = 'F';
		uartsend(&uart_handle);
	}
}
}
*/

//I2C TEST
/*
int main(void)
{
	DIO_InitPortDirection(0x00,0xFF,0xFF);	//port A as output
	
	I2C_InitTypeDef init;
	init.clock=9600; // setting clock rate 
	init.SlaveAddress=0x40; // write to slave 
	
	I2C_HandleTypeDef handle;
	handle.slaveAddress=0x40;
	handle.Txdata=0x55;
	
	i2cmasterinit(&init);

	while (1)
	{
		i2cmastersend(&handle);
		_delay_ms(10000);
		handle.Txdata = 0x45;
		i2cmastersend(&handle);
	}
}
*/
	
//TIMER TEST
/*
void toggle ()
{
	if (PORTA == 0xFF)
	{
		PORTA = 0x00;
	}
	else if (PORTA == 0x00)
	{
		PORTA = 0xFF;
	}		
}

int main(void)
{
	
	DDRA = 0xFF;
	PORTA = 0xFF;
		
	Timer_InitTypeDef timerInit;
	Timer_HandleTypeDef timerHandle;
	timerHandle.timeInMillis = 10;
	
	timerinit(&timerInit);
	
	timerHandle.timeoutFn = toggle;
	timerstart(&timerHandle);
	//timerdelay(&timerHandle);
	while(1);
}
*/
//ADC TEST 

int main(void)
{
	uint16_t result;
	DDRA &=(~(0xFF));
	
	DDRC |=0xFF;
	DDRD |=0xFF;
	
	ADC_InitTypeDef handle;
	handle.channel=ch_ADC0;
	handle.enable_interrupt= false;
	handle.trigger=Free_Running_mode;
	handle.voltage_ref_sel=Internal_2_dot_56V_Voltage_Reference_with_external_cap_at_AREF_pin;
	handle.u32MaxFreq=75000000UL;
	ADC_HandleTypeDef res;
	adcinit(&handle);
    while(1)
    {
	    result = adcread(&res);
	 
	 PORTC =(result &0xFF);
	 PORTD =((result)>>8);
}
	}
