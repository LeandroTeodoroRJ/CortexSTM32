/*
 *
 * Project name: Bit set and reset
 * Description: Creating a useful bit set and reset functions. This is a code
 *    refactoring for utils package.
 * Hostpage: https://github.com/LeandroTeodoroRJ/CortexSTM32
 * Stable: Yes
 * Version: 1.0
 * Last Update: 24.01.24
 * Current: Yes
 * Maintainer: leandroteodoro.rj@gmail.com
 * Architecture: MCU STM32F411re
 * Compile/Interpreter: STM Cube IDE Ver:1.13.1
 * Dependences: GPIO driver - version 1.1
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
#include "gpio.h"

#define LED_PIN		PIN5
#define SLOW_TIME	1000000
#define FAST_TIME	100000


int main(void){
	// Enable clock
	enable_gpio_clock(PORT_A);

	// Configure Pin
	gpio_config(
			GPIOA,
			OUTPUT_MODE,
			PIN5
			);

	while(1){
		gpio_bit_toggle(GPIOA, LED_PIN);
		for (int i=0; i < FAST_TIME; i++){}

	}
}


