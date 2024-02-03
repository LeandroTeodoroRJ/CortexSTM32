/*
 *
 * Project name: Output Compare
 * Description: How we can use the timer compare. We will use
 *   timer 2 to toggle the led (PA5).
 * Hostpage: https://github.com/LeandroTeodoroRJ/CortexSTM32
 * Stable: Yes
 * Version: 1.0
 * Last Update: 03.02.24
 * Current: Yes
 * Maintainer: leandroteodoro.rj@gmail.com
 * Architecture: MCU STM32F411re
 * Compile/Interpreter: STM Cube IDE Ver:1.13.1
 * Access: Public
 * Changelog: No
 * Readme and Documents: See in Doc folder.
 * Links: No
 * Other Notes: No
 *
 *
 */

#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "tim.h"


int main(void)
{
	tim2_pa5_output_compare();
	while(1)
	{

	}
}

