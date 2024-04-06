/*
 *
 * Project name: ADC and USART
 * Description: Code for refactory ADC and USART driver and test
 * Hostpage: https://github.com/LeandroTeodoroRJ/CortexSTM32
 * Stable: Yes
 * Version: 1.0
 * Last Update: 01.02.24
 * Current: Yes
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
#include "stm32f4xx.h"
#include "uart.h"
#include "adc.h"

#define GPIOAEN					(1U<<0)
#define CHANNEL_1				1
#define NUMBER_OF_GROUPS_1		1

uint32_t sensor_value;

void bios(void);

int main(void)
{
	bios();	//Start bios definitions

	// Init the peripherals
	enable_adc_clock();
	uart2_rxtx_init();
	add_sequence_group(SEQUENCE_1, CHANNEL_1);
	sequence_length(NUMBER_OF_GROUPS_1);
	enable_adc_module();

	// Start the conversion
	start_continuos_conversion();

	while(1)
	{
		sensor_value = adc_read();
		printf("Sensor value: %d \n \r", (int)sensor_value);
	}
}

void bios(void){
	// Enable clock to GPIOA
	RCC->AHB1ENR |= GPIOAEN;

	// Enable clock to GPIOA
	RCC->AHB1ENR |= GPIOAEN;

	// Set PA1 input mode analog
	GPIOA->MODER |= (1U << 2);
	GPIOA->MODER |= (1U << 3);

}



