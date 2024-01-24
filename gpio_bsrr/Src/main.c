/*
 *
 * Project name: Led Toggle with BSRR Register
 * Description: Toggle on-board led in NUCLEO-F411re using bit set/reset register
 * Hostpage: https://github.com/LeandroTeodoroRJ/CortexSTM32
 * Stable: Yes
 * Version: 1.0
 * Last Update: 24.01.24
 * Current: Yes
 * Maintainer: leandroteodoro.rj@gmail.com
 * Architecture: MCU STM32F411re
 * Compile/Interpreter: STM Cube IDE Ver:1.13.1
 * Access: Public
 * Changelog: No
 * Readme and Documents: No
 * Links: No
 * Other Notes:
 * 	1- You must include the include path in
 * 	project properties -> C/C++ general -> Path and Symbols -> Includes
 * 	2- See the stm32f4xx.h, you must include your processor definition STM32F411xE in
 * 	project properties -> C/C++ general -> Path and Symbols -> Symbols (Add...)
 * Code Structure Comments: None
 *
 */


#include "stm32f4xx.h"

#define GPIOAEN		(1U << 0)
#define PIN5		(1U << 5)
#define LED_PIN		PIN5

int main(void){
	// Enable clock
	RCC->AHB1ENR |= GPIOAEN;

	// Configure Pin
	GPIOA->MODER |= (1U << 10);
	GPIOA->MODER &=~(1U << 11);


	while(1){
		GPIOA->BSRR |= (1U << 5);
		for (int i=0; i<100000; i++){}
		GPIOA->BSRR |= (1U << 21);
		for (int i=0; i<100000; i++){}

	}
}
