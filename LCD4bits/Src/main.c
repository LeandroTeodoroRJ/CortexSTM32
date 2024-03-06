/*
 *
 * Project name: LCD 4 Bits
 * Description: Using LCD with for bits line
 * Hostpage: https://github.com/LeandroTeodoroRJ/CortexSTM32
 * Stable: Yes
 * Version: 1.0
 * Last Update: 24.01.24
 * Current: Yes
 * Maintainer: leandroteodoro.rj@gmail.com
 * Architecture: MCU STM32F411re
 * Compile/Interpreter: STM Cube IDE Ver:1.13.1
 * Access: Public
 * Changelog: No
 * Readme and Documents: No
 * Links: https://www.electronicsforu.com/technology-trends/learn-electronics/16x2-lcd-pinout-diagram
 * Other Notes:
 * 	1- You must include the include path in
 * 	project properties -> C/C++ general -> Path and Symbols -> Includes
 * 	2- See the stm32f4xx.h, you must include your processor definition STM32F411xE in
 * 	project properties -> C/C++ general -> Path and Symbols -> Symbols (Add...)
 * Code Structure Comments: None
 * MCU - LCD connection pinout
 * PC4-PC7 	: Data Lines
 * PB5 		: LCD R/S
 * LCD R/W 	: connected to GND
 * PB7 		: LCD EN
 *
 */



#include "stm32f4xx.h"
#include <stdio.h>

#define RS 0x20
#define EN 0x80

void delayMs(int n);
void LCD_nibble_write(char data, unsigned char control);
void LCD_command(unsigned char command);
void LCD_data(char data);
void LCD_Init(void);
void GPIO_Init(void);


int main(void) {

    LCD_Init();

    LCD_data('H');
    LCD_data('e');
    LCD_data('l');
    LCD_data('l');
    LCD_data('o');
    delayMs(500);
    LCD_command(0x01);
    delayMs(500);

    while(1) {

    }
}

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

    RCC->AHB1ENR |=  0x06;		//Enable clock for PB and PC
    GPIOB->MODER |=  0x00004400;
    GPIOB->BSRR = 0x00800000;

    GPIOC->MODER |=  0x00005500;
}

void LCD_nibble_write(char data, unsigned char control) {

    GPIOC->BSRR = 0x00F00000;
    GPIOC->BSRR = data & 0xF0;

    if (control & RS){
        GPIOB->BSRR = RS;  //Set enable line
	}
    else{
        GPIOB->BSRR = RS << 16;  //Reset enable line
	}

    GPIOB->BSRR = EN;
    delayMs(0);
    GPIOB->BSRR = EN << 16;
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
