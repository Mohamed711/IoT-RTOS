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

//channel
#define channel_ADC0 0b00000
#define channel_ADC1 0b00001
#define channel_ADC2 0b00010
#define channel_ADC3 0b00011
#define channel_ADC4 0b00100
#define channel_ADC5 0b00101
#define channel_ADC6 0b00110
#define channel_ADC7 0b00111
#define channel_ADC0_ADC0_10x  0b01000
#define channel_ADC1_ADC0_10x  0b01001
#define channel_ADC0_ADC0_200x 0b01010
#define channel_ADC1_ADC0_200x 0b01011
#define channel_ADC2_ADC2_10x  0b01100
#define channel_ADC3_ADC2_10x  0b01101
#define channel_ADC2_ADC2_200x 0b01110
#define channel_ADC3_ADC2_200x 0b01111

#define channel_ADC0_ADC1_1x 0b10000
#define channel_ADC1_ADC1_1x 0b10001
#define channel_ADC2_ADC1_1x 0b10010
#define channel_ADC3_ADC1_1x 0b10011
#define channel_ADC4_ADC1_1x ob10100
#define channel_ADC5_ADC1_1x 0b10101
#define channel_ADC6_ADC1_1x 0b10110
#define channel_ADC7_ADC1_1x ob10111

#define channel_ADC0_ADC2_1x ob11000
#define channel_ADC1_ADC2_1x ob11001
#define channel_ADC2_ADC2_1x ob11010
#define channel_ADC3_ADC2_1x ob11011
#define channel_ADC4_ADC2_1x ob11100
#define channel_ADC5_ADC2_1x ob11101
#define channel_122v ob11110
#define channel_0v ob11111





#define AREF_Internal_Vref_turned_off  0x00
#define AVCC_with_external_capacitor_at_AREF_pin  0x01
#define Internal_2_dot_56V_Voltage_Reference_with_external_cap_at_AREF_pin  0x03

#define Right_JUSTIFY 0x00
#define Left_JUSTIFY  0x01 
//#define ADC_JUSTIFY Left_JUSTIFY



#define PRESCALAR_NUM	0x07
#endif /* SPI_CFG_H_ */