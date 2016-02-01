/*
 * _8_bit_TimerCounter0.c
 *
 * Created: 1/31/2016 4:29:30 PM
 *  Author: Dell Ultrabook
 */ 

#include "8-bit_TimerCounter0.h"
#include "GPIO.h"
#include "8-bit_TimerCounter0_LCFG.h"
#include "8-bit_TimerCounter0_CFG.h"
#include "avr/interrupt.h"

uint8_t time;

void TimerCounter0_Init (void)
{
	//TCCR0 &= 0x00;
	//TCCR0 |= (1<< CS01) | (1 << CS00) | (1<< CS02) | (1 << WGM01);
	//OCR0 = 0xFF;		
	
	if((WGM01_VALUE==0) && (WGM00_VALUE==0))
	{
		//TIMSK|=(1<<TOIE0);
		TCNT0 &= 0x00;		
	}
	TCCR0 = (CS00_VALUE<<CS00)|(CS01_VALUE<<CS01)|(CS02_VALUE<<CS02)|(WGM01_VALUE<<WGM01)|(WGM00_VALUE<<WGM00)|(COM00_VALUE<<COM00)|(COM01_VALUE<<COM01);
	GPIO_InitPortDirection(PB, 0xFF,0xFF);
	
}


void TimerCounter0_milliTime_NORMAL (uint8_t t)
{
	time = t;
}	

uint8_t TimerCounter0_Read()
{
	return TCNT0;
}

void delay_NORMAL (void)
{
	
	TimerCounter0_Init();
	while((TIFR&0x01)==0)
		{GPIO_WritePort(PB, TCNT0, 0xFF);}
	TCCR0=0;
	TCNT0=0x00;
	TIFR = 0x01;
}