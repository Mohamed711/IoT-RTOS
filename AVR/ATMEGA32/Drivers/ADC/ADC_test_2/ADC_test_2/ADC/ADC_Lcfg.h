/*
 * ADC_Lcfg.h
 *
 * Created: 31-Jan-16 11:22:08 PM
 *  Author: nada
 */ 


#ifndef ADC_LCFG_H_
#define ADC_LCFG_H_
#include "StdTypes.h"
#include "ADC_CFG.h"

typedef struct
{
	 u8 voltage_ref_sel ;
}ADC_Config_Voltage_reference_selection ;

typedef struct
{
	u32 u32MaxFreq;
	
}Freq_of_micro;

extern const ADC_Config_Voltage_reference_selection ADC_volt_config;
extern const Freq_of_micro micro_freq;
#endif 
/* ADC_LCFG_H_ */


