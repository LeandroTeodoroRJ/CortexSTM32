/*
 * gpio.c
 *
 *  	Updated on: Mar 12, 2024
 *      Author: leandro
 */


#include "gpio.h"


void enable_gpio_clock(uint8_t port){
	if 	(port == PORT_A){
		RCC->AHB1ENR |= (1 << 0);
	}
	else if (port == PORT_B){
		RCC->AHB1ENR |= (1 << 1);
	}
	else if (port == PORT_C){
		RCC->AHB1ENR |= (1 << 2);
	}
	else if (port == PORT_D){
		RCC->AHB1ENR |= (1 << 3);
	}
	else if (port == PORT_E){
		RCC->AHB1ENR |= (1 << 4);
	}
	else if (port == PORT_H){
		RCC->AHB1ENR |= (1 << 7);
	}
}

void gpio_config(GPIO_TypeDef *pGPIO, uint32_t direction_mode, uint32_t pin_number){
	pGPIO->MODER &=~ ((uint32_t)3 << pin_number*2);
	pGPIO->MODER |= (direction_mode << pin_number*2);

}

void gpio_load_value(GPIO_TypeDef *pGPIO, uint32_t value){
	pGPIO->ODR = value;
}

void gpio_bit_toggle(GPIO_TypeDef *pGPIO, uint32_t pin_number){
	pGPIO->ODR ^= (1 << pin_number);
}

void digital_pin_state(GPIO_TypeDef *pGPIO, uint32_t pin_number, uint8_t state){
	if (state == SET){
		pGPIO->BSRR |= (1U << pin_number);
	}else{
		pGPIO->BSRR |= (1U << (pin_number+16));
	}
}

uint32_t read_gpio_pin(GPIO_TypeDef *pGPIO, uint32_t pin_number){
	return (pGPIO->IDR & pin_number);
}

void alternate_function_setup(GPIO_TypeDef *pGPIO, uint32_t pin_number, uint32_t alternate_function_value){
	if (pin_number > PIN7){
		pin_number = pin_number - 8;
		pGPIO->AFR[1] &=~ ((uint32_t)15 << pin_number*4);  //Clear all AFR bits of pin
		pGPIO->AFR[1] |=  (alternate_function_value << pin_number*4);  //Set alternate value
	}else{
		pGPIO->AFR[0] &=~ ((uint32_t)15 << pin_number*4);  //Clear all AFR bits of pin
		pGPIO->AFR[0] |=  (alternate_function_value << pin_number*4);  //Set alternate value
	}
}





