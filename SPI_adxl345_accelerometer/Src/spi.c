/*
 * spi.c
 *
 *  	Updated on: Feb 22, 2024
 *      Author: leandro
 */

#include "spi.h"


#define SR_TXE			(1U<<1)
#define SR_RXNE			(1U<<0)
#define SR_BSY			(1U<<7)


void spi_config(SPI_TypeDef *pSPI, uint8_t master_or_slave, uint8_t clock_polarity, uint8_t clock_phase){

	/*See in reference manual - CR1 register*/
	/*Set clock to fPCLK/4*/
	pSPI->CR1 |=(1U<<3);
	pSPI->CR1 &=~(1U<<4);
	pSPI->CR1 &=~(1U<<5);

	if (clock_phase == CAPTURE_SECOND_CLOCK){
		// CPHA to 1
		pSPI->CR1 |=  (1U<<0);
	}
	else{
		pSPI->CR1 &=~ (1U<<0);
	}

	if (clock_polarity == POLARITY_1_IDLE){
		// Set CPOL to 1
		pSPI->CR1 |= (1U<<1);
	}
	else{
		pSPI->CR1 &=~ (1U<<1);
	}

	/*Enable full duplex*/
	pSPI->CR1 &=~(1U<<10);

	/*Set MSB first*/
	pSPI->CR1 &= ~(1U<<7);

	if (master_or_slave == SPI_MASTER){
		/*Set mode to Master*/
		pSPI->CR1 |= (1U<<2);
	}
	else{
		/*Set mode to Slave*/
		pSPI->CR1 &=~ (1U<<2);
	}

	/*Set 8 bit data mode*/
	pSPI->CR1 &= ~(1U<<11);

	/*Select software slave management by
	 * setting SSM=1 and SSI=1*/
	pSPI->CR1 |= (1<<8);
	pSPI->CR1 |= (1<<9);

	/*Enable SPI module*/
	pSPI->CR1 |= (1<<6);
}


void spi_transmit(SPI_TypeDef *pSPI, uint8_t *data,uint32_t size)
{
	uint32_t i=0;
	uint16_t temp;

	while(i<size)
	{
		/*Wait until TXE is set, buffer is empty*/
		while(!(pSPI->SR & (SR_TXE))){}

		/*Write the data to the data register*/
		pSPI->DR = data[i];
		i++;
	}
	/*Wait until TXE is set*/
	while(!(pSPI->SR & (SR_TXE))){}

	/*Wait for BUSY flag to reset*/
	while((pSPI->SR & (SR_BSY))){}

	/*Clear OVR flag*/
	temp = pSPI->DR;
	temp = pSPI->SR;
}


void spi_receive(SPI_TypeDef *pSPI, uint8_t *data,uint32_t size)
{
	while(size)		//Enter if size not igual to zero
	{
		/*Send dummy data*/
		SPI1->DR =0;

		/*Wait for RXNE flag to be set - Receiver buffer not empty*/
		while(!(SPI1->SR & (SR_RXNE))){}

		/*Read data from data register*/
		*data++ = (SPI1->DR);
		size--;		//Decrement size buffer
	}
}


void enable_spi_clock(uint8_t clk_spi_number){
	if (clk_spi_number == CLK_SPI1){
		RCC->APB2ENR |= (1U << 12);
	}
	else if(clk_spi_number == CLK_SPI2){
		RCC->APB1ENR |= (1U << 14);
	}
	else if(clk_spi_number == CLK_SPI3){
		RCC->APB1ENR |= (1U << 15);
	}
}
