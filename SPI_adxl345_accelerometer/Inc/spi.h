/*
 *
 * File name: spi.h
 * Description: SPI peripheral driver
 * Hostpage: https://github.com/LeandroTeodoroRJ/CortexSTM32
 * Stable: Yes
 * Version: 1.0
 * Last Update: 22.02.24
 * Current: Yes
 * Maintainer: leandroteodoro.rj@gmail.com
 * Architecture: MCU STM32F411re
 * Compile/Interpreter: STM Cube IDE Ver:1.13.1
 * Access: Public
 * Changelog: No
 * Readme and Documents: No.
 * Links: No
 * Other Notes: No
 * Functions Descriptions:
 * 	void spi_gpio_init(void) - Initialize SPI1
 *	spi1_config(void) - Config SPI1 with default values
 *	void spi1_transmit(uint8_t *data,uint32_t size) - Transmit data from SPI1
 *		*data - Pointer to data buffer
 *		size  - Size of data buffer *
 *  void spi1_receive(uint8_t *data,uint32_t size) - Rceive a data buffer from SPI1
 *      *data - Pointer to data buffer
 *      size  - Size of data buffer
 *  void cs_enable(void) - Enable CS line putting to low CS pin
 *  void cs_disable(void) - Disable CS line putting to hight CS pin
 *
 */

#ifndef SPI_H_
#define SPI_H_

#include "stm32f4xx.h"
#include <stdint.h>

void spi_gpio_init(void);
void spi1_config(void);
void spi1_transmit(uint8_t *data,uint32_t size);
void spi1_receive(uint8_t *data,uint32_t size);
void cs_enable(void);
void cs_disable(void);

#endif /* SPI_H_ */
