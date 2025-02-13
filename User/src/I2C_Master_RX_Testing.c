#include "stm32f446xx.h"
#include "stm32f446xx_Gpio_Driver.h"
#include "stm32f446xx_I2C_Driver.h"
#include <stdio.h>
#include <string.h>

void I2C_GPIOInits(void);
void I2CInits(void);
void delay(void);

#define MY_ADDR         0x61
#define SLAVE_ADDR      0x68

/*
    PB6 -> SCL
    PB9 -> SDA
*/

I2C_Handle_t I2C1Handle;

//DATA
uint8_t rcv_buff[] = "";

void delay(void)
{
	int i = 0;
	
	for( i=0; i< 100000; i++);
}


void I2C_GPIOInits(void)
{   
    //Page 58 Datasheet stm32f446RE

    GPIO_Handle_t I2CPins = {                                 
                                .GPIO_PinConfig.GPIO_PinMode        = GPIO_MODE_ALTERNATE,
                                .GPIO_PinConfig.GPIO_PinAltFuncMode = GPIO_AF4,
                                .GPIO_PinConfig.GPIO_PinOPType      = GPIO_OPEN_DRAIN,
                                .GPIO_PinConfig.GPIO_PinPupdControl = GPIO_NPUPD,
                                .GPIO_PinConfig.GPIO_PinSpeed       = GPIO_FAST_SPEED,
                                .pGPIOx                             = GPIOB  
                            };
		
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
													

    I2CPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_6;
    GPIO_PerCLKControl( GPIOB, ENABLE );
    GPIO_Init(&I2CPins);

    I2CPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_7;
    GPIO_PerCLKControl( GPIOB, ENABLE );
    GPIO_Init(&I2CPins);

}

void I2CInits(void)
{
    I2C1Handle.pI2Cx                        = I2C1;
    I2C1Handle.I2C_Config.I2C_ACK_Control   = I2C_ACK_ENABLE;
    I2C1Handle.I2C_Config.I2C_DeviceAddress = MY_ADDR;
    I2C1Handle.I2C_Config.I2C_FM_DutyCycle  = I2C_FM_DUTY_2;
    I2C1Handle.I2C_Config.I2C_SCL_Speed     = I2C_SCL_SPEED_SM;

    I2C_Init(&I2C1Handle);

}

int main(){
	
    uint8_t commandCode = 0;
    uint8_t len  = 0;

   //I2C Pin Inits
	I2C_GPIOInits();

	//I2C peripheral Configuration
	I2CInits();

	//Enable the I2C peripheral
	I2C_PeripheralControl(I2C1,I2C_ACK_ENABLE);

    // ack bit is made 1 after PE = 1
    I2C_ManageAcking(I2C1,ENABLE);
	
	while(1)
	{
		//wait for Button press
		while(!GPIO_ReadFromInputPin( NUCLEO_PORT_BUTTON, NUCLEO_PIN_LED ));
		
		//to avoid button de-bouncing related issues 200ms of delay
		delay();
        
		commandCode = 0x51;

		//Send data
		I2C_MasterSendData(&I2C1Handle,&commandCode,1,SLAVE_ADDR,I2C_ENABLE_SR);

		//Read Data
		I2C_MasterReceiveData(&I2C1Handle,&len,1,SLAVE_ADDR,I2C_ENABLE_SR);

		commandCode = 0x52;

		//Send data
		I2C_MasterSendData(&I2C1Handle,&commandCode,1,SLAVE_ADDR,I2C_ENABLE_SR);

		//Read Data
		I2C_MasterReceiveData(&I2C1Handle,&rcv_buff,len,SLAVE_ADDR,I2C_DISABLE_SR);

		
	}
}



