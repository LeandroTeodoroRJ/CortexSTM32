/*
 *
 * Project name: I2C ADXL354 Accelerometer
 * Description: It's drive for I2C and ADXL digital accelerometer.
 * Hostpage: https://github.com/LeandroTeodoroRJ/CortexSTM32
 * Stable: Yes
 * Version: 1.1
 * Last Update: 28.03.24
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
 *	3- You can test this project putting the acelerometer board in
 *	ortogonals positions (x, y, z). Then you will see 1g in
 *	value variables in live expression window.
 */

// Pinout Map
// STM :: ADXL345
// PA5 -> CLK(SCL)
// PA6 -> MISO(SDO)
// PA7 -> MOSI(SDA)
// PA9 -> Slave Select(CS)


#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "gpio.h"
#include "adxl345.h"


int16_t x,y,z;
double xg, yg, zg;

 uint8_t data_rec[6];

int main(void)
{
	// GPIO Config
	/*Enable clock access to GPIOA*/
	enable_gpio_clock(PORT_A);

	/*Set PA5,PA6,PA7 mode to alternate function*/
	gpio_config(GPIOA, ALTERNATE_FUNCTION, PIN5);
	gpio_config(GPIOA, ALTERNATE_FUNCTION, PIN6);
	gpio_config(GPIOA, ALTERNATE_FUNCTION, PIN7);
	gpio_config(GPIOA, OUTPUT_MODE, PIN9);

	/*Set PA5,PA6,PA7 alternate function type to SPI1 number AF05*/
	alternate_function_setup(GPIOA, PIN5, 05);
	alternate_function_setup(GPIOA, PIN6, 05);
	alternate_function_setup(GPIOA, PIN7, 05);

	adxl_init();
	while(1)
	{
		adxl_read(DATA_START_ADDR,data_rec);

		 x = ((data_rec[1]<<8)|data_rec[0]);
		 y = ((data_rec[3]<<8)|data_rec[2]);
		 z = ((data_rec[5]<<8)|data_rec[4]);

		xg = (x * 0.0078);
		yg = (y * 0.0078);
		zg = (z * 0.0078);
	}
}





