#include <stdio.h>
#include <string.h>

#include "stm32f446xx.h"
#include "stm32f446xx_Gpio_Driver.h"
#include "stm32f446xx_Timers_Driver.h"
#include "stm32f446xx_NVIC.h"
#include "stm32f446xx_Systick_Driver.h"
#include "stm32f446xx_Clocks.h"

#include "usart2.h"

void GPIO_Setup(void);
void SYSClk_PLL_Setup(void);
void Systick_Setup(void);
void delay_ms( uint32_t ms );

#define SYSTICK_MAX_COUNT 0xFFFFFFFF

uint32_t systick_delay = 0;
uint32_t system_ticks = 0;

uint8_t button_pressed = 0;

void delay_ms( uint32_t ms ){

	systick_delay = ms;
	while(systick_delay);
}
	
	
void GPIO_Setup(){

	GPIO_Handle_t Button = {0};
	
	Button.pGPIOx 														= NUCLEO_PORT_BUTTON;
	Button.GPIO_PinConfig.GPIO_PinMode 				= GPIO_MODE_IT_FALLING;
	Button.GPIO_PinConfig.GPIO_PinNumber 			= NUCLEO_PIN_BUTTON;
	Button.GPIO_PinConfig.GPIO_PinPupdControl = GPIO_NPUPD;
	Button.GPIO_PinConfig.GPIO_PinSpeed 			= GPIO_LOW_SPEED;
	
	GPIO_Init(&Button);

	
}

void Systick_Setup( void ){
	
	Systick_Config_t Systick_Config = {0};
	
	Systick_Config.Systick_Clock_Source = Systick_CLK_Source_External;
	Systick_Config.Systick_Period = (Systick_GetCalib() & 0x00FFFFF)- 1 ;
	
	Systick_Init(&Systick_Config);
	
}

void SYSClk_PLL_Setup(void){
	
	
	// SYSCLK = 168 MHz
	
	uint32_t 	PLLM = 4,
						PLLN = 150,
						PLLP = 2,
						PLLQ = 2,
						PLLR = 8;
	
	// Configurar prescaler APB1 y APB2.
	RCC_APBlCkConfig( RCC_APB_Prescaler_4 );
	RCC_APB2CkConfig( RCC_APB_Prescaler_2 );

	// Habilitar HSE.
	RCC_HSEConfig(RCC_HSE_ON);
	
	// Esperar a que HSE este OK.
	RCC_WaitForClkRdy(RCC_Clock_HSE);
	
	//Config PLL.
	RCC_PLLConfig(RCC_PLL_Source_HSE,PLLM,PLLN,PLLP,PLLQ,PLLR);
	
	// Habilitar PLLM
	RCC_PLL_Enable(ENABLE);
	
	// Esperar a que PLL este OK.
	RCC_WaitForClkRdy(RCC_Clock_PLL);
	
	//Flash Latency  pag RM 66.
	setLatencyFlash(4);
	
	//Seleccionar PLL_P como fuente de reloj del sistema.
	RCC_SysclkConfig(RCC_Sysclk_Src_PLL_P);
	
}



void SysTick_Handler(void){
	
	 if ( systick_delay > 0 ){
			systick_delay--;
	 }
	
	 system_ticks++;
}
	
void EXTI15_10_IRQHandler(void){

	GPIO_IRQHandling(GPIO_PIN_13);
	
	button_pressed = 1;
}


int main(){
	
	uint32_t last_ticks = 0;
	//uint16_t last_ticks = 0;
	uint32_t current_ticks = 0;
	//uint16_t current_ticks = 0;
	uint32_t elapsed_ticks = 0;
	//uint16_t elapsed_ticks = 0;
	uint8_t system_ticks_overflow = 0;
	uint8_t msg[64];
	
	SYSClk_PLL_Setup();
	GPIO_Setup();
	Systick_Setup();
	
	USART2_PIN_setup();
	USART2_Init();
	
	IRQInterruptConfig( IRQ_NO_EXTI15_10, ENABLE);
	Systick_ITConfig(ENABLE);
	Systick_Enable(ENABLE);
	
	while(1){
		
		if( button_pressed ){
			
			current_ticks = system_ticks;
			delay_ms(100);
			button_pressed = 0;
			
			if (current_ticks>= last_ticks){
				
				system_ticks_overflow = 0;
				elapsed_ticks = current_ticks - last_ticks;
			}
			else{
				
				system_ticks_overflow = 1;
				elapsed_ticks = (SYSTICK_MAX_COUNT-last_ticks) + current_ticks;
			}
				
			snprintf((char*)msg,sizeof(msg),"ET: %ld\r\n",elapsed_ticks);
			//snprintf((char*)msg,sizeof(msg),"ET: %d [ms] (current %d last:%d overflow:%d) \r\n",elapsed_ticks,current_ticks,last_ticks,system_ticks_overflow);
			USART2_SendData(msg,strlen((char*)msg));
			last_ticks = current_ticks;
			
		}
	}
	
}


void assert_failed( uint8_t *file, uint32_t line){
	while(1);
}


