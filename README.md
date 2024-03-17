# CortexSTM32
STM32 MCU projects repository.

## Important Notes
1- You must include the path with original STM32 declarations in
project properties -> C/C++ general -> Path and Symbols -> Includes.\
2- See the stm32f4xx.h, you must include your processor definition STM32F411xE in
project properties -> C/C++ general -> Path and Symbols -> Symbols (Add...).

## List of Content
led_toggle_addr_struct  ::  Toggle led using struct memory registers.\
gpio_output  ::  How use the original ST driver header.\
gpio_bsrr  ::  Toggle led using set/reset register.\
gpio_input  ::  Read digital input pin (user button).\
gpio_output_bit_set_function  ::  Set and Reset bits using a utils functions (Refac for utils).\
usart2_tx  ::  Simple example how to use usart.\
usart2_modular  ::  Driver code for usart2.\
chip_headers  ::  Original STM headers files to STM32.\
usart2_rx  ::  USART2 transmitter and reicever test.\
usart2_printf  ::  Sending a string with printf function. \
usart2_driver  ::  USART2 driver files and test program.\
adc_single_conversion  ::  Example how it use ADC1 as single conversion mode.\
adc_continuos_conversion  ::  ADC1 configured as continuos conversion.\
adc_usrt_refac  ::  Program to refactory and test ADC and USART drivers.\
systick_delay  ::  It use the Cortex M4 systick module to create delay time.\
timers ::  Example how it use timer 2 module.\
output_compare  ::  How it toggle led with timer compare module.\
input_compare  ::  It take a sample time with a external source.\
input_interrupt  ::  It use the GPIO with interrupt EXTI NVIC.\
usart_interrupt  ::  How it use usart with interrupt.\
adc_interrupt  ::  Send a serial byte on ADC interrupt conversiion.\
systick_interrupt  ::  Creating delay time with systick interrupt.\
timers_interrupt  ::  How it use a time event interrupt on timer2.\
usart_dma  ::  How it use the DMA for transfer a data to USART2.\
I2C_adxl345_accelerometer  ::  Obtain the ADXL345 acelerometer axis values. \
SPI_adxl345_accelerometer  ::  Using ADXL acelerometer with SPI interface. \
LCD4bits  ::  Using LCD with 4 data lines configuration.

## Last Updated Drivers Versions
ADC  ::  Ver 1.0  ::  adc_usrt_refac \
GPIO ::  Ver 1.3.1  ::  usart2_printf \
LCD  ::  Ver 1.1  ::  LCD4bits
USART  ::  Ver 1.2  ::  usart2_driver
