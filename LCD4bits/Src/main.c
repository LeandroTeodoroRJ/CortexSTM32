/*
 *
 * Project name: LCD 4 Bits
 * Description: Using LCD with for bits line
 * Hostpage: https://github.com/LeandroTeodoroRJ/CortexSTM32
 * Stable: Yes
 * Version: 1.0
 * Last Update: 13.03.24
 * Dependences:  LCD ver 1.1
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
#include "lcd.h"


int main(void) {
	char message[10] = " World.";

    LCD_Init();

    LCD_data('H');
    LCD_data('e');
    LCD_data('l');
    LCD_data('l');
    LCD_data('o');
    LCD_string(message);
    LCD_set_cursor_xy(0, 4);
//  LCD_cursor_off();

    while(1) {

    }
}


