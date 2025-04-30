/*
 * ds1307.h
 *
 *  Created on: Aug 7, 2023
 *      Author: Xavier.Rocher
 */

#ifndef INC_DS1307_H_
#define INC_DS1307_H_

#include "stm32f446xx.h"
#include "stm32f446xx_Gpio_Driver.h"
#include "stm32f446xx_I2C_Driver.h"
#include <string.h>
#include <stdint.h>



#define DS1307_I2C						I2C1
#define DS1307_I2C_GPIO_PORT	GPIOB
#define DS1307_I2C_SDA_PIN		GPIO_PIN_7
#define DS1307_I2C_SCL_PIN		GPIO_PIN_6
#define DS1307_I2C_SPEED			GPIO_LOW_SPEED
#define DS1307_I2C_PUPD				GPIO_NPUPD


#define DS1307_ADDR_SECONDS 	0x00
#define DS1307_ADDR_MINUTES 	0x01
#define DS1307_ADDR_HOURS 		0x02
#define DS1307_ADDR_DAY 			0x03
#define DS1307_ADDR_DATE 			0x04
#define DS1307_ADDR_MONTH 		0x05
#define DS1307_ADDR_YEAR 			0x06

#define TIME_FORMAT_12HOURS_AM	0
#define TIME_FORMAT_12HOURS_PM	1
#define TIME_FORMAT_24HOURS			2

#define DS1307_I2C_ADDRESS	0x68

#define SUNDAY 			1
#define MONDAY 			2
#define TUESDAY 		3
#define WEDSNESDAY 	4
#define THURSDAY 		5
#define FRIDAY 			6
#define SATURDAY 		7


typedef struct
{
	uint8_t date;
	uint8_t month;
	uint8_t year;
	uint8_t day;
	
}RTC_date_t;


typedef struct
{
	uint8_t seconds;
	uint8_t minutes;
	uint8_t hours;
	uint8_t time_format;
	
}RTC_time_t;

uint8_t ds1307_init(void);
void ds1307_set_current_time(RTC_time_t* rtc_time);
void ds1307_get_current_time(RTC_time_t* rtc_time);

void ds1307_set_current_date(RTC_date_t* rtc_date);
void ds1307_get_current_date(RTC_date_t* rtc_date);



#endif 
