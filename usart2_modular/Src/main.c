/*
 *
 * Project name: USART TX
 * Description: Using USART with printf instruction
 * Hostpage: https://github.com/LeandroTeodoroRJ/CortexSTM32
 * Stable: Yes
 * Version: 1.0
 * Last Update: 26.01.24
 * Current: Yes
 * Maintainer: leandroteodoro.rj@gmail.com
 * Architecture: MCU STM32F411re
 * Compile/Interpreter: STM Cube IDE Ver:1.13.1
 * Access: Public
 * Changelog: No
 * Readme and Documents: See in Doc folder.
 * Links: No
 * Other Notes: Nucleo is conected to ttyACM0
 *
 *
 */

#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "uart.h"


int main(void)
{

	uar2_tx_init();

	while(1)
	{
		printf("Send a string to standard output...");
	}
}

