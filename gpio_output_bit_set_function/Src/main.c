/*
 *
 * Project name: Bit set and reset
 * Description: Creating a useful bit set and reset functions
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
#include "utils.h"

#define GPIOAEN		0
#define PIN5		5
#define LED_PIN		PIN5
#define PIN_OUT		01
#define MODER5		10
#define SLOW_TIME	1000000
#define FAST_TIME	100000



int main(void){
	// Enable clock
	bit_set(&(RCC->AHB1ENR), GPIOAEN);


	// Configure Pin
	bit_set(&(GPIOA->MODER), 10);
	bit_reset(&(GPIOA->MODER), 11);

	while(1){
		bit_toggle(&(GPIOA->ODR), LED_PIN);
		for (int i=0; i < SLOW_TIME; i++){}

	}
}


