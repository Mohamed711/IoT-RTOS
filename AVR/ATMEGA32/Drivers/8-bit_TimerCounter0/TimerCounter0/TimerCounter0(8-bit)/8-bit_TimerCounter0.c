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
//#include "HAL.h"

static FnPtr TMR_CylicFunPtr; //global ptr2fn to pass it from init to ISR
//static u16 no_of_ticks = 0;
static u32 count = 0;
static u16 countCompare = 0;
static u16 no_of_ticks = 0;

void HAL_Timer_Init1ms ()
{		
	sei();
	TCCR0 = 0x00;
	TCCR0 |= (((MODE.MODE_NORMAL_CTC & 0x02)>>1)<<WGM01) | ((MODE.MODE_NORMAL_CTC & 0x01)<<WGM00) | (COM00_VALUE<<COM00)|(COM01_VALUE<<COM01);
	//TIMSK = 0x00;
	u8 u8LoopCounter;
	//u16 no_of_ticks = 0;
	
	for(u8LoopCounter=0; u8LoopCounter< PRESCALAR_NUM ; u8LoopCounter++)
	{
		no_of_ticks = clk1ms[u8LoopCounter].TempFreq;
		if (no_of_ticks < 256)
		{
			TCCR0 |= ((clk1ms[u8LoopCounter].RegVal) &0x07);
			break;
		}		
	}
	//TCNT0 = 0x00;
	
	//TIMSK |= 1<<OCIE0;
	//OCR0 = no_of_ticks-1;
	
	//countCompare = millis;
	//TMR_CylicFunPtr = timeoutFn;
}


void HAL_Timer_Start (u16 millis, FnPtr timeoutFn)
{
	//TCNT0 = 0x00;
	
	TIMSK = 0x00;
	OCR0 = no_of_ticks-1;
	TIMSK |= 1<<OCIE0;
	
	countCompare = millis;
	TMR_CylicFunPtr = timeoutFn;
	//TCNT0 = 0x00;
}

uint8_t timer0_Read()
{
	return TCNT0;
}

void HAL_Timer_delay1ms(u16 delay, FnPtr delayFn)
{
	//u8 u8LoopCounter;
	//u16 x;
//
	//for(u8LoopCounter=0; u8LoopCounter< PRESCALAR_NUM ; u8LoopCounter++)
	//{
		//x = clk1ms[u8LoopCounter].TempFreq;
		//
		//if (x < 256)
		//{
			//TCCR0 |= ((clk1ms[u8LoopCounter].RegVal) &0x07);
			//break;
		//}
		//
	//}
	//
	u16 i;
	for (i=0 ; i < delay ; i++)
	{
		if(MODE.MODE_NORMAL_CTC == u8_MODE_NORMAL)
		{
			TCNT0 = 256 - no_of_ticks;
			while ((TIFR&0x01)==0);
			TIFR = 0x01;
		}		
		else if (MODE.MODE_NORMAL_CTC == u8_MODE_CTC)
		{ 
			 TCNT0 = 0;
			 OCR0 = no_of_ticks-1;
			 while ((TIFR&0x02)==0);
			 TIFR = 0x02;
		}
	}
	delayFn();
}


u8 timer0_readOVFFlag()
{
	return (TIFR&0x01);
	//return GETBIT(TIFR,TOV0);
}

u8 timer0_readCMPFlag()
{
	//return GETBIT(TIFR,OCF0);
	return (TIFR&0x02);
}

void setTCNT0 (u8 TCNT0_value)
{
	TCNT0 = TCNT0_value;
}

void setOCR0 (u8 OCR0_value)
{
	OCR0 = OCR0_value - 1;
}

void timer0_stop()
{
	TCCR0 |= (0<<CS02) | (0<<CS01) | (0<<CS00);
}

ISR(TIMER0_OVF_vect)
{
	
}

ISR(TIMER0_COMP_vect)
{
	count++;
	if (count == countCompare)
	{
		TMR_CylicFunPtr();
		count = 0;
	}
	//TCNT0 = 0x00;
}


