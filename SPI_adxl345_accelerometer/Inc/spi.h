/*
 *
 * File name: spi.h
 * Description: SPI peripheral driver
 * Hostpage: https://github.com/LeandroTeodoroRJ/CortexSTM32
 * Stable: Yes
 * Version: 1.2
 * Last Update: 22.02.24
 * Current: Yes
 * Maintainer: leandroteodoro.rj@gmail.com
 * Architecture: MCU STM32F411re
 * Compiler: STM Cube IDE Ver:1.13.1
 * Dependences: GPIO Ver 1.4
 * Access: Public
 * Changelog: No
 * Readme and Documents: No.
 * Links: No
 * Other Notes: No
 * Functions Descriptions:
 *	void spi_config(SPI_TypeDef *pSPI, uint8_t master_or_slave, uint8_t clock_polarity, uint8_t clock_phase)  --Configure SPI parameters
 *		*pSPI  ::  Pointer to SPI struct
 *		master_or_slave  ::  Select master or slave mode
 *		clock_polarity  ::  Select clock polarity mode for idle mode
 *		clock_phase  ::  Select clock phase mode to data capture
 *		CAUTION: Default values
 *			-- Full-duplex enable
 *			-- Prescaller bus clock divided by 4
 *			-- MSB transmit first
 *			-- Software slave management enable
 *
 *	void spi_transmit(SPI_TypeDef *pSPI, uint8_t *data,uint32_t size) - Transmit data from SPI
 *		*pSPI  ::  Pointer to SPI struct
 *		*data - Pointer to data buffer
 *		size  - Size of data buffer *
 *
 *  void spi_receive(SPI_TypeDef *pSPI, uint8_t *data,uint32_t size) - Rceive a data buffer from SPI
 *  	*pSPI  ::  Pointer to SPI struct
 *      *data - Pointer to data buffer
 *      size  - Size of data buffer
 *
 *	void spi_chip_select_line(GPIO_TypeDef *pGPIO, uint32_t pin_number, uint8_t state)  --Enable/Disable CS Line
 *		--Function redefined from gpio.h - digital_pin_state
 *
 */

#ifndef SPI_H_
#define SPI_H_

#include "stm32f4xx.h"
#include <stdint.h>
#include "gpio.h"

#define CLK_SPI1	1
#define CLK_SPI2	2
#define CLK_SPI3	3
#define SPI_MASTER	1
#define SPI_SLAVE	0
#define POLARITY_0_IDLE		0
#define POLARITY_1_IDLE		1
#define CAPTURE_FIRST_CLOCK		0
#define CAPTURE_SECOND_CLOCK	1
#define spi_chip_select_line	digital_pin_state
#define LINE_LOW	RESET
#define	LINE_HIGH	SET


void spi_config(SPI_TypeDef *pSPI, uint8_t master_or_slave, uint8_t clock_polarity, uint8_t clock_phase);
void spi_transmit(SPI_TypeDef *pSPI, uint8_t *data,uint32_t size);
void spi_receive(SPI_TypeDef *pSPI, uint8_t *data,uint32_t size);
void enable_spi_clock(uint8_t clk_spi_number);

#endif /* SPI_H_ */
