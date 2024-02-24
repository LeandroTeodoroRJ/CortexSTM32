/*
 *
 * File name: adxl345.h
 * Description: Acelerometer ADXL driver with SPI
 * Hostpage: https://github.com/LeandroTeodoroRJ/CortexSTM32
 * Stable: Yes
 * Version: 1.0
 * Last Update: 24.02.24
 * Current: Yes
 * Maintainer: leandroteodoro.rj@gmail.com
 * Architecture: MCU STM32F411re
 * Compile/Interpreter: STM Cube IDE Ver:1.13.1
 * Access: Public
 * Changelog: No
 * Readme and Documents: See in Doc folder.
 * Links: No
 * Other Notes:
 *
 *
 *
 */

#ifndef ADXL345_H_
#define ADXL345_H_


#include "spi.h"
#include <stdint.h>

#define   DEVID_R					(0x00)
#define   DEVICE_ADDR    			(0x53)
#define   DATA_FORMAT_R   			(0x31)
#define   POWER_CTL_R 				(0x2D)
#define   DATA_START_ADDR			(0x32)
#define   DATA_FORMAT_R   			(0x31)


#define		FOUR_G					(0x01)
#define		RESET					(0x00)
#define     SET_MEASURE_B		    (0x08)




void adxl_init (void);
void adxl_read(uint8_t address, uint8_t * rxdata);

#endif /* ADXL345_H_ */
