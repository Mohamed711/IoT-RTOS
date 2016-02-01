
#include "ADC.h"
#include "GPIO.h"
//#include "ADC_Lcfg.h"
//#include "ADC_CFG.h"

#include <avr/io.h>
#include <avr/interrupt.h>


static volatile u16 u16_ADC_result;

/*
 * init adc
 */
void adc_init(void) 
{
	// Set ADC reference
	
		
		#if ADC_REF == 0
		ADMUX |= (0 << REFS1) | (0 << REFS0); // AREF_Internal_Vref_turned_off
		#elif ADC_REF == 1
		ADMUX |= (0 << REFS1) | (1 << REFS0); // AVCC_with_external_capacitor_at_AREF_pin
		#elif ADC_REF == 3
		ADMUX |= (1 << REFS1) | (1 << REFS0); // Internal_2.56V_Voltage_Reference_with_external_cap_at_AREF_pin
		#endif
	//select channel
	#if channel == 0 // "channel_ADCO" 
	ADMUX |=0b00000;
	#elif channel ==1  //"channel_ADC1" 
	ADMUX |=0b00001;
	#elif channel ==2 //"channel_ADC2" 
	ADMUX |=0b00010;
	#elif channel ==3 //"channel_ADC3" 
	ADMUX |=0b00011;
	#elif channel ==4 //"channel_ADC4" 
	ADMUX |=0b00100;
	#elif channel ==5 //"channel_ADC5" 
	ADMUX |=0b00101;
	#elif channel ==6 //"channel_ADC6" 
	ADMUX |=0b00110;
	#elif channel ==7 //"channel_ADC7" 
	ADMUX |=0b00111;
	
	#endif
	
	/// get the most suitable prescaler
	/*
	u8 u8LoopCount;
	
	for (u8LoopCount=2;u8LoopCount<256;2*u8LoopCount)
	{
	
	}
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
s16 ADC_u16_result(void)
{
return u16_ADC_result;	
}