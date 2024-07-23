#include <stm32f446xx.h>
#include <stm32f446xx_Gpio_Driver.h>
#include <stm32f446xx_Clocks.h>

static GPIO_Handle_t MCO1 	= { 0 };
static GPIO_Handle_t PA5 		= { 0 };

void GPIO_Setup(void);
void delay(uint32_t cnt);
void SYSClk_HSE_Setup(void);
void SYSClk_HSI_Setup(void);
void SYSClk_PLL_Setup(void);


void SYSClk_HSE_Setup(void){
	
	// Habilitar HSE.
	RCC_HSEConfig(RCC_HSE_ON);
	
	// Esperar a que HSE este OK.
	
	RCC_WaitForClkRdy(RCC_Clock_HSE);
	
	// Seleccionar HSE como fuente de reloj del sistema.
	RCC_SysclkConfig(RCC_Sysclk_Src_HSE);

}

void SYSClk_HSI_Setup(void){
	
	// Habilitar HSI.
	RCC_HSI_Enable(RCC_Clock_HSI);
	
	// Esperar a que HSI este OK.
	
	RCC_WaitForClkRdy(RCC_Clock_HSI);
	
	// Seleccionar HSI como fuente de reloj del sistema.
	RCC_SysclkConfig(RCC_Sysclk_Src_HSI);

}

void SYSClk_PLL_Setup(void){
	
	
	// SYSCLK = 168 MHz
	
	uint32_t 	PLLM = 8,
						PLLN = 336,
						PLLP = 2,
						PLLQ = 7,
						PLLR = 5;
	
	// Habilitar HSE.
	RCC_HSEConfig(RCC_HSE_ON);
	
	// Esperar a que HSI este OK.
	RCC_WaitForClkRdy(RCC_Clock_HSE);
	
	//Config PLL.
	RCC_PLLConfig(RCC_PLL_Source_HSE,PLLM,PLLN,PLLP,PLLQ,PLLR);
	
	// Habilitar PLLM
	RCC_PLL_Enable(ENABLE);
	
	// Esperar a que PLL este OK.
	RCC_WaitForClkRdy(RCC_Clock_PLL);
	
	//Flash Latency  pag RM 66.
	setLatencyFlash(5);
	
	//Seleccionar PLL_P como fuente de reloj del sistema.
	RCC_SysclkConfig(RCC_Sysclk_Src_PLL_P);
	
}

void delay(uint32_t cnt){

	while(cnt)
		cnt--;
}

void GPIO_Setup(void){
	
	MCO1.pGPIOx 																= GPIOA;
	MCO1.GPIO_PinConfig.GPIO_PinNumber 					= GPIO_PIN_8;
	MCO1.GPIO_PinConfig.GPIO_PinMode 						= GPIO_MODE_ALTERNATE;
	
	GPIO_Init(&MCO1);
	
	PA5.pGPIOx 																= NUCLEO_PORT_LED;
	PA5.GPIO_PinConfig.GPIO_PinNumber 				= NUCLEO_PIN_LED;
	PA5.GPIO_PinConfig.GPIO_PinMode 					= GPIO_MODE_OUTPUT;
	PA5.GPIO_PinConfig.GPIO_PinOPType 				= GPIO_PUSH_PULL;
	PA5.GPIO_PinConfig.GPIO_PinPupdControl 		= GPIO_NPUPD;
	PA5.GPIO_PinConfig.GPIO_PinSpeed 					= GPIO_HIGH_SPEED;
	
	GPIO_Init(&PA5);

}




int main(){
	
	uint32_t freq = 0;
	
	GPIO_Setup();
	
	delay(500000);
	
	/**************** HSE ****************/
	
	//1. Configurar HSE como fuente de reloj del sistema.
	
	SYSClk_HSE_Setup();
	
	//2. Configurar MC01 para sacar HSE por su pin.
	RCC_MCO1Config(RCC_MCO1_Source_HSE,RCC_MCO1_Prescaler_4);
	//3. Leer frecuencia de SYSCLK
	freq = RCC_getSysClk();
	//4. Mostrar tiempo de procesamiento de espera en PC10.
	GPIO_WriteTouOutPutPin(NUCLEO_PORT_LED,NUCLEO_PIN_LED,SET);
	delay(500000);
	GPIO_WriteTouOutPutPin(NUCLEO_PORT_LED,NUCLEO_PIN_LED,RESET);
	
	
	delay(500000);
	
	/**************** HSI ****************/
	
	//1. Configurar HSI como fuente de reloj del sistema.
	SYSClk_HSI_Setup();
	//2. Configurar MC01 para sacar HSI por su pin.
	RCC_MCO1Config(RCC_MCO1_Source_HSI,RCC_MCO1_Prescaler_4);
	
	//3. Leer frecuencia de SYSCLK
	freq = RCC_getSysClk();
	
	//4. Mostrar tiempo de procesamiento de espera en PC10.
	GPIO_WriteTouOutPutPin(NUCLEO_PORT_LED,NUCLEO_PIN_LED,SET);
	delay(500000);
	GPIO_WriteTouOutPutPin(NUCLEO_PORT_LED,NUCLEO_PIN_LED,RESET);
	
	delay(500000);
	
	/**************** PLL ****************/
	
	//1. Configurar PLL como fuente de reloj del sistema.
	SYSClk_PLL_Setup();
	
	//2. Configurar MC01 para sacar PLL por su pin.
	RCC_MCO1Config(RCC_MCO1_Source_PLL,RCC_MCO1_Prescaler_5);
	
	//3. Leer frecuencia de SYSCLK
	freq = RCC_getSysClk();
	
	//4. Mostrar tiempo de procesamiento de espera en PC10.
	GPIO_WriteTouOutPutPin(NUCLEO_PORT_LED,NUCLEO_PIN_LED,SET);
	delay(500000);
	GPIO_WriteTouOutPutPin(NUCLEO_PORT_LED,NUCLEO_PIN_LED,RESET);
	
	delay(500000);
	
	while(1);
}
