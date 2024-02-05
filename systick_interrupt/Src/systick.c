/*
 * systick.c
 *
 *  Created on: Feb 1, 2024
 *      Author: leandro
 */

#include "systick.h"

#define SYSTICK_LOAD_VAL_MS		16000		//Value for miliseconds load. (n = 0.001 * systemclock)
#define CRTL_ENABLE				(1U << 0)
#define CTRL_CLKSRC				(1U << 2)
#define CTRL_COUNTFLAG			(1U << 16)
#define ONE_SEC_TIME			16000000
#define SYSTICK_INT_EN			(1U << 1)  //TICKINT - Enables SysTick exception request

void systickDelayMs(int delay){
	// Reaload with number of clock in miliseconds
	SysTick->LOAD = SYSTICK_LOAD_VAL_MS;

	// Clear systick current value
	SysTick->VAL = 0;

	// Enable systick end select internal clock source
	SysTick->CTRL = CRTL_ENABLE | CTRL_CLKSRC;

	for (int i=0; i < delay; i++){
		// Wait until COUNTFLAG is set
		while((SysTick->CTRL & CTRL_COUNTFLAG) == 0){ }
	}

	SysTick->CTRL = 0;
}

void systick_1hz_interrupt(void){
	// Reaload with number of clock in miliseconds
	SysTick->LOAD = ONE_SEC_TIME - 1;

	// Clear systick current value
	SysTick->VAL = 0;

	// Enable systick end select internal clock source
	SysTick->CTRL = CRTL_ENABLE | CTRL_CLKSRC;

	// Enable systick interrupt
	SysTick->CTRL |= SYSTICK_INT_EN;
}
