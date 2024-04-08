#include "stm32f446xx.h"
#include "stm32f446xx_SPI_Driver.h"
#include "stm32f446xx_Gpio_Driver.h"
#include <string.h>


/*
*	PB13 -->SCLK
*	PB14 -->MISO
*	PB15 -->MOSI
*	PB12 -->NSS
*	Alternate Function: 5
*/
void SPI2_GPIO_Inits(void);
void GPIO_ButtonInit(void);
void SPI2_Init(void);
void delay(void);

void delay(){
	
	for ( uint32_t i=0;i<500000;i++);
}

void SPI2_Init(){
	
	SPI_Handle_t SPI2_Handle = {
	
		.pSPIx 										= SPI2,
		.SPICOnfig.SPI_BusConfig 	= SPI_BUS_CONFIG_FULL_DUPLEX,
		.SPICOnfig.SPI_CPHA 			= SPI_CPHA_LOW,
		.SPICOnfig.SPI_CPOL 			= SPI_CPOL_LOW,
		.SPICOnfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER,
		.SPICOnfig.SPI_DFF 				= SPI_DFF_8BITS,
		.SPICOnfig.SPI_SclkSpeed 	= SPI_SPICLK_PCLK_DIV_32,
		.SPICOnfig.SPI_SSM 				= SPI_SSM_DISABLE
	};
	
	SPI_Init(&SPI2_Handle);
}

void SPI2_GPIO_Inits(void){
	
	GPIO_Handle_t SPI_Pins = {
		
		.pGPIOx 															= GPIOB,
		.GPIO_PinConfig.GPIO_PinMode					= GPIO_MODE_ALTERNATE,
		.GPIO_PinConfig.GPIO_PinAltFuncMode 	= 5,
		.GPIO_PinConfig.GPIO_PinOPType				= GPIO_PUSH_PULL,
		.GPIO_PinConfig.GPIO_PinPupdControl		= GPIO_NPUPD,
		.GPIO_PinConfig.GPIO_PinSpeed					= GPIO_HIGH_SPEED
		
	};
	
	
	
	//SS
	SPI_Pins.GPIO_PinConfig.GPIO_PinNumber	= GPIO_PIN_12;
	GPIO_Init(&SPI_Pins);
	
	//SCLK
	SPI_Pins.GPIO_PinConfig.GPIO_PinNumber	= GPIO_PIN_13;
	GPIO_Init(&SPI_Pins);
	
	//MISO
	//SPI_Pins.GPIO_PinConfig.GPIO_PinNumber	= GPIO_PIN_14;
	//GPIO_Init(&SPI_Pins);
	//MOSI
	SPI_Pins.GPIO_PinConfig.GPIO_PinNumber	= GPIO_PIN_15;
	GPIO_Init(&SPI_Pins);
	
	//GPIO_PerCLKControl( GPIOB , ENABLE);
	
	//SPI_PerCLKControl(SPI2,ENABLE);
}

void GPIO_ButtonInit(void){

	GPIO_Handle_t GPIOButton = {
			
			.pGPIOx 															= NUCLEO_PORT_BUTTON,
			.GPIO_PinConfig.GPIO_PinMode					= GPIO_MODE_INPUT,
			.GPIO_PinConfig.GPIO_PinPupdControl		= GPIO_NPUPD,
			.GPIO_PinConfig.GPIO_PinSpeed					= GPIO_HIGH_SPEED,
			.GPIO_PinConfig.GPIO_PinNumber 				= NUCLEO_PIN_BUTTON 		
	
	};
	
	GPIO_Init(&GPIOButton);
	
}






int main(){
	
	char txData[] = "MPF52300!";
	
	GPIO_ButtonInit();
	SPI2_GPIO_Inits();
	SPI2_Init();
	
	SPI_SSOECOnfig(SPI2,ENABLE);
	
	/*
		Making SSOE 1 does NSS Output Enable
		The NSS pin automatically managed by HW
		when SPE = 1, NSS will be pulled to low
		and NSS pin will be high when SPE = 0
	*/
	
	while(1){
	
		while( GPIO_ReadFromInputPin(NUCLEO_PORT_BUTTON,NUCLEO_PIN_BUTTON) );
		
		//delay();
		//Enable SPI
		SPI_Enable(SPI2,ENABLE);
		
		uint8_t dataLen = strlen(txData);
		
		//Send length information
		SPI_Write(SPI2,&dataLen,1);
		
		// Send Data
		SPI_Write(SPI2,(uint8_t*)txData,strlen(txData));

		while( SPI_getFlagSTatus(SPI2,SPI_BUSY_FLAG) );
		SPI_Enable(SPI2,DISABLE);
	
	}

}