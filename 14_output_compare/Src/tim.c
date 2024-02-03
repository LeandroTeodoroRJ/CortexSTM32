/*
 * tim.c  ::  Timers source file
 *
 *  	Update on: Feb 3, 2024
 *      Author: leandro
 */


#include "tim.h"

#define TIM2EN			(1U << 0)
#define TIMCR1_EN		(1U << 0)
#define TIMCCER_CC1E	(1U << 0)  //CC1E: Capture/Compare 1 output enable.
#define GPIOAEN			(1U<<0)

void tim2_1hz_init(void){
	// Enable clock to timer 2
	RCC->APB1ENR |= TIM2EN;

	// Set the prescaller value
	TIM2->PSC = 1600 - 1 ;	// Then 16000000(sysclk) / 16000(psc) = 10000

	// Set auto-reload value
	TIM2->ARR = 10000 - 1;  //So 10000 / 10000 = 1Hz

	// Clear counter
	TIM2->CNT = 0;

	// Reset CR1 and enable timer
	TIM2->CR1 = TIMCR1_EN;

}

void tim2_pa5_output_compare(void){
	// Enable clock GPIOA
	RCC->AHB1ENR |= GPIOAEN;

	// Set PA5 to alternate function
	GPIOA->MODER &=~(1U << 10);
	GPIOA->MODER |= (1U << 11);

	// Set PA5 to TIMER2_CH1 alternate function (AF01)
	GPIOA->AFR[0] |= (1U << 20);

	// Enable clock to timer 2
	RCC->APB1ENR |= TIM2EN;

	// Set the prescaller value
	TIM2->PSC = 1600 - 1 ;	// Then 16000000(sysclk) / 16000(psc) = 10000

	// Set auto-reload value
	TIM2->ARR = 10000 - 1;  //So 10000 / 10000 = 1Hz

	// Set output comapre toggle mode
	// Bits 6:4 OC1M: Output Compare 1 mode
	// 011: Toggle - OC1REF toggles when TIMx_CNT=TIMx_CCR1. (See in reference manual)
	TIM2->CCMR1 = (1U << 4) | (1U << 5);

	// Enable timer 2 channel 1 in compare mode
	TIM2->CCER |= TIMCCER_CC1E;



	// Clear counter
	TIM2->CNT = 0;

	// Reset CR1 and enable timer
	TIM2->CR1 = TIMCR1_EN;

}
