/*
 *
 * Project name: USART RX TX Interrupt
 * Description: Coding USART2 interrupt mode
 * Hostpage: https://github.com/LeandroTeodoroRJ/CortexSTM32
 * Stable: Yes
 * Version: 1.0
 * Last Update: 26.01.24
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

#define GPIOAEN			(1U<<0)
#define GPIOA_5			(1U<<5)
#define LED_PIN			GPIOA_5

char key;

int main(void)
{
	// Enable clock to GPIOA
	RCC->AHB1ENR |= GPIOAEN;

	// Set PA5 as output
	GPIOA->MODER |= (1U << 10);
	GPIOA->MODER &=~(1U << 11);

	uart2_rxtx_interrupt_init();
	while(1)
	{

	}
}


static void usart_callback(void){
	key = USART2->DR;
	if (key == '1'){
		GPIOA->ODR ^= LED_PIN;  //Toggle led if receiver a char 1
	}

}

void USART2_IRQHandler(void){
	// Check if RXNE is set
	if (USART2->SR & SR_RXNE){
		usart_callback();
	}
}



