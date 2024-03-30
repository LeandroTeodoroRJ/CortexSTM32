/*
 *
 * File name: uart.h
 * Description: Driver for USART2
 * Hostpage: https://github.com/LeandroTeodoroRJ/CortexSTM32
 * Stable: Yes
 * Version: 1.3
 * Last Update: 30.03.24
 * Current: Yes
 * Maintainer: leandroteodoro.rj@gmail.com
 * Architecture: MCU STM32F411re
 * Compile/Interpreter: STM Cube IDE Ver:1.13.1
 * Access: Public
 * Changelog: No
 * Readme and Documents: See in Doc folder.
 * Links: No
 * Other Notes:
 * 	1- Nucleo is conected to ttyACM0 serial port;
 * 	2- The system frequency is set to 16MHz (usart.c definitions).
 * Functions:
 * 	void enable_usart_clock(uint8_t usart_number)	--Enable clock to usart
 * 		usart_number  ::  USART_1, USART_2 or USART_6
 *
 * 	void uart_rxtx_init(USART_TypeDef *pUSART, uint32_t UsartBaudRate)  --Initialize USART
 * 		pUSART :: Pointer to usart struct
 * 		UsartBaudRAte :: Baudrate value
 *
 * 	char usart_read(USART_TypeDef *pUSART)  --Return a char from usart
 * 		pUSART :: Pointer to usart struct
 *
 * 	void usart_write(USART_TypeDef *pUSART, int ch)  --Send one char to USART
 * 		pUSART :: Pointer to usart struct
 * 		ch :: char value
 *
 * 	void output_default_usart_stream(USART_TypeDef *pUSART)  --Default output usart for printf function
 * 		pUSART :: Pointer to usart struct
 *
 * 	void enable_usart_rx_interrupt(USART_TypeDef *pUSART)  --Enable RX interrupt
 * 		pUSART :: Pointer to usart struct
 *
 * 	void disable_usart_rx_interrupt(USART_TypeDef *pUSART)  --Disble RX interrupt
 * 		pUSART :: Pointer to usart struct
 *
 */

#ifndef USART_H_
#define USART_H_

#include <stdint.h>
#include "stm32f4xx.h"

// Clock usarts numbers
#define USART_1			1
#define USART_2			2
#define USART_6			6

#define NOT_READY_TO_READ	0

// Functions prototypes
void uart_rxtx_init(USART_TypeDef *pUSART, uint32_t UsartBaudRate);
char usart_read(USART_TypeDef *pUSART);
void usart_write(USART_TypeDef *pUSART, int ch);
void enable_usart_clock(uint8_t usart_number);
void output_default_usart_stream(USART_TypeDef *pUSART);
void enable_usart_rx_interrupt(USART_TypeDef *pUSART);
void disable_usart_rx_interrupt(USART_TypeDef *pUSART);
uint32_t usart_data_ready_read(USART_TypeDef *pUSART);


#endif /* USART_H_ */
