/*
 * tim.c  ::  Timers source file
 *
 *  	Update on: Feb 3, 2024
 *      Author: leandro
 */


#include "tim.h"

#define TIM2EN			(1U << 0)
#define TIMCR1_EN		(1U << 0)
#define TIM2_INT_EN		(1U << 0)  //UIE: Update interrupt enable

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


void tim2_1hz_interrupt_init(void){
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

	// Enable timer interrupt
	TIM2->DIER |= TIM2_INT_EN;

	// Enable timer 2 interrupt in NVIC
	NVIC_EnableIRQ(TIM2_IRQn);
}
