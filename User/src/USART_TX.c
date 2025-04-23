#include "stm32f446xx.h"
#include "stm32f446xx_Gpio_Driver.h"
#include "stm32f446xx_USART_Driver.h"
#include <stdio.h>
#include <string.h>

void USART2_Init(void);
void USART2_GPIOInit(void);




//DATA
uint8_t msg[1024] = "UART Tx testing...\n\r";


USART_Handle_t usart2_handle;


void delay(void)
{
	int i = 0;
	
	for( i=0; i< 100000; i++);
}


void GPIO_ButtonInit(void)
{   
		
		GPIO_Handle_t UserButton = {                                 
                                .GPIO_PinConfig.GPIO_PinMode        = GPIO_MODE_IT_FALLING,
                                .GPIO_PinConfig.GPIO_PinOPType      = GPIO_OPEN_DRAIN,
                                .GPIO_PinConfig.GPIO_PinPupdControl = GPIO_NPUPD,
                                .GPIO_PinConfig.GPIO_PinSpeed       = GPIO_HIGH_SPEED,
                                .pGPIOx                             = NUCLEO_PORT_BUTTON  
                            };											
														
		
		
		UserButton.GPIO_PinConfig.GPIO_PinNumber 			= NUCLEO_PIN_BUTTON;
		GPIO_PerCLKControl( NUCLEO_PORT_BUTTON, ENABLE );
    GPIO_Init(&UserButton);
												
}

void USART2_GPIOInit(void)
{   
    GPIO_Handle_t usart_gpios = {                                 
                                .GPIO_PinConfig.GPIO_PinMode        = GPIO_MODE_ALTERNATE,
                                .GPIO_PinConfig.GPIO_PinAltFuncMode = GPIO_AF7,
                                .GPIO_PinConfig.GPIO_PinOPType      = GPIO_PUSH_PULL,
                                .GPIO_PinConfig.GPIO_PinPupdControl = GPIO_PU,
                                .GPIO_PinConfig.GPIO_PinSpeed       = GPIO_FAST_SPEED,
                                .pGPIOx                             = GPIOA  
                            };
							
														
		//GPIO_PerCLKControl( GPIOA, ENABLE );
														
		//USART2 TX											
		usart_gpios.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_2;										
    GPIO_Init(&usart_gpios);
		
		//USART2 RX											
		usart_gpios.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_3;										
    GPIO_Init(&usart_gpios);
}

void USART2_Init(void)
{
    usart2_handle.pUSARTx 										= USART2;
		usart2_handle.USART_Config.Baudrate 			= USART_BAUDRATE_115200;
		usart2_handle.USART_Config.HW_FlowControl = USART_HW_FLOW_CONTROL_NONE;
		usart2_handle.USART_Config.Mode 					= USART_MODE_ONLY_TX;
		usart2_handle.USART_Config.N_StopBits 		= USART_STOPBITS_1;
		usart2_handle.USART_Config.ParityControl 	= USART_PARITY_DISABLE;
		usart2_handle.USART_Config.WordLength 		= USART_WORDLEN_8BITS;
		
		USART_Init(&usart2_handle);
}





int main(){
	
	GPIO_ButtonInit();
	USART2_GPIOInit();
	
	USART2_Init();
	USART_PeripheralClockControl(USART2,ENABLE);
	

	while(1)
	{
		//wait for Button press
		while( GPIO_ReadFromInputPin( NUCLEO_PORT_BUTTON, NUCLEO_PIN_BUTTON ) == 1 );
		delay();
		
		USART_SendData(&usart2_handle,(uint8_t*)msg,strlen(msg));
	}
}




