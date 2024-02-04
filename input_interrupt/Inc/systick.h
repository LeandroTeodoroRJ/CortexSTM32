/*
 *
 * File name: systick.h
 * Description: It's drive for systick counter
 * Hostpage: https://github.com/LeandroTeodoroRJ/CortexSTM32
 * Stable: Yes
 * Version: 1.0
 * Last Update: 02.02.24
 * Current: Yes
 * Maintainer: leandroteodoro.rj@gmail.com
 * Architecture: MCU STM32F411re
 * Compile/Interpreter: STM Cube IDE Ver:1.13.1
 * Access: Public
 * Changelog: No
 * Readme and Documents: No
 * Links: No
 * Other Notes: Nucleo is conected to ttyACM0 serial port
 *
 *
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

#include "stm32f4xx.h"

#define SYSTICK_LOAD_VAL_MS		16000		//Value for miliseconds load. (n = 0.001 * systemclock)
#define CRTL_ENABLE				(1U << 0)
#define CTRL_CLKSRC				(1U << 2)
#define CTRL_COUNTFLAG			(1U << 16)

void systickDelayMs(int delay);

#endif /* SYSTICK_H_ */
