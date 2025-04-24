/*
 * uart_tx.c
 *
 *  Created on: Jan 22, 2019
 *      Author: admin
 */

#include <stdio.h>
#include <string.h>
#include "stm32f446xx.h"
#include "stm32f446xx_USART_Driver.h"
#include "stm32f446xx_Gpio_Driver.h"

//we have 3 different messages that we transmit to arduino
//you can by all means add more messages
char *msg[3] = {"hihihihihihi123", "Hello How are you ?" , "Today is Monday !"};

//reply from arduino will be stored here
char rx_buf[1024] ;

USART_Handle_t usart2_handle;


//This flag indicates reception completion
uint8_t rxCmplt = RESET;

uint8_t g_data = 0;

extern void initialise_monitor_handles();

void USART2_Init(void)
{
	usart2_handle.pUSARTx 										= USART2;
	usart2_handle.USART_Config.Baudrate 			= USART_BAUDRATE_115200;
	usart2_handle.USART_Config.HW_FlowControl = USART_HW_FLOW_CONTROL_NONE;
	usart2_handle.USART_Config.Mode 					= USART_MODE_TXRX;
	usart2_handle.USART_Config.N_StopBits 		= USART_STOPBITS_1;
	usart2_handle.USART_Config.WordLength 		= USART_WORDLEN_8BITS;
	usart2_handle.USART_Config.ParityControl 	= USART_PARITY_DISABLE;
	
	USART_Init(&usart2_handle);
}

void 	USART2_GPIOInit(void)
{

	GPIO_Handle_t usart_gpios = {                                 
                                .GPIO_PinConfig.GPIO_PinMode        = GPIO_MODE_ALTERNATE,
                                .GPIO_PinConfig.GPIO_PinAltFuncMode = GPIO_AF7,
                                .GPIO_PinConfig.GPIO_PinOPType      = GPIO_PUSH_PULL,
                                .GPIO_PinConfig.GPIO_PinPupdControl = GPIO_PU,
                                .GPIO_PinConfig.GPIO_PinSpeed       = GPIO_FAST_SPEED,
                                .pGPIOx                             = GPIOA  
                            };
	
	usart_gpios.GPIO_PinConfig.GPIO_PinNumber  = GPIO_PIN_2;
	GPIO_Init(&usart_gpios);

	usart_gpios.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_3;
	GPIO_Init(&usart_gpios);

}

void GPIO_ButtonInit(void)
{
	//this is btn gpio configuration
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
	
		
	
	GPIO_Handle_t GpioLed = {                                 
															.pGPIOx 															= NUCLEO_PORT_LED,
															.GPIO_PinConfig.GPIO_PinNumber 				= NUCLEO_PIN_LED,
															.GPIO_PinConfig.GPIO_PinMode 					= GPIO_MODE_OUTPUT,
															.GPIO_PinConfig.GPIO_PinOPType 				= GPIO_PUSH_PULL,
															.GPIO_PinConfig.GPIO_PinPupdControl 	= GPIO_NPUPD,
															.GPIO_PinConfig.GPIO_PinSpeed 				= GPIO_HIGH_SPEED
													};															
	//this is led gpio configuration
	GPIO_PerCLKControl( NUCLEO_PORT_BUTTON, ENABLE );
	GPIO_Init(&GpioLed);

}

void delay(void)
{
	for(uint32_t i = 0 ; i < 500000/2 ; i ++);
}
int main(void)
{
	uint32_t cnt = 0;


	initialise_monitor_handles();

	USART2_GPIOInit();
    USART2_Init();

    USART_IRQInterruptConfig(IRQ_NO_USART2,ENABLE);

    USART_PeripheralControl(USART2,ENABLE);

    printf("Application is running\n");

    //do forever
    while(1)
    {
		//wait till button is pressed
		while( ! GPIO_ReadFromInputPin(NUCLEO_PORT_BUTTON,NUCLEO_PIN_BUTTON) );

		//to avoid button de-bouncing related issues 200ms of delay
		delay();

		// Next message index ; make sure that cnt value doesn't cross 2
		cnt = cnt % 3;

		//First lets enable the reception in interrupt mode
		//this code enables the receive interrupt
		while ( USART_ReceiveDataIT(&usart2_handle,rx_buf,strlen(msg[cnt])) != USART_READY );

		//Send the msg indexed by cnt in blocking mode
    	USART_SendData(&usart2_handle,(uint8_t*)msg[cnt],strlen(msg[cnt]));

    	printf("Transmitted : %s\n",msg[cnt]);


    	//Now lets wait until all the bytes are received from the arduino .
    	//When all the bytes are received rxCmplt will be SET in application callback
    	while(rxCmplt != SET);

    	//just make sure that last byte should be null otherwise %s fails while printing
    	rx_buf[strlen(msg[cnt])+ 1] = '\0';

    	//Print what we received from the arduino
    	printf("Received    : %s\n",rx_buf);

    	//invalidate the flag
    	rxCmplt = RESET;

    	//move on to next message indexed in msg[]
    	cnt ++;
    }


	return 0;
}


void USART2_IRQHandler(void)
{
	USART_IRQHandling(&usart2_handle);
}





void USART_ApplicationEventCallback( USART_Handle_t *pUSARTHandle,uint8_t ApEv)
{
   if(ApEv == USART_EVENT_RX_CMPLT)
   {
			rxCmplt = SET;

   }else if (ApEv == USART_EVENT_TX_CMPLT)
   {
	   ;
   }
}
