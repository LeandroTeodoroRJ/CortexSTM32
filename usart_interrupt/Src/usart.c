/*
 * uart.c
 *
 *  	Uodated on: Mar 30, 2024
 *      Author: leandro
 */

#include <usart.h>

//Internal definitions
#define SYS_FREQ		16000000		//Bus frequency
#define APB1_CLK		SYS_FREQ

// Bits declarations
#define CR1_TE			(1U<<3)
#define CR1_RE			(1U<<2)
#define CR1_UE			(1U<<13)
#define SR_TXE			(1U<<7)
#define SR_RXNE			(1U<<5)
#define RX_INT_EN		(1U << 5)  //RXNEIE: RXNE interrupt enable


// Internal functions prototypes
static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk,  uint32_t BaudRate);
static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate);
int __io_putchar(int ch);

uint32_t *usart_stream;		//Global pointer to usart out stream function

// Functions definitions
void uart_rxtx_init(USART_TypeDef *pUSART, uint32_t UsartBaudRate){

	/*Configure baudrate*/
	uart_set_baudrate(pUSART,APB1_CLK,UsartBaudRate);

	/*Configure the transfer direction*/
	// Enable transmitter and receiver
	 pUSART->CR1 =  (CR1_TE | CR1_RE);

	/*Enable uart module*/
	 pUSART->CR1 |= CR1_UE;
}


char usart_read(USART_TypeDef *pUSART){
	/*Make sure the receive data register is not empty*/
	while(!(pUSART->SR & SR_RXNE)){}

	/* Read data */
	return pUSART->DR;
}


void usart_write(USART_TypeDef *pUSART, int ch){
  /*Make sure the transmit data register is empty*/
	while(!(pUSART->SR & SR_TXE)){}

  /*Write to transmit data register*/
	pUSART->DR	=  (ch & 0xFF);
}

//It's necessary to declare this function to use with printf
int __io_putchar(int ch){
	usart_write((USART_TypeDef*) usart_stream, ch);
	return ch;
}


static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk,  uint32_t BaudRate){
	USARTx->BRR =  compute_uart_bd(PeriphClk,BaudRate);
}

static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate){
	return ((PeriphClk + (BaudRate/2U))/BaudRate);
}

void enable_usart_clock(uint8_t usart_number){
	if 	(usart_number == USART_1){
		RCC->APB2ENR |= (1 << 4);
	}
	else if (usart_number == USART_2){
		RCC->APB1ENR |= (1 << 17);
	}
	else if (usart_number == USART_6){
		RCC->APB2ENR |= (1 << 5);
	}
}

void output_default_usart_stream(USART_TypeDef *pUSART){
	usart_stream = (uint32_t*) pUSART;	//Cast and global save
}

void enable_usart_rx_interrupt(USART_TypeDef *pUSART){
	// Enable RX interrupt
	 pUSART->CR1 |= RX_INT_EN;
}

void disable_usart_rx_interrupt(USART_TypeDef *pUSART){
	// Enable RX interrupt
	 pUSART->CR1 &=~ RX_INT_EN;
}


uint32_t usart_data_ready_read(USART_TypeDef *pUSART){
	// Check if RXNE is set
	return (pUSART->SR & SR_RXNE);
}


