/*
 * SPI_CFG.h
 *
 * Created: 31-Jan-16 11:22:32 PM
 *  Author: nada
 */ 


#ifndef SPI_CFG_H_
#define SPI_CFG_H_
//to dooo
// address of ADMUX reg
//address of ADCSRA reg
// address of ADCL
// address of ADCH
//ADMUX register
#define REFS1  7
#define REFS0  6
#define ADLAR  5
#define MUX4   4
#define MUX3   3
#define MUX2   2
#define MUX1   1
#define MUX0   0
// ADCSRA  (ADR Control and status Register)
#define ADEN   7
#define ADSC   6
#define ADATE  5
#define ADIF   4
#define ADIE   3
#define ADPS2  2
#define ADPS1  1
#define ADPSO  0




#define AREF_Internal_Vref_turned_off  0x00
#define AVCC_with_external_capacitor_at_AREF_pin  0x01
#define Internal_2_dot_56V_Voltage_Reference_with_external_cap_at_AREF_pin  0x03

#define Right_JUSTIFY 0x00
#define Left_JUSTIFY  0x01 
//#define ADC_JUSTIFY Left_JUSTIFY

#endif /* SPI_CFG_H_ */