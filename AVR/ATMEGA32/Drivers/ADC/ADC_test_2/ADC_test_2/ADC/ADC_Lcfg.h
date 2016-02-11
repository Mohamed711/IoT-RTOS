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
	 u8 channel;
}ADC_Config_Voltage_reference_and_CH_selection ;

typedef struct
{
	u32 u32MaxFreq;
	
}Freq_of_micro;

typedef struct
{
	u32 u32TempFreq;
	u8 u8RegVal;
}CLK_Rate;

extern const CLK_Rate clk[PRESCALAR_NUM];
extern const ADC_Config_Voltage_reference_and_CH_selection ADC_volt_CH_config;
extern const Freq_of_micro micro_freq;
#endif 
/* ADC_LCFG_H_ */


