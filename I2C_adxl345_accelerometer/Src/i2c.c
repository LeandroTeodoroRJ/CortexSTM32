/*
 * i2c.c
 *
 *  	Update on: Mar 22, 2024
 *      Author: leandro
 */


#include "i2c.h"
#include "gpio.h"

//#define GPIOB_EN			(1U << 1)
//#define I2C1_CLOCK_EN		(1U << 21)
#define I2C_RESET			(1U << 15)  //SWRST: Software reset - When set, the I2C is under reset state.
#define I2C_CLK_100KHZ		80
#define MAX_VALUE_STD_MODE	17
#define I2C_EN				(1U << 0)  //PE: Peripheral enable
#define BUSSY_STATUS		(1U << 1)  //BUSY: Bus busy
#define START				(1U << 8)
#define START_STATUS		(1U << 0)  //SB: Start bit (Master mode)
#define ADDRESS_SENT		(1U << 1)  //ADDR: Address sent (master mode)/matched (slave mode)
#define DATA_EMPTY			(1U << 7)  //TxE: Data register empty (transmitters)
#define ACK					(1U << 10) //ACK: Acknowledge enable
#define STOP				(1U << 9)
#define RECEIVER_EMPTY		(1U << 6)  //RxNE: Data register not empty (receivers)
#define TRANSFER_FINISHED	(1U << 2)  //BTF: Byte transfer finished

void I2C_init(I2C_TypeDef *pI2C, uint32_t bus_frequency){
	// Reset I2C peripheral
	pI2C->CR1 |= I2C_RESET;

	// Exit reset mode
	pI2C->CR1 &=~I2C_RESET;

	// Insert a clock bus value as binary mode in 0:5 bits CR2 register
	// The FREQ field is used by the peripheral to generate data setup and
	// hold times compliant with the I2C specifications.
	pI2C->CR2 &=~((uint32_t)0x3F << 0);  //Clear CR2 Freq bits
	pI2C->CR2 |= (bus_frequency << 0);

	// Set the clock frequency
	pI2C->CCR = I2C_CLK_100KHZ;

	// Configure the rise time
	pI2C->TRISE = MAX_VALUE_STD_MODE;

	// Enable I2C peripheral
	pI2C->CR1 |= I2C_EN;
}


void I2C_byteRead(I2C_TypeDef *pI2C, char slave_addr, char memory_addr, char* data_storage){
	volatile int tmp;

	//Wait until bus is free.
	while (pI2C->SR2 & BUSSY_STATUS) {}  //0: No communication on the bus

	//Generate start condition
	pI2C->CR1 |= START;

	//Wait until start flag is set
	while (!(pI2C->SR1 & START_STATUS)) {}

	//Transmit slave adress + write bit
	pI2C->DR = slave_addr << 1;

	//Wait until address send
	while(!(pI2C->SR1 & ADDRESS_SENT)) {}

	//Clear ADDR flag reading SR2
	tmp = pI2C->SR2;

	//Send memory address
	pI2C->DR = memory_addr;

	//Wait the data register is empty
	while (!(pI2C->SR1 & DATA_EMPTY)) {}

	//Generate restart condition
	pI2C->CR1 |= START;

	//Wait until start flag is set
	while (!(pI2C->SR1 & START_STATUS)) {}

	//Transmit slave address + Read
	pI2C->DR = slave_addr << 1 | 1;

	//Wait until address send
	while(!(pI2C->SR1 & ADDRESS_SENT)) {}

	//Dissable acknowledge
	pI2C->CR1 &=~ACK;

	//Clear ADDR flag reading SR2
	tmp = pI2C->SR2;

	//Gerate stop after data received
	pI2C->CR1 |= STOP;

	//Wait until RXNE is set
	while(!(pI2C->SR1 & RECEIVER_EMPTY)) {}

	//Read data
	*data_storage++ = pI2C->DR;
}


void I2C_burstRead(I2C_TypeDef *pI2C, char saddr, char maddr, int n, char* data){
	volatile int tmp;

	//Wait until bus is free.
	while (pI2C->SR2 & BUSSY_STATUS) {}  //0: No communication on the bus

	//Generate start condition
	pI2C->CR1 |= START;

	//Wait until start flag is set
	while (!(pI2C->SR1 & START_STATUS)) {}

	//Transmit slave adress + write bit
	pI2C->DR = saddr << 1;

	//Wait until address send
	while(!(pI2C->SR1 & ADDRESS_SENT)) {}

	//Clear ADDR flag reading SR2
	tmp = pI2C->SR2;

	//Wait the data register is empty
	while (!(pI2C->SR1 & DATA_EMPTY)) {}

	//Send memory address
	pI2C->DR = maddr;

	//Wait the data register is empty
	while (!(pI2C->SR1 & DATA_EMPTY)) {}

	//Generate restart condition
	pI2C->CR1 |= START;

	//Wait until start flag is set
	while (!(pI2C->SR1 & START_STATUS)) {}

	//Transmit slave address + Read
	pI2C->DR = saddr << 1 | 1;

	//Wait until address send
	while(!(pI2C->SR1 & ADDRESS_SENT)) {}

	//Clear ADDR flag reading SR2
	tmp = pI2C->SR2;

	//Enable acknowledge
	pI2C->CR1 |= ACK;

	while(n > 0U){
		if (n == 1){
			//if one byte to read
			//Dissable acknowledge
			pI2C->CR1 &=~ACK;

			//Gerate stop condition
			pI2C->CR1 |= STOP;

			//Wait until RXNE is set
			while(!(pI2C->SR1 & RECEIVER_EMPTY)) {}

			//Read data
			*data++ = pI2C->DR;

			break;
		}else{
			//Wait until RXNE is set
			while(!(pI2C->SR1 & RECEIVER_EMPTY)) {}

			//Read data
			*data++ = pI2C->DR;

			n--;
		}
	}
}


void I2C_burstWrite(I2C_TypeDef *pI2C, char saddr, char maddr, int n, char* data){
	volatile int tmp;

	//Wait until bus is free.
	while (pI2C->SR2 & BUSSY_STATUS) {}  //0: No communication on the bus

	//Generate start condition
	pI2C->CR1 |= START;

	//Wait until start flag is set
	while (!(pI2C->SR1 & START_STATUS)) {}

	//Transmit slave adress + write bit
	pI2C->DR = saddr << 1;

	//Wait until address send
	while(!(pI2C->SR1 & ADDRESS_SENT)) {}

	//Clear ADDR flag reading SR2
	tmp = pI2C->SR2;

	//Wait the data register is empty
	while (!(pI2C->SR1 & DATA_EMPTY)) {}

	//Send memory address
	pI2C->DR = maddr;

	for (int i = 0; i < n; i++){
		//Wait the data register is empty
		while (!(pI2C->SR1 & DATA_EMPTY)) {}

		//Transmit data
		pI2C->DR = *data++;
	}

	//Wait the transfer finished
	while (!(pI2C->SR1 & TRANSFER_FINISHED)) {}

	//Gerate stop condition
	pI2C->CR1 |= STOP;

}

void i2c_clock_enable(uint32_t i2cx){
	if 	(i2cx == CLK_I2C1){
		RCC->APB1ENR |= (1 << 21);
	}
	else if (i2cx == CLK_I2C2){
		RCC->APB1ENR |= (1 << 22);
	}
	else if (i2cx == CLK_I2C3){
		RCC->APB1ENR |= (1 << 23);
	}
}

