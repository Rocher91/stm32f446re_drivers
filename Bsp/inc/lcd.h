/*
 * lcd.h
 *
 *  Created on: Aug 7, 2023
 *      Author: Xavier.Rocher
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_

#include "stm32f446xx.h"
#include "stm32f446xx_Gpio_Driver.h"

void lcd_init(void);
void lcd_send_commamd(uint8_t command);
void lcd_print_char(uint8_t data);
void lcd_print_string( char* message );
void lcd_display_clear(void);
void lcd_display_return_home( void);
void lcd_set_cursor( uint8_t row, uint8_t column );

#define LCD_GPIO_PORT 						GPIOD

#define LCD_GPIO_RS								GPIO_PIN_0
#define LCD_GPIO_RW								GPIO_PIN_1
#define LCD_GPIO_EN								GPIO_PIN_2

#define LCD_GPIO_D4								GPIO_PIN_3
#define LCD_GPIO_D5								GPIO_PIN_4
#define LCD_GPIO_D6								GPIO_PIN_5
#define LCD_GPIO_D7								GPIO_PIN_6

#define LCD_CMD_4DL_2N_5X8F				0x28
#define LCD_CMD_DON_CURON					0x0E
#define LCD_CMD_INCADD						0x06
#define LCD_CMD_DIS_CLEAR					0x01
#define LCD_CMD_DIS_RETURN_HOME		0x02

#endif /* INC_STM32F446XX_ADC_DRIVER_H_ */
