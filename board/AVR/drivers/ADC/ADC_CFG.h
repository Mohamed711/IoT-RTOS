/*
 * SPI_CFG.h
 *
 * Created: 31-Jan-16 11:22:32 PM
 *  Author: nada
 */ 


#ifndef SPI_CFG_H_
#define SPI_CFG_H_

#define PRESCALAR_NUM	0x07
// ADC Registers
#define ADMUX_REG	 *((uint8_t volatile *const)0x27)
#define ADCSRA_REG	 *((uint8_t volatile *const)0x26)
#define ADCL_REG	 *((uint8_t volatile *const)0x24)
#define ADCH_REG	 *((uint8_t volatile *const)0x25)
#define SFIOR_REG    *((uint8_t volatile *const)0x50)

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
#define ch_ADC0 0b00000
#define ch_ADC1 0b00001
#define ch_ADC2 0b00010
#define ch_ADC3 0b00011
#define ch_ADC4 0b00100
#define ch_ADC5 0b00101
#define ch_ADC6 0b00110
#define ch_ADC7 0b00111
#define ch_ADC0_ADC0_10x  0b01000
#define ch_ADC1_ADC0_10x  0b01001
#define ch_ADC0_ADC0_200x 0b01010
#define ch_ADC1_ADC0_200x 0b01011
#define ch_ADC2_ADC2_10x  0b01100
#define ch_ADC3_ADC2_10x  0b01101
#define ch_ADC2_ADC2_200x 0b01110
#define ch_ADC3_ADC2_200x 0b01111

#define ch_ADC0_ADC1_1x 0b10000
#define ch_ADC1_ADC1_1x 0b10001
#define ch_ADC2_ADC1_1x 0b10010
#define ch_ADC3_ADC1_1x 0b10011
#define ch_ADC4_ADC1_1x 0b10100
#define ch_ADC5_ADC1_1x 0b10101
#define ch_ADC6_ADC1_1x 0b10110
#define ch_ADC7_ADC1_1x 0b10111

#define ch_ADC0_ADC2_1x 0b11000
#define ch_ADC1_ADC2_1x 0b11001
#define ch_ADC2_ADC2_1x 0b11010
#define ch_ADC3_ADC2_1x 0b11011
#define ch_ADC4_ADC2_1x 0b11100
#define ch_ADC5_ADC2_1x 0b11101
#define ch_122v 0b11110
#define ch_0v 0b11111





#define AREF_Internal_Vref_turned_off  0x00
#define AVCC_with_external_capacitor_at_AREF_pin  0x01
#define Internal_Voltage_Reference  0x03
// ADC Auto trigger Source Selection

#define Free_Running_mode 0b000
#define Analog_comparator 0b001
#define Eternal_Interrupt_Request0 0b010
#define Timer_conter0_compare_match 0b011
#define Timer_conter0_overflow 0b100
#define Timer_conter1_compare_match_B 0b101
#define Timer_conter1_overflow  0b110
#define Timer_conter0_capture_Event 0b111


#define ADC_JUSTIFY 'R'

#endif /* SPI_CFG_H_ */