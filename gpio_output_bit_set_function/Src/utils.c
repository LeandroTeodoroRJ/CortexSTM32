/*
 *
 * File name: utils.c
 * Last Update: 24.01.24
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

// 	bit_toggle(&(GPIOA->ODR), 5);
void bit_toggle(__IO uint32_t *reg, uint32_t bit){
	*reg ^= (1 << bit);
}
