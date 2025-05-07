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
void lcd_send_data(uint8_t command);

#define LCD_GPIO_PORT GPIOD

#define LCD_GPIO_RS		GPIO_PIN_0
#define LCD_GPIO_RW		GPIO_PIN_1
#define LCD_GPIO_EN		GPIO_PIN_2

#define LCD_GPIO_D4		GPIO_PIN_3
#define LCD_GPIO_D5		GPIO_PIN_4
#define LCD_GPIO_D6		GPIO_PIN_5
#define LCD_GPIO_D7		GPIO_PIN_6



#endif /* INC_STM32F446XX_ADC_DRIVER_H_ */
