/*
 *
 * File name: i2c.h
 * Description: I2C header drive file
 * Hostpage: https://github.com/LeandroTeodoroRJ/CortexSTM32
 * Stable: Yes
 * Version: 1.1
 * Last Update: 22.03.24
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
 * Driver funstions:
 * 	void i2c_clock_enable(uint32_t i2cx)  --Enable i2c clock to peripheral
 * 		i2cx  ::  CLK_I2C1, CLK_I2C2, CLK_I2C3
 *
 * 	void I2C_init(I2C_TypeDef *pI2C, uint32_t bus_frequency);
 * 		*pI2C  ::  Pointer to I2C struct
 * 		bus_frequency  ::  Current frequency in I2C bus (MHz)
 *
 * 	void I2C_byteRead(I2C_TypeDef *pI2C, char slave_addr, char memory_addr, char* data_storage);
 * 		*pI2C  ::  Pointer to I2C struct
 * 		slave_addr  ::  Sleva address
 * 		memory_addr  ::  Memory address
 *
 * 	void I2C_burstRead(I2C_TypeDef *pI2C, char saddr, char maddr, int n, char* data);
 * 		*pI2C  ::  Pointer to I2C struct
 * 		saddr  ::  Slave adress
 * 		maddr  ::  Memory address
 *
 *
 * 	void I2C_burstWrite(I2C_TypeDef *pI2C, char saddr, char maddr, int n, char* data);
 * 		*pI2C  ::  Pointer to I2C struct
 * 		saddr  ::  Slave adress
 * 		maddr  ::  Memory address
 *
 *
 */


#ifndef I2C_H_
#define I2C_H_

#include "stm32f4xx.h"

//Clock I2C enable definitions
#define CLK_I2C1	1
#define CLK_I2C2	2
#define CLK_I2C3	3

void i2c_clock_enable(uint32_t i2cx);
void I2C_init(I2C_TypeDef *pI2C, uint32_t bus_frequency);
void I2C_byteRead(I2C_TypeDef *pI2C, char slave_addr, char memory_addr, char* data_storage);
void I2C_burstRead(I2C_TypeDef *pI2C, char saddr, char maddr, int n, char* data);
void I2C_burstWrite(I2C_TypeDef *pI2C, char saddr, char maddr, int n, char* data);

#endif /* I2C_H_ */
