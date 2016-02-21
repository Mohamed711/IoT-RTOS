
#include "ADC.h"

#if ADC_JUSTIFY == 'L'
static volatile u8 ADC_result;
#elif ADC_JUSTIFY == 'R'
static volatile u16 ADC_result;
#endif
u8  enable_interrupt;
void adc_off(void)
{
	// disable interrupt
	ADCSRA &= (0 << ADIE);
	// disable ADC
	ADCSRA &= (0 << ADEN);
}

void adc_init(u8 voltage_ref_sel , u8 enable_interrupt_, u8 trigger , u8 channel,u32 u32MaxFreq ) 
{
	// 1)Set ADC reference
	enable_interrupt=enable_interrupt_;
	ADMUX |= (  (( (voltage_ref_sel)&0x02)>>1)<<REFS1 )| (((voltage_ref_sel)&0x01)<<REFS0 ) ;
		
	// 2) Get the most suitable pre-scalar 
	
	u8 u8LoopCount;
	for( u8LoopCount = 0; u8LoopCount < PRESCALAR_NUM ;u8LoopCount++)
	{
		if(clk[u8LoopCount].u32TempFreq < u32MaxFreq )
		{
			break;
		}
	}
	ADCSRA &=0xF8;
	ADCSRA |=(clk[u8LoopCount].u8RegVal & 0x03);
	
	
    
	

	
	// i only support right adjust
	// 3)Set ADC justify
	#if ADC_JUSTIFY == 'L'
	ADMUX |= (1 << ADLAR); // Left adjust ADC result to allow easy 8 bit reading
	#elif ADC_JUSTIFY == 'R'
	ADMUX |= (0 << ADLAR); // Right adjust
	#endif
	
	if( enable_interrupt == 1)
	{	
    //4) Enable ADC Interrupt
	ADCSRA |= (1 << ADIE);
	//6) set global interrupt
	sei();
	}	
	// enable 
	if(trigger != Free_Running_mode )
	{	
	ADCSRA |=(1<<ADATE);
	}	
	//8)set channel
	ADMUX |=((channel)&0x1F);
	//5) Enable ADC
	ADCSRA |= (1 << ADEN);
	
	if( enable_interrupt == 1)	
	{
		
	
	//7) Start conversions single conversion
	ADCSRA |= (1 << ADSC);
	}	
	//set trigger
	SFIOR |= ((trigger)&07)<<5;
	//_delay_ms(25);
}
//#if enable_interrupt == 1
ISR(ADC_vect)
{  
	 #if ADC_JUSTIFY == 'R'
	/*read the low byte of the converted data*/
	ADC_result = ADCL;
	/*read the high byte of the converted data*/
	ADC_result |= ADCH <<8;
	
	#elif ADC_JUSTIFY == 'L'
	ADC_result = ADCH ;
	#endif		
	/* set the start conversion to begin next conversion  */
	ADCSRA |= (1 << ADSC);

}
//#endif


u16 ADC_u16_result()
{  
	if( enable_interrupt == 0)
	{
		
	
	//ADMUX=(ADMUX & 0xE0); // clear channel
	//ADMUX |=((ADC_volt_CH_config.channel)&0x1F);
	
	//7) Start conversions single conversion
	//_delay_ms(30);
	ADCSRA |= (1 << ADSC);
	// while(ADCSRA & (1<<ADSC));
	 while(!(ADCSRA & (1<<ADIF)));
	
	 ADC_result = ADCL;
	 ADC_result |= ADCH<<8;
	
	 ADCSRA|=(1<<ADIF);
	}     

    return ADC_result;	
	
}

// in case of left adjust 

u8 ADC_u8_result()
{
	if( enable_interrupt == 0)
	{
		
	
	//ADMUX=(ADMUX & 0xE0); // clear channel
	//ADMUX |=((ADC_volt_CH_config.channel)&0x1F);
	//_delay_ms(100);
	//7) Start conversions single conversion
	ADCSRA |= (1 << ADSC);
	//_delay_ms(100);
	//while(ADCSRA & (1<<ADSC));
	while(!(ADCSRA & (1<<ADIF)));
	ADC_result = ADCH;
	 ADCSRA|=(1<<ADIF);
	}		
	return ADC_result;
}
