
#include "8-bit_TimerCounter0.h"
#include "8-bit_TimerCounter0_LCFG.h"
#include "8-bit_TimerCounter0_CFG.h"
#include "avr/interrupt.h"


static FnPtr TMR_CylicFunPtr; /*global ptr2fn to pass it from init to ISR*/
static uint32_t count = 0;
static uint16_t countCompare = 0;
static uint16_t no_of_ticks = 0;


/*************************************************************************************************
*
*	This function initializes the timer.
*	
*	Whether you are using interrupt or not you use this function to initialize the timer
*
*	\return none
**************************************************************************************************/
void timer0Init1ms ()
{		
	sei();
	TCCR0 = 0x00;
	TCCR0 |= (((MODE.MODE_NORMAL_CTC & 0x02)>>1)<<WGM01) | ((MODE.MODE_NORMAL_CTC & 0x01)<<WGM00) | (COM00_VALUE<<COM00)|(COM01_VALUE<<COM01);
	uint8_t u8LoopCounter;
	
	for(u8LoopCounter=0; u8LoopCounter< PRESCALAR_NUM ; u8LoopCounter++)
	{
		no_of_ticks = clk1ms[u8LoopCounter].TempFreq;
		if (no_of_ticks < 256)
		{
			TCCR0 |= ((clk1ms[u8LoopCounter].RegVal) &0x07);
			break;
		}		
	}
	
}




/*************************************************************************************************
*
*	This function starts the timer. You use this function when you want 
*	the timer to work with interrupt.
*
*	\param	millis		this is the number of milli-seconds you want to timer to count.
*	\param	timeoutFn	this is the function to be executed after the delay
*	
*	\return none
**************************************************************************************************/
void timer0Start (uint16_t millis, FnPtr timeoutFn)
{	
	TIMSK = 0x00;
	OCR0 = no_of_ticks-1;
	TIMSK |= 1<<OCIE0;
	countCompare = millis;
	TMR_CylicFunPtr = timeoutFn;
}



/*************************************************************************************************
*
*	This function reads the current value of the counter and returns it.
*	
*	\return the timer's counter
**************************************************************************************************/
uint8_t timer0Read()
{
	return TCNT0;
}


/*************************************************************************************************
*
*	This function starts the timer. You use this function when you want to make a software delay.
*
*	\param	millis		this is the number of milli-seconds you want to timer to count.
*	\param	timeoutFn	this is the function to be executed after the delay
*
*	\return none
**************************************************************************************************/
void timer0Delay1ms(uint16_t millis, FnPtr timeoutFn)
{
	
	uint16_t i;
	for (i=0 ; i < millis ; i++)
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
	timeoutFn();
}



/*************************************************************************************************
*
*	This function reads the value of the overflow flag and returns it.
*
*	\return the value of the overflow flag
**************************************************************************************************/
uint8_t timer0ReadOVFFlag()
{
	return (TIFR&0x01);
}



/*************************************************************************************************
*
*	This function reads the value of the compare and match flag and returns it.
*
*	\return the value of the compare and match flag
**************************************************************************************************/
uint8_t timer0ReadCMPFlag()
{
	return (TIFR&0x02);
}



/*************************************************************************************************
*
*	This function sets the value of the counter.
*	
*	\param	TCNT0_value	the needed counter's value
*
*	\return none
**************************************************************************************************/
void setTCNT0 (uint8_t TCNT0_value)
{
	TCNT0 = TCNT0_value;
}



/*************************************************************************************************
*
*	This function sets the value to compare with the TCNT0. So when TCNT0 matches with OCR0 
*	a flag is set.
*
*	\param OCR0_value	the value to compare with the counter's value
*
*	\return	none
**************************************************************************************************/
void setOCR0 (uint8_t OCR0_value)
{
	OCR0 = OCR0_value - 1;
}



/*************************************************************************************************
*
*	This function stops the timer.
*
*	\return none
**************************************************************************************************/
void timer0Stop()
{
	TCCR0 |= (0<<CS02) | (0<<CS01) | (0<<CS00);
}



/*************************************************************************************************
*
*	This is the interrupt service routine of the compare and match timer. The 'count' counts the 
*	number of milli-seconds required. When the 'count' matches the 'countCompare' the required
*	function is executed. 
*
**************************************************************************************************/
ISR(TIMER0_COMP_vect)
{
	count++;
	if (count == countCompare)
	{
		TMR_CylicFunPtr();
		count = 0;
	}
}