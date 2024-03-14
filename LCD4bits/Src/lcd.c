/*
 * lcd.c
 *
 *  	Updated on: Mar 12, 2024
 *      Author: leandro
 */

#include "lcd.h"
#include "gpio.h"
#include <string.h>

#define RS 0x20

void LCD_nibble_write(char data, unsigned char control);
void LCD_command(unsigned char command);
void delayMs(int n);

void LCD_Init(void) {
    GPIO_Init();

    delayMs(30);
    LCD_nibble_write(0x30, 0);
    delayMs(5);
    LCD_nibble_write(0x30, 0);
    delayMs(1);
    LCD_nibble_write(0x30, 0);
    delayMs(1);

    LCD_nibble_write(0x20, 0);  // set 4-bit data mode
    delayMs(1);
    LCD_command(0x28);          // 4-bit data, 2-line, 5x7 font
    LCD_command(0x06);          // move cursor right
    LCD_command(0x01);          // clear screen, move cursor to home
    LCD_command(0x0F);          // turn on display, cursor blinking
}

void GPIO_Init(void) {
	enable_gpio_clock(CONTROL_PORT);
	enable_gpio_clock(DATA_PORT);
	gpio_config(GPIO_CONTROL, OUTPUT_MODE,	LCD_RS);
	gpio_config(GPIO_CONTROL, OUTPUT_MODE,	LCD_EN);
	digital_pin_state(GPIO_CONTROL, DATA7, RESET);
    gpio_config(GPIO_DATA, OUTPUT_MODE, DATA4);
    gpio_config(GPIO_DATA, OUTPUT_MODE, DATA5);
    gpio_config(GPIO_DATA, OUTPUT_MODE, DATA6);
    gpio_config(GPIO_DATA, OUTPUT_MODE, DATA7);

}

void LCD_nibble_write(char data, unsigned char control) {

    digital_pin_state(GPIO_DATA, DATA4, RESET);
    digital_pin_state(GPIO_DATA, DATA5, RESET);
    digital_pin_state(GPIO_DATA, DATA6, RESET);
    digital_pin_state(GPIO_DATA, DATA7, RESET);

    if (data & (1U << 4)){
    	digital_pin_state(GPIO_DATA, DATA4, SET);
    }
    if (data & (1U << 5)){
    	digital_pin_state(GPIO_DATA, DATA5, SET);
    }
    if (data & (1U << 6)){
    	digital_pin_state(GPIO_DATA, DATA6, SET);
    }
    if (data & (1U << 7)){
    	digital_pin_state(GPIO_DATA, DATA7, SET);
    }


    if (control & RS){
    	digital_pin_state(GPIO_CONTROL, LCD_RS, SET);   //Set RS line
	}
    else{
    	digital_pin_state(GPIO_CONTROL, LCD_RS, RESET);  //Reset RS line
	}

    digital_pin_state(GPIO_CONTROL, LCD_EN, SET);   //Set enable line
    delayMs(0);
    digital_pin_state(GPIO_CONTROL, LCD_EN, RESET);  //Reset enable line

}

void delayMs(int delay) {
    int i;
    for (; delay > 0; delay--)
        for (i = 0; i < 3195; i++) ;
}


void LCD_command(unsigned char command) {
    LCD_nibble_write(command & 0xF0, 0);    /* upper 4 bits */
    LCD_nibble_write(command << 4, 0);      /* lower 4 bits */
    if (command < 4){
        delayMs(2);
     }
    else{
        delayMs(1);
    }
}

void LCD_data(char data) {
    LCD_nibble_write(data & 0xF0, RS);      /* upper nibble first */
    LCD_nibble_write(data << 4, RS);        /* then lower nibble */
    delayMs(1);
}

void LCD_string(char *str){
	int len = strlen(str);
	for (int i = 0;i < len; i++){
		LCD_data(str[i]);
	}
}

void LCD_set_cursor_xy(uint32_t row, int col){
	if(row == 0){
		LCD_command(0x80);
	}
	else{
		LCD_command(0xC0);
	}
	 delayMs(40);
	for (int i = 0; i < col; i++){
		LCD_command(0x14);
	}
}

void LCD_cursor_off(){
	LCD_command(0x0C);
	delayMs(1);
}
