/*
 *
 * File name: utils.h
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
 * Code Structure Comments:
 * (1)Set a one bit in register
 * void bit_set(__IO uint32_t *reg, uint32_t bit);
 * (2)Reset a one bit in register
 * void bit_reset(__IO uint32_t *reg, uint32_t bit);
 * (3)Toggle a bit in register
 * void bit_toggle(__IO uint32_t *reg, uint32_t bit);
 *
 *
 */


#ifndef UTILS_H_
#define UTILS_H_


#include <stdint.h>
#define __IO	volatile

void bit_set(__IO uint32_t *reg, uint32_t bit);
void bit_reset(__IO uint32_t *reg, uint32_t bit);
void bit_toggle(__IO uint32_t *reg, uint32_t bit);



#endif /* UTILS_H_ */
