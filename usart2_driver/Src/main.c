/*
 *
 * Project name: USART RX TX
 * Description: Writing the driver for USART2
 * Hostpage: https://github.com/LeandroTeodoroRJ/CortexSTM32
 * Stable: Yes
 * Version: 1.0
 * Last Update: 26.01.24
 * Current: Yes
 * Dependences: GPIO Ver 1.3.1 ; USART Ver 1.2
 * Maintainer: leandroteodoro.rj@gmail.com
 * Architecture: MCU STM32F411re
 * Compile/Interpreter: STM Cube IDE Ver:1.13.1
 * Access: Public
 * Changelog: No
 * Readme and Documents: See in Doc folder.
 * Links: No
 * Other Notes: Nucleo is conected to ttyACM0 serial port
 *
 *
 */

#include <stdio.h>
#include <stdint.h>
#include <usart.h>
#include "gpio.h"
#include "stm32f4xx.h"

#define UART_BAUDRATE	115200

char key;

int main(void)
{
	// Enable clock to GPIOA --LED
	enable_gpio_clock(PORT_A);

	// Set PA5 as output
	gpio_config(GPIOA, OUTPUT_MODE, PIN5);


	/****************Configure usart gpio pin***************/
	/*Enable clock access to gpioa */
	enable_gpio_clock(PORT_A);

	/*Set PA2 mode to alternate function mode*/
	gpio_config(GPIOA, ALTERNATE_FUNCTION, PIN2);

	/*Set PA2 alternate function type to UART_TX (AF07)*/
	alternate_function_setup(GPIOA, PIN2, 07);

	/*Set PA3 mode to alternate function mode*/
	gpio_config(GPIOA, ALTERNATE_FUNCTION, PIN3);

	/*Set PA3 alternate function type to UART_TX (AF07)*/
	alternate_function_setup(GPIOA, PIN3, 07);

	enable_usart_clock(USART_2);
	uart2_rxtx_init(USART2, UART_BAUDRATE);
	output_default_usart_stream(USART2);	//To use with printf funcion
	while(1)
	{
		key = usart_read(USART2);
		if (key == '1'){
			gpio_bit_toggle(GPIOA, PIN5);	//Led pin
			printf("You receiver a special key. \n");
		}
	}
}

