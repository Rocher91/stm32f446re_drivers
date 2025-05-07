
/**************************************************************************//**
   @file     rtc_lcd.c
   @author   Xavier Rocher
   @version  V0.0
   @date     2025-04-30
   @brief    RTC Application
 ******************************************************************************/

/* Includes ------------------------------------------------------------------*/	 

#include "stm32f446xx.h"
#include "stm32f446xx_USART_Driver.h"
#include "ds1307.h"
#include <stdio.h>
#include <string.h>


/* Private define ------------------------------------------------------------*/

#define SYSTICK_TIM_CLK   16000000UL

/* Private typedef -----------------------------------------------------------*/


/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

//DATA

USART_Handle_t usart2_handle;

/* Private functions ---------------------------------------------------------*/
void init_systick_timer(uint32_t tick_hz);
char* get_day_of_week(uint8_t day);
char* time_to_string(RTC_time_t* rtc_time);
char* date_to_string(RTC_date_t *rtc_date);
void number_to_string(uint8_t num, char* buf);
void assert_failed(uint8_t* file, uint32_t line){}
void USART2_Init(void);
void USART2_GPIOInit(void);

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
	
	
int main(void)
{	
	USART2_GPIOInit();
	USART2_Init();
	USART_PeripheralClockControl(USART2,ENABLE);
	
	RTC_time_t current_time;
	RTC_date_t current_date;
	
	
	uint8_t status = ds1307_init();
	
	if( !status )
	{	
		
		//init_systick_timer(1);
		
		char initMessage[] = "DS1307 is initiated";
		USART_SendData(&usart2_handle,(uint8_t*)initMessage,strlen(initMessage));
		
		current_date.day = FRIDAY;
		current_date.date = 30;
		current_date.month = 4;
		current_date.year = 25;
		
		current_time.hours = 4;
		current_time.minutes = 25;
		current_time.seconds = 41;
		current_time.time_format = TIME_FORMAT_12HOURS_PM;
		
		ds1307_set_current_date(&current_date);
		ds1307_set_current_time(&current_time);
		
		char* am_pm = NULL;
		
		if ( current_time.time_format != TIME_FORMAT_24HOURS )
		{
			am_pm = ( current_time.time_format )?"PM":"AM";
			// uart wite 04:25:41 PM
			
			char* msg = time_to_string( &current_time );
			USART_SendData(&usart2_handle,(uint8_t*)msg,strlen(msg));
		}
		else
		{
			// uart wite 04:25:41 
			char* msg = time_to_string( &current_time );
			USART_SendData(&usart2_handle,(uint8_t*)msg,strlen(msg));
		}
		
		// uart wite 30/04/25
		char* msg = date_to_string( &current_date );
		USART_SendData(&usart2_handle,(uint8_t*)msg,strlen(msg));
		
	}
	else
	{	
		char initMessage[] = "DS1307 is not initiated. Check connections!";
		USART_SendData(&usart2_handle,(uint8_t*)initMessage,strlen(initMessage));
		while(1);
	}
	
	return 0;
}

void init_systick_timer(uint32_t tick_hz)
{
	uint32_t *pSRVR = (uint32_t*)0xE000E014;
	uint32_t *pSCSR = (uint32_t*)0xE000E010;

    /* calculation of reload value */
    uint32_t count_value = (SYSTICK_TIM_CLK/tick_hz)-1;

    //Clear the value of SVR
    *pSRVR &= ~(0x00FFFFFFFF);

    //load the value in to SVR
    *pSRVR |= count_value;

    //do some settings
    *pSCSR |= ( 1 << 1); //Enables SysTick exception request:
    *pSCSR |= ( 1 << 2);  //Indicates the clock source, processor clock source

    //enable the systick
    *pSCSR |= ( 1 << 0); //enables the counter

}

char* get_day_of_week(uint8_t day)
{
	char* days[] = { "Monday","Tuesday","Wednesday","Tueday","Friday","Saturday","Sunday" };
	
	return days[ day-1 ];
}

void number_to_string(uint8_t num, char* buf)
{
	if(num<10)
	{
		buf[0] = '0';
		buf[0] = num+48;
	}
	else if (num>=10 && num <99)
	{
		buf[0] = (num/10)+48;
		buf[1] = (num%10)+48;
	}
}
	
//hh:mm:ss
char* time_to_string(RTC_time_t* rtc_time)
{
	static char buf[9];
	
	buf[2]= ':';
	buf[5]= ':';
	
	number_to_string( rtc_time->hours ,buf );
	number_to_string( rtc_time->minutes,&buf[3] );
	number_to_string( rtc_time->seconds,&buf[6] );
	
	buf[8] = '\0';
	
	return buf;
	
}

char* date_to_string(RTC_date_t *rtc_date)
{
	static char buf[9];
	
	buf[2] = '/';
	buf[5] = '/';
	
	number_to_string(rtc_date->date,buf);
	number_to_string(rtc_date->month,&buf[3]);
	number_to_string(rtc_date->year,&buf[6]);
	
	buf[8] = '\0';
	
	return buf;

}

/* User interrupts -----------------------------------------------------------*/

void SysTick_Handler(void)
{

}