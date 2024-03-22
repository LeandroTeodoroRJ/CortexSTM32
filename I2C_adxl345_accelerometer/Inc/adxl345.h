/*
 *
 * File name: adxl345.h
 * Description: Acelerometer ADXL driver
 * Hostpage: https://github.com/LeandroTeodoroRJ/CortexSTM32
 * Stable: Yes
 * Version: 1.0
 * Last Update: 17.02.24
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

#include "i2c.h"
#include <stdint.h>

// ADXL345 Memory Map
#define   DEVID_R					(0x00)  //Address to device ID
#define   DATA_FORMAT_R   			(0x31)
#define   POWER_CTL_R 				(0x2D)
#define   DATA_START_ADDR			(0x32)
#define   DATA_FORMAT_R   			(0x31)

#define   DEVICE_ADDR    			(0x53)	//Alternate I2C address - SDO/ALT ADDRESS pin grounding (I2C section)

#define		FOUR_G					(0x01)  //Constant to operate at 4G
#define		ADXL_RESET				(0x00)  //Value to reset device
#define     SET_MEASURE_B		    (0x08)  //0b00001000 - Set bit4 in power_ctl register device


void adxl_init ();
void adxl_read_values (uint8_t reg);

#endif /* ADXL345_H_ */
