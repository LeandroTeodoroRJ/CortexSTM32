/*
 *
 * Project name: Systick Interrupt
 * Description: It controll the delay time with systick interrupt.
 * Hostpage: https://github.com/LeandroTeodoroRJ/CortexSTM32
 * Stable: Yes
 * Version: 1.0
 * Last Update: 02.02.24
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
#include "systick.h"

#define GPIOAEN		(1U<<0)
#define PIN5		(1U << 5)
#define LED_PIN		PIN5

uint32_t sensor_value;

static void systick_callback(void);

int main(void)
{
	// Enable clock to GPIOA
	RCC->AHB1ENR |= GPIOAEN;

	// Configure Pin
	GPIOA->MODER |= (1U << 10);
	GPIOA->MODER &=~(1U << 11);

	// Init the peripherals
	uart2_rxtx_init();
	systick_1hz_interrupt();
	while(1)
	{

	}
}

static void systick_callback(void){
	GPIOA->ODR ^= LED_PIN;
	printf("A second passed!! \n");
}

void SysTick_Handler(void){
	systick_callback();
}
