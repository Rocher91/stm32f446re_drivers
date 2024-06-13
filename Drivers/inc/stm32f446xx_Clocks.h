#ifndef INC_STM32F446XX_CLOCKS_DRIVER_H_
#define INC_STM32F446XX_CLOCKS_DRIVER_H_

#include "stm32f446xx.h"

//Config Externla Clocks (ON,OFF Bypass)

#define PLL_SRC_HSI 0
#define PLL_SRC_HSE 1

static uint16_t AHB_Prescaler[16] = { 1,1,1,1,1,1,1,1,2,4,8,16,64,128,256,512 };
static uint8_t APB_Prescaler[8] 	= { 1,1,1,1,2,4,8,16 };	

typedef enum{
	 RCC_HSE_OFF,
	 RCC_HSE_ON,
	 RCC_HSE_BYP
	
}RCC_HSE_Status_t;

typedef enum{
	 RCC_LSE_OFF,
	 RCC_LSE_ON,
	 RCC_LSE_BYP
	
}RCC_LSE_Status_t;

typedef enum{
	RCC_PLL_Source_HSI,
	RCC_PLL_Source_HSE
	
}RCC_PLL_Source_t;



#define IS_VALID_PLLM_VAL(x)  	( x<64 && x>1 )?1:0
#define IS_VALID_PLLN_VAL(x)  	( x<433 && x>50 )?1:0
#define IS_VALID_PLLP_VAL(x)  	( x==2 || x==4 || x==6 || x==8 )?1:0
#define IS_VALID_PLLMQ_VAL(x)  	( x<16 && x>1 )?1:0
#define IS_VALID_PLLR_VAL(x)  	( x<8 && x>1 )?1:0

typedef enum{
	
	RCC_MCO1_Source_HSI,
	RCC_MCO1_Source_LSE,
	RCC_MCO1_Source_HSE,
	RCC_MCO1_Source_PLL,
	
}RCC_MCO1_Source_t;

typedef enum{
	RCC_MCO1_Prescaler_None,
	RCC_MCO1_Prescaler_2 = 4,
	RCC_MCO1_Prescaler_4 = 5,
	RCC_MCO1_Prescaler_5 = 6,
	RCC_MCO1_Prescaler_6 = 7,
	
}RCC_MCO1_Prescaler_t;


typedef enum{
	RCC_MCO2_Source_HSI,
	RCC_MCO2_Source_LSE,
	RCC_MCO2_Source_HSE,
	RCC_MCO2_Source_PLL,
	
}RCC_MCO2_Source_t;


typedef enum{
	RCC_MCO2_Prescaler_None,
	RCC_MCO2_Prescaler_2 = 4,
	RCC_MCO2_Prescaler_4 = 5,
	RCC_MCO2_Prescaler_5 = 6,
	RCC_MCO2_Prescaler_6 = 7,
	
}RCC_MCO2_Prescaler_t;


typedef enum{
	RCC_Clock_HSI,
	RCC_Clock_HSE,
	RCC_Clock_PLL,
	RCC_Clock_LSE,
	
}RCC_Clock_t;

typedef enum{
	RCC_Sysclk_Src_HSI,
	RCC_Sysclk_Src_HSE,
	RCC_Sysclk_Src_PLL_P,
	RCC_Sysclk_Src_PLL_R
	
}RCC_SysClk_Source_t;

typedef enum{
	
	RCC_AHB_Prescaler_None 	= 0,
	RCC_AHB_Prescaler_2 		= 8,
	RCC_AHB_Prescaler_4 		= 9,
	RCC_AHB_Prescaler_8 		= 10,
	RCC_AHB_Prescaler_16 		= 11,
	RCC_AHB_Prescaler_64 		= 12,
	RCC_AHB_Prescaler_128 	= 13,
	RCC_AHB_Prescaler_256 	= 14,
	RCC_AHB_Prescaler_512 	= 15,
	
}RCC_AHB_Prescaler_t;

typedef enum{

	RCC_APB_Prescaler_None 	= 0,
	RCC_APB_Prescaler_2 		= 4,
	RCC_APB_Prescaler_4 		= 5,
	RCC_APB_Prescaler_8 		= 6,
	RCC_APB_Prescaler_16 		= 7,
	
}RCC_APB_Prescaler_t;


void RCC_HSEConfig(RCC_HSE_Status_t HSE_Status);
void RCC_LSEConfig(RCC_LSE_Status_t LSE_Status);

//Config PLL
void RCC_PLLConfig(RCC_PLL_Source_t PLL_Source,uint32_t PLLM,uint32_t PLLN,uint32_t PLLP,uint32_t PLLQ,uint32_t PLLR);

////Enable/Disable internal Clocks y PLL
void RCC_HSI_Enable(uint8_t status);
void RCC_LSI_Enable(uint8_t status);
void RCC_PLL_Enable(uint8_t status);

////Configuracion salidas MCO1 y MCO2
void RCC_MCO1Config(RCC_MCO1_Source_t MCO1_Source, RCC_MCO1_Prescaler_t MCO1_Prescaler);
void RCC_MCO2Config(RCC_MCO2_Source_t MCO1_Source, RCC_MCO2_Prescaler_t MCO2_Prescaler);

////Routine to wait determined sysclk
void RCC_WaitForClkRdy(RCC_Clock_t clk);

void RCC_SysclkConfig(RCC_SysClk_Source_t AHB_Prescaler);
RCC_SysClk_Source_t RCC_getSysclkSorce(void);

void RCC_AHB1CkConfig(RCC_AHB_Prescaler_t AHB_Prescaler);
void RCC_APBlCkConfig(RCC_APB_Prescaler_t AHB_Prescaler);
void RCC_APB2CkConfig(RCC_APB_Prescaler_t AHB_Prescaler);

uint32_t RCC_getSysClk(void);
uint32_t RCC_GetAHBClk(void);
uint32_t RCC_GetAPB1Clk(void);
uint32_t RCC_GetAPB2Clk(void);

uint32_t RCC_GetAPB1_TimerClk(void);
uint32_t RCC_GetAPB2_TimerClk(void);

void setLatencyFlash(uint8_t latency);
#endif