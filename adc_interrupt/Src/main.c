/*
 *
 * Project name: ADC Interrupt
 * Description: How it use ADC continuos conversion with interrupt mode.
 * Hostpage: https://github.com/LeandroTeodoroRJ/CortexSTM32
 * Stable: Yes
 * Version: 1.0
 * Last Update: 28.01.24
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

#define GPIOAEN			(1U<<0)

uint32_t sensor_value;

static void adc_callback(void);

int main(void)
{
	// Enable clock to GPIOA
	RCC->AHB1ENR |= GPIOAEN;

	// Init the peripherals
	uart2_rxtx_init();
	pa1_adc_interrupt_init();

	// Start the conversion
	start_conversion();

	while(1)
	{

	}
}

static void adc_callback(void){
	sensor_value = ADC1->DR;
	printf("Sensor value: %d \n \r", (int)sensor_value);
}

void ADC_IRQHandler(void){
	if(ADC1->SR & SR_EOC){
		ADC1->SR |= SR_EOC;
		adc_callback();
	}
}

