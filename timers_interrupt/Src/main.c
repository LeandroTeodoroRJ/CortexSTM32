/*
 *
 * Project name: Timers Interrupt
 * Description: How it know to use the mcu timer 2 with interrupt mode.
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
 * Other Notes: Nucleo is conected to ttyACM0 serial port
 *
 *
 */

#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "systick.h"
#include "tim.h"

#define GPIOAEN		(1U<<0)
#define PIN5		(1U << 5)
#define LED_PIN		PIN5

uint32_t sensor_value;

static void tim2_callback(void);

int main(void)
{
	// Enable clock to GPIOA
	RCC->AHB1ENR |= GPIOAEN;

	// Configure Pin
	GPIOA->MODER |= (1U << 10);
	GPIOA->MODER &=~(1U << 11);

	// Init the peripherals
	uart2_rxtx_init();
	tim2_1hz_interrupt_init();

	while(1)
	{

	}
}


static void tim2_callback(void){
	GPIOA->ODR ^= LED_PIN;
	printf("A second passed!! \n");
}

void TIM2_IRQHandler(void){
	// Clear UIF - Ipdate interrupt flag
	TIM2->SR &=~ TIMSR_UIF;
	tim2_callback();
}
