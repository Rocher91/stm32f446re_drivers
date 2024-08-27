#include "stm32f446xx.h"
#include "stm32f446xx_Gpio_Driver.h"
#include "stm32f446xx_Timers_Driver.h"

#include "stm32f446xx_NVIC.h"

static TIM_handle_t htim2 = {0};

uint32_t CCR1_Pulse = 0;
uint8_t button_pressed_f = 0;
uint8_t duty_cycle = 0;

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
	//TIM2_Pin.GPIO_PinConfig.GPIO_PinNumber 					= GPIO_PIN_5;
	TIM2_Pin.GPIO_PinConfig.GPIO_PinMode 						= GPIO_MODE_ALTERNATE;
	TIM2_Pin.GPIO_PinConfig.GPIO_PinAltFuncMode			= GPIO_AF1;
	TIM2_Pin.GPIO_PinConfig.GPIO_PinSpeed 					= GPIO_LOW_SPEED;
	
	GPIO_Init(&TIM2_Pin);
	
	GPIO_Handle_t Button = {0};
	
	Button.pGPIOx 														= NUCLEO_PORT_BUTTON;
	Button.GPIO_PinConfig.GPIO_PinMode 				= GPIO_MODE_IT_FALLING;
	Button.GPIO_PinConfig.GPIO_PinNumber 			= NUCLEO_PIN_BUTTON;
	Button.GPIO_PinConfig.GPIO_PinPupdControl = GPIO_NPUPD;
	Button.GPIO_PinConfig.GPIO_PinSpeed 			= GPIO_LOW_SPEED;
	
	GPIO_Init(&Button);
	
}

void TIM_Setup(){
	
	htim2.pTIMx = TIM2;
	htim2.TIM_TimeBase.TIM_Preescaler = 9;
	htim2.TIM_TimeBase.TIM_Period = 1599;
	htim2.TIM_TimeBase.TIM_CounterMode = TIM_CounterMode_UP;
	TIM_TimeBase_Init(&htim2);
	
	CCR1_Pulse = 0;

	htim2.TIM_OutputCompare.TIM_Channel = TIM_CH1;
	htim2.TIM_OutputCompare.TIM_OC_Mode = TIM_OCMode_PWM1;
	htim2.TIM_OutputCompare.TIM_OC_Polarity = TIM_OCPolarity_Active_HIGH;
	htim2.TIM_OutputCompare.TIM_Pulse = CCR1_Pulse;
	TIM_OCInit(&htim2);
	
}

int main(){
	
	GPIO_Setup();
	TIM_Setup();

	TIM_ClockController(htim2.pTIMx,ENABLE);
	IRQInterruptConfig(IRQ_NO_EXTI15_10,ENABLE);
	
	while(1){
	
		if(button_pressed_f == 1 ){
			delay(70000);
			button_pressed_f = 0;
			duty_cycle+= 25;
			
			if(duty_cycle == 100){
				duty_cycle = 0;
			}
			
			CCR1_Pulse = ( duty_cycle * (htim2.TIM_TimeBase.TIM_Period + 1))/100;
			TIM_SetCompare(htim2.pTIMx,TIM_CH1, CCR1_Pulse);
		}
	}
}


void assert_failed( uint8_t *file, uint32_t line){
	while(1);
}


void EXTI15_10_IRQHandler(void){
	
	GPIO_IRQHandling(GPIO_PIN_13);
	
}

