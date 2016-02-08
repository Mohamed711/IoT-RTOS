
#include "ADC.h"
#include "GPIO.h"
#include "ADC_Lcfg.h"
#include "ADC_CFG.h"

#include <avr/io.h>
#include <avr/interrupt.h>


static volatile u16 u16_ADC_result;


void adc_init(void) 
{
	// Set ADC reference
	
		ADMUX |= (  (( (ADC_volt_config.voltage_ref_sel)&0x02)>>1)<<REFS1 )| (((ADC_volt_config.voltage_ref_sel)&0x01)<<REFS0 ) ;
		
	
	
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
	 // Start conversions
	ADCSRA |= (1 << ADSC);
	
}
ISR(ADC_vect)
{
	/*read the low byte of the converted data*/
	u16_ADC_result = ADCL;
	/*read the high byte of the converted data*/
	u16_ADC_result |= ADCH <<8;
	
	/* set the start conversion to begin next conversion  */
	ADCSRA |= (1 << ADSC);

}
s16 ADC_u16_result(u8 channel)
{  
	//set channel 
	ADMUX |=(channel&0x1F);
	
    return u16_ADC_result;	
}