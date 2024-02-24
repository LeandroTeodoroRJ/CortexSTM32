/*
 *
 * File name: i2c.h
 * Description: I2C header drive file
 * Hostpage: https://github.com/LeandroTeodoroRJ/CortexSTM32
 * Stable: Yes
 * Version: 1.0
 * Last Update: 26.01.24
 * Current: Yes
 * Maintainer: leandroteodoro.rj@gmail.com
 * Architecture: MCU STM32F411re
 * Compile/Interpreter: STM Cube IDE Ver:1.13.1
 * Access: Public
 * Changelog: No
 * Readme and Documents: See in Doc folder.
 * Links: No
 * Other Notes:
 * 	1- Nucleo is conected to ttyACM0 serial port
 *
 *
 */


#ifndef I2C_H_
#define I2C_H_

#include "stm32f4xx.h"

void I2C1_init(void);
void I2C1_byteRead(char slave_addr, char memory_addr, char* data_storage);
void I2C1_burstRead(char saddr, char maddr, int n, char* data);
void I2C1_burstWrite(char saddr, char maddr, int n, char* data);

#endif /* I2C_H_ */
