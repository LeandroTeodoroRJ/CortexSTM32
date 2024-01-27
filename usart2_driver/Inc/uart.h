/*
 *
 * File name: uart.h
 * Description: Driver for USART2
 * Hostpage: https://github.com/LeandroTeodoroRJ/CortexSTM32
 * Stable: Yes
 * Version: 1.0
 * Last Update: 27.01.24
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

#ifndef UART_H_
#define UART_H_

#include <stdint.h>
#include "stm32f4xx.h"

// Registers declarations
#define GPIOAEN			(1U<<0)
#define UART2EN			(1U<<17)

// Bits declarations
#define CR1_TE			(1U<<3)
#define CR1_RE			(1U<<2)
#define CR1_UE			(1U<<13)
#define SR_TXE			(1U<<7)
#define SR_RXNE			(1U<<5)

// Other declarations
#define SYS_FREQ		16000000
#define APB1_CLK		SYS_FREQ
#define UART_BAUDRATE		115200


// Functions prototypes
void uart2_rxtx_init(void);
char uart2_read();
void uart2_write(int ch);


#endif /* UART_H_ */
