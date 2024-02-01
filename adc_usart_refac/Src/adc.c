/*
 * adc.c
 *
 *  Created on: Jan 30, 2024
 *      Author: leandro
 */


#include "stm32f4xx.h"
#include "adc.h"

#define GPIOAEN			(1U << 0)
#define ADC1EN			(1U << 8)
#define ADC_CH1			(1U << 0)
#define ADC_SEQ_LEN_1	0x00
#define CR2_ADON		(1U << 0)
#define CR2_SWSTART		(1U << 30)
#define CR2_CONT		(1U << 1)
#define SR_EOC			(1U << 1)


void pa1_adc_init(void){
	// Enable clock to GPIOA
	RCC->AHB1ENR |= GPIOAEN;

	// Set PA1 input mode analog
	GPIOA->MODER |= (1U << 2);
	GPIOA->MODER |= (1U << 3);

	// Enable clock to ADC module
	RCC->APB2ENR |= ADC1EN;

	// Configure ADC parameters
	// 1-Conversion sequence start
	ADC1->SQR3 |= ADC_CH1;  //Put one in SQ1 group (channel 1)

	// 2-Conservion length
	ADC1->SQR1 |= ADC_SEQ_LEN_1;

	// 3-Enable adc module
	ADC1->CR2 |= CR2_ADON;
}


void start_conversion(void){
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
