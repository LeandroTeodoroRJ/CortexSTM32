/*
 *
 * Project name: Input Capture
 * Description: How we can use the input capture. The PA5
 *   is the input signal source to PA6.
 * Hostpage: https://github.com/LeandroTeodoroRJ/CortexSTM32
 * Stable: Yes
 * Version: 1.0
 * Last Update: 04.02.24
 * Current: Yes
 * Maintainer: leandroteodoro.rj@gmail.com
 * Architecture: MCU STM32F411re
 * Compile/Interpreter: STM Cube IDE Ver:1.13.1
 * Access: Public
 * Changelog: No
 * Readme and Documents: See in Doc folder.
 * Links: No
 * Other Notes:
 *   IMPORTANT: Connect a jump wire from PA5 to PA6.
 *
 *
 */

#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "tim.h"

int timestamp = 0;

int main(void)
{
	tim2_pa5_output_compare();
	tim3_pa6_input_capture();
	while(1)
	{
		while(!(TIM3->SR & TIMSR_CC1IF)){ } //Waiting UIF set
		timestamp = TIM3->CCR1;
//		printf("A second passed!! \n");
	}
}

