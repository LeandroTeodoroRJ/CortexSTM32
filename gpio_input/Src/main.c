/*
 *
 * Project name: GPIO Input
 * Description: Test the input button to turn on the led.
 * Hostpage: https://github.com/LeandroTeodoroRJ/CortexSTM32
 * Stable: Yes
 * Version: 1.0
 * Last Update: 24.01.24
 * Current: Yes
 * Maintainer: leandroteodoro.rj@gmail.com
 * Architecture: MCU STM32F411re
 * Compile/Interpreter: STM Cube IDE Ver:1.13.1
 * Dependences: GPIO version 1.2.2
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

#define LED_ONBOARD		PIN5
#define BTN_ONBOARD		PIN13
#define BUTTON_PRESSED	0
#define LED_ON			SET
#define LED_OFF			RESET

int main(void){
	// Enable clock
	enable_gpio_clock(PORT_A);
	enable_gpio_clock(PORT_C);

	// Configure PA5 as output
	gpio_config(GPIOA, OUTPUT_MODE,	LED_ONBOARD);

	// Configure PC13 as input
	gpio_config(GPIOC, INPUT_MODE, BTN_ONBOARD);

	while(1){
		if (read_gpio_pin(GPIOC, PIN13) == BUTTON_PRESSED){
			digital_pin_state(GPIOA, PIN5, LED_ON);
		}else{
			digital_pin_state(GPIOA, PIN5, LED_OFF);
		}
	}
}
