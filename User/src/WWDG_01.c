#include <stdio.h>
#include <string.h>

#include "stm32f446xx.h"
#include "stm32f446xx_Gpio_Driver.h"
#include "stm32f446xx_Timers_Driver.h"
#include "stm32f446xx_NVIC.h"
#include "stm32f446xx_Systick_Driver.h"
#include "stm32f446xx_Clocks.h"
#include "stm32f446xx_WWDG_Driver.h"

#include "usart2.h"

void GPIO_Setup(void);
void SYSClk_PLL_Setup(void);
void Systick_Setup(void);
void delay_ms( uint32_t ms );
void WWDG_Setup(void);
void min11max25( uint8_t val);
void generate_fault(void);


GPIO_Handle_t LED = {0};
uint32_t systick_delay = 0;

WWDG_Config_t WWDG_Config = {0};

void WWDG_Setup(){
	
	WWDG_Config.WWDG_prescaler = WWDG_Prescaler_4096x4;
	WWDG_Config.WWWDG_Window = 97;
	WWDG_Config.WWDG_Counter = 121;
	
	WWDG_Init(&WWDG_Config);
}
void delay_ms( uint32_t ms ){

	systick_delay = ms;
	while(systick_delay);
}
	
	
void GPIO_Setup(){

	LED.pGPIOx 																= NUCLEO_PORT_LED;
	LED.GPIO_PinConfig.GPIO_PinNumber 				= NUCLEO_PIN_LED;
	LED.GPIO_PinConfig.GPIO_PinMode 					= GPIO_MODE_OUTPUT;
	LED.GPIO_PinConfig.GPIO_PinSpeed 					= GPIO_FAST_SPEED;
	
	GPIO_Init(&LED);
	
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
		 
}
	
	


int main(){

	SYSClk_PLL_Setup();
	GPIO_Setup();
	Systick_Setup();
	
	Systick_ITConfig(ENABLE);
	Systick_Enable(ENABLE);
	
	delay_ms(300);
	GPIO_WriteTouOutPutPin(NUCLEO_PORT_LED,NUCLEO_PIN_LED,SET);
	*((volatile uint32_t*) 0xE0042008UL) |= (1 << 11);
	
	WWDG_Setup();
	
	WWDG_Enable(ENABLE);
	
	while(1){
		
		if( !GPIO_ReadFromInputPin(NUCLEO_PORT_BUTTON,NUCLEO_PIN_BUTTON) ){
			generate_fault();
		}
		min11max25(20);
		WWDG_Refresh(&WWDG_Config);
	}
	
}


void min11max25( uint8_t val){
	delay_ms(val);
}

void assert_failed( uint8_t *file, uint32_t line){
	while(1);
}

void generate_fault(void){

	uint32_t* SRAM_Address = (uint32_t*)0x20014000;
	*SRAM_Address = 0xFFFFFFFF;
	
	void (*function_pointer)(void);
	
	function_pointer = (void*) SRAM_Address;
	function_pointer();
}


void HardFault_Handler(){
	
	while(1);
}