/*
 *
 * File name: lcd.h
 * Description: Driver for LCD 12x2 using 4 data lines
 * Hostpage: https://github.com/LeandroTeodoroRJ/CortexSTM32
 * Stable: Yes
 * Version: 1.1
 * Last Update: 12.03.24
 * Current: Yes
 * Dependences: GPIO ver 1.3.1
 * Maintainer: leandroteodoro.rj@gmail.com
 * Architecture: MCU STM32F411re
 * Compile/Interpreter: STM Cube IDE Ver:1.13.1
 * Access: Public
 * Changelog: No
 * Readme and Documents: No
 * Links: No
 * Other Notes:
 * Code Structure Comments:
 *
 * 	void LCD_cursor_off()  	--Disable cursor
 * 	void LCD_Init(void)		--Initialize LCD, you must select the pins and ports in definitions
 * 	void LCD_data(char data)   --Send a one char data
 * 		char data  ::  Valid char ASCII
 * 	void LCD_string(char *str)   --Send a string
 * 		char *str  ::  Pointer to string array
 * 	void LCD_set_cursor_xy(uint32_t row, char col)  --Set cursor position
 * 		row  ::  Upper line row 0, Bottom line row 1
 * 		col  ::  Collum number, valid 0 to 15
 * 	void LCD_cursor_off()   --Disable the cursor symbol
 *
 */

#ifndef LCD_H_
#define LCD_H_

#include "stm32f4xx.h"

/* PINs and PORTS definitions */
#define DATA_PORT		PORT_C
#define GPIO_DATA		GPIOC
#define CONTROL_PORT	PORT_B
#define GPIO_CONTROL	GPIOB
#define LCD_RS		PIN5		//in control port
#define	LCD_EN		PIN7		//in control port
#define DATA7		PIN7
#define DATA6		PIN6
#define DATA5		PIN5
#define DATA4		PIN4

void LCD_data(char data);
void LCD_Init(void);
void GPIO_Init(void);
void LCD_string(char *str);
void LCD_set_cursor_xy(uint32_t row, int col);
void LCD_cursor_off();


#endif /* LCD_H_ */
