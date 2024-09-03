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


void GPIO_Setup(){

	GPIO_Handle_t PC10_debug = {0};
	
	PC10_debug.pGPIOx 																= GPIOC;
	PC10_debug.GPIO_PinConfig.GPIO_PinNumber 					= GPIO_PIN_10;
	PC10_debug.GPIO_PinConfig.GPIO_PinMode 						= GPIO_MODE_OUTPUT;
	PC10_debug.GPIO_PinConfig.GPIO_PinSpeed 					= GPIO_FAST_SPEED;
	
	GPIO_Init(&PC10_debug);

	
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

	GPIO_ToggleOutputPin(GPIOC,GPIO_PIN_10);
}
	
	


int main(){

	SYSClk_PLL_Setup();
	GPIO_Setup();
	Systick_Setup();
	
	Systick_ITConfig(ENABLE);
	Systick_Enable(ENABLE);
	
	while(1){
	
		
		
	}
	
}


void assert_failed( uint8_t *file, uint32_t line){
	while(1);
}


