/*
 *
 * Project name: Input Interrupt
 * Description: How we can use the NVIC to gerate a input interrupt.
 * Hostpage: https://github.com/LeandroTeodoroRJ/CortexSTM32
 * Stable: Yes
 * Version: 1.0
 * Last Update: 04.02.24
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
#include "tim.h"
#include "uart.h"
#include "exti.h"

#define GPIOAEN		(1U << 0)
#define PIN5		(1U << 5)
#define LED_PIN		PIN5

static void exti_callback(void);

int main(void)
{
	// Enable clock
	RCC->AHB1ENR |= GPIOAEN;

	// Configure Led Pin
	GPIOA->MODER |= (1U << 10);
	GPIOA->MODER &=~(1U << 11);

	uart2_rxtx_init();
	pc13_exti_init();
	while(1)
	{

	}
}

static void exti_callback(void){
	printf("BTN pressed... \n \r");
	GPIOA->ODR ^= LED_PIN;
}


void EXTI15_10_IRQHandler(void){  //This name is defined on vector table file
	if(EXTI->PR & LINE13){		  //This interrupt occured by line 13?
		// Clear PR flag - This bit is cleared by programming it to ‘1’.
		EXTI->PR |= LINE13;

		// Do something
		exti_callback();
	}
}
