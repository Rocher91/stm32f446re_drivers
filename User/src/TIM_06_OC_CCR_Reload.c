#include "stm32f446xx.h"
#include "stm32f446xx_Gpio_Driver.h"
#include "stm32f446xx_Timers_Driver.h"
#include "stm32f446xx_Clocks.h"
#include "stm32f446xx_NVIC.h"

static TIM_handle_t htim2 = {0};

uint32_t CCR1_Pulse = 0; 
uint32_t CCR2_Pulse = 0; 
uint32_t CCR3_Pulse = 0; 
uint32_t CCR4_Pulse = 0; 

void GPIO_Setup(void);
void TIM_Setup(void);


void GPIO_Setup(){

	GPIO_Handle_t TIM2_Pin = {0};
	
	TIM2_Pin.pGPIOx 																= GPIOA;
	TIM2_Pin.GPIO_PinConfig.GPIO_PinNumber 					= GPIO_PIN_0;
	TIM2_Pin.GPIO_PinConfig.GPIO_PinMode 						= GPIO_MODE_ALTERNATE;
	TIM2_Pin.GPIO_PinConfig.GPIO_PinAltFuncMode			= GPIO_AF1;
	TIM2_Pin.GPIO_PinConfig.GPIO_PinSpeed 					= GPIO_LOW_SPEED;
	
	GPIO_Init(&TIM2_Pin);
	
	TIM2_Pin.GPIO_PinConfig.GPIO_PinNumber 					= GPIO_PIN_1;
	GPIO_Init(&TIM2_Pin);
	
	TIM2_Pin.pGPIOx 																= GPIOB;
	TIM2_Pin.GPIO_PinConfig.GPIO_PinNumber 					= GPIO_PIN_10;
	GPIO_Init(&TIM2_Pin);
	
	TIM2_Pin.pGPIOx 																= GPIOB;
	TIM2_Pin.GPIO_PinConfig.GPIO_PinNumber 					= GPIO_PIN_2;
	GPIO_Init(&TIM2_Pin);
	
}

void TIM_Setup(){
	
	
	uint32_t CKcnt = 0;
	
	htim2.pTIMx = TIM2;
	htim2.TIM_TimeBase.TIM_Preescaler = 1;
	htim2.TIM_TimeBase.TIM_Period = 0xFFFFFFFF;
	htim2.TIM_TimeBase.TIM_CounterMode = TIM_CounterMode_UP;
	TIM_TimeBase_Init(&htim2);
	
	CKcnt = RCC_GetAPB1_TimerClk()/(htim2.TIM_TimeBase.TIM_Preescaler+1);
	CCR1_Pulse = CKcnt/(2*500);
	CCR2_Pulse = CKcnt/(2*1000);
	CCR3_Pulse = CKcnt/(2*2000);
	CCR4_Pulse = CKcnt/(2*4000);
	
	htim2.TIM_OutputCompare.TIM_Channel = TIM_CH1;
	htim2.TIM_OutputCompare.TIM_OC_Mode = TIM_OCMode_Toggle;
	htim2.TIM_OutputCompare.TIM_OC_Polarity = TIM_OCPolarity_Active_HIGH;
	htim2.TIM_OutputCompare.TIM_Pulse = CCR1_Pulse;
	TIM_OCInit(&htim2);
	
	htim2.TIM_OutputCompare.TIM_Channel = TIM_CH2;
	htim2.TIM_OutputCompare.TIM_OC_Mode = TIM_OCMode_Toggle;
	htim2.TIM_OutputCompare.TIM_OC_Polarity = TIM_OCPolarity_Active_HIGH;
	htim2.TIM_OutputCompare.TIM_Pulse = CCR2_Pulse;
	TIM_OCInit(&htim2);
	
	htim2.TIM_OutputCompare.TIM_Channel = TIM_CH3;
	htim2.TIM_OutputCompare.TIM_OC_Mode = TIM_OCMode_Toggle;
	htim2.TIM_OutputCompare.TIM_OC_Polarity = TIM_OCPolarity_Active_HIGH;
	htim2.TIM_OutputCompare.TIM_Pulse = CCR3_Pulse;
	TIM_OCInit(&htim2);
	
	htim2.TIM_OutputCompare.TIM_Channel = TIM_CH4;
	htim2.TIM_OutputCompare.TIM_OC_Mode = TIM_OCMode_Toggle;
	htim2.TIM_OutputCompare.TIM_OC_Polarity = TIM_OCPolarity_Active_HIGH;
	htim2.TIM_OutputCompare.TIM_Pulse = CCR4_Pulse;
	TIM_OCInit(&htim2);
	
}

int main(){
	
	GPIO_Setup();
	TIM_Setup();
	TIM_ITConfig(htim2.pTIMx,TIM_EVENT_CC1I,ENABLE);
	TIM_ITConfig(htim2.pTIMx,TIM_EVENT_CC2I,ENABLE);
	TIM_ITConfig(htim2.pTIMx,TIM_EVENT_CC3I,ENABLE);
	TIM_ITConfig(htim2.pTIMx,TIM_EVENT_CC4I,ENABLE);
	
	IRQInterruptConfig(IRQ_TIM2,ENABLE);
	
	TIM_ClockController(htim2.pTIMx,ENABLE);
	
	while(1);
}


void assert_failed( uint8_t *file, uint32_t line){
	while(1);
}

void TIM2_IRQHandler(void){
	TIM_IRQHandling(&htim2);
}

void TIM_EventCallback(TIM_handle_t* pTIMHadle, TIM_Event_t event){
	
	uint32_t TIMx_CCRx_value = 0;
	
	if(event == TIM_EVENT_CC1I){
		TIMx_CCRx_value = TIM_GetCapture( pTIMHadle->pTIMx , TIM_CH1);
		TIM_SetCompare(pTIMHadle->pTIMx,TIM_CH1,TIMx_CCRx_value + CCR1_Pulse);
	}
	else if(event == TIM_EVENT_CC2I){
		TIMx_CCRx_value = TIM_GetCapture( pTIMHadle->pTIMx , TIM_CH2);
		TIM_SetCompare(pTIMHadle->pTIMx,TIM_CH2,TIMx_CCRx_value + CCR2_Pulse);
	}
	else if(event == TIM_EVENT_CC3I){
		TIMx_CCRx_value = TIM_GetCapture( pTIMHadle->pTIMx , TIM_CH3);
		TIM_SetCompare(pTIMHadle->pTIMx,TIM_CH3,TIMx_CCRx_value + CCR3_Pulse);
	}
	else if(event == TIM_EVENT_CC4I){
		TIMx_CCRx_value = TIM_GetCapture( pTIMHadle->pTIMx , TIM_CH4);
		TIM_SetCompare(pTIMHadle->pTIMx,TIM_CH4,TIMx_CCRx_value + CCR4_Pulse);
	}

}


