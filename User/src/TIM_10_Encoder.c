#include <stdio.h>
#include <string.h>

#include "stm32f446xx.h"
#include "stm32f446xx_Gpio_Driver.h"
#include "stm32f446xx_Timers_Driver.h"
#include "stm32f446xx_NVIC.h"

#include "usart2.h"

static TIM_handle_t htim2 = {0};


void GPIO_Setup(void);
void TIM_Setup(void);
void delay( uint32_t cnt);

void delay( uint32_t cnt){

	while(cnt){
		cnt--;
	}
}
void GPIO_Setup(){

	GPIO_Handle_t TIM2_Pin = {0};
	
	TIM2_Pin.pGPIOx 																= GPIOA;
	TIM2_Pin.GPIO_PinConfig.GPIO_PinNumber 					= GPIO_PIN_0;
	TIM2_Pin.GPIO_PinConfig.GPIO_PinMode 						= GPIO_MODE_ALTERNATE;
	TIM2_Pin.GPIO_PinConfig.GPIO_PinAltFuncMode			= GPIO_AF1;
	TIM2_Pin.GPIO_PinConfig.GPIO_PinSpeed 					= GPIO_LOW_SPEED;
	
	GPIO_Init(&TIM2_Pin);
	
	TIM2_Pin.pGPIOx 																= GPIOA;
	TIM2_Pin.GPIO_PinConfig.GPIO_PinNumber 					= GPIO_PIN_1;
	TIM2_Pin.GPIO_PinConfig.GPIO_PinMode 						= GPIO_MODE_ALTERNATE;
	TIM2_Pin.GPIO_PinConfig.GPIO_PinAltFuncMode			= GPIO_AF1;
	TIM2_Pin.GPIO_PinConfig.GPIO_PinSpeed 					= GPIO_LOW_SPEED;
	
	GPIO_Init(&TIM2_Pin);

	
}

void TIM_Setup(){
	
	/* ********* TIM 2 (Medicion PWM) ********* */
	htim2.pTIMx = TIM2;
	
	//Canal 1: modo directo  y flanco de subida
	htim2.TIM_InputCapture.TIM_Channel = TIM_CH1;
	htim2.TIM_InputCapture.TIM_IC_Selection = TIM_ICSelection_Direct;
	htim2.TIM_InputCapture.TIM_IC_Polarity = TIM_ICPolarity_RE;
	TIM_ICInit(&htim2);
	
	//Canal 2: modo directo  y flanco de subida
	htim2.TIM_InputCapture.TIM_Channel = TIM_CH2;
	htim2.TIM_InputCapture.TIM_IC_Selection = TIM_ICSelection_Direct;
	htim2.TIM_InputCapture.TIM_IC_Polarity = TIM_ICPolarity_RE;
	TIM_ICInit(&htim2);
	
	//Modo Esclavo: Input Trigger el timer input 1 y modo reset
	TIM_SlaveMode(htim2.pTIMx,TIM_Slave_Encoder_Mode_2);
	
}

int main(){
	
	uint32_t tim2_cnt = 0;
	uint8_t dir = 0;
	
	GPIO_Setup();
	TIM_Setup();
	
	USART2_PIN_setup();
	USART2_Init();

	TIM_ClockController(htim2.pTIMx,ENABLE);

	IRQInterruptConfig(IRQ_NO_EXTI15_10,ENABLE);
	
	uint8_t msg[48] = {0};
	htim2.pTIMx->ARR = 100;
	
	while(1){
		
		tim2_cnt = TIM_GetCounter(htim2.pTIMx);
		dir = (htim2.pTIMx->CR[0] >> TIMx_CR1_DIR)& 0x01;
		
		snprintf((char*)msg,sizeof(msg),"CNT: %ld [%s]\r\n",tim2_cnt,dir?"-":"+");
		USART2_SendData(msg,strlen((char*)msg));
		
		delay(50000);
		
	}
}


void assert_failed( uint8_t *file, uint32_t line){
	while(1);
}


