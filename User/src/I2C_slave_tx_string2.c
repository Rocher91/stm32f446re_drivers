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
uint8_t Tx_buff[] = "HiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHi";
uint8_t rxComplete = RESET;

uint32_t data_len = 0;
uint8_t CommandCode = 0xFF;

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
	
	data_len = strlen((char*)Tx_buff);
	
  //I2C Pin Inits
	I2C_GPIOInits();

	//I2C peripheral Configuration
	I2CInits();
	
	//I2C IRQ Configurations
	I2C_IRQInterruptConfig( IRQ_NO_I2C1_EV, ENABLE );
	I2C_IRQInterruptConfig( IRQ_NO_I2C1_ER, ENABLE );
	I2C_SlaveEnableCallbackEvents( I2C1, ENABLE );

	//Enable the I2C peripheral
	I2C_PeripheralControl(I2C1,I2C_ACK_ENABLE);

  // ack bit is made 1 after PE = 1
  I2C_ManageAcking(I2C1,ENABLE);
	
	while(1)
	{
	
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

void I2C_ApplicationEventCallback(I2C_Handle_t *pI2CHandle, uint8_t AppEv)
{


	static uint32_t cnt = 0;
	static uint32_t w_ptr = 0;



	if(AppEv == I2C_ERROR_AF)
	{
		//This will happen during slave transmitting data to master .
		// slave should understand master needs no more data
		//slave concludes end of Tx


		//if the current active code is 0x52 then dont invalidate
		if(! (CommandCode == 0x52))
			CommandCode = 0XFF;

		//reset the cnt variable because its end of transmission
		cnt = 0;

		//Slave concludes it sent all the bytes when w_ptr reaches data_len
		if(w_ptr >= (data_len))
		{
			w_ptr=0;
			CommandCode = 0xff;
		}

	}else if (AppEv == I2C_EV_STOP)
	{
		//This will happen during end slave reception
		//slave concludes end of Rx

		cnt = 0;

	}else if (AppEv == I2C_EV_DATA_REQ)
	{
		//Master is requesting for the data . send data
		if(CommandCode == 0x51)
		{
			//Here we are sending 4 bytes of length information
			I2C_SlaveSendData(I2C1,((data_len >> ((cnt%4) * 8)) & 0xFF));
		    cnt++;
		}else if (CommandCode == 0x52)
		{
			//sending Tx_buf contents indexed by w_ptr variable
			I2C_SlaveSendData(I2C1,Tx_buff[w_ptr++]);
		}
	}else if (AppEv == I2C_EV_DATA_RCV)
	{
		//Master has sent command code, read it
		 CommandCode = I2C_SlaveReceiveData(I2C1);

	}
}
