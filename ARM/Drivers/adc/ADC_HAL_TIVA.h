
#ifndef DRIVERS_ADC_ADC_HAL_TIVA_H_
#define DRIVERS_ADC_ADC_HAL_TIVA_H_

#include<stdint.h>
#include<stdbool.h>
#include"adc.h"
#include "../sysctl/sysctl.h"
#include "../inc/hw_memmap.h"
typedef struct
{
	uint32_t ADCn;
	uint8_t seq;
	uint32_t ADC_TRIGGER;
	uint32_t prio;
	uint32_t steps;
	uint32_t src;
	uint32_t *ui32ADCnValue;
	bool diff;


	}
ADC_InitTypeDef;

typedef struct
{

	}
ADC_handle_typedef;




void HAL_ADC_Init(ADC_InitTypeDef *adc);
void HAL_ADC_read(ADC_InitTypeDef *adc);
bool HAL_ADC_OFF();



#endif /* DRIVERS_ADC_ADC_HAL_TIVA_H_ */
