/*
 *
 * File name: ADC driver
 * Description: ADC driver for continuos conversion
 * Hostpage: https://github.com/LeandroTeodoroRJ/CortexSTM32
 * Stable: Yes
 * Version: 1.2
 * Last Update: 06.04.24
 * Current: Yes
 * Maintainer: leandroteodoro.rj@gmail.com
 * Architecture: MCU STM32F411re
 * Compile/Interpreter: STM Cube IDE Ver:1.13.1
 * Access: Public
 * Changelog: No
 * Dependences: stdint.h; stm32f4xx.h; adc.c
 * Links: No
 * Other Notes:
 * 	1- The STM32F411 has the ADC1 only
 *
 *	Internal functions:
 *		void enable_adc_clock(void)  --Enable clock to ADC1
 *
 *		void add_sequence_group(uint8_t sequence_number, uint32_t channel)  --Add a channel in sequence group
 *			sequence_number  ::  Valid sequence 0 to 6 (SQR3 only for this version)
 *			channel  ::  Channel number
 *
 *		void sequence_length(uint32_t number_of_sequences_groups)  --Number of sequences groups to converstion
 *			number_of_sequences_groups  ::  Number of groups instances add on add_sequence_group
 *
 *		void enable_adc_module(void)   --Enable ADC peripheral
 *
 *		void start_continuos_conversion(void)  --It runs a continuos convertion
 *
 *
 */


#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

//Sequences group definitions
#define SEQUENCE_1	0
#define SEQUENCE_2	1
#define SEQUENCE_3	2
#define SEQUENCE_4	3
#define SEQUENCE_5	4
#define SEQUENCE_6	5

void enable_adc_clock(void);
void add_sequence_group(uint8_t sequence_number, uint32_t channel);
void sequence_length(uint32_t number_of_sequences_groups);
void enable_adc_module(void);
void start_continuos_conversion(void);
uint32_t adc_read(void);

#endif /* ADC_H_ */
