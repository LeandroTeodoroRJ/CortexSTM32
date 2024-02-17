/*
 * i2c.c
 *
 *  	Update on: Feb 9, 2024
 *      Author: leandro
 */


#include "i2c.h"

#define GPIOB_EN			(1U << 1)
#define I2C1_CLOCK_EN		(1U << 21)
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

void I2C1_init(void){
	// Enable clock acssess to GPIOB
	RCC->AHB1ENR |= GPIOB_EN;

	// Configuring alternate functions
	// PB9 - AF04 (SDA Pin)
	GPIOB->MODER &=~(1U << 18);
	GPIOB->MODER |= (1U << 19);
	GPIOB->AFR[1] &=~(1U<<4);
	GPIOB->AFR[1] &=~(1U<<5);
	GPIOB->AFR[1] |=(1U<<6);
	GPIOB->AFR[1] &=~(1U<<7);


	// PB8 - AF04 (SCL Pin)
	GPIOB->MODER &=~(1U << 16);
	GPIOB->MODER |= (1U << 17);
	GPIOB->AFR[1] &=~(1U<<0);
	GPIOB->AFR[1] &=~(1U<<1);
	GPIOB->AFR[1] |=(1U<<2);
	GPIOB->AFR[1] &=~(1U<<3);


	// Set output type as open-drain
	GPIOB->OTYPER |= (1U << 8);
	GPIOB->OTYPER |= (1U << 9);

	// Enable pull-ups to PB8 and PB9
	GPIOB->PUPDR |= (1U << 16);  //PB8
	GPIOB->PUPDR &=~(1U << 17);
	GPIOB->PUPDR |= (1U << 18);  //PB9
	GPIOB->PUPDR &=~(1U << 19);


	// Enable clock acssess to I2C1
	RCC->APB1ENR |= I2C1_CLOCK_EN;

	// Reset I2C peripheral
	I2C1->CR1 |= I2C_RESET;

	// Exit reset mode
	I2C1->CR1 &=~I2C_RESET;

	// Insert a clock bus value as binary mode in 0:5 bits CR2 register
	// The FREQ field is used by the peripheral to generate data setup and
	// hold times compliant with the I2C specifications.
	I2C1->CR2 &=~(1U << 0);
	I2C1->CR2 &=~(1U << 1);
	I2C1->CR2 &=~(1U << 2);
	I2C1->CR2 &=~(1U << 3);		//CR2 Bits:    43210
	I2C1->CR2 |= (1U << 4);		//16-binary    10000

	// Set the clock frequency
	I2C1->CCR = I2C_CLK_100KHZ;

	// Configure the rise time
	I2C1->TRISE = MAX_VALUE_STD_MODE;

	// Enable I2C peripheral
	I2C1->CR1 |= I2C_EN;
}


void I2C1_byteRead(char slave_addr, char memory_addr, char* data_storage){
	volatile int tmp;

	//Wait until bus is free.
	while (I2C1->SR2 & BUSSY_STATUS) {}  //0: No communication on the bus

	//Generate start condition
	I2C1->CR1 |= START;

	//Wait until start flag is set
	while (!(I2C1->SR1 & START_STATUS)) {}

	//Transmit slave adress + write bit
	I2C1->DR = slave_addr << 1;

	//Wait until address send
	while(!(I2C1->SR1 & ADDRESS_SENT)) {}

	//Clear ADDR flag reading SR2
	tmp = I2C1->SR2;

	//Send memory address
	I2C1->DR = memory_addr;

	//Wait the data register is empty
	while (!(I2C1->SR1 & DATA_EMPTY)) {}

	//Generate restart condition
	I2C1->CR1 |= START;

	//Wait until start flag is set
	while (!(I2C1->SR1 & START_STATUS)) {}

	//Transmit slave address + Read
	I2C1->DR = slave_addr << 1 | 1;

	//Wait until address send
	while(!(I2C1->SR1 & ADDRESS_SENT)) {}

	//Dissable acknowledge
	I2C1->CR1 &=~ACK;

	//Clear ADDR flag reading SR2
	tmp = I2C1->SR2;

	//Gerate stop after data received
	I2C1->CR1 |= STOP;

	//Wait until RXNE is set
	while(!(I2C1->SR1 & RECEIVER_EMPTY)) {}

	//Read data
	*data_storage++ = I2C1->DR;
}


void I2C1_burstRead(char saddr, char maddr, int n, char* data){
	volatile int tmp;

	//Wait until bus is free.
	while (I2C1->SR2 & BUSSY_STATUS) {}  //0: No communication on the bus

	//Generate start condition
	I2C1->CR1 |= START;

	//Wait until start flag is set
	while (!(I2C1->SR1 & START_STATUS)) {}

	//Transmit slave adress + write bit
	I2C1->DR = saddr << 1;

	//Wait until address send
	while(!(I2C1->SR1 & ADDRESS_SENT)) {}

	//Clear ADDR flag reading SR2
	tmp = I2C1->SR2;

	//Wait the data register is empty
	while (!(I2C1->SR1 & DATA_EMPTY)) {}

	//Send memory address
	I2C1->DR = maddr;

	//Wait the data register is empty
	while (!(I2C1->SR1 & DATA_EMPTY)) {}

	//Generate restart condition
	I2C1->CR1 |= START;

	//Wait until start flag is set
	while (!(I2C1->SR1 & START_STATUS)) {}

	//Transmit slave address + Read
	I2C1->DR = saddr << 1 | 1;

	//Wait until address send
	while(!(I2C1->SR1 & ADDRESS_SENT)) {}

	//Clear ADDR flag reading SR2
	tmp = I2C1->SR2;

	//Enable acknowledge
	I2C1->CR1 |= ACK;

	while(n > 0U){
		if (n == 1){
			//if one byte to read
			//Dissable acknowledge
			I2C1->CR1 &=~ACK;

			//Gerate stop condition
			I2C1->CR1 |= STOP;

			//Wait until RXNE is set
			while(!(I2C1->SR1 & RECEIVER_EMPTY)) {}

			//Read data
			*data++ = I2C1->DR;

			break;
		}else{
			//Wait until RXNE is set
			while(!(I2C1->SR1 & RECEIVER_EMPTY)) {}

			//Read data
			*data++ = I2C1->DR;

			n--;
		}
	}
}


void I2C1_burstWrite(char saddr, char maddr, int n, char* data){
	volatile int tmp;

	//Wait until bus is free.
	while (I2C1->SR2 & BUSSY_STATUS) {}  //0: No communication on the bus

	//Generate start condition
	I2C1->CR1 |= START;

	//Wait until start flag is set
	while (!(I2C1->SR1 & START_STATUS)) {}

	//Transmit slave adress + write bit
	I2C1->DR = saddr << 1;

	//Wait until address send
	while(!(I2C1->SR1 & ADDRESS_SENT)) {}

	//Clear ADDR flag reading SR2
	tmp = I2C1->SR2;

	//Wait the data register is empty
	while (!(I2C1->SR1 & DATA_EMPTY)) {}

	//Send memory address
	I2C1->DR = maddr;

	for (int i = 0; i < n; i++){
		//Wait the data register is empty
		while (!(I2C1->SR1 & DATA_EMPTY)) {}

		//Transmit data
		 I2C1->DR = *data++;
	}

	//Wait the transfer finished
	while (!(I2C1->SR1 & TRANSFER_FINISHED)) {}

	//Gerate stop condition
	I2C1->CR1 |= STOP;

}


