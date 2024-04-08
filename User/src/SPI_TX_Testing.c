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
void SPI2_Init(void);


void SPI2_Init(){
	
	SPI_Handle_t SPI2_Handle = {
	
		.pSPIx 										= SPI2,
		.SPICOnfig.SPI_BusConfig 	= SPI_BUS_CONFIG_FULL_DUPLEX,
		.SPICOnfig.SPI_CPHA 			= SPI_CPHA_LOW,
		.SPICOnfig.SPI_CPOL 			= SPI_CPOL_HIGH,
		.SPICOnfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER,
		.SPICOnfig.SPI_DFF 				= SPI_DFF_8BITS,
		.SPICOnfig.SPI_SclkSpeed 	= SPI_SPICLK_PCLK_DIV_2,
		.SPICOnfig.SPI_SSM 				= SPI_SSM_ENABLE
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
	//SPI_Pins.GPIO_PinConfig.GPIO_PinNumber	= GPIO_PIN_12;
	//GPIO_Init(&SPI_Pins);
	
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


int main(){
	
	char txData[] = "MPF52300!";
	
	SPI2_GPIO_Inits();
	SPI2_Init();
	
	SPI_SSIConfig(SPI2,ENABLE);
	
	//Enable SPI
	SPI_Enable(SPI2,ENABLE);
	
	SPI_Write(SPI2,(uint8_t*)txData,strlen(txData));
	
	while( SPI_getFlagSTatus(SPI2,SPI_BUSY_FLAG) );
	SPI_Enable(SPI2,DISABLE);
	
	while(1);

}