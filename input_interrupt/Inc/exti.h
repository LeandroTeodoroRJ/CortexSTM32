/*
 *
 * File name: exti.h
 * Description: EXTI driver.
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
 * Other Notes:
 *   IMPORTANT: Connect a jump wire from PA5 to PA6.
 *
 *
 */

#ifndef EXTI_H_
#define EXTI_H_

#include "stm32f4xx.h"

#define LINE13		(1U << 13)

void pc13_exti_init(void);

#endif /* EXTI_H_ */
