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
#include "stm32f446xx_Clocks.h"



/* Peripheral user definitions*/

TIM_handle_t 	htim2			   = { 0 };
GPIO_Handle_t MCO1_Pin 		 = { 0 };
GPIO_Handle_t TIM2_CH2_Pin = { 0 };

uint32_t capture1 = 0;
uint32_t capture2 = 0;
uint32_t capture_diff = 0;
uint32_t CNT_CLK_freq = 0;

double freq =0.0;

typedef enum{
	waiting_for_cap1_st,
	waiting_for_cap2_st,
	processing_st
		
}freq_measurement_st_t;

freq_measurement_st_t freq_measurement_st = waiting_for_cap1_st;

void GPIO_configurations(void);
void TIM_setup(void);
void TIM_EventCallback(TIM_handle_t* pTIMHandle,TIM_Event_t event);

void GPIO_configurations(){
	
	MCO1_Pin.pGPIOx                             = GPIOA;
	MCO1_Pin.GPIO_PinConfig.GPIO_PinNumber      = GPIO_PIN_8;
	MCO1_Pin.GPIO_PinConfig.GPIO_PinMode        = GPIO_MODE_ALTERNATE;
	MCO1_Pin.GPIO_PinConfig.GPIO_PinAltFuncMode = GPIO_AF0;
	MCO1_Pin.GPIO_PinConfig.GPIO_PinOPType      = GPIO_PUSH_PULL;
	MCO1_Pin.GPIO_PinConfig.GPIO_PinSpeed       = GPIO_FAST_SPEED;
	
	GPIO_Init(&MCO1_Pin);
	
	TIM2_CH2_Pin.pGPIOx                             = GPIOA;
	TIM2_CH2_Pin.GPIO_PinConfig.GPIO_PinNumber      = GPIO_PIN_1;
	TIM2_CH2_Pin.GPIO_PinConfig.GPIO_PinMode        = GPIO_MODE_ALTERNATE;
	TIM2_CH2_Pin.GPIO_PinConfig.GPIO_PinAltFuncMode = GPIO_AF1;
	TIM2_CH2_Pin.GPIO_PinConfig.GPIO_PinOPType      = GPIO_PUSH_PULL;
	TIM2_CH2_Pin.GPIO_PinConfig.GPIO_PinSpeed       = GPIO_FAST_SPEED;
	
	GPIO_Init(&TIM2_CH2_Pin);
}

void TIM_setup(){
	
	htim2.pTIMx = TIM2;
	htim2.TIM_TimeBase.TIM_Preescaler = 1;
	htim2.TIM_TimeBase.TIM_Period 		= 0xFFFFFFFF;
	htim2.TIM_TimeBase.TIM_CounterMode = TIM_CounterMode_UP;
	
	htim2.TIM_InputCapture.TIM_Channel = TIM_CH2;
	htim2.TIM_InputCapture.TIM_IC_Filter = TIM_ICFilter_NONE;
	htim2.TIM_InputCapture.TIM_IC_Polarity = TIM_ICPolarity_RE;
	htim2.TIM_InputCapture.TIM_IC_Prescaler = TIM_ICPrescaler_NONE;
	htim2.TIM_InputCapture.TIM_IC_Selection = TIM_ICSelection_Direct;
	
	TIM_ICInit(&htim2);

}


int main(void)
{
	// COnfigurar LSE
	
	RCC_LSEConfig(RCC_LSE_ON);
	//RCC_WaitForClkRdy(RCC_Clock_LSE);
	
	//COnfigurar MCO1
	RCC_MCO1Config(RCC_MCO1_Source_LSE,RCC_MCO1_Prescaler_None);
	
	GPIO_configurations();
	
	TIM_setup();
	
	TIM_ITConfig(htim2.pTIMx,TIM_EVENT_CC2I,ENABLE);
	TIM_Init(htim2.pTIMx,ENABLE);
	
	IRQInterruptConfig(IRQ_TIM2,ENABLE);
	
	CNT_CLK_freq = RCC_GetAPB1_TimerClk()/(htim2.TIM_TimeBase.TIM_Preescaler+1);
	
	while(1){
	
		if( freq_measurement_st == processing_st){
			freq = CNT_CLK_freq / capture_diff; 
			freq_measurement_st = waiting_for_cap1_st;
		}
	}
}


void TIM2_IRQHandler(void){
	
	TIM_IRQHandling(&htim2);

}

void TIM_EventCallback(TIM_handle_t* pTIMHandle,TIM_Event_t event){

	if(event == TIM_EVENT_CC2I){
		
		switch (freq_measurement_st){
	
			case waiting_for_cap1_st:
			{
				capture1 = TIM_GetCapture(pTIMHandle->pTIMx,TIM_CH2);
				freq_measurement_st = waiting_for_cap2_st;
			}
			break;
			
			case waiting_for_cap2_st:
				{
					capture2 = TIM_GetCapture(pTIMHandle->pTIMx,TIM_CH2);
			
					if(capture2>capture1){
					
						capture_diff = capture2-capture1;
					}
					else{
						capture_diff = ( 0xFFFFFFFF- capture1 )+ capture2 +1;
					}
			
					freq_measurement_st = processing_st;
				}	
			break;
			
			case processing_st:
			break;
			
			default:
				{
					freq_measurement_st = waiting_for_cap1_st;
				}
			break;
		
		}	
	}

}
