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
#include "stm32f446xx_NVIC.h"
#include "stm32f446xx_Gpio_Driver.h"
#include "stm32f446xx_Timers_Driver.h"

/* Peripheral user definitions*/

GPIO_Handle_t LED 				= { 0 };
TIM_handle_t 	htim_led		= { 0 };

void GPIO_configurations(void);
void TIM_setup(void);
void TIM_EventCallback(TIM_handle_t* pTIMHandle,TIM_Event_t event);

void GPIO_configurations(){
		
	
		LED.pGPIOx 																= NUCLEO_PORT_LED;
		LED.GPIO_PinConfig.GPIO_PinNumber 				= NUCLEO_PIN_LED;
		LED.GPIO_PinConfig.GPIO_PinMode 					= GPIO_MODE_OUTPUT;
		LED.GPIO_PinConfig.GPIO_PinOPType 				= GPIO_PUSH_PULL;
		LED.GPIO_PinConfig.GPIO_PinPupdControl 		= GPIO_NPUPD;
		LED.GPIO_PinConfig.GPIO_PinSpeed 					= GPIO_HIGH_SPEED;
		
		GPIO_Init(&LED);
}

void TIM_setup(){
	
	htim_led.pTIMx 												= TIM6;
	htim_led.TIM_TimeBase.TIM_Period 			= 7979;
	htim_led.TIM_TimeBase.TIM_Preescaler 	= 2004;

	TIM_TimeBase_Init(&htim_led);

}


int main(void)
{
	
	GPIO_configurations();
	
	TIM_setup();
	TIM_ITConfig(htim_led.pTIMx,TIM_EVENT_UI,ENABLE);
	TIM_Init(htim_led.pTIMx,ENABLE);
	
	IRQInterruptConfig(IRQ_TIM6_DAC,ENABLE);
	
	while(1);
}


void TIM6_DAC_IRQHandler(void){
	
	TIM_IRQHandling(&htim_led);
	//TIM_ClearITPendingBit( htim_led.pTIMx, (uint16_t)(0x01 << TIMx_DIER_UIE));
	//GPIO_ToggleOutputPin(LED.pGPIOx,NUCLEO_PIN_LED);
}

void TIM_EventCallback(TIM_handle_t* pTIMHandle,TIM_Event_t event){

	if(event == TIM_EVENT_UI){
		GPIO_ToggleOutputPin(LED.pGPIOx,NUCLEO_PIN_LED);
	}

}
