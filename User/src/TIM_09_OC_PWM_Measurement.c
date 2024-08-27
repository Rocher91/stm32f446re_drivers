#include <stdio.h>
#include <string.h>

#include "stm32f446xx.h"
#include "stm32f446xx_Gpio_Driver.h"
#include "stm32f446xx_Timers_Driver.h"
#include "stm32f446xx_NVIC.h"

#include "usart2.h"

static TIM_handle_t htim2 = {0};
static TIM_handle_t htim5 = {0};

uint32_t TIM5_CCR1_Pulse = 0;

uint8_t button_pressed_f = 0;
uint8_t duty_cycle = 25;

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
	
	GPIO_Handle_t TIM5_Pin = {0};
	
	TIM5_Pin.pGPIOx 																= GPIOA;
	TIM5_Pin.GPIO_PinConfig.GPIO_PinNumber 					= GPIO_PIN_1;
	TIM5_Pin.GPIO_PinConfig.GPIO_PinMode 						= GPIO_MODE_ALTERNATE;
	TIM5_Pin.GPIO_PinConfig.GPIO_PinAltFuncMode			= GPIO_AF2;
	TIM5_Pin.GPIO_PinConfig.GPIO_PinSpeed 					= GPIO_LOW_SPEED;
	
	GPIO_Init(&TIM5_Pin);
	
	GPIO_Handle_t Button = {0};
	
	Button.pGPIOx 														= NUCLEO_PORT_BUTTON;
	Button.GPIO_PinConfig.GPIO_PinMode 				= GPIO_MODE_IT_FALLING;
	Button.GPIO_PinConfig.GPIO_PinNumber 			= NUCLEO_PIN_BUTTON;
	Button.GPIO_PinConfig.GPIO_PinPupdControl = GPIO_NPUPD;
	Button.GPIO_PinConfig.GPIO_PinSpeed 			= GPIO_LOW_SPEED;
	
	GPIO_Init(&Button);
	
}

void TIM_Setup(){
	
	/* ********* TIM 2 (Medicion PWM) ********* */
	htim2.pTIMx = TIM2;
	htim2.TIM_TimeBase.TIM_Preescaler = 1;
	htim2.TIM_TimeBase.TIM_Period = 0xFFFFFFFF; 
	htim2.TIM_TimeBase.TIM_CounterMode = TIM_CounterMode_UP;
	TIM_TimeBase_Init(&htim2);
	
	//Canal 1: modo directo  y flanco de subida
	htim2.TIM_InputCapture.TIM_Channel = TIM_CH1;
	htim2.TIM_InputCapture.TIM_IC_Selection = TIM_ICSelection_Direct;
	htim2.TIM_InputCapture.TIM_IC_Polarity = TIM_ICPolarity_RE;
	TIM_ICInit(&htim2);
	
	//Canal 2: modo indirecto  y flanco de bajada
	htim2.TIM_InputCapture.TIM_Channel = TIM_CH2;
	htim2.TIM_InputCapture.TIM_IC_Selection = TIM_ICSelection_Indirect;
	htim2.TIM_InputCapture.TIM_IC_Polarity = TIM_ICPolarity_FE;
	TIM_ICInit(&htim2);
	
	//Modo Esclavo: Input Trigger el timer input 1 y modo reset
	TIM_InputTrigger(htim2.pTIMx,TIM_Trigger_Filtered_Timer_Input_1);
	TIM_SlaveMode(htim2.pTIMx,TIM_Slave_Reset_Mode);
	
	/* ********* TIM 5 (Generacion PWM) ********* */
	
	htim5.pTIMx = TIM5;
	htim5.TIM_TimeBase.TIM_Preescaler =99;
	htim5.TIM_TimeBase.TIM_Period = 3199; 
	htim5.TIM_TimeBase.TIM_CounterMode = TIM_CounterMode_UP;
	TIM_TimeBase_Init(&htim5);
	
	TIM5_CCR1_Pulse = 0;
	htim2.TIM_OutputCompare.TIM_Channel = TIM_CH2;
	htim2.TIM_OutputCompare.TIM_OC_Mode = TIM_OCMode_PWM1;
	htim2.TIM_OutputCompare.TIM_OC_Polarity = TIM_OCPolarity_Active_HIGH;
	htim2.TIM_OutputCompare.TIM_Pulse = TIM5_CCR1_Pulse;
	TIM_OCInit(&htim5);
	
}

int main(){
	
	uint32_t cc1r = 0;
	uint32_t PWM_T = 0;
	float PWM_DC = 0.0;
	
	GPIO_Setup();
	TIM_Setup();
	
	USART2_PIN_setup();
	USART2_Init();

	TIM_ClockController(htim2.pTIMx,ENABLE);
	TIM_ClockController(htim5.pTIMx,ENABLE);
	
	IRQInterruptConfig(IRQ_NO_EXTI15_10,ENABLE);
	
	uint8_t msg[48] = {0};
	
	while(1){
	
		if(button_pressed_f == 1 ){
			delay(70000);
			button_pressed_f = 0;
			
			duty_cycle += 5;
			
			if(duty_cycle > 125){
				duty_cycle = 25;
			}
			
			TIM5_CCR1_Pulse = (duty_cycle*(htim5.TIM_TimeBase.TIM_Period+1))/100;
			TIM_SetCompare(htim5.pTIMx,TIM_CH2,TIM5_CCR1_Pulse);
			
		}
		
		cc1r = TIM_GetCapture(htim2.pTIMx,TIM_CH1);
		
		if(cc1r > 0){
			PWM_T = (cc1r+1)*1000/RCC_GetAPB1_TimerClk()/(htim2.TIM_TimeBase.TIM_Preescaler+1);
			PWM_DC = 100.0 * (TIM_GetCapture(htim2.pTIMx,TIM_CH2)+1)/(cc1r+1);
		}
		else{
			
			PWM_T = 0;
			PWM_DC = 0;
		}
		snprintf((char*)msg,sizeof(msg),"T: %ldms  DC: %.2f%%\r\n",PWM_T,PWM_DC);
		USART2_SendData(msg,strlen((char*)msg));
		
		delay(50000);
		
	}
}


void assert_failed( uint8_t *file, uint32_t line){
	while(1);
}


void EXTI15_10_IRQHandler(void){
	
	GPIO_IRQHandling(GPIO_PIN_13);
	button_pressed_f = 1;
	
}

