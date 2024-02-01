/*
 * uart.h
 *
 *  Created on: Jan 26, 2024
 *      Author: leandro
 */

#ifndef UART_H_
#define UART_H_

#include <stdint.h>
#include "stm32f4xx.h"

void uart2_rxtx_init(void);
char uart2_read();


#endif /* UART_H_ */
