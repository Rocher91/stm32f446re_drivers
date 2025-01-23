/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Xavier Rocher
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c)
 * All rights reserved.
 *
 ******************************************************************************
 */

#include "stm32f446xx.h"
#include "stm32f446xx_Gpio_Driver.h"
#include "stm32f446xx_Timers_Driver.h"


/* Peripheral user definitions*/

GPIO_Handle_t LED 				= { 0 };
TIM_handle_t 	htim_led		= { 0 };
#define TIMES 24

void GPIO_configurations(void);
void TIM_setup(void);


void GPIO_configurations(void){
		
		LED.pGPIOx 																= NUCLEO_PORT_LED;
		LED.GPIO_PinConfig.GPIO_PinNumber 				= NUCLEO_PIN_LED;
		LED.GPIO_PinConfig.GPIO_PinMode 					= GPIO_MODE_OUTPUT;
		LED.GPIO_PinConfig.GPIO_PinOPType 				= GPIO_PUSH_PULL;
		LED.GPIO_PinConfig.GPIO_PinPupdControl 		= GPIO_NPUPD;
		LED.GPIO_PinConfig.GPIO_PinSpeed 					= GPIO_HIGH_SPEED;
		
		GPIO_Init(&LED);
}

void TIM_setup(void){
	
	htim_led.pTIMx 												= TIM6;
	htim_led.TIM_TimeBase.TIM_Period 			= 133;
	htim_led.TIM_TimeBase.TIM_Preescaler 	= 2;

	TIM_TimeBase_Init(&htim_led);
}


int main(void)
{
	
	GPIO_configurations();
	TIM_setup();
	TIM_Init(htim_led.pTIMx,ENABLE);
	uint8_t times = 0;
	
	while(1){
			
		
				if(TIM6->SR & (0x01<<TIMx_SR_UIF)){
					
					if (times == 0 || times == TIMES ){
						GPIO_ToggleOutputPin(NUCLEO_PORT_LED,NUCLEO_PIN_LED);
					}
					
					TIM6->SR &= (uint32_t)~(0x01<<TIMx_SR_UIF);
					if ( times < (TIMES+1) )
					{
						times++;
					}
				}
				
	}

}


