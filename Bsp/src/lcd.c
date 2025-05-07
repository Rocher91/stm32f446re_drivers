#include "lcd.h"

static void write_4_bits( uint8_t value );
static void lcd_enable(void);

void lcd_send_commamd(uint8_t command)
{
	
	/* RS = 0 for LCD command*/
	GPIO_WriteTouOutPutPin(LCD_GPIO_PORT,LCD_GPIO_RS,RESET);
	
	/* R/nW = 0 for write*/
	GPIO_WriteTouOutPutPin(LCD_GPIO_PORT,LCD_GPIO_RW,RESET);
	
	write_4_bits( (command & 0xF0) >> 4 );
	write_4_bits( (command & 0x0F)  );
	
	
}

void lcd_send_data(uint8_t data)
{
	
	/* RS = 0 for LCD command*/
	GPIO_WriteTouOutPutPin(LCD_GPIO_PORT,LCD_GPIO_RS,RESET);
	
	/* R/nW = 0 for write*/
	GPIO_WriteTouOutPutPin(LCD_GPIO_PORT,LCD_GPIO_RW,RESET);
	
	write_4_bits( (data & 0xF0) >> 4 );
	write_4_bits( (data & 0x0F)  );
	
	
}
void lcd_init(void)
{

	//1.COnfigure the GPIO pins which are used for lcd connections.
	
		GPIO_Handle_t lcd_signal = 	{
																		.pGPIOx 														= LCD_GPIO_PORT,
																		.GPIO_PinConfig.GPIO_PinMode 				= GPIO_MODE_OUTPUT,
																		.GPIO_PinConfig.GPIO_PinNumber 			= LCD_GPIO_RS,
																		.GPIO_PinConfig.GPIO_PinOPType 			= GPIO_PUSH_PULL,
																		.GPIO_PinConfig.GPIO_PinPupdControl = GPIO_NPUPD,
																		.GPIO_PinConfig.GPIO_PinSpeed 			= GPIO_FAST_SPEED
																};
	
		GPIO_Init(&lcd_signal);
																
		lcd_signal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_RS;
		GPIO_Init(&lcd_signal);		
																
		lcd_signal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_RW;
		GPIO_Init(&lcd_signal);
															
		lcd_signal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_EN;
		GPIO_Init(&lcd_signal);
		
		lcd_signal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_D4;
		GPIO_Init(&lcd_signal);

		lcd_signal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_D5;
		GPIO_Init(&lcd_signal);

		lcd_signal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_D6;
		GPIO_Init(&lcd_signal);

		lcd_signal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_D7;
		GPIO_Init(&lcd_signal);
																
		GPIO_WriteTouOutPutPin( LCD_GPIO_PORT, LCD_GPIO_RS, RESET );	
		GPIO_WriteTouOutPutPin( LCD_GPIO_PORT, LCD_GPIO_RW, RESET );
		GPIO_WriteTouOutPutPin( LCD_GPIO_PORT, LCD_GPIO_EN, RESET );		

		GPIO_WriteTouOutPutPin( LCD_GPIO_PORT, LCD_GPIO_D4, RESET );	
		GPIO_WriteTouOutPutPin( LCD_GPIO_PORT, LCD_GPIO_D5, RESET );
		GPIO_WriteTouOutPutPin( LCD_GPIO_PORT, LCD_GPIO_D6, RESET );
		GPIO_WriteTouOutPutPin( LCD_GPIO_PORT, LCD_GPIO_D7, RESET );
		
	//2. Do the LCD initialization
	
	//mdelay(40);
	
	/* RS = 0, For LCD command */
	GPIO_WriteTouOutPutPin(LCD_GPIO_PORT,LCD_GPIO_RS,RESET);
	GPIO_WriteTouOutPutPin(LCD_GPIO_PORT,LCD_GPIO_RW,RESET);
	
	write_4_bits(0x03);
	mdelay(40);
	write_4_bits(0x03);
	udelay(150);
	write_4_bits(0x03);
	write_4_bits(0x02);
	
	
	
}

static void write_4_bits( uint8_t value )
{
	GPIO_WriteTouOutPutPin( LCD_GPIO_PORT, LCD_GPIO_D4, ( value >> 0 )& 0x01 );	
	GPIO_WriteTouOutPutPin( LCD_GPIO_PORT, LCD_GPIO_D5, ( value >> 1 )& 0x01 );
	GPIO_WriteTouOutPutPin( LCD_GPIO_PORT, LCD_GPIO_D6, ( value >> 2 )& 0x01 );
	GPIO_WriteTouOutPutPin( LCD_GPIO_PORT, LCD_GPIO_D7, ( value >> 3 )& 0x01 );
	
	lcd_enable();
}

static void lcd_enable(void)
{
	GPIO_WriteTouOutPutPin( LCD_GPIO_PORT, LCD_GPIO_EN, SET );
	udelay(10);
	GPIO_WriteTouOutPutPin( LCD_GPIO_PORT, LCD_GPIO_EN, RESET );
	udelay(100);

}