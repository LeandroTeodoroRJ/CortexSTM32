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

#define SR_RXNE						(1U<<5)
#define S6_TRANSFER_COMP_INT_FLAG	(1U << 21)  //TCIFx: Stream x transfer complete interrupt flag

void uart2_rxtx_init(void);
char uart2_read();
void uart2_rxtx_interrupt_init(void);
void dma1_stream6_init(uint32_t src, uint32_t dest, uint32_t len);


#endif /* UART_H_ */
