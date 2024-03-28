/*
 * adxl345.c
 *
 *  	Updated on: Mar 28, 2024
 *      Author: leandro
 */

#include "adxl345.h"

#define   MULTI_BYTE_EN				0x40	//Multi byte enable
#define	  READ_OPERATION		    0x80

void adxl_read(uint8_t address, uint8_t * rxdata)
{
	  /*Set read operation*/
	  address |= READ_OPERATION;

	  /*Enable multi-byte*/
	  address |= MULTI_BYTE_EN;

	  /*Pull cs line low to enable slave*/
	  spi_chip_select_line(GPIOA, PIN9, LINE_LOW);


      /*Send address*/
	  spi_transmit(SPI1, &address,1);

	  /*Read 6 bytes */
	  spi_receive(SPI1, rxdata,6);

	  /*Pull cs line high to disable slave*/
	  spi_chip_select_line(GPIOA, PIN9, LINE_HIGH);
}


void adxl_write (uint8_t address, uint8_t value)
{
  uint8_t data[2];

  /*Enable multi-byte, place address into buffer*/
  data[0] = address|MULTI_BYTE_EN;

  /*Place data into buffer*/
  data[1] = value;

  /*Pull cs line low to enable slave*/
  spi_chip_select_line(GPIOA, PIN9, LINE_LOW);


  /*Transmit data and address*/
  spi_transmit(SPI1, data, 2);

  /*Pull cs line high to disable slave*/
  spi_chip_select_line(GPIOA, PIN9, LINE_HIGH);
}


void adxl_init (void)
{
	/*Config SPI*/
	enable_spi_clock(CLK_SPI1);
	spi_config(SPI1, SPI_MASTER, POLARITY_1_IDLE, CAPTURE_SECOND_CLOCK);

	/*Set data format range to +-4g*/
	adxl_write (DATA_FORMAT_R, FOUR_G);

	/*Reset all bits*/
	adxl_write (POWER_CTL_R, ADXL_RESET);

	/*Configure power control measure bit*/
	adxl_write (POWER_CTL_R, SET_MEASURE_B);
}
