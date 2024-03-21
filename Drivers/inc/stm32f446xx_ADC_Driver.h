/*
 * stm32f446xx_ADC_Driver.h
 *
 *  Created on: Aug 7, 2023
 *      Author: Xavier.Rocher
 */

#ifndef INC_STM32F446XX_ADC_DRIVER_H_
#define INC_STM32F446XX_ADC_DRIVER_H_

#include "stm32f446xx.h"
#include "stm32f446xx_Gpio_Driver.h"



typedef struct{

	GPIO_RegDef_t *pGPIOx;
	ADC_RegDef_t  *pADCx;
	GPIO_PinConfig_t GPIO_PinConfig;

}ADC_Handle_t;


void ADC_Init(GPIO_RegDef_t* pGPIOx , ADC_RegDef_t  *pADCx ,uint8_t nChannel,uint8_t nConversions  );
void start_ADC_Conversion( void );
uint32_t adc_read( void );

#endif /* INC_STM32F446XX_ADC_DRIVER_H_ */
