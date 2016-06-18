

#include"ADC_HAL_TIVA.h"
void HAL_ADC_Init(ADC_InitTypeDef *adc)
{


	uint32_t ADCn_BASE;
	SysCtlPeripheralEnable(adc->ADCn); /*enabling adc periph*/

	switch(adc->ADCn)
	{
	case SYSCTL_PERIPH_ADC0 :
		ADCn_BASE = ADC0_BASE;
		break;
	case SYSCTL_PERIPH_ADC1 :
		ADCn_BASE = ADC1_BASE;
		break;
	}




	ADCSequenceConfigure(ADCn_BASE, adc->seq, adc->ADC_TRIGGER, adc->prio);


	int8_t count;
	adc->steps=4;
	switch (adc->seq)
	{
	case 0: adc->steps=8;
	break;
	case 3: adc->steps=1;
	break;

	}

	for(count=0;count<adc->steps-1 ;++count)
	{
		ADCSequenceStepConfigure(ADCn_BASE, adc->seq, count, adc->src|((1 & adc->diff)<<1));
	}



	ADCSequenceStepConfigure(ADCn_BASE,adc->seq,adc->steps-1,adc->src|ADC_CTL_IE|ADC_CTL_END|((1 & adc->diff)<<1));


	ADCSequenceEnable(ADCn_BASE, adc->seq);

}
void HAL_ADC_read(ADC_InitTypeDef *adc)
{
	uint32_t ADCn_BASE;
	switch(adc->ADCn)
		{
		case SYSCTL_PERIPH_ADC0 :
			ADCn_BASE = ADC0_BASE;
			break;
		case SYSCTL_PERIPH_ADC1 :
			ADCn_BASE = ADC1_BASE;
			break;
		}


			ADCIntClear(ADCn_BASE,adc->seq);
			ADCProcessorTrigger(ADCn_BASE,adc->seq);

			/*maybe use interrupt*/
			while(!ADCIntStatus(ADCn_BASE, 1, 0))
			{
			}



			ADCSequenceDataGet(ADCn_BASE,adc->seq, (adc->ui32ADCnValue));
			int8_t counting;

}


bool HAL_ADC_OFF()
{
	//Before using this function, it is highly recommended that the event trigger
	//is changed to ADC_TRIGGER_NEVER on all enabled sequencers to prevent the ADC from
	//starting after checking the busy status


	if(ADCBusy(ADC0_BASE)||ADCBusy(ADC1_BASE))
	{ return false;}
	else
	{

		return true;
	}
}
