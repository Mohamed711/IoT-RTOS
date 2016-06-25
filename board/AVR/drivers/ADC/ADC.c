
#include "ADC.h"
const CLK_Rate clk[PRESCALAR_NUM] =
{
{F_CPU/2,0},
{F_CPU/4,2},
{F_CPU/8,3},
{F_CPU/16,4},
{F_CPU/32,5},
{F_CPU/64,6},
{F_CPU/128,7}
};

/* ADC justify ('L' or 'R') L for only 8 bit precision*/

#if ADC_JUSTIFY == 'L'
static volatile uint8_t ADC_result;
#elif ADC_JUSTIFY == 'R'
static volatile uint16_t ADC_result;
#endif
static bool  enable_interrupt;

/*************************************************************************************************************************
*
*  the function's purpose is to turn off the ADC 
* 
*   \param None
* 
*   \return None
*
**************************************************************************************************************************/
void adcOff(void)
{
	// disable interrupt
	ADCSRA_REG &= (0 << ADIE);
	// disable ADC
	ADCSRA_REG &= (0 << ADEN);
}

/*************************************************************************************************************************
* the function's purpose is to Initialize the ADC
*
* \param voltage_ref_sel   Voltage Reference Selection 
*
* \param enable_interrupt_    to set interrupt
*
* \param trigger     Auto Trigger Source Selections
*
* \param channel to choose the channel on which output is written
*
* \param u32MaxFreq  max frequency of the micro
*
* \return None
*
**************************************************************************************************************************/
void adcInit(uint8_t voltage_ref_sel , bool enable_interrupt_, uint8_t trigger , uint8_t channel , uint32_t u32MaxFreq ) 
{
	/* 1)Set ADC reference */
	enable_interrupt=enable_interrupt_;
	ADMUX_REG |= (  (( (voltage_ref_sel)&0x02)>>1)<<REFS1 )| (((voltage_ref_sel)&0x01)<<REFS0 ) ;
		
	/* 2)Get the most suitable pre-scalar */ 
	
	uint8_t u8LoopCount;
	for( u8LoopCount = 0; u8LoopCount < PRESCALAR_NUM ;u8LoopCount++)
	{
		if(clk[u8LoopCount].u32TempFreq < u32MaxFreq )
		{
			break;
		}
	}
	ADCSRA_REG &=0xF8; 
	ADCSRA_REG |=(clk[u8LoopCount].u8RegVal & 0x03);
	
	/* i only support right adjust for 10 bit result and left adjust for 8 bit result */
	/* 3)Set ADC justify */
	#if ADC_JUSTIFY == 'L'
	/* Left adjust ADC result to allow easy 8 bit reading */
	ADMUX_REG |= (1 << ADLAR); 
	#elif ADC_JUSTIFY == 'R'
    /*Right adjust */
	ADMUX_REG |= (0 << ADLAR); 
	#endif
	/* 4) Enable ADC Interrupt */
	if( enable_interrupt == 1)
	{	
	ADCSRA_REG |= (1 << ADIE);
	/* 6) set global interrupt */
	sei();
	}	
	/* enable */ 
	if(trigger != Free_Running_mode )
	{	
	ADCSRA_REG |=(1<<ADATE);
	}	
	/* 8)set channel */
	ADMUX_REG |=((channel)&0x1F);
	/* 5) Enable ADC */
	ADCSRA_REG |= (1 << ADEN);
	
	if( enable_interrupt == 1)	
	{	
	/* 7) Start conversions single conversion */
	ADCSRA_REG |= (1 << ADSC);
	}	
	/* set trigger */
	SFIOR_REG |= ((trigger)&07)<<5;
	
}
/* #if enable_interrupt == 1 */
ISR(ADC_vect)
{  
	 #if ADC_JUSTIFY == 'R'
	/*read the low byte of the converted data*/
	ADC_result = ADCL_REG;
	/*read the high byte of the converted data*/
	ADC_result |= ADCH_REG <<8;
	
	#elif ADC_JUSTIFY == 'L'
	ADC_result = ADCH ;
	#endif		
	/* set the start conversion to begin next conversion  */
	ADCSRA_REG |= (1 << ADSC);

}

/*************************************************************************************************************************
*  in case of right adjust this function is used
* 
*  this function Return the 10 bit of the result if (ADC_JUSTIFY == 'R') right justify
*
* \param None
*
* \return the ADC 10 bit result
*
**************************************************************************************************************************/
uint16_t adcResult_u16()
{  
	if( enable_interrupt == 0)
	{
		
	ADCSRA_REG |= (1 << ADSC);
	while(!(ADCSRA_REG & (1<<ADIF)));
	
	ADC_result = ADCL_REG;
	ADC_result |= ADCH_REG<<8;
	
	ADCSRA_REG|=(1<<ADIF);
	} 
	    
    return ADC_result;	
}

/*************************************************************************************************************************
*   in case of left adjust this function is used
*
*   this function Return the 8 bit of the result if (ADC_JUSTIFY == 'L') left justify
*
*  \param None
*
*  \return the ADC 8 bit result
*
**************************************************************************************************************************/
uint8_t adcResult_u8()
{
	if( enable_interrupt == 0)
	{
		
	ADCSRA_REG |= (1 << ADSC);
	
	while(!(ADCSRA_REG & (1<<ADIF)));
	ADC_result = ADCH_REG;
	ADCSRA_REG|=(1<<ADIF);
	}	
		
	return ADC_result;
}
