/*
 * ADC_Lcfg.c
 *
 * Created: 31-Jan-16 11:21:47 PM
 *  Author: nada
 */ 

#include "ADC_Lcfg.h"

const ADC_Config_Voltage_reference_and_CH_selection ADC_volt_CH_config =
{
	
   Internal_2_dot_56V_Voltage_Reference_with_external_cap_at_AREF_pin ,
	 ch_ADC3_ADC2_1x,
	 Free_Running_mode,
};
const CLK_Rate clk[7] =
{
{F_CPU/2,0},
{F_CPU/4,2},
{F_CPU/8,3},
{F_CPU/16,4},
{F_CPU/32,5},
{F_CPU/64,6},
{F_CPU/128,7}
};
const Freq_of_micro micro_freq=
{
	75000000UL
	};

