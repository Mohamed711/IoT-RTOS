
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
		
	/// get the most suitable prescaler
	/*
	u8 u8LoopCount;
	u8 vu8_prescaler_num;
     u32 x_min = micro_freq.u32MaxFreq/200;
	
	
	for (u8LoopCount=2;u8LoopCount<256;2*u8LoopCount)
	{
	  if (x_min < u8LoopCount)
	  {
		    u8LoopCount;
		  break;
	  		  
	  }
	}
	ADCSRA |=(u8LoopCount&0x03);
	*/
	//////
	
	// Set ADC prescaler
	#if ADC_PRESCALER == 2
	ADCSRA |= (0 << ADPS2) | (0 << ADPS1) | (1 << ADPS0); // Prescaler 2
	#elif ADC_PRESCALER == 4
	ADCSRA |= (0 << ADPS2) | (1 << ADPS1) | (0 << ADPS0); // Prescaler 4
	#elif ADC_PRESCALER == 8
	ADCSRA |= (0 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Prescaler 8
	#elif ADC_PRESCALER == 16
	ADCSRA |= (1 << ADPS2) | (0 << ADPS1) | (0 << ADPS0); // Prescaler 16
	#elif ADC_PRESCALER == 32
	ADCSRA |= (1 << ADPS2) | (0 << ADPS1) | (1 << ADPS0); // Prescaler 32
	#elif ADC_PRESCALER == 64
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (0 << ADPS0); // Prescaler 64
	#elif ADC_PRESCALER == 128
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Prescaler 128
	#endif
	
	
	
	
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