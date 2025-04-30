#include "ds1307.h"
#include "stm32f446xx_I2C_Driver.h"

I2C_Handle_t g_ds1307_I2cHandle;

static void ds1307_I2C_Pin_config(void);
static void ds1307_I2C_Config(void);
static void ds1307_write( uint8_t reg_address, uint8_t value );
static uint8_t ds1307_read( uint8_t reg_address );
static uint8_t binary_to_BCD(uint8_t value);
static uint8_t BCD_to_binary(uint8_t value);

// returns 1 : CH =1; init failed
// returns 0 : CH =0; init success

uint8_t ds1307_init(void)
{
	//1. Init I2C pins.
	ds1307_I2C_Pin_config();
	
	//2. Initialize the I2C peripheral.
	ds1307_I2C_Config();
	
	//3. Enable the I2C peripheral
	I2C_PeripheralControl( DS1307_I2C, ENABLE);
	
	//4. Make clock halt = 0
	ds1307_write( DS1307_ADDR_SECONDS, 0x00 );
	
	//5. Read back clock halt bit 
	uint8_t clock_state =  ds1307_read( DS1307_ADDR_SECONDS );
	
	return ( (clock_state >> 7) &0x01) ;
}
void ds1307_set_current_time(RTC_time_t* rtc_time)
{
	uint8_t 	hours 	= 0, 
						minutes = 0, 
						seconds	= 0;
	
	hours 	= binary_to_BCD( rtc_time->hours );
	minutes = binary_to_BCD( rtc_time->minutes );
	seconds = binary_to_BCD( rtc_time->seconds );
	
	seconds &= ~( 1 << 7 );
	
	ds1307_write(DS1307_I2C_ADDRESS,DS1307_ADDR_SECONDS);
	ds1307_write(DS1307_ADDR_MINUTES,minutes);
	
	if( rtc_time->time_format == TIME_FORMAT_24HOURS )
	{
		hours &= ~(1 << 6);
	}
	else
	{
		hours |= (1 << 6);
		hours = (rtc_time->time_format == TIME_FORMAT_12HOURS_PM)? ( hours | (1 << 5) ) : ( hours & ~(1 << 5) );
	}
		
	ds1307_write(DS1307_ADDR_HOURS,hours);
	
}

void ds1307_get_current_time(RTC_time_t* rtc_time)
{
	uint8_t 	hours 	= 0, 
						minutes = 0, 
						seconds	= 0;
	
	seconds = ds1307_read(DS1307_ADDR_SECONDS);
	seconds &= ~( 1 << 7 );
	
	minutes = ds1307_read(DS1307_ADDR_MINUTES);
	hours 	= ds1307_read(DS1307_ADDR_HOURS);
	
	if ( hours & (1 << 6) )
	{
		// 12H FORMAT
		rtc_time->time_format = (( hours & (1 << 5)) == 0) ? TIME_FORMAT_12HOURS_AM : TIME_FORMAT_12HOURS_PM;
		hours &= ~( 0x03 << 5); // Clear bit 6 and 5
		
	}
	else
	{
		// 24H FORMAT
		rtc_time->time_format = TIME_FORMAT_24HOURS;
	}
	
	rtc_time->seconds = BCD_to_binary(seconds);
	rtc_time->minutes = BCD_to_binary(minutes);
	rtc_time->hours 	= BCD_to_binary(hours);
	
}

void ds1307_set_current_date(RTC_date_t* rtc_date)
{
	uint8_t 	date 	= 0, 
						month = 0, 
						year  = 0,
						day		= 0;
	
		date 	= binary_to_BCD( rtc_date->date );
		month = binary_to_BCD( rtc_date->month );
		year 	= binary_to_BCD( rtc_date->year );
		day 	= binary_to_BCD( rtc_date->day );
		
		ds1307_write(DS1307_ADDR_YEAR,year);
		ds1307_write(DS1307_ADDR_MONTH,month);
		ds1307_write(DS1307_ADDR_DAY,day);
		ds1307_write(DS1307_ADDR_DATE,date);
	
}
void ds1307_get_current_date(RTC_date_t* rtc_date)
{
		uint8_t 	date 	= 0, 
							month = 0, 
							year  = 0,
							day		= 0;
	
		date 	= binary_to_BCD( rtc_date->date );
		month = binary_to_BCD( rtc_date->month );
		year 	= binary_to_BCD( rtc_date->year );
		day 	= binary_to_BCD( rtc_date->day );
		
		rtc_date->date 	= date;
		rtc_date->year 	= year;
		rtc_date->month = month;
		rtc_date->day 	= day;

	
}

