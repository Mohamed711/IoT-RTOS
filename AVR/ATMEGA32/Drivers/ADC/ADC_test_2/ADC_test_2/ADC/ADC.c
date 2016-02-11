
#include "ADC.h"
#include "GPIO.h"
#include "ADC_Lcfg.h"
#include "ADC_CFG.h"

#include <avr/io.h>
#include <avr/interrupt.h>


#if ADC_JUSTIFY == 'L'
static volatile u8 ADC_result;
#else
static volatile u16 ADC_result;
#endif

void adc_off(void)
{
	// disable interrupt
	ADCSRA &= (0 << ADIE);
	// disable ADC
	ADCSRA &= (0 << ADEN);
}
void adc_init(void) 
{
	// Set ADC reference
	
		ADMUX |= (  (( (ADC_volt_CH_config.voltage_ref_sel)&0x02)>>1)<<REFS1 )| (((ADC_volt_CH_config.voltage_ref_sel)&0x01)<<REFS0 ) ;
		
	
	
	/*Get the most suitable pre-scalar */
	
	u8 u8LoopCount;
	for( u8LoopCount = 0; u8LoopCount < PRESCALAR_NUM ;u8LoopCount++)
	{
		if(clk[u8LoopCount].u32TempFreq < micro_freq.u32MaxFreq )
		{
			break;
		}
	}
	ADCSRA &=0xF8;
	ADCSRA |=(clk[u8LoopCount].u8RegVal & 0x03);
	
	
    
	
	// i only support right adjust
	// Set ADC justify
	#if ADC_JUSTIFY == 'L'
	ADMUX |= (1 << ADLAR); // Left adjust ADC result to allow easy 8 bit reading
	#elif ADC_JUSTIFY == 'R'
	ADMUX |= (0 << ADLAR); // Right adjust
	#endif
		
    // Enable ADC Interrupt
	ADCSRA |= (1 << ADIE);
	
	// Enable ADC
	ADCSRA |= (1 << ADEN);
	
	//set global interrupt
	sei();
	 // Start conversions single conversion
	ADCSRA |= (1 << ADSC);
	//set channel
	ADMUX |=((ADC_volt_CH_config.channel)&0x1F);
	
}
ISR(ADC_vect)
{  
	 #if ADC_JUSTIFY == 'R'
	/*read the low byte of the converted data*/
	ADC_result = ADCL;
	/*read the high byte of the converted data*/
	ADC_result |= ADCH <<8;
	#elif ADC_JUSTIFY=='L'
	ADC_result = ADCH ;
	#endif	
	
	
	/* set the start conversion to begin next conversion  */
	ADCSRA |= (1 << ADSC);

}

u16 ADC_u16_result()
{  
	
    return ADC_result;	
}
// in case of left adjust 
u8 ADC_u8_result()
{
	
	return ADC_result;
}
