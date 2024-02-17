/*
 * adxl345.c
 *
 *  	Updated on: Feb 17, 2024
 *      Author: leandro
 */


#include "adxl345.h"



char data;
uint8_t data_rec[6];  //To store axis values

void adxl_read_address (uint8_t reg)
{
	 I2C1_byteRead( DEVICE_ADDR, reg, &data);

}

void adxl_write (uint8_t reg, char value){
	char data[1];
	data[0] = value;

	I2C1_burstWrite( DEVICE_ADDR, reg,1, data);  //Write one byte in device memory
}

void adxl_read_values (uint8_t reg)
{
	I2C1_burstRead(DEVICE_ADDR, reg, 6,(char *)data_rec);  //Because the device has 6 bytes to storage axis values

}


void adxl_init (void)
{
	/*Enable I2C*/
	I2C1_init();

	/*Read the DEVID, this should return 0xE5*/
	adxl_read_address(DEVID_R);

	/*Set data format range to +-4g*/
	adxl_write (DATA_FORMAT_R, FOUR_G);

	/*Reset all bits*/
	adxl_write (POWER_CTL_R, RESET);

	/*Configure power control measure bit*/
	adxl_write (POWER_CTL_R, SET_MEASURE_B);
}
