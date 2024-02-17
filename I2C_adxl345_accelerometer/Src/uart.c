/*
 * uart.c
 *
 *  Created on: Jan 26, 2024
 *      Author: leandro
 */

#include "uart.h"

#define GPIOAEN			(1U<<0)
#define UART2EN			(1U<<17)

#define CR1_TE			(1U<<3)
#define CR1_RE			(1U<<2)
#define RX_INT_EN		(1U << 5)  //RXNEIE: RXNE interrupt enable
#define CR1_UE			(1U<<13)
#define SR_TXE			(1U<<7)
#define DMA1_EN			(1U << 21)
#define STREAM_EN			(1U << 0)
#define MEMORY_INC_EN		(1U << 10)
#define TRANSF_COMPL_INT_EN	(1U << 4)	//TCIE: Transfer complete interrupt enable
#define DIRECT_MODE_DIS		(1U << 2)	//DMDIS: Direct mode disable
#define FIFO_ERR_INT_EN		(1U << 7)	//FEIE: FIFO error interrupt enable
#define	TRANSMITTER_DMA_EN	(1U << 7)	//DMAT: DMA enable transmitter

#define SYS_FREQ		16000000
#define APB1_CLK		SYS_FREQ

#define UART_BAUDRATE		115200

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk,  uint32_t BaudRate);
static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate);
void uart2_write(int ch);

//It's necessary to declare this function to use with printf
int __io_putchar(int ch){
	uart2_write(ch);
	return ch;
}

void dma1_stream6_init(uint32_t src, uint32_t dest, uint32_t len){
	// Enable clock acssess DMA
	RCC->AHB1ENR |= DMA1_EN;

	// Disable DMA1 Stream6
	DMA1_Stream6->CR &=~STREAM_EN;

	// Clear all interrupt flags of Stream6
	DMA1->HIFCR |= (1U << 16);  //Writing 1 to this bit clears the corresponding HTIFx flag in the DMA_HISR register
	DMA1->HIFCR |= (1U << 18);
	DMA1->HIFCR |= (1U << 19);
	DMA1->HIFCR |= (1U << 20);
	DMA1->HIFCR |= (1U << 21);

	// Set the destination buffer
	DMA1_Stream6->PAR = dest;

	// Set source buffer
	DMA1_Stream6->M0AR = src;

	// Set length
	DMA1_Stream6->NDTR = len;

	// Select Stream6 - Channel 4
	DMA1_Stream6->CR |= (1U << 27);	// Wrinting binary 100 in bits 27:25

	// Enable memory increment
	DMA1_Stream6->CR |= MEMORY_INC_EN;

	// Configure transfer direction - memory to peripheral
	DMA1_Stream6->CR |= (1U << 6);  // Wrinting binary 01 in bits 07:06

	// Enable DMA transfer complete interrupt
	DMA1_Stream6->CR |= TRANSF_COMPL_INT_EN;

	// Enable direct mode and disable FIFO
	DMA1_Stream6->FCR &=~DIRECT_MODE_DIS;
	DMA1_Stream6->FCR &=~FIFO_ERR_INT_EN;

	// Enable DMA1 Stream6
	DMA1_Stream6->CR |= STREAM_EN;

	// Enable USART2 transmitter DMA
	USART2->CR3 |= TRANSMITTER_DMA_EN;

	// DMA interrupt enable - NVIC_EnableIRQ(DMA)
	NVIC_EnableIRQ(DMA1_Stream6_IRQn);
}



void uart2_rxtx_init(void){
	/****************Configure uart gpio pin***************/
	/*Enable clock access to gpioa */
	RCC->AHB1ENR |= GPIOAEN;

	/*Set PA2 mode to alternate function mode*/
	GPIOA->MODER &=~(1U<<4);
	GPIOA->MODER |= (1U<<5);

	/*Set PA2 alternate function type to UART_TX (AF07)*/
	GPIOA->AFR[0] |= (1U<<8);
	GPIOA->AFR[0] |= (1U<<9);
	GPIOA->AFR[0] |= (1U<<10);
	GPIOA->AFR[0] &= ~(1U<<11);

	/*Set PA3 mode to alternate function mode*/
	GPIOA->MODER &=~(1U<<6);
	GPIOA->MODER |= (1U<<7);

	/*Set PA3 alternate function type to UART_TX (AF07)*/
	GPIOA->AFR[0] |= (1U<<12);
	GPIOA->AFR[0] |= (1U<<13);
	GPIOA->AFR[0] |= (1U<<14);
	GPIOA->AFR[0] &= ~(1U<<15);


	/****************Configure uart module ***************/
	/*Enable clock access to uart2 */
	RCC->APB1ENR |= UART2EN;

	/*Configure baudrate*/
	uart_set_baudrate(USART2,APB1_CLK,UART_BAUDRATE);

	/*Configure the transfer direction*/
	// Enable transmitter and receiver
	 USART2->CR1 =  (CR1_TE | CR1_RE);

	/*Enable uart module*/
	 USART2->CR1 |= CR1_UE;
}

void uart2_rxtx_interrupt_init(void){
	/****************Configure uart gpio pin***************/
	/*Enable clock access to gpioa */
	RCC->AHB1ENR |= GPIOAEN;

	/*Set PA2 mode to alternate function mode*/
	GPIOA->MODER &=~(1U<<4);
	GPIOA->MODER |= (1U<<5);

	/*Set PA2 alternate function type to UART_TX (AF07)*/
	GPIOA->AFR[0] |= (1U<<8);
	GPIOA->AFR[0] |= (1U<<9);
	GPIOA->AFR[0] |= (1U<<10);
	GPIOA->AFR[0] &= ~(1U<<11);

	/*Set PA3 mode to alternate function mode*/
	GPIOA->MODER &=~(1U<<6);
	GPIOA->MODER |= (1U<<7);

	/*Set PA3 alternate function type to UART_TX (AF07)*/
	GPIOA->AFR[0] |= (1U<<12);
	GPIOA->AFR[0] |= (1U<<13);
	GPIOA->AFR[0] |= (1U<<14);
	GPIOA->AFR[0] &= ~(1U<<15);


	/****************Configure uart module ***************/
	/*Enable clock access to uart2 */
	RCC->APB1ENR |= UART2EN;

	/*Configure baudrate*/
	uart_set_baudrate(USART2,APB1_CLK,UART_BAUDRATE);

	/*Configure the transfer direction*/
	// Enable transmitter and receiver
	 USART2->CR1 =  (CR1_TE | CR1_RE);

	// Enable RX interrupt
	 USART2->CR1 |= RX_INT_EN;

	// Enable USART2 interrupt in NVIC
	 NVIC_EnableIRQ(USART2_IRQn);

	/*Enable uart module*/
	 USART2->CR1 |= CR1_UE;
}


char uart2_read(){
	/*Make sure the receive data register is not empty*/
	while(!(USART2->SR & SR_RXNE)){}

	/* Read data */
	return USART2->DR;
}


void uart2_write(int ch)
{
  /*Make sure the transmit data register is empty*/
	while(!(USART2->SR & SR_TXE)){}

  /*Write to transmit data register*/
	USART2->DR	=  (ch & 0xFF);
}




static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk,  uint32_t BaudRate)
{
	USARTx->BRR =  compute_uart_bd(PeriphClk,BaudRate);
}

static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate)
{
	return ((PeriphClk + (BaudRate/2U))/BaudRate);
}

