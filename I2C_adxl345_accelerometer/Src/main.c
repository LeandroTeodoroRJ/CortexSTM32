/*
 *
 * Project name: I2C ADXL354 Accelerometer
 * Description: It's drive for I2C and ADXL digital accelerometer.
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
 *	2- It will uses I2C number 1
 *	3- Pinout connection
 *	ADXL345		STM32F411(Nucleo Board)
 *	GND			GND
 *	VCC			5V
 *	SDA			PB9
 *	SCL			PB8
 *	4- You can test this project putting the acelerometer board in
 *	ortogonals positions (x, y, z). Then you will see 1g in
 *	value variables in live expression window.
 */

#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "i2c.h"
#include "adxl345.h"
#include "gpio.h"


int16_t x,y,z;
double xg, yg, zg;
extern uint8_t data_rec[6];  //Variable declared in adxl345.c

int main(void)
{

	// GPIO Settup
	// Enable clock acssess to GPIOB
	enable_gpio_clock(PORT_B);

	// Configuring alternate functions
	// PB9 - AF04 (SDA Pin)
	gpio_config(GPIOB, ALTERNATE_FUNCTION, PIN9);
	alternate_function_setup(GPIOB, PIN9, 04);
	// PB8 - AF04 (SCL Pin)
	gpio_config(GPIOB, ALTERNATE_FUNCTION, PIN8);
	alternate_function_setup(GPIOB, PIN8, 04);

	// Set output type as open-drain
	gpio_enable_open_drain(GPIOB, PIN8);
	gpio_enable_open_drain(GPIOB, PIN9);

	// Enable pull-ups to PB8 and PB9
	gpio_pull_resistor_configure(GPIOB, PULL_UP, PIN8);
	gpio_pull_resistor_configure(GPIOB, PULL_UP, PIN9);



	adxl_init();

	while(1)
	{
		adxl_read_values (DATA_START_ADDR);

		x = ((data_rec[1]<<8)|data_rec[0]);
		y = ((data_rec[3]<<8)|data_rec[2]);
		z = ((data_rec[5]<<8)|data_rec[4]);

		//Four G scale factor: 0.0078 :: xg, yg, zg show unit in G
		xg = (x * 0.0078);
		yg = (y * 0.0078);
		zg = (z * 0.0078);

	}
}



