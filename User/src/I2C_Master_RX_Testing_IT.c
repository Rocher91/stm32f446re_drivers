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
uint8_t rxComplete = RESET;

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
	
	//I2C IRQ Configurations
	I2C_IRQInterruptConfig( IRQ_NO_I2C1_EV, ENABLE );
	I2C_IRQInterruptConfig( IRQ_NO_I2C1_ER, ENABLE );

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
		while( I2C_MasterSendDataIT(&I2C1Handle,&commandCode,1,SLAVE_ADDR,I2C_ENABLE_SR) != I2C_READY );

		//Read Data
		while( I2C_MasterReceiveDataIT(&I2C1Handle,&len,1,SLAVE_ADDR,I2C_ENABLE_SR) != I2C_READY );

		commandCode = 0x52;

		//Send data
		while( I2C_MasterSendDataIT(&I2C1Handle,&commandCode,1,SLAVE_ADDR,I2C_ENABLE_SR) != I2C_READY );

		//Read Data
		while( I2C_MasterReceiveDataIT(&I2C1Handle,&rcv_buff[0],len,SLAVE_ADDR,I2C_DISABLE_SR) != I2C_READY );
		
		rxComplete = RESET;
		
		while( rxComplete != SET);
		
		rcv_buff[len+1] = '\0';
			
	}
}

void I2C_EV_IRQHandler(void)
{
	I2C_EV_IRQHandling( &I2C1Handle );
}

void I2C_ER_IRQHandler(void)
{
	I2C_ER_IRQHandling( &I2C1Handle );
}

void I2C_ApplicationEventCallback(I2C_Handle_t *pI2CHandle, uint8_t AppEv )
{
	if( AppEv == I2C_EV_TX_CMPLTE)
	{
		//printf("Tx is completed.\n");
	}
	else if( AppEv == I2C_EV_RX_CMPLTE)
	{
		//printf("Rx is completed.\n");
		rxComplete = SET;
	}
	else if( AppEv == I2C_ERROR_AF)
	{	
		//in master ack failure happens when fails to send ack for the byte 
		//sent from the master
		
		//printf("Error Ack failure.\n");
		I2C_CloseSendData(pI2CHandle);
		
		//generate stop condition to release the bus.
		I2C_GenerateStopCondition(pI2CHandle->pI2Cx);
		
		//hang in infinite loop
		while(1);
		
	}
}
