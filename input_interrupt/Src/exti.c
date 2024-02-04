/*
 * exti.c
 *
 *  	Update on: Feb 4, 2024
 *      Author: leandro
 */

#include "exti.h"

#define GPIOCEN		(1U << 2)
#define SYSCFG_EN	(1U << 14)

void pc13_exti_init(void){
	// Dissable global interrupt
	__disable_irq();

	// Enable GPIOC clock
	RCC->AHB1ENR |= GPIOCEN;

	// Set PC13 as input
	GPIOC->MODER &=~(1U << 26);
	GPIOC->MODER &=~(1U << 27);

	// Enable clock acssess to SYSCFG
	RCC->APB2ENR |= SYSCFG_EN;

	// Select PORTC to connect to EXTI13
	SYSCFG->EXTICR[3] |= (1U << 5);

	// Unmask EXTI13
	EXTI->IMR |= (1U << 13);

	// Select the trigger edge (falling)
	EXTI->FTSR |= (1U << 13);

	// Enable to EXTI13 line in NVIC
	NVIC_EnableIRQ(EXTI15_10_IRQn);

	// Enable global interrupt
	__enable_irq();
}
