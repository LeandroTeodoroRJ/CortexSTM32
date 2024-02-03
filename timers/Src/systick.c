/*
 * systick.c
 *
 *  Created on: Feb 1, 2024
 *      Author: leandro
 */

#include "systick.h"

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
