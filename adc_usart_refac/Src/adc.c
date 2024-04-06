/*
 * adc.c
 *
 *  Created on: Apr 06, 2024
 *      Author: leandro
 */


#include "stm32f4xx.h"
#include "adc.h"

#define GPIOAEN			(1U << 0)
#define ADC1EN			(1U << 8)
#define CR2_ADON		(1U << 0)
#define CR2_SWSTART		(1U << 30)
#define CR2_CONT		(1U << 1)
#define SR_EOC			(1U << 1)


void enable_adc_module(void){
	// 3-Enable adc module
	ADC1->CR2 |= CR2_ADON;
}


void start_continuos_conversion(void){
	// Enable continuos conversion
	ADC1->CR2 |= CR2_CONT;
	// Start ADC conversion
	ADC1->CR2 |= CR2_SWSTART;
}

uint32_t adc_read(void){
	// Waiting for convertion completed
	while (!(ADC1->SR & SR_EOC)) {}  // EOC returns 1 if conversion is completed

	// Read conversion result
	return ADC1->DR;
}

void enable_adc_clock(void){
	// Enable clock to ADC module
	RCC->APB2ENR |= ADC1EN;
}

void add_sequence_group(uint8_t sequence_number, uint32_t channel){
	// Configure ADC parameters
	// 1-Conversion sequence start
	ADC1->SQR3 |= (channel << (sequence_number * 5));  //Put one in SQ1 group (channel 1)
}

void sequence_length(uint32_t number_of_sequences_groups){
	// 2-Convertion length
	ADC1->SQR1 |= ((number_of_sequences_groups - 1) <<  20);
}


