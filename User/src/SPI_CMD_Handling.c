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

#define COMMAND_LED_CTRL		0x50
#define COMMAND_SENSOR_READ	0x51
#define COMMAND_LED_READ		0x52
#define COMMAND_PRINT				0x53
#define COMMAND_ID_READ			0x54

#define LED_ON	1
#define LED_OFF	0

#define ANALOG_PIN0	0
#define ANALOG_PIN1	1
#define ANALOG_PIN2	2
#define ANALOG_PIN3	3
#define ANALOG_PIN4	4

#define LED_PIN			9


void SPI2_GPIO_Inits(void);
void GPIO_ButtonInit(void);
void SPI2_Init(void);
void delay(void);
uint8_t SPI_VerifyResponse(uint8_t ackbyte);
uint8_t SPI_WriteCommand(SPI_RegDef_t* pSPIx,uint8_t cmd,uint8_t* args);

void delay(){
	
	for ( uint32_t i=0;i<500000/2;i++);
}

void SPI2_Init(){
	
	SPI_Handle_t SPI2_Handle = {
	
		.pSPIx 										= SPI2,
		.SPICOnfig.SPI_BusConfig 	= SPI_BUS_CONFIG_FULL_DUPLEX,
		.SPICOnfig.SPI_CPHA 			= SPI_CPHA_LOW,
		.SPICOnfig.SPI_CPOL 			= SPI_CPOL_LOW,
		.SPICOnfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER,
		.SPICOnfig.SPI_DFF 				= SPI_DFF_8BITS,
		.SPICOnfig.SPI_SclkSpeed 	= SPI_SPICLK_PCLK_DIV_8,
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
	SPI_Pins.GPIO_PinConfig.GPIO_PinNumber	= GPIO_PIN_14;
	GPIO_Init(&SPI_Pins);
	
	//MOSI
	SPI_Pins.GPIO_PinConfig.GPIO_PinNumber	= GPIO_PIN_15;
	GPIO_Init(&SPI_Pins);
	
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

uint8_t SPI_VerifyResponse(uint8_t ackbyte){
	
	return (ackbyte == 0xF5)?1:0;
}

uint8_t SPI_WriteCommand(SPI_RegDef_t* pSPIx,uint8_t cmd,uint8_t* args){
		
		uint8_t dummy_write 	= 0xFF;
		uint8_t dummy_read		= 0xFF;
		uint8_t ackByte 			= 0x00;
		uint8_t	response			= 0x00;
	
		SPI_Write(pSPIx,&cmd,strlen(cmd));
		
		// do dummy read to clear off the RXNE
		SPI_Read(pSPIx,&dummy_read,strlen(dummy_read));
		
		//send some Dummy bits (1byte) to fetch the response fom slave.
		SPI_Write(pSPIx,&dummy_write,strlen(dummy_write));
		
		//read the ack byte received
		SPI_Read(pSPIx,&ackByte,1);
		
		if ( SPI_VerifyResponse(ackByte)  ){
			
			if (cmd == COMMAND_LED_CTRL ){ args[0] = LED_PIN; args[1] = LED_ON; }
			else if (cmd == COMMAND_LED_CTRL )	{ args[0] = ANALOG_PIN0;}
			
			//send arguments
			SPI_Write(pSPIx,&args,1);
		}
		
		if (cmd == COMMAND_LED_CTRL ){
			
			SPI_Write(pSPIx,&dummy_write,1);
			SPI_Read(pSPIx,&response,1);
			
			return response;
		
		}
		else{	return 0xEE;}
		

}

int main(){
	
	uint8_t dummy_write 	= 0xFF;
	uint8_t dummy_read	= 0xFF;
	uint8_t cmd_code 		= 0x00;
	uint8_t ackByte 		= 0x00;
	uint8_t args[2];
	uint8_t analog_read = 0x00;
	
	
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

		while( !GPIO_ReadFromInputPin(NUCLEO_PORT_BUTTON,NUCLEO_PIN_BUTTON) );
		delay();
		
		//Enable SPI
		SPI_Enable(SPI2,ENABLE);
		
		//1. Send CMD_LED_CTRL <pin no(1)> <value(1)>
		
		cmd_code = COMMAND_LED_CTRL;
		
		SPI_Write(SPI2,&cmd_code,strlen(cmd_code));
		
		// do dummy read to clear off the RXNE
		SPI_Read(SPI2,&dummy_read,strlen(dummy_read));
		
		//send some Dummy bits (1byte) to fetch the response fom slave.
		SPI_Write(SPI2,&dummy_write,strlen(dummy_write));
		
		//read the ack byte received
		SPI_Read(SPI2,&ackByte,1);
		
		if ( SPI_VerifyResponse(ackByte)  ){
			
			args[0] = LED_PIN;
			args[1] = LED_ON;
			
			//send arguments
			SPI_Write(SPI2,&args,1);
		}
		
		//2.
		
		while( !GPIO_ReadFromInputPin(NUCLEO_PORT_BUTTON,NUCLEO_PIN_BUTTON) );
		delay();
		
		cmd_code = COMMAND_SENSOR_READ;
		
		//response = SPI_WriteCommand(SPI2,cmd_code,args);
		
		SPI_Write(SPI2,&cmd_code,strlen(cmd_code));
		
		// do dummy read to clear off the RXNE
		SPI_Read(SPI2,&dummy_read,strlen(dummy_read));
		
		delay();
		//send some Dummy bits (1byte) to fetch the response fom slave.
		SPI_Write(SPI2,&dummy_write,strlen(dummy_write));
		
		//read the ack byte received
		SPI_Read(SPI2,&ackByte,1);
		
		if ( SPI_VerifyResponse(ackByte)  ){
			
			args[0] = ANALOG_PIN0;
	
			//send arguments
			SPI_Write(SPI2,&args,1);
			
			SPI_Read(SPI2,&dummy_read,1);
			delay();
			
			SPI_Write(SPI2,&dummy_write,1);
			
			SPI_Read(SPI2,&analog_read,1);
		}
		
		

		
		
		while( SPI_getFlagSTatus(SPI2,SPI_BUSY_FLAG) );
		SPI_Enable(SPI2,DISABLE);
	
	}

}