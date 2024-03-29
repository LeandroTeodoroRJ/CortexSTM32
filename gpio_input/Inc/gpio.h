/*
 *
 * File name: gpio
 * Description: Driver for GPIO port
 * Hostpage: https://github.com/LeandroTeodoroRJ/CortexSTM32
 * Stable: Yes
 * Version: 1.2.2
 * Last Update: 28.03.24
 * Current: Yes
 * Maintainer: leandroteodoro.rj@gmail.com
 * Architecture: MCU STM32F411re
 * Compile/Interpreter: STM Cube IDE Ver:1.13.1
 * Access: Public
 * Changelog: No
 * Readme and Documents: No
 * Links: No
 * Other Notes:
 * Code Structure Comments:
 * 	void enable_gpio_clock(uint8_t port)  --Enable clock for GPIOx
 * 		port :: PORT_A, PORT_B, ...
 *
 * 	void gpio_config(GPIO_TypeDef *pGPIO, uint32_t direction_mode, uint32_t pin_number) --Configure GPIO.
 * 		*pGPIO :: Pointer to GPIO struct
 * 		direction_mode :: INPUT_MODE, OUTPUT_MODE, ...
 * 		pin_number :: PIN0, PIN1, PIN2, ...
 *
 * 	void gpio_load_value(GPIO_TypeDef *pGPIO, uint32_t value)  --Togle GPIO pin.
 * 		*pGPIO :: Pointer to GPIO struct
 * 		pin_number :: PIN0, PIN1, PIN2, ...
 *
 * 	void digital_pin_state(GPIO_TypeDef *pGPIO, uint32_t pin_number, uint8_t state);  --Set hight or low a pin.
 * 		*pGPIO :: Pointer to GPIO struct
 * 		pin_number :: PIN0, PIN1, PIN2, ...
 * 		state :: SET to high or RESET to low value on pin.
 *
 * 	uint32_t read_gpio_pin(GPIO_TypeDef *pGPIO, uint32_t pin_number);  --Read a digital input pin
 * 		*pGPIO :: Pointer to GPIO struct
 * 		 pin_number :: PIN0, PIN1, PIN2, ...
 * 		 Return 1 if high value or 0 to low value.
 *
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "stm32f4xx.h"

/* General definitions */
#define SET		1
#define RESET	0

#define	PORT_A	0	/* Clock for Port A */
#define	PORT_B	1	/* Clock for Port B */
#define	PORT_C	2	/* Clock for Port C */
#define	PORT_D	3	/* Clock for Port D */
#define	PORT_E	4	/* Clock for Port E */
#define	PORT_H	5	/* Clock for Port H */

/* PIN definitions */
#define PIN0	0
#define PIN1	1
#define PIN2	2
#define PIN3	3
#define PIN4	4
#define PIN5	5
#define PIN6	6
#define PIN7	7
#define PIN8	8
#define PIN9	9
#define PIN10	10
#define PIN11	11
#define PIN12	12
#define PIN13	13
#define PIN14	14
#define PIN15	15

/* Input modes definitions */
#define INPUT_MODE				00	/* Digital input mode */
#define OUTPUT_MODE				01	/* Digital output mode */
#define ALTERNATE_FUNCTION		02	/* ALternate function mode */
#define ANALOG_MODE				03	/* Analog mode */

void enable_gpio_clock(uint8_t port);
void gpio_config(GPIO_TypeDef *pGPIO, uint32_t direction_mode, uint32_t pin_number);
void gpio_bit_toggle(GPIO_TypeDef *pGPIO, uint32_t pin_number);
void digital_pin_state(GPIO_TypeDef *pGPIO, uint32_t pin_number, uint8_t state);
uint32_t read_gpio_pin(GPIO_TypeDef *pGPIO, uint32_t pin_number);

#endif /* GPIO_H_ */
