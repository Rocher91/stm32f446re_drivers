#include "stm32f446xx.h"
#include "stm32f446xx_Gpio_Driver.h"
#include "stm32f446xx_I2C_Driver.h"
#include <stdio.h>
#include <string.h>

void I2C_GPIOInits(void);
void I2CInits(void);
void delay(void);

/*
    PB6 -> SCL
    PB9 -> SDA
*/

I2C_Handle_t I2C1Handle;

//DATA
uint8_t data[] = "We are Testing I2C Master TX\n";

void delay(void)
{
	for( uint32_t i=0; i< 500000/2; i++);
}


void I2C_GPIOInits(void)
{   
    //Page 58 Datasheet stm32f446RE

    GPIO_Handle_t I2CPins = {                                 
                                .GPIO_PinConfig.GPIO_PinMode        = GPIO_MODE_ALTERNATE,
                                .GPIO_PinConfig.GPIO_PinAltFuncMode = GPIO_AF4,
                                .GPIO_PinConfig.GPIO_PinOPType      = GPIO_OPEN_DRAIN,
                                .GPIO_PinConfig.GPIO_PinPupdControl = GPIO_PU,
                                .GPIO_PinConfig.GPIO_PinSpeed       = GPIO_FAST_SPEED,
                                .pGPIOx                             = GPIOB  
                            };
		
		GPIO_Handle_t UserButton = {                                 
                                .GPIO_PinConfig.GPIO_PinMode        = GPIO_MODE_INPUT,
                                .GPIO_PinConfig.GPIO_PinPupdControl = GPIO_NPUPD,
                                .GPIO_PinConfig.GPIO_PinSpeed       = GPIO_HIGH_SPEED,
                                .pGPIOx                             = NUCLEO_PORT_BUTTON  
                            };											
														
		UserButton.GPIO_PinConfig.GPIO_PinNumber 			= NUCLEO_PIN_BUTTON;
		GPIO_PerCLKControl( NUCLEO_PORT_BUTTON, ENABLE );
    GPIO_Init(&UserButton);
													

    I2CPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_6;
    GPIO_Init(&I2CPins);

    I2CPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_9;
    GPIO_Init(&I2CPins);

}

void I2CInits(void)
{
    I2C1Handle.pI2Cx                        = I2C1;
    I2C1Handle.I2C_Config.I2C_ACK_Control   = I2C_ACK_ENABLE;
    I2C1Handle.I2C_Config.I2C_DeviceAddress = 0x61;
    I2C1Handle.I2C_Config.I2C_FM_DutyCycle  = I2C_FM_DUTY_2;
    I2C1Handle.I2C_Config.I2C_SCL_Speed     = I2C_SCL_SPEED_SM;

    I2C_Init(&I2C1Handle);

}

int main(){
	
   //I2C Pin Inits
	I2C_GPIOInits();

	//I2C peripheral Configuration
	I2CInits();

	//Enable the I2C peripheral
	I2C_PeripheralControl(I2C1,ENABLE);
	
	while(1)
	{
		//wait for Button press
		while( GPIO_ReadFromInputPin( NUCLEO_PORT_BUTTON, NUCLEO_PIN_BUTTON ) == 1 );
		
		//to avoid button de-bouncing related issues 200ms of delay
		delay();
		//I2C_ScanBus(&I2C1Handle );
		//Send data
		I2C_MasterSendData( &I2C1Handle, data, strlen((char*)data), 0x68 ,I2C_DISABLE_SR);
		
	}
}

void I2C_ApplicationEventCallback(I2C_Handle_t*pI2CHandle,uint8_t AppEv)
{

}


