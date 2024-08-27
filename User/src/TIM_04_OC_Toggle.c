#include "stm32f446xx.h"
#include "stm32f446xx_Gpio_Driver.h"
#include "stm32f446xx_Timers_Driver.h"

static TIM_handle_t htim2 = {0};

void GPIO_Setup(void);
void TIM_Setup(void);


void GPIO_Setup(){

	GPIO_Handle_t TIM2_Pin = {0};
	
	TIM2_Pin.pGPIOx 																= NUCLEO_PORT_LED;
	TIM2_Pin.GPIO_PinConfig.GPIO_PinNumber 					= NUCLEO_PIN_LED;
	TIM2_Pin.GPIO_PinConfig.GPIO_PinMode 						= GPIO_MODE_ALTERNATE;
	TIM2_Pin.GPIO_PinConfig.GPIO_PinAltFuncMode			= GPIO_AF1;
	TIM2_Pin.GPIO_PinConfig.GPIO_PinSpeed 					= GPIO_LOW_SPEED;
	
	GPIO_Init(&TIM2_Pin);

}

void TIM_Setup(){

	htim2.pTIMx = TIM2;
	htim2.TIM_TimeBase.TIM_Preescaler = 15999;
	htim2.TIM_TimeBase.TIM_Period = 999;
	htim2.TIM_TimeBase.TIM_CounterMode = TIM_CounterMode_UP;
	TIM_TimeBase_Init(&htim2);
	
	htim2.TIM_OutputCompare.TIM_Channel = TIM_CH1;
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

