/*
 *
 * File name: utils.c
 * Description: Utils user functions
 * Hostpage: https://github.com/LeandroTeodoroRJ/CortexSTM32
 * Stable: Yes
 * Version: 1.0
 * Last Update: 24.01.24
 * Current: Yes
 * Maintainer: leandroteodoro.rj@gmail.com
 * Architecture: MCU STM32F411re
 * Compile/Interpreter: STM Cube IDE Ver:1.13.1
 * Access: Public
 * Changelog: No
 * Readme and Documents: No
 * Links: No
 * Other Notes: No
 * Code Structure Comments: None
 *
 */

#include "utils.h"


// 	bit_set(&(RCC->AHB1ENR), 0);
void bit_set(__IO uint32_t *reg, uint32_t bit){
	*reg |= (1 << bit);
}

//	bit_set(&(GPIOA->MODER), 10);
void bit_reset(__IO uint32_t *reg, uint32_t bit){
	*reg &= ~(1 << bit);
}

// 		bit_toggle(&(GPIOA->ODR), 5);
void bit_toggle(__IO uint32_t *reg, uint32_t bit){
	*reg ^= (1 << bit);
}
