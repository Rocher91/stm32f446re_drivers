/*
 * stm32f446xx_Systick_Driver.h
 *
 *  Created on: Aug 27, 2024
 *      Author: Xavier.Rocher
 */

#ifndef INC_STM32F446XX_SYSTICK_DRIVER_H_
#define INC_STM32F446XX_SYSTICK_DRIVER_H_

#include "stm32f446xx.h"

typedef enum{
	Systick_CLK_Source_External,
	Systick_CLK_Source_Processor
}Systick_CLK_Source_t;


typedef struct{
	
	uint32_t Systick_Period;
	Systick_CLK_Source_t Systick_Clock_Source;
	
}Systick_Config_t;


void Systick_Init(Systick_Config_t* Systick_config);
void Systick_Enable(uint8_t status);
void Systick_ITConfig(uint8_t status);


uint32_t Systick_GetCounter(void);
void Systick_SetPeriod(uint32_t value);
uint8_t Systick_GetCountFlag(void);
uint32_t Systick_GetCalib(void);



#endif /* INC_STM32F446XX_ADC_DRIVER_H_ */