static void ds1307_I2C_Pin_config(void)
{
	GPIO_Handle_t I2C_sda,I2C_scl;
	
	memset(&I2C_sda,0,sizeof(I2C_sda));
	memset(&I2C_scl,0,sizeof(I2C_scl));
	
	/*
		I2C1_SCL ==> PB6
		I2C1_SDA ==> PB7	
	*/
	
	I2C_sda.pGPIOx 															= DS1307_I2C_GPIO_PORT;
	I2C_sda.GPIO_PinConfig.GPIO_PinAltFuncMode 	= 4;
	I2C_sda.GPIO_PinConfig.GPIO_PinMode 				= GPIO_MODE_ALTERNATE;
	I2C_sda.GPIO_PinConfig.GPIO_PinNumber 			= DS1307_I2C_SDA_PIN;
	I2C_sda.GPIO_PinConfig.GPIO_PinOPType 			= GPIO_OPEN_DRAIN;
	I2C_sda.GPIO_PinConfig.GPIO_PinPupdControl 	= DS1307_I2C_PUPD;
	I2C_sda.GPIO_PinConfig.GPIO_PinSpeed				= DS1307_I2C_SPEED;
	
	GPIO_Init(&I2C_sda);
	
	I2C_scl.pGPIOx 															= DS1307_I2C_GPIO_PORT;
	I2C_scl.GPIO_PinConfig.GPIO_PinAltFuncMode 	= 4;
	I2C_scl.GPIO_PinConfig.GPIO_PinMode 				= GPIO_MODE_ALTERNATE;
	I2C_scl.GPIO_PinConfig.GPIO_PinNumber 			= DS1307_I2C_SCL_PIN;
	I2C_scl.GPIO_PinConfig.GPIO_PinOPType 			= GPIO_OPEN_DRAIN;
	I2C_scl.GPIO_PinConfig.GPIO_PinPupdControl 	= DS1307_I2C_PUPD;
	I2C_scl.GPIO_PinConfig.GPIO_PinSpeed				= DS1307_I2C_SPEED;
	
	GPIO_Init(&I2C_scl);
	
	
}

static void ds1307_I2C_Config(void)
{
	g_ds1307_I2cHandle.pI2Cx 											= DS1307_I2C;
	g_ds1307_I2cHandle.I2C_Config.I2C_ACK_Control = I2C_ACK_ENABLE;
	g_ds1307_I2cHandle.I2C_Config.I2C_SCL_Speed 	= DS1307_I2C_SPEED;
	
	I2C_Init(&g_ds1307_I2cHandle);

}

static void ds1307_write( uint8_t reg_address, uint8_t value )
{
	uint8_t tx[2] = { reg_address, value };
	
	I2C_MasterSendData( &g_ds1307_I2cHandle,tx,2,DS1307_I2C_ADDRESS,0);
	
}

static uint8_t ds1307_read( uint8_t reg_address )
{	
	
	uint8_t data = 0x00;
	
	I2C_MasterSendData( &g_ds1307_I2cHandle,&reg_address,1,DS1307_I2C_ADDRESS,0);
	I2C_MasterReceiveData(&g_ds1307_I2cHandle,&data,1,DS1307_I2C_ADDRESS,0);
	
	return data;

}

static uint8_t binary_to_BCD(uint8_t value)
{
	return ( ( ( value / 10 ) << 4 ) | ( value % 10 ) );
}

static uint8_t BCD_to_binary( uint8_t value )
{	
	return ((( value & 0xF0 ) >> 4 )* 10 ) + ( value & 0x0F );
}
