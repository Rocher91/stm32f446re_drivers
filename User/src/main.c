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
#include "stm32f446xx_ADC_Driver.h"


/* Peripheral user definitions*/

GPIO_Handle_t PA5 			= { 0 };
GPIO_Handle_t UserButton 	= { 0 };
GPIO_Handle_t Button 	= { 0 };
GPIO_Handle_t MCO1 	= { 0 };

void GPIO_configurations(void);
void ADC_configurations(void);
void configs(void);

void GPIO_configurations(){

		PA5.pGPIOx 																= NUCLEO_PORT_LED;
		PA5.GPIO_PinConfig.GPIO_PinNumber 				= NUCLEO_PIN_LED;
		PA5.GPIO_PinConfig.GPIO_PinMode 					= GPIO_MODE_OUTPUT;
		PA5.GPIO_PinConfig.GPIO_PinOPType 				= GPIO_PUSH_PULL;
		PA5.GPIO_PinConfig.GPIO_PinPupdControl 		= GPIO_NPUPD;
		PA5.GPIO_PinConfig.GPIO_PinSpeed 					= GPIO_HIGH_SPEED;
	
		MCO1.pGPIOx 																= GPIOA;
		MCO1.GPIO_PinConfig.GPIO_PinNumber 					= GPIO_PIN_8;
		MCO1.GPIO_PinConfig.GPIO_PinMode 						= GPIO_MODE_ALTERNATE;
		//MCO1.GPIO_PinConfig.GPIO_PinOPType 					= GPIO_PUSH_PULL;
		//MCO1.GPIO_PinConfig.GPIO_PinPupdControl 		= GPIO_NPUPD;
		//MCO1.GPIO_PinConfig.GPIO_PinSpeed 					= GPIO_HIGH_SPEED;

		UserButton.pGPIOx 														= NUCLEO_PORT_BUTTON;
		UserButton.GPIO_PinConfig.GPIO_PinNumber 			= NUCLEO_PIN_BUTTON;
		UserButton.GPIO_PinConfig.GPIO_PinMode 				= GPIO_MODE_IT_FALLING;
		UserButton.GPIO_PinConfig.GPIO_PinOPType 			= GPIO_OPEN_DRAIN;
		UserButton.GPIO_PinConfig.GPIO_PinPupdControl = GPIO_NPUPD;
		UserButton.GPIO_PinConfig.GPIO_PinSpeed 			= GPIO_HIGH_SPEED;
	
		Button.pGPIOx 														= GPIOB;
		Button.GPIO_PinConfig.GPIO_PinNumber 			= GPIO_PIN_0;
		Button.GPIO_PinConfig.GPIO_PinMode 				= GPIO_MODE_IT_RISING;
		Button.GPIO_PinConfig.GPIO_PinOPType 			= GPIO_OPEN_DRAIN;
		Button.GPIO_PinConfig.GPIO_PinPupdControl = GPIO_NPUPD;
		Button.GPIO_PinConfig.GPIO_PinSpeed 			= GPIO_HIGH_SPEED;


		GPIO_PerCLKControl( GPIOA , ENABLE);
		GPIO_PerCLKControl( GPIOB , ENABLE);
		GPIO_PerCLKControl( GPIOC , ENABLE);

		GPIO_Init( &PA5 );
		GPIO_Init( &UserButton );
		GPIO_Init( &Button );
		GPIO_Init( &MCO1 );

		GPIO_IRQConfigPriority( IRQ_NO_EXTI15_10, NVIC_IRQ_PRIORITY_15 );
		GPIO_IRQInterruptConfig( IRQ_NO_EXTI15_10, ENABLE);
		
		GPIO_IRQConfigPriority( IRQ_NO_EXTI0, NVIC_IRQ_PRIORITY_0 );
		GPIO_IRQInterruptConfig( IRQ_NO_EXTI0, ENABLE);
		
		RCC->CFGR |=( 0x1<<21);
		
		

}

void ADC_configurations(){

	ADC_Init(GPIOA , ADC1 , GPIO_PIN_0 , ADC_1_CONVERSION  );
}

void configs(){

	GPIO_configurations();
	ADC_configurations();

}



uint32_t ADC_value = 0.0F;

int main(void)
{

	configs();

	while(1){

		start_ADC_Conversion();
		ADC_value = adc_read();
		//GPIO_WriteTouOutPutPin( PA0.pGPIOx, GPIO_PIN_0 , SET);
		//GPIO_WriteTouOutPutPin( PA0.pGPIOx, GPIO_PIN_0 , RESET);
		//while(1){
			//GPIO_ToggleOutputPin( GPIOA, GPIO_PIN_0 );
			//for(int i=0;i<5000;i++);
		}

}

void EXTI15_10_IRQHandler( void ){

		GPIO_IRQHandling( NUCLEO_PIN_BUTTON );
		GPIO_ToggleOutputPin( NUCLEO_PORT_LED, NUCLEO_PIN_LED );
}

void EXTI0_IRQHandler( void ){

		GPIO_IRQHandling( GPIO_PIN_0 );
		GPIO_ToggleOutputPin( NUCLEO_PORT_LED, NUCLEO_PIN_LED );
}

