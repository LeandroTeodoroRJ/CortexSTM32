/*
 *
 * Project name: Led Toggle Struct
 * Description: Toggle on-board led in NUCLEO-F411re and learn about struct registers declaration.
 * Hostpage: https://github.com/LeandroTeodoroRJ/CortexSTM32
 * Stable: Yes
 * Version: 1.0
 * Last Update: 22.01.24
 * Current: Yes
 * Maintainer: leandroteodoro.rj@gmail.com
 * Architecture: MCU STM32F411re
 * Compile/Interpreter: STM Cube IDE Ver:1.13.1
 * Access: Public
 * Changelog: No
 * Readme and Documents: Read in Doc folder
 * Links: No
 * Other Notes: No
 * Code Structure Comments: None
 *
 */

#include <stdint.h>

#define PERIPH_BASE				(0x40000000UL)	//See this address in datasheet - memory map
#define AHB1PERIPH_OFFSET		(0x00020000UL)
#define AHB1PERIPH_BASE			(PERIPH_BASE + AHB1PERIPH_OFFSET)
#define GPIOA_OFFSET			(0x0000UL)
#define GPIOA_BASE				(AHB1PERIPH_BASE + GPIOA_OFFSET)
#define RCC_OFFSET				(0x3800UL)
#define RCC_BASE				(AHB1PERIPH_BASE + RCC_OFFSET)

#define GPIOAEN					(1U << 0)  //Set AHB1EN bit 0

//Led: PA5
#define PIN5					(1U << 5)
#define LED_PIN					PIN5

#define __IO 	volatile

typedef struct{
	__IO uint32_t MODER;	// Configure the pin to Input, output, alt. func. or analog - Offset: 0x00
	__IO uint32_t OTYPER;	// Configure the pin to push-pull or open-drain - Offset: 0x04
	__IO uint32_t OSPEEDR;	// Configure the speed mode - Offset: 0x08
	__IO uint32_t PUPDR;	// Configure pull-up(down) mode - Offset: 0x0C
	__IO uint32_t IDR;		// Store the Input value(read only) - Offset: 0x10
	__IO uint32_t ODR;		// Store the Output value - Offset: 0x14
	__IO uint32_t BSRR;		// Offset: 0x1C
	__IO uint32_t LCKR;		// Offset: 0x20
	__IO uint32_t AFR[2];	// Configure the 16 modes of alternate function - Offset: 0x24
}GPIO_TypeDef;

typedef struct{
	__IO uint32_t DUMMY[12];		//For preserve the register memory struct
	__IO uint32_t AHB1ENR;
}RCC_TypeDef;

#define RCC		((RCC_TypeDef*)RCC_BASE)		//Typecast struct definition
#define GPIOA	((GPIO_TypeDef*)GPIOA_BASE)


int main(void){

	// 1. Enable clock to access to GPIOA
	RCC->AHB1ENR |= GPIOAEN;

	// 2. Set PA5 as output pin (see the reference manual)
	GPIOA->MODER |=  (1U << 10);	//Set bit 10
	GPIOA->MODER &= ~(1U << 11);	//Reset bit 11


	while(1){
		// 3. Toggle PA5
		GPIOA->ODR ^= LED_PIN;

		//Delay time
		for(int i=0; i<1000000; i++);

	}

}





























