/*
 *
 * File name: Timers drive
 * Description: How it know to use the mcu timers.
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
 * Other Notes: No
 *
 *
 */

#ifndef TIM_H_
#define TIM_H_

#include "stm32f4xx.h"

#define	TIMSR_UIF		(1U << 0)
#define TIMSR_CC1IF		(1U << 1)

void tim2_1hz_init(void);
void tim2_pa5_output_compare(void);
void tim3_pa6_input_capture(void);

#endif /* TIM_H_ */
