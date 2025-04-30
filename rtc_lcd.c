
/**************************************************************************//**
   @file     rtc_lcd.c
   @author   Xavier Rocher
   @version  V0.0
   @date     2025-04-30
   @brief    RTC Application
 ******************************************************************************/

/* Includes ------------------------------------------------------------------*/	 

#include "stm32f446xx.h"
#include "ds1307.h"

/* Private define ------------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
void assert_failed(uint8_t* file, uint32_t line){}

	
	
int main(void)
{	
	RTC_time_t current_time;
	RTC_date_t current_date;
	
	uint8_t fail = 0;
	
	uint8_t status = ds1307_init();
	
	if( !status )
	{
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
		}
		else
		{
			// uart wite 04:25:41 
		}
		
		// uart wite 30/04/25
		
	}
	else
	{	
		fail = 1;
		while(1);
	}
	
	return 0;
}


/* User interrupts -----------------------------------------------------------*/