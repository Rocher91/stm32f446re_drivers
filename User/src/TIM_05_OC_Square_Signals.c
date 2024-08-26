#include "stm32f446xx.h"
#include "stm32f446xx_Gpio_Driver.h"
#include "stm32f446xx_Timers_Driver.h"

static TIM_handle_t htim2 = {0};

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

	htim2.pTIMx = TIM2;
	htim2.TIM_TimeBase.TIM_Preescaler = 15999;
	htim2.TIM_TimeBase.TIM_Period = 999;
	htim2.TIM_TimeBase.TIM_CounterMode = TIM_CounterMode_UP;
	
	htim2.TIM_OutputCompare.TIM_Channel = TIM_CH1;
	htim2.TIM_OutputCompare.TIM_OC_Mode = TIM_OCMode_Toggle;
	htim2.TIM_OutputCompare.TIM_OC_Polarity = TIM_OCPolarity_Active_HIGH;
	htim2.TIM_OutputCompare.TIM_Pulse = 249;
	TIM_OCInit(&htim2);
	
	htim2.TIM_OutputCompare.TIM_Channel = TIM_CH2;
	htim2.TIM_OutputCompare.TIM_OC_Mode = TIM_OCMode_Toggle;
	htim2.TIM_OutputCompare.TIM_OC_Polarity = TIM_OCPolarity_Active_HIGH;
	htim2.TIM_OutputCompare.TIM_Pulse = 499;
	TIM_OCInit(&htim2);
	
	htim2.TIM_OutputCompare.TIM_Channel = TIM_CH3;
	htim2.TIM_OutputCompare.TIM_OC_Mode = TIM_OCMode_Toggle;
	htim2.TIM_OutputCompare.TIM_OC_Polarity = TIM_OCPolarity_Active_HIGH;
	htim2.TIM_OutputCompare.TIM_Pulse = 749;
	TIM_OCInit(&htim2);
	
	htim2.TIM_OutputCompare.TIM_Channel = TIM_CH4;
	htim2.TIM_OutputCompare.TIM_OC_Mode = TIM_OCMode_Toggle;
	htim2.TIM_OutputCompare.TIM_OC_Polarity = TIM_OCPolarity_Active_HIGH;
	htim2.TIM_OutputCompare.TIM_Pulse = 999;
	TIM_OCInit(&htim2);
	
}

int main(){
	
	GPIO_Setup();
	TIM_Setup();
	
	TIM_ClockController(htim2.pTIMx,ENABLE);
	
	while(1);
}


void assert_failed( uint8_t *file, uint32_t line){
	while(1);
}

