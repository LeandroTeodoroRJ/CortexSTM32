/*
 *
 * Project name: USART RX TX DMA
 * Description: How it acssess the usart using DMA.
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
 * Other Notes:
 * 	1- Nucleo is conected to ttyACM0 serial port
 * 	2- This program uses the DMA1-Stream_6-Channel_4 to acssess the USART2 module
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
char message[31] = "Hello STM32 from DMA transfer\n\r";

int main(void)
{
	// Enable clock to GPIOA
	RCC->AHB1ENR |= GPIOAEN;

	// Set PA5 as output
	GPIOA->MODER |= (1U << 10);
	GPIOA->MODER &=~(1U << 11);

	uart2_rxtx_init();
	dma1_stream6_init((uint32_t) message, (uint32_t) &USART2->DR, 31);
	while(1)
	{

	}
}


static void dma_callback(void){
		GPIOA->ODR ^= LED_PIN;  //Toggle led if transfer is completed
}

void DMA1_Stream6_IRQHandler(void){
	// Check for transfer complete interrupt
	if (DMA1->HISR & S6_TRANSFER_COMP_INT_FLAG){
		// Clear flag
		DMA1->HIFCR |= S6_TRANSFER_COMP_INT_FLAG;	//For clear is not same register!

		//Do something
		dma_callback();
	}
}


