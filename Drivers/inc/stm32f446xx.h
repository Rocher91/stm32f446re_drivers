/*
 * stmf446xx.h
 *
 *  Created on: Jul 27, 2023
 *  Author: Xavier.Rocher
 */


#ifndef INC_STM32F446XX_H_
#define INC_STM32F446XX_H_

#include <stdint.h>
#include <stddef.h>

#define __vo 		volatile
#define __weak 	__attribute__((weak))

#define ENABLE 	1
#define DISABLE 0

#define SET 	ENABLE
#define RESET	DISABLE

#define FLAG_SET 		ENABLE
#define FLAG_RESET 	DISABLE

#define HSE_FREQ ( (uint32_t) 8000000 )
#define HSI_FREQ ( (uint32_t) 16000000 )

__weak void assert_failed(uint8_t* file, uint32_t line);

#define ASSERT_TRUE(expr)  	( (expr)? (void)0 : assert_failed((uint8_t*)__FILE__,__LINE__) )
#define ASSERT_FALSE(expr)  ( (!expr)? (void)0 : assert_failed((uint8_t*)__FILE__,__LINE__) )

#define GPIO_BASEADDR_TO_CODE( x ) 	(	( x == GPIOA )? 0 :\
										( x == GPIOB )? 1 :\
										( x == GPIOC )? 2 :\
										( x == GPIOD )? 3 :\
										( x == GPIOE )? 4 :\
										( x == GPIOF )? 5 :\
										( x == GPIOG )? 6 :\
										( x == GPIOH )? 7 :0 )

#define ADC_CHANNEL_VALUE( x ) 			(	 (x == 0 )? ADC_CH0 :\
																		( x == 1 )? ADC_CH1 :\
																		( x == 2 )? ADC_CH2 :\
																		( x == 3 )? ADC_CH3 :\
																		( x == 4 )? ADC_CH4 :\
																		( x == 5 )? ADC_CH5 :\
																		( x == 6 )? ADC_CH6 :\
																		( x == 7 )? ADC_CH7 :\
																		( x == 8 )? ADC_CH8 :\
																		( x == 9 )? ADC_CH9 :\
																		( x == 10 )? ADC_CH10 :\
																		( x == 11 )? ADC_CH11 :\
																		( x == 12 )? ADC_CH12 :\
																		( x == 13 )? ADC_CH13 :\
																		( x == 14 )? ADC_CH14 :\
																		( x == 15 )? ADC_CH15 :0 )


/* !< MEMORY_peripheral_Bases >*/
#define FLASH_BASEADDR			0x08000000U
#define SRAM1_BASEADDR			0x20000000U
#define SRAM2_BASEADDR			0x2001C000U

#define ROM_BASEADDR			0x1FFF0000U
#define OTP_BASEADDR			0x1FFF7800U
#define OPTION_BYTES_BASEADDR	0x1FFFC000U
#define SRAM1					SRAM1_BASEADDR
#define SRAM2					SRAM2_BASEADDR

#define PERIPHERAL_BASE			0x40000000U

/* !< Processor Specific details >*/

#define NVIC_ISER0					( (__vo uint32_t* )0xE000E100U )
#define NVIC_ISER1					( (__vo uint32_t* )0xE000E104U )
#define NVIC_ISER2					( (__vo uint32_t* )0xE000E108U )
#define NVIC_ISER3					( (__vo uint32_t* )0xE000E10CU )
#define NVIC_ISER4					( (__vo uint32_t* )0xE000E110U )
#define NVIC_ISER5					( (__vo uint32_t* )0xE000E114U )
#define NVIC_ISER6					( (__vo uint32_t* )0xE000E118U )
#define NVIC_ISER7					( (__vo uint32_t* )0xE000E11CU )

#define NVIC_ICER0					( (__vo uint32_t* )0xE000E180U )
#define NVIC_ICER1					( (__vo uint32_t* )0xE000E184U )
#define NVIC_ICER2					( (__vo uint32_t* )0xE000E188U )
#define NVIC_ICER3					( (__vo uint32_t* )0xE000E18CU )
#define NVIC_ICER4					( (__vo uint32_t* )0xE000E190U )
#define NVIC_ICER5					( (__vo uint32_t* )0xE000E194U )
#define NVIC_ICER6					( (__vo uint32_t* )0xE000E198U )
#define NVIC_ICER7					( (__vo uint32_t* )0xE000E19CU )

#define NVIC_ICPR0					( (__vo uint32_t* )0xE000E200U )
#define NVIC_ICPR1					( (__vo uint32_t* )0xE000E204U )
#define NVIC_ICPR2					( (__vo uint32_t* )0xE000E208U )
#define NVIC_ICPR3					( (__vo uint32_t* )0xE000E20CU )
#define NVIC_ICPR4					( (__vo uint32_t* )0xE000E210U )
#define NVIC_ICPR5					( (__vo uint32_t* )0xE000E214U )
#define NVIC_ICPR6					( (__vo uint32_t* )0xE000E218U )
#define NVIC_ICPR7					( (__vo uint32_t* )0xE000E21CU )

#define NVIC_IABR0					( (__vo uint32_t* )0xE000E300U )
#define NVIC_IABR1					( (__vo uint32_t* )0xE000E304U )
#define NVIC_IABR2					( (__vo uint32_t* )0xE000E308U )
#define NVIC_IABR3					( (__vo uint32_t* )0xE000E30CU )
#define NVIC_IABR4					( (__vo uint32_t* )0xE000E310U )
#define NVIC_IABR5					( (__vo uint32_t* )0xE000E314U )
#define NVIC_IABR6					( (__vo uint32_t* )0xE000E318U )
#define NVIC_IABR7					( (__vo uint32_t* )0xE000E31CU )

#define NVIC_IPR_BASE				( (__vo uint32_t* )0xE000E400U )
#define NO_PR_BITS_IMPLEMENTED		4

#define STIR								( (__vo uint32_t* )0xE000EF00U )

#define SYSTICK_BASEADDR		0xE000E010UL


typedef struct{
	__vo uint32_t CSR;
	__vo uint32_t RVR;
	__vo uint32_t CVR;
	__vo uint32_t CALIB;
}Systick_RegDef_t;

#define SYSTICK	( ( Systick_RegDef_t*) SYSTICK_BASEADDR )


#define SYSTICK_CSR_ENABLE		0
#define SYSTICK_CSR_TICKINT		1
#define SYSTICK_CSR_CLKSOURCE	2
#define SYSTICK_CSR_COUNTFLAG	16

#define SYSTICK_CALIB_TENMS		0
#define SYSTICK_CALIB_SKEW		30
#define SYSTICK_CALIB_NOREF		31



/* !< PERIPHERAL_Bases >*/

#define APB1_PERIPH_BASE	PERIPHERAL_BASE
#define APB2_PERIPH_BASE	0x40010000U
#define AHB1_PERIPH_BASE	0x40020000U
#define AHB2_PERIPH_BASE	0x50000000U
#define AHB3_PERIPH_BASE	0x60000000U

/* !< DBG_peripheral_Bases >*/

#define DBG_BASEADDR				( 0xE0042000U )


/* !< TIM_peripheral_Bases >*/

#define TIM1_BASEADDR				( APB2_PERIPH_BASE + 0x0000 )
#define TIM2_BASEADDR				( APB1_PERIPH_BASE + 0x0000 )
#define TIM3_BASEADDR				( APB1_PERIPH_BASE + 0x0400 )
#define TIM4_BASEADDR				( APB1_PERIPH_BASE + 0x0800 )
#define TIM5_BASEADDR				( APB1_PERIPH_BASE + 0x0C00 )
#define TIM6_BASEADDR				( APB1_PERIPH_BASE + 0x1000 )
#define TIM7_BASEADDR				( APB1_PERIPH_BASE + 0x1400 )
#define TIM8_BASEADDR				( APB2_PERIPH_BASE + 0x0400 )
#define TIM9_BASEADDR				( APB2_PERIPH_BASE + 0x4000 )
#define TIM10_BASEADDR				( APB2_PERIPH_BASE + 0x4400 )
#define TIM11_BASEADDR				( APB2_PERIPH_BASE + 0x4800 )
#define TIM12_BASEADDR				( APB1_PERIPH_BASE + 0x1800 )
#define TIM13_BASEADDR				( APB1_PERIPH_BASE + 0x1C00 )
#define TIM14_BASEADDR				( APB1_PERIPH_BASE + 0x2000 )

/* !< RTC_peripheral_Bases >*/

#define RTC_BKP_BASEADDR			( APB1_PERIPH_BASE + 0x2800 )

/* !< WATCHDOG_peripheral_Bases >*/

#define WWDG_BASEADDR				( APB1_PERIPH_BASE + 0x2C00 )
#define IWDG_BASEADDR				( APB1_PERIPH_BASE + 0x3000 )

/* !< SPI_peripheral_Bases >*/

#define SPI2_I2S2_BASEADDR			( APB1_PERIPH_BASE + 0x3800 )
#define SPI3_I2S3_BASEADDR			( APB1_PERIPH_BASE + 0x3C00 )

/* !< SPDIF_peripheral_Bases >*/

#define SPDIF_RX					( APB1_PERIPH_BASE + 0x4000 )

/* !< UART_peripheral_Bases >*/

#define USART1_BASEADDR				( APB2_PERIPH_BASE + 0x1000 )
#define USART2_BASEADDR				( APB1_PERIPH_BASE + 0x4400 )
#define USART3_BASEADDR				( APB1_PERIPH_BASE + 0x4800 )
#define UART4_BASEADDR				( APB1_PERIPH_BASE + 0x4C00 )
#define UART5_BASEADDR				( APB1_PERIPH_BASE + 0x5000 )
#define USART6_BASEADDR				( APB2_PERIPH_BASE + 0x1400 )


/* !< I2C_peripheral_Bases >*/
#define I2C1_BASEADDR					( APB1_PERIPH_BASE + 0x5400 )
#define I2C2_BASEADDR					( APB1_PERIPH_BASE + 0x5800 )
#define I2C3_BASEADDR					( APB1_PERIPH_BASE + 0x5C00 )

/* !< CAN_peripheral_Bases >*/
#define CAN1_BASEADDR					( APB1_PERIPH_BASE + 0x6400 )
#define CAN2_BASEADDR					( APB1_PERIPH_BASE + 0x6800 )

/* !< HDMI_peripheral_Bases >*/
#define HDMI_CEC_BASEADDR			( APB1_PERIPH_BASE + 0x6C00 )

/* !< POWER_peripheral_Bases >*/
#define PWR_BASEADDR					( APB1_PERIPH_BASE + 0x7000 )

/* !< DAC_peripheral_Bases >*/
#define DAC_BASEADDR					( APB1_PERIPH_BASE + 0x7400 )

/* !< ADC_peripheral_Bases >*/
#define ADC1_BASEADDR					( APB2_PERIPH_BASE + 0x2000 )
#define ADC2_BASEADDR					( ADC1_BASEADDR + 0x0100 )
#define ADC3_BASEADDR					( ADC1_BASEADDR + 0x0200 )
#define ADC_COMMON_BASEADDR		( ADC1_BASEADDR + 0x0300 )


/* !< SDMMC_peripheral_Bases >*/
#define SDMMC_BASEADDR				( APB2_PERIPH_BASE + 0x2C00 )

/* !< SPI_peripheral_Bases >*/
#define SPI1_BASEADDR					( APB2_PERIPH_BASE + 0x3000 )
#define SPI4_BASEADDR					( APB2_PERIPH_BASE + 0x3400 )

/* !< SYSTEM_peripheral_Bases >*/
#define SYSCFG_BASEADDR				( APB2_PERIPH_BASE + 0x3800 )

/* !< EXTI_peripheral_Bases >*/
#define EXTI_BASEADDR					( APB2_PERIPH_BASE + 0x3C00 )

/* !< SERIAL_AUDIO_peripheral_Bases >*/
#define SAI1_BASEADDR					( APB2_PERIPH_BASE + 0x5800 )
#define SAI2_BASEADDR					( APB2_PERIPH_BASE + 0x5C00 )

/* !< GPIO_peripheral_Bases >*/
#define GPIOA_BASEADDR				( AHB1_PERIPH_BASE + 0x0000 )
#define GPIOB_BASEADDR				( AHB1_PERIPH_BASE + 0x0400 )
#define GPIOC_BASEADDR				( AHB1_PERIPH_BASE + 0x0800 )
#define GPIOD_BASEADDR				( AHB1_PERIPH_BASE + 0x0C00 )
#define GPIOE_BASEADDR				( AHB1_PERIPH_BASE + 0x1000 )
#define GPIOF_BASEADDR				( AHB1_PERIPH_BASE + 0x1400 )
#define GPIOG_BASEADDR				( AHB1_PERIPH_BASE + 0x1800 )
#define GPIOH_BASEADDR				( AHB1_PERIPH_BASE + 0x1C00 )

/* !< CRC_peripheral_Bases >*/
#define CRC_BASEADDR							( AHB1_PERIPH_BASE + 0x3000 )

/* !< RCC_peripheral_Bases >*/
#define RCC_BASEADDR							( AHB1_PERIPH_BASE + 0x3800 )

/* !< FLASH_peripheral_Bases >*/
#define FLASH_INTERFACE_BASEADDR	( AHB1_PERIPH_BASE + 0x3C00 )

/* !< ADDR_peripheral_Bases >*/
#define BKPSRAM_BASEADDR					( AHB1_PERIPH_BASE + 0x4000 )

/* !< DMA_peripheral_Bases >*/
#define DMA1_BASEADDR							( AHB1_PERIPH_BASE + 0x6000 )
#define DMA2_BASEADDR							( AHB1_PERIPH_BASE + 0x6400 )

/* !< USB_peripheral_Bases >*/
#define USB_OTG_HS_BASEADDR				( AHB1_PERIPH_BASE + 0x0000 )
#define USB_OTG_FS_BASEADDR				( AHB2_PERIPH_BASE + 0x0000 )

/* !< DIGITAL_CAMERA_peripheral_Bases >*/
#define DCMI_BASEADDR							( AHB2_PERIPH_BASE + 0x00050000 )

/* !< QUADSPI_peripheral_Bases >*/
#define QUADSPI_BASEADDR					( AHB3_PERIPH_BASE + 0x1000 )

/* !< FLEXIBLE_MEMORY_peripheral_Bases >*/
#define FMC_BASEADDR							( AHB3_PERIPH_BASE + 0x0000 )



/**************************************************Peripheral Register Definition Structures***************************************************/

typedef struct{

	__vo uint32_t ACR;					/**/
	__vo uint32_t KEYR;					/**/
	__vo uint32_t OPTKEYR;			/**/
	__vo uint32_t SR;						/**/
	__vo uint32_t CR;						/**/
	__vo uint32_t OPTCR;				/**/

}Flash_RegDef_t;

#define FLASH	( ( Flash_RegDef_t*) FLASH_INTERFACE_BASEADDR )


/*>>>GPIO Structure<<<*/

typedef struct{

	__vo uint32_t MODER;			/**/
	__vo uint32_t OTYPER;			/**/
	__vo uint32_t OSPEEDER;		/**/
	__vo uint32_t PUPDR;			/**/
	__vo uint32_t IDR;				/**/
	__vo uint32_t ODR;				/**/
	__vo uint32_t BSRR;				/**/
	__vo uint32_t LCKR;				/**/
	__vo uint32_t AFR[2];			/**/

}GPIO_RegDef_t;

#define GPIOA	( ( GPIO_RegDef_t*) GPIOA_BASEADDR )
#define GPIOB	( ( GPIO_RegDef_t*) GPIOB_BASEADDR )
#define GPIOC	( ( GPIO_RegDef_t*) GPIOC_BASEADDR )
#define GPIOD	( ( GPIO_RegDef_t*) GPIOD_BASEADDR )
#define GPIOE	( ( GPIO_RegDef_t*) GPIOE_BASEADDR )
#define GPIOF	( ( GPIO_RegDef_t*) GPIOF_BASEADDR )
#define GPIOG	( ( GPIO_RegDef_t*) GPIOG_BASEADDR )
#define GPIOH	( ( GPIO_RegDef_t*) GPIOH_BASEADDR )

/*>>>RCC Structure<<<*/

typedef struct{

	__vo uint32_t CR;						/**/
	__vo uint32_t PLLCFGR;			/**/
	__vo uint32_t CFGR;					/**/
	__vo uint32_t CIR;					/**/
	__vo uint32_t AHB1RSTR;			/**/
	__vo uint32_t AHB2RSTR;			/**/
	__vo uint32_t AHB3RSTR;			/**/
	__vo uint32_t RESERVED0;		/**/
	__vo uint32_t APB1RSTR;			/**/
	__vo uint32_t APB2RSTR;			/**/
	__vo uint32_t RESERVED1[2];	/**/
	__vo uint32_t AHB1ENR;			/**/
	__vo uint32_t AHB2ENR;			/**/
	__vo uint32_t AHB3ENR;			/**/
	__vo uint32_t RESERVE2;			/**/
	__vo uint32_t APB1ENR;			/**/
	__vo uint32_t APB2ENR;			/**/
	__vo uint32_t RESERVED3[2];	/**/
	__vo uint32_t AHB1LPENR;		/**/
	__vo uint32_t AHB2LPENR;		/**/
	__vo uint32_t AHB3LPENR;		/**/
	__vo uint32_t RESERVED4;		/**/
	__vo uint32_t APB1LPENR;		/**/
	__vo uint32_t APB2LPENR;		/**/
	__vo uint32_t RESERVED5[2];	/**/
	__vo uint32_t BDCR;					/**/
	__vo uint32_t CSR;					/**/
	__vo uint32_t RESERVED6[2];	/**/
	__vo uint32_t SSCGR;				/**/
	__vo uint32_t PLLI2SCFG;		/**/
	__vo uint32_t PLLSAICFGR;		/**/
	__vo uint32_t DCKCFGR;			/**/
	__vo uint32_t CKGATENR;			/**/
	__vo uint32_t DCKCFGR2;			/**/


}RCC_RegDef_t;

#define RCC	( ( RCC_RegDef_t*) RCC_BASEADDR )

/*>>> RCC CR Bitfields <<<*/

#define RCC_CR_HSION			0
#define RCC_CR_HSIRDY			1
#define RCC_CR_HSITRIM		3
#define RCC_CR_HSICAL			8
#define RCC_CR_HSEON			16
#define RCC_CR_HSERDY			17
#define RCC_CR_HSEBYP			18
#define RCC_CR_CSSON			19
#define RCC_CR_PLLON			24
#define RCC_CR_PLLRDY			25
#define RCC_CR_PLLI2SON		26
#define RCC_CR_PLLI2SRDY	27
#define RCC_CR_PLLSAION		28
#define RCC_CR_PLLSAIRDY	29


/*>>> RCC PLLCFGR Bitfields <<<*/

#define RCC_PLLCFGR_PLLM		0
#define RCC_PLLCFGR_PLLN		6
#define RCC_PLLCFGR_PLLP		16
#define RCC_PLLCFGR_PLLSRC		22
#define RCC_PLLCFGR_PLLQ		24
#define RCC_PLLCFGR_PLLR		28

/*>>> RCC CFGR Bitfields <<<*/

#define RCC_CFGR_SW				0
#define RCC_CFGR_SWS			2
#define RCC_CFGR_HPRE			4
#define RCC_CFGR_PPRE1			10
#define RCC_CFGR_PPRE2			13
#define RCC_CFGR_RTCPRE			16
#define RCC_CFGR_MCO1			21
#define RCC_CFGR_MCO1PRE		24
#define RCC_CFGR_MCO2PRE		27
#define RCC_CFGR_MC02			30

/*>>> RCC CIR Bitfields <<<*/

#define RCC_CIR_LSI_RDYF			0
#define RCC_CIR_LSE_RDYF			1
#define RCC_CIR_HSI_RDYF			2
#define RCC_CIR_HSE_RDYF			3
#define RCC_CIR_PLL_RDYF			4
#define RCC_CIR_PLLI2S_RDYF		5
#define RCC_CIR_PLLSAI_RDYF		6
#define RCC_CIR_CSSF					7
#define RCC_CIR_LSI_RDYIE			8
#define RCC_CIR_LSE_RDYIE			9
#define RCC_CIR_HSI_RDYIE			10
#define RCC_CIR_HSE_RDYIE			11
#define RCC_CIR_PLL_RDYIE			12
#define RCC_CIR_PLLI2S_RDYIE	13
#define RCC_CIR_PLLSAI_RDYIE	14
#define RCC_CIR_LSI_RDYIC			16
#define RCC_CIR_LSE_RDYIC			17
#define RCC_CIR_HSI_RDYIC			18
#define RCC_CIR_HSE_RDYIC			19
#define RCC_CIR_PLL_RDYIC			20
#define RCC_CIR_PLLI2S_RDYIC	21
#define RCC_CIR_PLLSAI_RDYIC	22
#define RCC_CIR_CSSC_RDYIC		23


/*>>> RCC AHB1RSTR Bitfields <<<*/

#define RCC_AHB1RSTR_GPIOA	0
#define RCC_AHB1RSTR_GPIOB	1
#define RCC_AHB1RSTR_GPIOC	2
#define RCC_AHB1RSTR_GPIOD	3
#define RCC_AHB1RSTR_GPIOE	4
#define RCC_AHB1RSTR_GPIOF	5
#define RCC_AHB1RSTR_GPIOG	6
#define RCC_AHB1RSTR_GPIOH	7
#define RCC_AHB1RSTR_CRC		12
#define RCC_AHB1RSTR_DMA1		21
#define RCC_AHB1RSTR_DMA2		22
#define RCC_AHB1RSTR_OTGHS	29

/*>>> RCC AHB2RSTR Bitfields <<<*/

#define RCC_AHB2RSTR_DCMI		0
#define RCC_AHB2RSTR_OTGFS	7

/*>>> RCC AHB3RSTR Bitfields <<<*/

#define RCC_AHB3RSTR_FMC		0
#define RCC_AHB3RSTR_QSPI		1

/*>>> RCC APB1RSTR Bitfields <<<*/

#define RCC_APB1RSTR_TIM2			0
#define RCC_APB1RSTR_TIM3			1
#define RCC_APB1RSTR_TIM4			2
#define RCC_APB1RSTR_TIM5			3
#define RCC_APB1RSTR_TIM6			4
#define RCC_APB1RSTR_TIM7			5
#define RCC_APB1RSTR_TIM12		6
#define RCC_APB1RSTR_TIM13		7
#define RCC_APB1RSTR_TIM14		8
#define RCC_APB1RSTR_WWDG			11
#define RCC_APB1RSTR_SPI2			14
#define RCC_APB1RSTR_SPI3			15
#define RCC_APB1RSTR_SPDIFRX	16
#define RCC_APB1RSTR_UART2		17
#define RCC_APB1RSTR_UART3		18
#define RCC_APB1RSTR_UART4		19
#define RCC_APB1RSTR_UART5		20
#define RCC_APB1RSTR_I2C1			21
#define RCC_APB1RSTR_I2C2			22
#define RCC_APB1RSTR_I2C3			23
#define RCC_APB1RSTR_FMPI2C1	24
#define RCC_APB1RSTR_CAN1			25
#define RCC_APB1RSTR_CAN2			26
#define RCC_APB1RSTR_CEC			27
#define RCC_APB1RSTR_PWR			28
#define RCC_APB1RSTR_DAC			29

/*>>> RCC APB2RSTR Bitfields <<<*/

#define RCC_APB2RSTR_TIM1			0
#define RCC_APB2RSTR_TIM8			1
#define RCC_APB2RSTR_USART1		4
#define RCC_APB2RSTR_USART6		5
#define RCC_APB2RSTR_ADC			8
#define RCC_APB2RSTR_SDIO			11
#define RCC_APB2RSTR_SPI1			12
#define RCC_APB2RSTR_SPI4			13
#define RCC_APB2RSTR_SYSCFG		14


/*>>> RCC AHB1ENR Bitfields <<<*/

#define RCC_AHB1ENR_GPIOA				0
#define RCC_AHB1ENR_GPIOB				1
#define RCC_AHB1ENR_GPIOC				2
#define RCC_AHB1ENR_GPIOD				3
#define RCC_AHB1ENR_GPIOE				4
#define RCC_AHB1ENR_GPIOF				5
#define RCC_AHB1ENR_GPIOG				6
#define RCC_AHB1ENR_GPIOH				7
#define RCC_AHB1ENR_CRC					12
#define RCC_AHB1ENR_BKP_SRAM			18
#define RCC_AHB1ENR_DMA1				21
#define RCC_AHB1ENR_DMA2				22
#define RCC_AHB1ENR_OTGHS				29
#define RCC_AHB1ENR_OTGHS_ULPI			30

/*>>> RCC AHB2ENR Bitfields <<<*/

#define RCC_AHB2ENR_DCMI				0
#define RCC_AHB2ENR_OTGFS				7

/*>>> RCC AHB3ENR Bitfields <<<*/

#define RCC_AHB3ENR_FMC				0
#define RCC_AHB3ENR_QSPI			1

/*>>> RCC APB1ENR Bitfields <<<*/

#define RCC_APB1ENR_TIM2		0
#define RCC_APB1ENR_TIM3		1
#define RCC_APB1ENR_TIM4		2
#define RCC_APB1ENR_TIM5		3
#define RCC_APB1ENR_TIM6		4
#define RCC_APB1ENR_TIM7		5
#define RCC_APB1ENR_TIM12		6
#define RCC_APB1ENR_TIM13		7
#define RCC_APB1ENR_TIM14		8
#define RCC_APB1ENR_WWDG		11
#define RCC_APB1ENR_SPI2		14
#define RCC_APB1ENR_SPI3		15
#define RCC_APB1ENR_SPDIFRX	16
#define RCC_APB1ENR_USART2	17
#define RCC_APB1ENR_USART3	18
#define RCC_APB1ENR_UART4		19
#define RCC_APB1ENR_UART5		20
#define RCC_APB1ENR_I2C1		21
#define RCC_APB1ENR_I2C2		22
#define RCC_APB1ENR_I2C3		23
#define RCC_APB1ENR_FMPI2C1	24
#define RCC_APB1ENR_CAN1		25
#define RCC_APB1ENR_CAN2		26
#define RCC_APB1ENR_CEC			27
#define RCC_APB1ENR_PWR			28
#define RCC_APB1ENR_DAC			29

/*>>> RCC APB2ENR Bitfields <<<*/

#define RCC_APB2ENR_TIM1			0
#define RCC_APB2ENR_TIM8			1
#define RCC_APB2ENR_USART1		4
#define RCC_APB2ENR_USART6		5
#define RCC_APB2ENR_ADC1			8
#define RCC_APB2ENR_ADC2			9
#define RCC_APB2ENR_ADC3			10
#define RCC_APB2ENR_SDIO			11
#define RCC_APB2ENR_SPI1			12
#define RCC_APB2ENR_SPI4			13
#define RCC_APB2ENR_SYSCFG		14
#define RCC_APB2ENR_TIM9			16
#define RCC_APB2ENR_TIM10			17
#define RCC_APB2ENR_TIM11			18
#define RCC_APB2ENR_SAI1			22
#define RCC_APB2ENR_SAI2			23

/*>>> RCC AHB1LPENR Bitfields <<<*/

#define RCC_AHB1LPENR_GPIOA			0
#define RCC_AHB1LPENR_GPIOB			1
#define RCC_AHB1LPENR_GPIOC			2
#define RCC_AHB1LPENR_GPIOD			3
#define RCC_AHB1LPENR_GPIOE			4
#define RCC_AHB1LPENR_GPIOF			5
#define RCC_AHB1LPENR_GPIOG			6
#define RCC_AHB1LPENR_GPIOH			7
#define RCC_AHB1LPENR_CRC				8
#define RCC_AHB1LPENR_FLITF			15
#define RCC_AHB1LPENR_SRAM1			16
#define RCC_AHB1LPENR_SRAM2			17
#define RCC_AHB1LPENR_BKP_SRAM	18
#define RCC_AHB1LPENR_DMA1			21
#define RCC_AHB1LPENR_DMA2			22
#define RCC_AHB1LPENR_OTGHS			29
#define RCC_AHB1LPENR_OTGHS_ULPI	30

/*>>> RCC AHB2LPENR Bitfields <<<*/

#define RCC_AHB2LPENR_DCMI			0
#define RCC_AHB2LPENR_OTGFS			7

/*>>> RCC AHB3LPENR Bitfields <<<*/

#define RCC_AHB3LPENR_FMC			0
#define RCC_AHB3LPENR_QSPI		1

/*>>> RCC APB1LPENR Bitfields <<<*/

#define RCC_APB1LPENR_TIM2			0
#define RCC_APB1LPENR_TIM3			1
#define RCC_APB1LPENR_TIM4			2
#define RCC_APB1LPENR_TIM5			3
#define RCC_APB1LPENR_TIM6			4
#define RCC_APB1LPENR_TIM7			5
#define RCC_APB1LPENR_TIM12			6
#define RCC_APB1LPENR_TIM13			7
#define RCC_APB1LPENR_TIM14			8
#define RCC_APB1LPENR_WWDG			11
#define RCC_APB1LPENR_SPI2			14
#define RCC_APB1LPENR_SPI3			15
#define RCC_APB1LPENR_SPDIFRX		16
#define RCC_APB1LPENR_USART2		17
#define RCC_APB1LPENR_USART3		18
#define RCC_APB1LPENR_UART4			19
#define RCC_APB1LPENR_UART5			20
#define RCC_APB1LPENR_I2C1			21
#define RCC_APB1LPENR_I2C2			22
#define RCC_APB1LPENR_I2C3			23
#define RCC_APB1LPENR_FMPI2C1		24
#define RCC_APB1LPENR_CAN1			25
#define RCC_APB1LPENR_CAN2			26
#define RCC_APB1LPENR_CECLP			27
#define RCC_APB1LPENR_PWR				28
#define RCC_APB1LPENR_DAC				29

/*>>> RCC APB2LPENR Bitfields <<<*/

#define RCC_APB2LPENR_TIM1			0
#define RCC_APB2LPENR_TIM8			1
#define RCC_APB2LPENR_USART1		4
#define RCC_APB2LPENR_USART6		5
#define RCC_APB2LPENR_ADC1			8
#define RCC_APB2LPENR_ADC2			9
#define RCC_APB2LPENR_ADC3			10
#define RCC_APB2LPENR_SDIO			11
#define RCC_APB2LPENR_SPI1			12
#define RCC_APB2LPENR_SPI4			13
#define RCC_APB2LPENR_SYSCFG		14
#define RCC_APB2LPENR_TIM9			16
#define RCC_APB2LPENR_TIM10			17
#define RCC_APB2LPENR_TIM11			18
#define RCC_APB2LPENR_SAI1			22
#define RCC_APB2LPENR_SAI2			23

/*>>> RCC BDCR Bitfields <<<*/

#define RCC_BDCR_LSEON				0
#define RCC_BDCR_LSERDY				1
#define RCC_BDCR_LSEBYP				2
#define RCC_BDCR_LSEMOD				3
#define RCC_BDCR_RTCSEL				8
#define RCC_BDCR_RTCEN				15
#define RCC_BDCR_BDRST				16

/*>>> RCC CSR Bitfields <<<*/

#define RCC_CSR_LSION			0
#define RCC_CSR_LSIRDY		1
#define RCC_CSR_RMVF			24
#define RCC_CSR_BORRSTF		25
#define RCC_CSR_PINRSTF		26
#define RCC_CSR_PORRSTF		27
#define RCC_CSR_SFTRSTF		28
#define RCC_CSR_IWDGRSTF	29
#define RCC_CSR_WWDGRSTF	30
#define RCC_CSR_LPWRRSTF	31

/*>>> RCC SSCGR Bitfields <<<*/

#define RCC_SSCGR_MODPER		0
#define RCC_SSCGR_INCSTEP		16
#define RCC_SSCGR_SPREADSEL	30
#define RCC_SSCGR_SSCGEN		31

/*>>> RCC PLLI2SSCGR Bitfields <<<*/

#define RCC_PLLI2SCFGR_PLLI2SM		0
#define RCC_PLLI2SCFGR_PLLI2SN		6
#define RCC_PLLI2SCFGR_PLLI2SP		16
#define RCC_PLLI2SCFGR_PLLI2SQ		24
#define RCC_PLLI2SCFGR_PLLI2SR		28

/*>>> RCC PLLSAICFGR Bitfields <<<*/

#define RCC_PLLSAICFGR_PLLSAIM		0
#define RCC_PLLSAICFGR_PLLSAIN		6
#define RCC_PLLSAICFGR_PLLSAIP		16
#define RCC_PLLSAICFGR_PLLSAIQ		24

/*>>> RCC DCKCFGR Bitfields <<<*/

#define RCC_DCKCFGR_PLLIS2DIVQ		0
#define RCC_DCKCFGR_PLLSAIDIVQ		8
#define RCC_DCKCFGR_SAI1SRC				20
#define RCC_DCKCFGR_SAI2SRC				22
#define RCC_DCKCFGR_TIMPRE				24
#define RCC_DCKCFGR_I2S1SRC				25
#define RCC_DCKCFGR_I2S2SRC				27

/*>>> RCC CKGATENR Bitfields <<<*/

#define RCC_CKGATENR_AHB2APB1_CLK		0
#define RCC_CKGATENR_AHB2APB2_CLK		1
#define RCC_CKGATENR_CM4DBG_CLK			2
#define RCC_CKGATENR_SPARE_CLK			3
#define RCC_CKGATENR_SRAM_CLK				4
#define RCC_CKGATENR_FLITF_CLK			5
#define RCC_CKGATENR_RCC_CLK				6

/*>>> RCC DCKCFGR2 Bitfields <<<*/

#define RCC_DCKCFGR2_FMPI2C1SEL		22
#define RCC_DCKCFGR2_CEC					26
#define RCC_DCKCFGR2_CK48M				27
#define RCC_DCKCFGR2_SDIO					28
#define RCC_DCKCFGR2_SPDIFRX			29



// Clock Enable Macros for GPIOx peripherals

#define GPIOA_PCLCK_EN()	RCC->AHB1ENR |= (uint32_t)(0x01 << 0)
#define GPIOB_PCLCK_EN()	RCC->AHB1ENR |= (uint32_t)(0x01 << 1)
#define GPIOC_PCLCK_EN()	RCC->AHB1ENR |= (uint32_t)(0x01 << 2)
#define GPIOD_PCLCK_EN()	RCC->AHB1ENR |= (uint32_t)(0x01 << 3)
#define GPIOE_PCLCK_EN()	RCC->AHB1ENR |= (uint32_t)(0x01 << 4)
#define GPIOF_PCLCK_EN()	RCC->AHB1ENR |= (uint32_t)(0x01 << 5)
#define GPIOG_PCLCK_EN()	RCC->AHB1ENR |= (uint32_t)(0x01 << 6)
#define GPIOH_PCLCK_EN()	RCC->AHB1ENR |= (uint32_t)(0x01 << 7)

// Clock Enable Macros for CRC peripheral

#define CRC_PCLCK_EN()			RCC->AHB1ENR |= (uint32_t)(0x01 << 12)


// Clock Enable Macros for BKPSRAM peripheral

#define BKPSRAM_PCLCK_EN()		RCC->AHB1ENR |= (uint32_t)(0x01 << 18)

// Clock Enable Macros for DMA peripherals

#define DMA1_PCLCK_EN()			RCC->AHB1ENR |= (uint32_t)(0x01 << 21)
#define DMA2_PCLCK_EN()			RCC->AHB1ENR |= (uint32_t)(0x01 << 22)

// Clock Enable Macros for USB peripherals

#define OTGHS_ULPI_PCLCK_EN()	RCC->AHB1ENR |= (uint32_t)(0x01 << 30)
#define OTGHS_PCLCK_EN()		RCC->AHB1ENR |= (uint32_t)(0x01 << 29)


// Clock Enable Macros for DMI peripheral

#define DCMI_PCLCK_EN()			RCC->AHB2ENR |= (uint32_t)(0x01 << 0)

// Clock Enable Macros for OTGFS peripheral

#define OTGFS_PCLCK_EN()		RCC->AHB2ENR |= (uint32_t)(0x01 << 7)

// Clock Enable Macros for FMC peripheral

#define FMC_PCLCK_EN()			RCC->AHB3ENR |= (uint32_t)(0x01 << 0)

// Clock Enable Macros for FMC peripheral

#define QSPI_PCLCK_EN()			RCC->AHB3ENR |= (uint32_t)(0x01 << 1)


// Clock Enable Macros for Timers peripherals

#define TIM2_PCLCK_EN()			RCC->APB1ENR |= (uint32_t)(0x01 << 0)
#define TIM3_PCLCK_EN()			RCC->APB1ENR |= (uint32_t)(0x01 << 1)
#define TIM4_PCLCK_EN()			RCC->APB1ENR |= (uint32_t)(0x01 << 2)
#define TIM5_PCLCK_EN()			RCC->APB1ENR |= (uint32_t)(0x01 << 3)
#define TIM6_PCLCK_EN()			RCC->APB1ENR |= (uint32_t)(0x01 << 4)
#define TIM7_PCLCK_EN()			RCC->APB1ENR |= (uint32_t)(0x01 << 5)
#define TIM12_PCLCK_EN()		RCC->APB1ENR |= (uint32_t)(0x01 << 6)
#define TIM13_PCLCK_EN()		RCC->APB1ENR |= (uint32_t)(0x01 << 7)
#define TIM14_PCLCK_EN()		RCC->APB1ENR |= (uint32_t)(0x01 << 8)


// Clock Enable Macros for WWDG peripherals

#define WWDG_PCLCK_EN()			RCC->APB1ENR |= (uint32_t)(0x01 << 11)

#define WWDG_CR_T			0
#define WWDG_CR_WDGA	7

#define WWDG_CFR_W 			0
#define WWDG_CFR_WDGTB 	7
#define WWDG_CFR_EWI 		9

#define WWDG_SR_EWIF 		0


// Clock Enable Macros for SPI peripherals

#define SPI2_PCLCK_EN()			RCC->APB1ENR |= (uint32_t)(0x01 << 14)
#define SPI3_PCLCK_EN()			RCC->APB1ENR |= (uint32_t)(0x01 << 15)

// Clock Enable Macros for SPDIFRX peripherals

#define SPDIFRX_PCLCK_EN()			RCC->APB1ENR |= (uint32_t)(0x01 << 16)

// Clock Enable Macros for UART peripherals

#define USART2_PCLCK_EN()			RCC->APB1ENR |= (uint32_t)(0x01 << 17)
#define USART3_PCLCK_EN()			RCC->APB1ENR |= (uint32_t)(0x01 << 18)
#define UART4_PCLCK_EN()			RCC->APB1ENR |= (uint32_t)(0x01 << 19)
#define UART5_PCLCK_EN()			RCC->APB1ENR |= (uint32_t)(0x01 << 20)

// Clock Enable Macros for I2C peripherals

#define I2C1_PCLCK_EN()			RCC->APB1ENR |= (uint32_t)(0x01 << 21)
#define I2C2_PCLCK_EN()			RCC->APB1ENR |= (uint32_t)(0x01 << 22)
#define I2C3_PCLCK_EN()			RCC->APB1ENR |= (uint32_t)(0x01 << 23)


// Clock Enable Macros for FMPI2C1 peripherals

#define FMPI2C1_PCLCK_EN()			RCC->APB1ENR |= (0x01 << 24)

// Clock Enable Macros for CAN peripherals

#define CAN1_PCLCK_EN()			RCC->APB1ENR |= (0x01 << 25)
#define CAN2_PCLCK_EN()			RCC->APB1ENR |= (0x01 << 26)


// Clock Enable Macros for CEC peripherals

#define CEC_PCLCK_EN()			RCC->APB1ENR |= (0x01 << 27)

// Clock Enable Macros for PWR peripherals

#define PWR_PCLCK_EN()			RCC->APB1ENR |= (0x01 << 28)

#define PWR_CR_LPDS			0
#define PWR_CR_PDDS			1
#define PWR_CR_CWUF			2
#define PWR_CR_CSBF			3
#define PWR_CR_PVDE			4
#define PWR_CR_PLS			5
#define PWR_CR_DBP			8
#define PWR_CR_FPDS			9
#define PWR_CR_LPUDS		10
#define PWR_CR_MRUDS		11
#define PWR_CR_ADCDC1		13
#define PWR_CR_VOS			14
#define PWR_CR_ODEN			16
#define PWR_CR_ODSWEN		17
#define PWR_CR_UDEN			18
#define PWR_CR_FMSSR		20
#define PWR_CR_FISSR		21


// Clock Enable Macros for DAC peripherals

#define DAC_PCLCK_EN()			RCC->APB1ENR |= (uint32_t) (0x01 << 29)


// Clock Enable Macros for TIMERS peripherals

#define TIM1_PCLCK_EN()			RCC->APB2ENR |= (uint32_t) (0x01 << 0)
#define TIM8_PCLCK_EN()			RCC->APB2ENR |= (uint32_t) (0x01 << 1)
#define TIM9_PCLCK_EN()			RCC->APB2ENR |= (uint32_t) (0x01 << 16)
#define TIM10_PCLCK_EN()		RCC->APB2ENR |= (uint32_t) (0x01 << 17)
#define TIM11_PCLCK_EN()		RCC->APB2ENR |= (uint32_t) (0x01 << 18)


// Clock Enable Macros for TIMERS peripherals

#define USART1_PCLCK_EN()		RCC->APB2ENR |= (uint32_t) (0x01 << 5)
#define USART6_PCLCK_EN()		RCC->APB2ENR |= (uint32_t) (0x01 << 6)

// Clock Enable Macros for ADC peripherals

#define ADC1_PCLCK_EN()			RCC->APB2ENR |= (uint32_t) (0x01 << 8)
#define ADC2_PCLCK_EN()			RCC->APB2ENR |= (uint32_t) (0x01 << 9)
#define ADC3_PCLCK_EN()			RCC->APB2ENR |= (uint32_t) (0x01 << 10)

// Clock Enable Macros for SDIO peripherals

#define SDIO_PCLCK_EN()			RCC->APB2ENR |= (uint32_t) (0x01 << 11)

// Clock Enable Macros for SPI peripherals

#define SPI1_PCLCK_EN()			RCC->APB2ENR |= (uint32_t) (0x01 << 12)
#define SPI4_PCLCK_EN()			RCC->APB2ENR |= (uint32_t) (0x01 << 13)

// Clock Enable Macros for SYSCFG peripherals

#define SYSCFG_PCLCK_EN()		RCC->APB2ENR |= (uint32_t) (0x01 << 14)


// Clock Enable Macros for SAI peripherals

#define SAI1_PCLCK_EN()			RCC->APB2ENR |= (uint32_t) (0x01 << 22)
#define SAI2_PCLCK_EN()			RCC->APB2ENR |= (uint32_t) (0x01 << 23)


// Clock Disable Macros for GPIOx peripherals

#define GPIOA_PCLCK_DIS()		RCC->AHB1ENR &= (uint32_t) ~(0x01 << 0)
#define GPIOB_PCLCK_DIS()		RCC->AHB1ENR &= (uint32_t) ~(0x01 << 1)
#define GPIOC_PCLCK_DIS()		RCC->AHB1ENR &= (uint32_t) ~(0x01 << 2)
#define GPIOD_PCLCK_DIS()		RCC->AHB1ENR &= (uint32_t) ~(0x01 << 3)
#define GPIOE_PCLCK_DIS()		RCC->AHB1ENR &= (uint32_t) ~(0x01 << 4)
#define GPIOF_PCLCK_DIS()		RCC->AHB1ENR &= (uint32_t) ~(0x01 << 5)
#define GPIOG_PCLCK_DIS()		RCC->AHB1ENR &= (uint32_t) ~(0x01 << 6)
#define GPIOH_PCLCK_DIS()		RCC->AHB1ENR &= (uint32_t) ~(0x01 << 7)

// Clock Disable Macros for CRC peripheral

#define CRC_PCLCK_DIS()			RCC->AHB1ENR &= ~(0x01 << 12)


// Clock Disable Macros for BKPSRAM peripheral

#define BKPSRAM_PCLCK_DIS()		RCC->AHB1ENR &= ~(0x01 << 18)

// Clock Disable Macros for DMA peripherals

#define DMA1_PCLCK_DIS()		RCC->AHB1ENR &= ~(0x01 << 21)
#define DMA2_PCLCK_DIS()		RCC->AHB1ENR &= ~(0x01 << 22)

// Clock Disable Macros for USB peripherals

#define OTGHS_ULPI_PCLCK_DIS()	RCC->AHB1ENR &= ~(0x01 << 30)
#define OTGHS_PCLCK_DIS()		RCC->AHB1ENR &= ~(0x01 << 29)

// Clock Disable Macros for DMI peripheral

#define DCMI_PCLCK_DIS()		RCC->AHB2ENR &= ~(0x01 << 0)

// Clock Disable Macros for OTGFS peripheral

#define OTGFS_PCLCK_DIS()		RCC->AHB2ENR &= ~(0x01 << 7)

// Clock Disable Macros for FMC peripheral

#define FMC_PCLCK_DIS()			RCC->AHB3ENR &= ~(0x01 << 0)

// Clock Disable Macros for FMC peripheral

#define QSPI_PCLCK_DIS()		RCC->AHB3ENR &= ~(0x01 << 1)

// Clock Disable Macros for Timers peripherals

#define TIM2_PCLCK_DIS()		RCC->APB1ENR &= (uint32_t) ~(0x01 << 0)
#define TIM3_PCLCK_DIS()		RCC->APB1ENR &= (uint32_t) ~(0x01 << 1)
#define TIM4_PCLCK_DIS()		RCC->APB1ENR &= (uint32_t) ~(0x01 << 2)
#define TIM5_PCLCK_DIS()		RCC->APB1ENR &= (uint32_t) ~(0x01 << 3)
#define TIM6_PCLCK_DIS()		RCC->APB1ENR &= (uint32_t) ~(0x01 << 4)
#define TIM7_PCLCK_DIS()		RCC->APB1ENR &= (uint32_t) ~(0x01 << 5)
#define TIM12_PCLCK_DIS()		RCC->APB1ENR &= (uint32_t) ~(0x01 << 6)
#define TIM13_PCLCK_DIS()		RCC->APB1ENR &= (uint32_t) ~(0x01 << 7)
#define TIM14_PCLCK_DIS()		RCC->APB1ENR &= (uint32_t) ~(0x01 << 8)


// Clock Disable Macros for WWDG peripherals

#define WWDG_PCLCK_DIS()		RCC->APB1ENR &= ~(0x01 << 11)


// Clock Disable Macros for SPI peripherals

#define SPI2_PCLCK_DIS()		RCC->APB1ENR &= (uint32_t) ~(0x01 << 14)
#define SPI3_PCLCK_DIS()		RCC->APB1ENR &= (uint32_t) ~(0x01 << 15)

// Clock Enable Macros for SPDIFRX peripherals

#define SPDIFRX_PCLCK_DIS()		RCC->APB1ENR &= (uint32_t) ~(0x01 << 16)

// Clock Enable Macros for UART peripherals

#define USART2_PCLCK_DIS()		RCC->APB1ENR &= (uint32_t) ~(0x01 << 17)
#define USART3_PCLCK_DIS()		RCC->APB1ENR &= (uint32_t) ~(0x01 << 18)
#define UART4_PCLCK_DIS()		RCC->APB1ENR &= (uint32_t) ~(0x01 << 19)
#define UART5_PCLCK_DIS()		RCC->APB1ENR &= (uint32_t) ~(0x01 << 20)

// Clock Enable Macros for I2C peripherals

#define I2C1_PCLCK_DIS()		RCC->APB1ENR &= (uint32_t) ~(0x01 << 21)
#define I2C2_PCLCK_DIS()		RCC->APB1ENR &= (uint32_t) ~(0x01 << 22)
#define I2C3_PCLCK_DIS()		RCC->APB1ENR &= (uint32_t) ~(0x01 << 23)


// Clock Enable Macros for FMPI2C1 peripherals

#define FMPI2C1_PCLCK_DIS()		RCC->APB1ENR &= (uint32_t) ~(0x01 << 24)

// Clock Enable Macros for CAN peripherals

#define CAN1_PCLCK_DIS()		RCC->APB1ENR &= (uint32_t) ~(0x01 << 25)
#define CAN2_PCLCK_DIS()		RCC->APB1ENR &= (uint32_t) ~(0x01 << 26)


// Clock Enable Macros for CEC peripherals

#define CEC_PCLCK_DIS()			RCC->APB1ENR &= (uint32_t) ~(0x01 << 27)

// Clock Enable Macros for PWR peripherals

#define PWR_PCLCK_DIS()			RCC->APB1ENR &= (uint32_t) ~(0x01 << 28)

// Clock Enable Macros for DAC peripherals

#define DAC_PCLCK_DIS()			RCC->APB1ENR &= (uint32_t) ~(0x01 << 29)


// Clock Enable Macros for TIMERS peripherals

#define TIM1_PCLCK_DIS()		RCC->APB2ENR &= (uint32_t)~(0x01 << 0)
#define TIM8_PCLCK_DIS()		RCC->APB2ENR &= (uint32_t)~(0x01 << 1)
#define TIM9_PCLCK_DIS()		RCC->APB2ENR &= (uint32_t)~(0x01 << 16)
#define TIM10_PCLCK_DIS()		RCC->APB2ENR &= (uint32_t)~(0x01 << 17)
#define TIM11_PCLCK_DIS()		RCC->APB2ENR &= (uint32_t)~(0x01 << 18)


// Clock Disable Macros for TIMERS peripherals

#define USART1_PCLCK_DIS()		RCC->APB2ENR &= (uint32_t) ~(0x01 << 5)
#define USART6_PCLCK_DIS()		RCC->APB2ENR &= (uint32_t) ~(0x01 << 6)

// Clock Disable Macros for ADC peripherals

#define ADC1_PCLCK_DIS()		RCC->APB2ENR &= (uint32_t) ~(0x01 << 8)
#define ADC2_PCLCK_DIS()		RCC->APB2ENR &= (uint32_t) ~(0x01 << 9)
#define ADC3_PCLCK_DIS()		RCC->APB2ENR &= (uint32_t) ~(0x01 << 10)

// Clock Disable Macros for SDIO peripherals

#define SDIO_PCLCK_DIS()		RCC->APB2ENR &= (uint32_t) ~(0x01 << 11)

// Clock Disable Macros for SPI peripherals

#define SPI1_PCLCK_DIS()		RCC->APB2ENR &= (uint32_t) ~(0x01 << 12)
#define SPI4_PCLCK_DIS()		RCC->APB2ENR &= (uint32_t) ~(0x01 << 13)

// Clock Disable Macros for SYSCFG peripherals

#define SYSCFG_PCLCK_DIS()		RCC->APB2ENR &= (uint32_t) ~(0x01 << 14)


// Clock Disable Macros for SAI peripherals

#define SAI1_PCLCK_DIS()		RCC->APB2ENR &= (uint32_t) ~(0x01 << 22)
#define SAI2_PCLCK_DIS()		RCC->APB2ENR &= (uint32_t) ~(0x01 << 23)


// Reset Macros peripherals

#define RESET_GPIOA()			do{ RCC->AHB1RSTR |= (0x01 << 0);   RCC->AHB1RSTR &= (uint32_t)~(0x01 << 0); }while(0)
#define RESET_GPIOB()			do{ RCC->AHB1RSTR |= (0x01 << 1);   RCC->AHB1RSTR &= (uint32_t)~(0x01 << 1); }while(0)
#define RESET_GPIOC()			do{ RCC->AHB1RSTR |= (0x01 << 2);   RCC->AHB1RSTR &= (uint32_t)~(0x01 << 2); }while(0)
#define RESET_GPIOD()			do{ RCC->AHB1RSTR |= (0x01 << 3);   RCC->AHB1RSTR &= (uint32_t)~(0x01 << 3); }while(0)
#define RESET_GPIOE()			do{ RCC->AHB1RSTR |= (0x01 << 4);   RCC->AHB1RSTR &= (uint32_t)~(0x01 << 4); }while(0)
#define RESET_GPIOF()			do{ RCC->AHB1RSTR |= (0x01 << 5);   RCC->AHB1RSTR &= (uint32_t)~(0x01 << 5); }while(0)
#define RESET_GPIOG()			do{ RCC->AHB1RSTR |= (0x01 << 6);   RCC->AHB1RSTR &= (uint32_t)~(0x01 << 6); }while(0)
#define RESET_GPIOH()			do{ RCC->AHB1RSTR |= (0x01 << 7);   RCC->AHB1RSTR &= (uint32_t)~(0x01 << 7); }while(0)

#define RESET_WWDG()			do{ RCC->APB1RSTR |= (0x01 << 11);  RCC->APB1RSTR &= (uint32_t)~(0x01 << 11); }while(0)

#define RESET_CRC()				RCC->AHB1RSTR |= (0x01 << 12)

#define RESET_DMA1()			RCC->AHB1RSTR |= (0x01 << 21)
#define RESET_DMA2()			RCC->AHB1RSTR |= (0x01 << 22)

#define RESET_OTGHS()			RCC->AHB1RSTR |= (0x01 << 29)


#define RESET_DCMI()			RCC->AHB2RSTR |= (0x01 << 0)
#define RESET_OTGFS()			RCC->AHB2RSTR |= (0x01 << 7)

#define RESET_FMC()				RCC->AHB3RSTR |= (0x01 << 0)
#define RESET_QSPIRST()		RCC->AHB3RSTR |= (0x01 << 1)


#define RESET_TIM2()			RCC->APB1RSTR |= (0x01 << 0)
#define RESET_TIM3()			RCC->APB1RSTR |= (0x01 << 1)
#define RESET_TIM4()			RCC->APB1RSTR |= (0x01 << 2)
#define RESET_TIM5()			RCC->APB1RSTR |= (0x01 << 3)
#define RESET_TIM6()			RCC->APB1RSTR |= (0x01 << 4)
#define RESET_TIM7()			RCC->APB1RSTR |= (0x01 << 5)
#define RESET_TIM12()			RCC->APB1RSTR |= (0x01 << 6)
#define RESET_TIM13()			RCC->APB1RSTR |= (0x01 << 7)
#define RESET_TIM14()			RCC->APB1RSTR |= (0x01 << 8)

//#define RESET_WWDG()			RCC->APB1RSTR |= (0x01 << 11)

#define RESET_SPI2()			RCC->APB1RSTR |= (0x01 << 14)
#define RESET_SPI3()			RCC->APB1RSTR |= (0x01 << 15)

#define RESET_SPDIFRX()		RCC->APB1RSTR |= (0x01 << 16)


#define RESET_UART2()			RCC->APB1RSTR |= (0x01 << 17)
#define RESET_UART3()			RCC->APB1RSTR |= (0x01 << 18)
#define RESET_UART4()			RCC->APB1RSTR |= (0x01 << 19)
#define RESET_UART5()			RCC->APB1RSTR |= (0x01 << 20)

#define RESET_I2C1()			RCC->APB1RSTR |= (0x01 << 21)
#define RESET_I2C2()			RCC->APB1RSTR |= (0x01 << 22)
#define RESET_I2C3()			RCC->APB1RSTR |= (0x01 << 23)

#define RESET_FMPI2C1()		RCC->APB1RSTR |= (0x01 << 24)

#define RESET_CAN1()			RCC->APB1RSTR |= (0x01 << 25)
#define RESET_CAN2()			RCC->APB1RSTR |= (0x01 << 26)

#define RESET_CECRS()			RCC->APB1RSTR |= (0x01 << 27)

#define RESET_PWR()				RCC->APB1RSTR |= (0x01 << 28)

#define RESET_DAC()				RCC->APB1RSTR |= (0x01 << 29)

#define RESET_TIM1()			RCC->APB2RSTR |= (0x01 << 0)
#define RESET_TIM8()			RCC->APB2RSTR |= (0x01 << 1)

#define RESET_USART1()		RCC->APB2RSTR |= (0x01 << 4)
#define RESET_USART6()		RCC->APB2RSTR |= (0x01 << 5)

#define RESET_ADC()				RCC->APB2RSTR |= (0x01 << 8)

#define RESET_SDIO()			RCC->APB2RSTR |= (0x01 << 11)

#define RESET_SPI1()			RCC->APB2RSTR |= (0x01 << 12)
#define RESET_SPI4()			RCC->APB2RSTR |= (0x01 << 13)

#define RESET_SYSCFG()		RCC->APB2RSTR |= (0x01 << 14)

#define RESET_TIM9()			RCC->APB2RSTR |= (0x01 << 16)
#define RESET_TIM10()			RCC->APB2RSTR |= (0x01 << 17)
#define RESET_TIM11()			RCC->APB2RSTR |= (0x01 << 18)

#define RESET_SAI1()			RCC->APB2RSTR |= (0x01 << 22)
#define RESET_SAI2()			RCC->APB2RSTR |= (0x01 << 23)


/*>>>CRC Structure<<<*/

typedef struct{

	__vo uint32_t DR;		/**/
	__vo uint32_t IDR;	/**/
	__vo uint32_t CR;		/**/

}CRC_RegDef_t;

#define CRC	( ( CRC_RegDef_t*) CRC_BASEADDR )


/*>>>PWR Structure<<<*/

typedef struct{

	__vo uint32_t CR;	/**/
	__vo uint32_t CSR;	/**/

}PWR_RegDef_t;

#define PWR	( ( PWR_RegDef_t*) PWR_BASEADDR )

/*>>>SYSCFGR Structure<<<*/



#define IRQ_TIM6_DAC						54
#define IRQ_NO_TIM7							55
#define IRQ_NO_TIM1_BRK_TIM9				24
#define IRQ_NO_TIM1_UP_TIM10				25
#define IRQ_NO_TIM1_TRG_COM_TIM11			26
#define IRQ_NO_TIM1_CC						27
#define IRQ_NO_TIM2							28
#define IRQ_NO_TIM3							72
#define IRQ_NO_TIM4							73

#define IRQ_NO_I2C1_EV						31
#define IRQ_NO_I2C1_ER						32
#define IRQ_NO_I2C2_EV						33
#define IRQ_NO_I2C2_ER						34
#define IRQ_NO_I2C3_EV						72
#define IRQ_NO_I2C3_ER						73

#define IRQ_NO_SPI1							35
#define IRQ_NO_SPI2							36

#define IRQ_NO_USART1						37
#define IRQ_NO_USART2						38
#define IRQ_NO_USART3						39
#define IRQ_NO_UART4						52
#define IRQ_NO_UART5						53
#define IRQ_NO_USART6						71


#define IRQ_NO_EXTI0						6
#define IRQ_NO_EXTI1						7
#define IRQ_NO_EXTI2						8
#define IRQ_NO_EXTI3						9
#define IRQ_NO_EXTI4						10
#define IRQ_NO_EXTI9_5						23
#define IRQ_NO_EXTI15_10					40

#define IRQ_NO_RTC_ALARM					41
#define IRQ_NO_OTG_FS_WKUP					42

#define IRQ_NO_TIM8_BRK_TIM12				43
#define IRQ_NO_TIM8_UP_TIM13				44
#define IRQ_NO_TIM8_COM_TIM14				45
#define IRQ_TIM8_CC							46

#define IRQ_CAN2_TX							63
#define IRQ_CAN2_RX0						64
#define IRQ_CAN2_RX1						65
#define IRQ_CAN2_SCE						66

#define IRQ_OTG_FS							67

#define IRQ_DMA1_STREAM_0					18
#define IRQ_DMA1_STREAM_1					19
#define IRQ_DMA1_STREAM_2					20
#define IRQ_DMA1_STREAM_3					21
#define IRQ_DMA1_STREAM_4					22
#define IRQ_DMA1_STREAM_5					23
#define IRQ_DMA1_STREAM_6					24
#define IRQ_DMA1_STREAM_7					47


#define IRQ_DMA2_STREAM_0					56
#define IRQ_DMA2_STREAM_1					57
#define IRQ_DMA2_STREAM_2					58
#define IRQ_DMA2_STREAM_3					59
#define IRQ_DMA2_STREAM_4					60
#define IRQ_DMA2_STREAM_5					68
#define IRQ_DMA2_STREAM_6					69
#define IRQ_DMA2_STREAM_7					70

#define IRQ_FMC								48
#define IRQ_SDIO							49
#define IRQ_TIM5							50
#define IRQ_SPI3							51
#define IRQ_SPI4							84

#define IRQ_SAI1							87
#define IRQ_SAI2							91

#define IRQ_QUADSPI							92

#define IRQ_HDMI_CEC						93
#define IRQ_SPDIF_RX						94
#define IRQ_FMPI2C1							95
#define IRQ_FMPI2C1_ERROR					96

#define IRQ_HS_EP1_OUT						74
#define IRQ_HS_EP1_IN						75
#define IRQ_HS_WKUP							76
#define IRQ_OTG_HS							77
#define IRQ_DCMI							78
#define IRQ_FPU								81



#define NVIC_IRQ_PRIORITY_0					0
#define NVIC_IRQ_PRIORITY_15				15


typedef struct{

	__vo uint32_t MEMRMP;				/**/
	__vo uint32_t PMC;					/**/
	__vo uint32_t EXTICR[4];			/**/
	__vo uint32_t RESERVED0[2];			/**/
	__vo uint32_t CMPCR;				/**/
	__vo uint32_t RESERVED1[2];			/**/
	__vo uint32_t CFGR;					/**/

}SYSCFGR_RegDef_t;

#define SYSCFGR	( ( SYSCFGR_RegDef_t*) SYSCFG_BASEADDR )

/*>>>DMA Structure<<<*/

typedef struct{

	__vo uint32_t LISR;				/**/
	__vo uint32_t HISR;				/**/
	__vo uint32_t LIFCR;			/**/
	__vo uint32_t HIFCR;			/**/
	__vo uint32_t S0CR;				/**/
	__vo uint32_t S0NDTR;			/**/
	__vo uint32_t S0PAR;			/**/
	__vo uint32_t S0M0AR;			/**/
	__vo uint32_t S0M1AR;			/**/
	__vo uint32_t S0FCR;			/**/
	__vo uint32_t S1CR;				/**/
	__vo uint32_t S1NDTR;			/**/
	__vo uint32_t S1PAR;			/**/
	__vo uint32_t S1M0AR;			/**/
	__vo uint32_t S1M1AR;			/**/
	__vo uint32_t S1FCR;			/**/
	__vo uint32_t S2CR;				/**/
	__vo uint32_t S2NDTR;			/**/
	__vo uint32_t S2PAR;			/**/
	__vo uint32_t S2M0AR;			/**/
	__vo uint32_t S2M1AR;			/**/
	__vo uint32_t S2FCR;			/**/
	__vo uint32_t S3CR;				/**/
	__vo uint32_t S3NDTR;			/**/
	__vo uint32_t S3PAR;			/**/
	__vo uint32_t S3M0AR;			/**/
	__vo uint32_t S3M1AR;			/**/
	__vo uint32_t S3FCR;			/**/
	__vo uint32_t S4CR;				/**/
	__vo uint32_t S4NDTR;			/**/
	__vo uint32_t S4PAR;			/**/
	__vo uint32_t S4M0AR;			/**/
	__vo uint32_t S4M1AR;			/**/
	__vo uint32_t S4FCR;			/**/
	__vo uint32_t S5CR;				/**/
	__vo uint32_t S5NDTR;			/**/
	__vo uint32_t S5PAR;			/**/
	__vo uint32_t S5M0AR;			/**/
	__vo uint32_t S5M1AR;			/**/
	__vo uint32_t S5FCR;			/**/
	__vo uint32_t S6CR;				/**/
	__vo uint32_t S6NDTR;			/**/
	__vo uint32_t S6PAR;			/**/
	__vo uint32_t S6M0AR;			/**/
	__vo uint32_t S6M1AR;			/**/
	__vo uint32_t S6FCR;			/**/
	__vo uint32_t S7CR;				/**/
	__vo uint32_t S7NDTR;			/**/
	__vo uint32_t S7PAR;			/**/
	__vo uint32_t S7M0AR;			/**/
	__vo uint32_t S7M1AR;			/**/
	__vo uint32_t S7FCR;			/**/

}DMA_RegDef_t;

#define DMA1	( ( DMA_RegDef_t*) DMA1_BASEADDR )
#define DMA2	( ( DMA_RegDef_t*) DMA2_BASEADDR )

/*>>> DMA LISR Bitfields <<<*/

#define DMA_LISR_FEIF0			0
#define DMA_LISR_DMEIF0			2
#define DMA_LISR_TEIF0			3
#define DMA_HTIF0				4
#define DMA_LISR_TCIF0			5
#define DMA_LISR_FEIF1			6
#define DMA_LISR_DMEIF1			8
#define DMA_LISR_TEIF1			9
#define DMA_LISR_HTIF1			10
#define DMA_LISR_TCIF1			11
#define DMA_LISR_FEIF2			16
#define DMA_LISR_DMEIF2			18
#define DMA_LISR_TEIF2			19
#define DMA_LISR_HTIF2			20
#define DMA_LISR_TCIF2			21
#define DMA_LISR_FEIF3			22
#define DMA_DMEIF3				24
#define DMA_LISR_TEIF3			25
#define DMA_LISR_HTIF3			26
#define DMA_LISR_TCIF3			27

/*>>> DMA HISR Bitfields <<<*/

#define DMA_HISR_FEIF4			0
#define DMA_HISR_DMEIF4			2
#define DMA_HISR_TEIF4			3
#define DMA_HISR_HTIF4			4
#define DMA_HISR_TCIF4			5
#define DMA_HISR_FEIF5			6
#define DMA_HISR_DMEIF5			8
#define DMA_HISR_TEIF5			9
#define DMA_HISR_HTIF5			10
#define DMA_HISR_TCIF5			11
#define DMA_HISR_FEIF6			16
#define DMA_HISR_DMEIF6			18
#define DMA_HISR_TEIF6			19
#define DMA_HISR_HTIF6			20
#define DMA_HISR_TCIF6			21
#define DMA_HISR_FEIF7			22
#define DMA_HISR_DMEIF7			24
#define DMA_HISR_TEIF7			25
#define DMA_HISR_HTIF7			26
#define DMA_HISR_TCIF7			27

/*>>> DMA LIFCR Bitfields <<<*/

#define DMA_LIFCR_CFEIF0			0
#define DMA_LIFCR_CDMEIF0			2
#define DMA_LIFCR_CTEIF0			3
#define DMA_LIFCR_CHTIF0			4
#define DMA_LIFCR_CTCIF0			5
#define DMA_LIFCR_CFEIF1			6
#define DMA_LIFCR_CDMEIF1			8
#define DMA_LIFCR_CTEIF1			9
#define DMA_LIFCR_CHTIF1			10
#define DMA_LIFCR_CTCIF1			11
#define DMA_LIFCR_CFEIF2			16
#define DMA_LIFCR_CDMEIF2			18
#define DMA_LIFCR_CTEIF2			19
#define DMA_LIFCR_CHTIF2			20
#define DMA_LIFCR_CTCIF2			21
#define DMA_LIFCR_CFEIF3			22
#define DMA_LIFCR_CDMEIF3			24
#define DMA_LIFCR_CTEIF3			25
#define DMA_LIFCR_CHTIF3			26
#define DMA_LIFCR_CTCIF3			27

/*>>> DMA HIFCR Bitfields <<<*/

#define DMA_HIFCR_CFEIF4			0
#define DMA_HIFCR_CDMEIF4			2
#define DMA_HIFCR_CTEIF4			3
#define DMA_HIFCR_CHTIF4			4
#define DMA_HIFCR_CTCIF4			5
#define DMA_HIFCR_CFEIF5			6
#define DMA_HIFCR_CDMEIF5			8
#define DMA_HIFCR_CTEIF5			9
#define DMA_HIFCR_CHTIF5			10
#define DMA_HIFCR_CTCIF5			11
#define DMA_HIFCR_CFEIF6			16
#define DMA_HIFCR_CDMEIF6			18
#define DMA_HIFCR_CTEIF6			19
#define DMA_HIFCR_CHTIF6			20
#define DMA_HIFCR_CTCIF6			21
#define DMA_HIFCR_CFEIF7			22
#define DMA_HIFCR_CDMEIF7			24
#define DMA_HIFCR_CTEIF7			25
#define DMA_HIFCR_CHTIF7			26
#define DMA_HIFCR_CTCIF7			27

/*>>> DMA SxNDTR Bitfields <<<*/

#define DMA_SxNDTR_NDT		0

/*>>> DMA SxCR Bitfields <<<*/

#define DMA_SxCR_EN			0
#define DMA_SxCR_DMEIE		1
#define DMA_SxCR_TEIE		2
#define DMA_SxCR_HTIE		3
#define DMA_SxCR_TCIE		4
#define DMA_SxCR_PFCTRL		5
#define DMA_SxCR_DIR		6
#define DMA_SxCR_CIRC		8
#define DMA_SxCR_PINC		9
#define DMA_SxCR_MINC		10
#define DMA_SxCR_PSIZE		11
#define DMA_SxCR_MSIZE		13
#define DMA_SxCR_PINCOS		15
#define DMA_SxCR_PL			16
#define DMA_SxCR_DBM		18
#define DMA_SxCR_CT			19
#define DMA_SxCR_PBURST	 	21
#define DMA_SxCR_MBURST	 	23
#define DMA_SxCR_CHSEL		25


#define MSIZE_1BYTE				0
#define MSIZE_HALF_WORD			1
#define MSIZE_WORD				2

#define PSIZE_1BYTE				0
#define PSIZE_HALF_WORD			1
#define PSIZE_WORD				2

#define MEM_INC_FIXED			0
#define MEM_INC_INCREMENT		1

#define MEM_PINC_FIXED			0
#define MEM_PINC_INCREMENT		1

#define TRANSFER_PERIPHERAL_TO_MEMORY 			0
#define TRANSFER_MEMORY_TO_PERIPHERAL 			1
#define TRANSFER_MEMORY_TO_MEMORY 				2

#define TRANSFER_COMPLETE_INTERRUPT_DISABLE 	0
#define TRANSFER_COMPLETE_INTERRUPT_ENABLE 		1

#define TRANSFER_ERROR_INTERRUPT_DISABLE 		0
#define TRANSFER_ERROR_INTERRUPT_ENABLE 		1


#define DIRECT_MODE_ERROR_INTERRUPT_DISABLE 	0
#define DIRECT_MODE_ERROR_INTERRUPT_ENABLE 		1

#define DIRECT_MODE_ENABLE 		0
#define DIRECT_MODE_DISABLE 	1

#define _1_4_FULL_FIFO 			0
#define _1_2_FULL_FIFO 			1
#define _3_4_FULL_FIFO 			2
#define FULL_FIFO 				3


/*>>> DMA SxFCR Bitfields <<<*/

#define DMA_SxFCR_FTH			0
#define DMA_SxFCR_DMDIS			2
#define DMA_SxFCR_FS			3
#define DMA_SxFCR_FEIE			7


/*>>>EXTI Structure<<<*/

typedef struct{

	__vo uint32_t IMR;				/**/
	__vo uint32_t EMR;				/**/
	__vo uint32_t RTSR;				/**/
	__vo uint32_t FTSR;				/**/
	__vo uint32_t SWIER;			/**/
	__vo uint32_t PR;					/**/


}EXTI_RegDef_t;

#define EXTI	( ( EXTI_RegDef_t*) EXTI_BASEADDR )

/*>>>FMC Structure<<<*/

typedef struct{

	__vo uint32_t BCR1;				/**/
	__vo uint32_t BCR2;				/**/
	__vo uint32_t BCR3;				/**/
	__vo uint32_t BCR4;				/**/
	__vo uint32_t BTR1;				/**/
	__vo uint32_t BTR2;				/**/
	__vo uint32_t BTR3;				/**/
	__vo uint32_t BTR4;				/**/
	__vo uint32_t BWTR1;			/**/
	__vo uint32_t BWTR2;			/**/
	__vo uint32_t BWTR3;			/**/
	__vo uint32_t BWTR4;			/**/
	__vo uint32_t PCR;				/**/
	__vo uint32_t SR;				/**/
	__vo uint32_t PMEM;				/**/
	__vo uint32_t PATT;				/**/
	__vo uint32_t ECCR;				/**/
	__vo uint32_t SDCR1;			/**/
	__vo uint32_t SDCR2;			/**/
	__vo uint32_t SDTR1;			/**/
	__vo uint32_t SDTR2;			/**/
	__vo uint32_t SDCMR;			/**/
	__vo uint32_t SDRTR;			/**/
	__vo uint32_t SDSR;				/**/


}FMC_RegDef_t;

#define FMC	( ( FMC_RegDef_t*) FMC_BASEADDR )

/*>>>QUADSPI Structure<<<*/

typedef struct{

	__vo uint32_t CR;				/**/
	__vo uint32_t DCR;				/**/
	__vo uint32_t SR;				/**/
	__vo uint32_t FCR;				/**/
	__vo uint32_t DLR;				/**/
	__vo uint32_t CCR;				/**/
	__vo uint32_t AR;				/**/
	__vo uint32_t ABR;				/**/
	__vo uint32_t DR;				/**/
	__vo uint32_t PSMKR;			/**/
	__vo uint32_t PSMAR;			/**/
	__vo uint32_t PIR;				/**/
	__vo uint32_t LPTR;				/**/


}QUADSPI_RegDef_t;

#define QUADSPI	( ( QUADSPI_RegDef_t*) QUADSPI_BASEADDR )

/*>>>ADC Structure<<<*/

typedef struct{

	__vo uint32_t SR;					/**/
	__vo uint32_t CR[2];				/**/
	__vo uint32_t SMPR[2];				/**/
	__vo uint32_t JOFR[4];				/**/
	__vo uint32_t HTR;					/**/
	__vo uint32_t LTR;					/**/
	__vo uint32_t SQR[3];				/**/
	__vo uint32_t JSQR;					/**/
	__vo uint32_t JDR[4];				/**/
	__vo uint32_t DR;					/**/

}ADC_RegDef_t;

#define ADC1				( ( ADC_RegDef_t*) ADC1_BASEADDR )
#define ADC2				( ( ADC_RegDef_t*) ADC2_BASEADDR )
#define ADC3				( ( ADC_RegDef_t*) ADC3_BASEADDR )
#define ADC_Commons	( ( ADC_RegDef_t*) ADC_COMMON_BASEADDR )

/*>>>ADC Common Structure<<<*/

typedef struct{

	__vo uint32_t CSR;					/**/
	__vo uint32_t CCR;					/**/
	__vo uint32_t CDR;					/**/

}ADC_Common_RegDef_t;

#define ADC_COMMON	( ( ADC_RegDef_t*) ADC_COMMON_BASEADDR )

#define ADC_CH0					 0x00 << 0 
#define ADC_CH1					 0x01 << 1 
#define ADC_CH2					 0x01 << 2 
#define ADC_CH3					 0x01 << 3 
#define ADC_CH4					 0x01 << 4 
#define ADC_CH5					 0x01 << 5 
#define ADC_CH6					 0x01 << 6 
#define ADC_CH7					 0x01 << 7 
#define ADC_CH8					 0x01 << 8 
#define ADC_CH9					 0x01 << 9 
#define ADC_CH10				 0x01 << 10
#define ADC_CH11				 0x01 << 11
#define ADC_CH12				 0x01 << 12
#define ADC_CH13				 0x01 << 13
#define ADC_CH14				 0x01 << 14
#define ADC_CH15				 0x01 << 15

#define ADC_1_CONVERSION 		 0x00	
#define ADC_2_CONVERSION 		 0x01	
#define ADC_3_CONVERSION 		 0x02	
#define ADC_4_CONVERSION 		 0x03	
#define ADC_5_CONVERSION 		 0x04	
#define ADC_6_CONVERSION 		 0x05	
#define ADC_7_CONVERSION 		 0x06	
#define ADC_8_CONVERSION 		 0x07	
#define ADC_9_CONVERSION 		 0x08	
#define ADC_10_CONVERSION 		 0x09	
#define ADC_11_CONVERSION 		 0x0A	
#define ADC_12_CONVERSION 		 0x0B	
#define ADC_13_CONVERSION 		 0x0C	
#define ADC_14_CONVERSION 		 0x0D	
#define ADC_15_CONVERSION 		 0x0E	
#define ADC_16_CONVERSION 		 0x0F	


#define ADC_N_CONVERSION( x ) 		(	( x == 1 )? ADC_1_CONVERSION :\
										( x == 2 )? ADC_2_CONVERSION :\
										( x == 3 )? ADC_3_CONVERSION :\
										( x == 4 )? ADC_4_CONVERSION :\
										( x == 5 )? ADC_5_CONVERSION :\
										( x == 6 )? ADC_6_CONVERSION :\
										( x == 7 )? ADC_7_CONVERSION :\
										( x == 8 )? ADC_8_CONVERSION :\
										( x == 9 )? ADC_9_CONVERSION :\
										( x == 10 )? ADC_10_CONVERSION :\
										( x == 11 )? ADC_11_CONVERSION :\
										( x == 12 )? ADC_12_CONVERSION :\
										( x == 13 )? ADC_13_CONVERSION :\
										( x == 14 )? ADC_14_CONVERSION :\
										( x == 15 )? ADC_15_CONVERSION :\
										( x == 15 )? ADC_16_CONVERSION :0 )


/*>>>DAC Common Structure<<<*/

typedef struct{

	__vo uint32_t CR;					/**/
	__vo uint32_t SWTRIGR;				/**/
	__vo uint32_t DHR12R1;				/**/
	__vo uint32_t DHR12L1;				/**/
	__vo uint32_t DHR8R1;				/**/
	__vo uint32_t DHR12R2;				/**/
	__vo uint32_t DHR12L2;				/**/
	__vo uint32_t DHR8R2;				/**/
	__vo uint32_t DHR12RD;				/**/
	__vo uint32_t DHR12LD;				/**/
	__vo uint32_t DHR8RD;				/**/
	__vo uint32_t DOR1;					/**/
	__vo uint32_t DOR2;					/**/
	__vo uint32_t SR;					/**/


}DAC_RegDef_t;

#define DAC	( ( DAC_RegDef_t*) DAC_BASEADDR )

/*>>>DCMI Structure<<<*/

typedef struct{

	__vo uint32_t CR;					/**/
	__vo uint32_t SR;					/**/
	__vo uint32_t RIS;					/**/
	__vo uint32_t IER;					/**/
	__vo uint32_t MIS;					/**/
	__vo uint32_t ICR;					/**/
	__vo uint32_t ESCR;					/**/
	__vo uint32_t ESUR;					/**/
	__vo uint32_t CWSTRT;				/**/
	__vo uint32_t CWSIZE;				/**/
	__vo uint32_t DR;					/**/

}DCMI_RegDef_t;

#define DCMI	( ( DCMI_RegDef_t*) DCMI_BASEADDR )

typedef struct{

	__vo uint32_t CR[2];					/**/
	__vo uint32_t SMCR;						/**/
	__vo uint32_t DIER;						/**/
	__vo uint32_t SR;						/**/
	__vo uint32_t EGR;						/**/
	__vo uint32_t CCMR[2];					/**/
	__vo uint32_t CCER;						/**/
	__vo uint32_t CNT;						/**/
	__vo uint32_t PSC;						/**/
	__vo uint32_t ARR;						/**/
	__vo uint32_t RCR;						/**/
	__vo uint32_t CCR[4];					/**/
	__vo uint32_t BDTR;						/**/
	__vo uint32_t DCR;						/**/
	__vo uint32_t DMAR;						/**/
	__vo uint32_t OR;						/**/

}TIM_RegDef_t;

/*>>>Advanced Control timers Structure<<<*/

#define TIM1	( ( TIM_RegDef_t*) TIM1_BASEADDR )
#define TIM8	( ( TIM_RegDef_t*) TIM8_BASEADDR )

/*>>>General Purpose Timers Structure<<<*/

#define TIM2	( ( TIM_RegDef_t*) TIM2_BASEADDR )
#define TIM3	( ( TIM_RegDef_t*) TIM3_BASEADDR )
#define TIM4	( ( TIM_RegDef_t*) TIM4_BASEADDR )
#define TIM5	( ( TIM_RegDef_t*) TIM5_BASEADDR )

/*>>>General Purpose Timers Structure<<<*/

#define TIM9	( ( TIM_RegDef_t*) TIM9_BASEADDR )
#define TIM10	( ( TIM_RegDef_t*) TIM10_BASEADDR )
#define TIM11	( ( TIM_RegDef_t*) TIM11_BASEADDR )
#define TIM12	( ( TIM_RegDef_t*) TIM12_BASEADDR )
#define TIM13	( ( TIM_RegDef_t*) TIM13_BASEADDR )
#define TIM14	( ( TIM_RegDef_t*) TIM14_BASEADDR )


/*>>>Basic Timers Structure<<<*/
#define TIM6	( ( TIM_RegDef_t*) TIM6_BASEADDR )
#define TIM7	( ( TIM_RegDef_t*) TIM7_BASEADDR )

/*>>>Independent Watchdog Structure<<<*/

typedef struct{

	__vo uint32_t KR;					/**/
	__vo uint32_t PR;					/**/
	__vo uint32_t RLR;					/**/
	__vo uint32_t SR;					/**/

}Independent_Watchdog_RegDef_t;

#define IWDG	( ( Independent_Watchdog_RegDef_t*) IWDG_BASEADDR )

/*>>>Window Watchdog Structure<<<*/

typedef struct{

	__vo uint32_t CR;					/**/
	__vo uint32_t CFR;					/**/
	__vo uint32_t SR;					/**/

}Window_Watchdog_RegDef_t;

#define WWDG	( ( Window_Watchdog_RegDef_t*) WWDG_BASEADDR )

/*>>>RTC Structure<<<*/

typedef struct{

	__vo uint32_t TR;					/**/
	__vo uint32_t DR;					/**/
	__vo uint32_t CR;					/**/
	__vo uint32_t ISR;					/**/
	__vo uint32_t PRER;					/**/
	__vo uint32_t WUTR;					/**/
	__vo uint32_t CALIBR;				/**/
	__vo uint32_t ALRMAR;				/**/
	__vo uint32_t ALRMBR;				/**/
	__vo uint32_t WPR;					/**/
	__vo uint32_t SSR;					/**/
	__vo uint32_t SHIFTR;				/**/
	__vo uint32_t TSTR;					/**/
	__vo uint32_t TSSSR;				/**/
	__vo uint32_t CALR;					/**/
	__vo uint32_t TAFCR;				/**/
	__vo uint32_t ALRMASSR;				/**/
	__vo uint32_t ALRMBSSR;				/**/
	__vo uint32_t BKP0R;				/**/
	__vo uint32_t BKP19R;				/**/

}RTC_RegDef_t;

#define RTC	( ( RTC_RegDef_t*) RTC_BKP_BASEADDR )

/*>>>FMPI2C Structure<<<*/

typedef struct{

	__vo uint32_t CR[2];				/**/
	__vo uint32_t OAR[2];				/**/
	__vo uint32_t TIMINGR;				/**/
	__vo uint32_t TIMEOUTR;				/**/
	__vo uint32_t ISR;					/**/
	__vo uint32_t ICR;					/**/
	__vo uint32_t PECR;					/**/
	__vo uint32_t RXDR;					/**/
	__vo uint32_t TXDR;					/**/

}FMPI2C_RegDef_t;

#define FMPI2C	( ( FMPI2C_RegDef_t*) FMC_BASEADDR )

/*>>>I2C Structure<<<*/

typedef struct{

	__vo uint32_t CR[2];				/**/
	__vo uint32_t OAR[2];				/**/
	__vo uint32_t DR;					/**/
	__vo uint32_t SR[2];				/**/
	__vo uint32_t CCR;					/**/
	__vo uint32_t TRISE;				/**/
	__vo uint32_t FLTR;					/**/

}I2C_RegDef_t;

#define I2C1	( ( I2C_RegDef_t*) I2C1_BASEADDR )
#define I2C2	( ( I2C_RegDef_t*) I2C2_BASEADDR )
#define I2C3	( ( I2C_RegDef_t*) I2C3_BASEADDR )

/*>>>UART Structure<<<*/

typedef struct{

	__vo uint32_t SR;				/**/
	__vo uint32_t DR;				/**/
	__vo uint32_t BRR;				/**/
	__vo uint32_t CR[3];			/**/
	__vo uint32_t GTPR;				/**/

}UART_RegDef_t;

#define USART1	( ( UART_RegDef_t*) USART1_BASEADDR )
#define USART2	( ( UART_RegDef_t*) USART2_BASEADDR )
#define USART3	( ( UART_RegDef_t*) USART3_BASEADDR )
#define USART4	( ( UART_RegDef_t*) UART4_BASEADDR )
#define USART5	( ( UART_RegDef_t*) UART5_BASEADDR )


/*>>>SPI Structure<<<*/

typedef struct{

	__vo uint32_t CR[2];			/**/
	__vo uint32_t SR;				/**/
	__vo uint32_t DR;				/**/
	__vo uint32_t CRCPR;			/**/
	__vo uint32_t RXCRCR;			/**/
	__vo uint32_t TXCRCR;			/**/
	__vo uint32_t I2SCFGR;			/**/
	__vo uint32_t I2SPR;			/**/

}SPI_RegDef_t;

#define SPI1	( ( SPI_RegDef_t*) SPI1_BASEADDR )
#define SPI2	( ( SPI_RegDef_t*) SPI2_I2S2_BASEADDR )
#define SPI3	( ( SPI_RegDef_t*) SPI3_I2S3_BASEADDR )
#define SPI4	( ( SPI_RegDef_t*) SPI4_BASEADDR )


#define SPI_CR1_CPHA 								0
#define SPI_CR1_CPOL 								1
#define SPI_CR1_MASTER_SELECTION 					2
#define SPI_CR1_BAUDRATE 							3
#define SPI_CR1_ENABLE 								6
#define SPI_CR1_LSBFIRST 							7
#define SPI_CR1_SSI 								8
#define SPI_CR1_SSM 								9
#define SPI_CR1_RXONLY 								10
#define SPI_CR1_DFF 								11
#define SPI_CR1_CRC_EN 								13
#define SPI_CR1_BIDIMODE 							15



#define SPI_CR2_RX_DMA_ENABLE						0
#define SPI_CR2_TX_DMA_ENABLE						1
#define SPI_CR2_SS_ENABLE 							2
#define SPI_CR2_FRAME_FORMAT						4
#define SPI_CR2_ERROR_INTERRUPT_ENABLE				5
#define SPI_CR2_RXBUFFER_NEMPTY_INTERRUPT_ENABLE	6
#define SPI_CR2_TXBUFFER_EMPTY_INTERRUPT_ENABLE		7


#define SPI_SR_RXBUFFER_NEMPTY						0
#define SPI_SR_TXBUFFER_EMPTY						1
#define SPI_SR_CH_SIDE 								2
#define SPI_SR_UDR									3
#define SPI_SR_CRC_ERROR							4
#define SPI_SR_MODE_FAULT							5
#define SPI_SR_OVERRUN								6
#define SPI_SR_BUSY									7
#define SPI_SR_FRAME_ERROR							8


#define SPI_RXBUFFER_EMPTY_FLAG  					1<<SPI_SR_RXBUFFER_NEMPTY
#define SPI_TXBUFFER_EMPTY_FLAG  					1<<SPI_SR_TXBUFFER_EMPTY
#define SPI_CH_SID_FLAG  							1<<SPI_SR_CH_SIDE
#define SPI_UDR_FLAG  								1<<SPI_SR_UDR
#define SPI_CRC_ERROR_FLAG  						1<<SPI_SR_CRC_ERROR
#define SPI_MODE_FAULT_FLAG  						1<<SPI_SR_MODE_FAULT
#define SPI_BUSY_FLAG  								1<<SPI_SR_BUSY
#define SPI_FRAME_ERROR_FLAG  						1<<SPI_SR_FRAME_ERROR

/*>>>SPDIFRX Structure<<<*/

typedef struct{

	__vo uint32_t CR;				/**/
	__vo uint32_t IMR;				/**/
	__vo uint32_t SR;				/**/
	__vo uint32_t IFCR;				/**/
	__vo uint32_t FMT0_DR;			/**/
	__vo uint32_t FMT1_DR;			/**/
	__vo uint32_t FMT2_DR;			/**/
	__vo uint32_t CSR;				/**/
	__vo uint32_t DIR;				/**/

}SPDIFRX_RegDef_t;

#define SPDIF	( ( SPDIFRX_RegDef_t*) SPDIF_RX )

/*>>>SAI Structure<<<*/

typedef struct{

	__vo uint32_t xSLOTR;			/**/
	__vo uint32_t xIM;				/**/
	__vo uint32_t xSR;				/**/
	__vo uint32_t xCLRFR;			/**/
	__vo uint32_t xDR;				/**/

}SAI_RegDef_t;

#define SAI1	( ( SAI_RegDef_t*) SAI1_BASEADDR )
#define SAI2	( ( SAI_RegDef_t*) SAI2_BASEADDR )

/*>>>SDMMC Structure<<<*/

typedef struct{

	__vo uint32_t POWER;			/**/
	__vo uint32_t CLKCR;			/**/
	__vo uint32_t ARG;				/**/
	__vo uint32_t CMD;				/**/
	__vo uint32_t RESPCMD;			/**/
	__vo uint32_t RESP[4];			/**/
	__vo uint32_t DTIMER;			/**/
	__vo uint32_t DLEN;				/**/
	__vo uint32_t DCTRL;			/**/
	__vo uint32_t DCOUNT;			/**/
	__vo uint32_t STA;				/**/
	__vo uint32_t ICR;				/**/
	__vo uint32_t MASK;				/**/
	__vo uint32_t FIFOCNT;			/**/
	__vo uint32_t FIFO;				/**/

}SDMCC_RegDef_t;

#define SDMCC	( ( SDMCC_RegDef_t*) SDMMC_BASEADDR )

/*>>>CAN Structure<<<*/

typedef struct{

	__vo uint32_t MCR;					/**/
	__vo uint32_t MSR;					/**/
	__vo uint32_t TSR;					/**/
	__vo uint32_t RF0R;					/**/
	__vo uint32_t RF1R;					/**/
	__vo uint32_t IER;					/**/
	__vo uint32_t ESR;					/**/
	__vo uint32_t BTR;					/**/
	__vo uint32_t TI0R;					/**/
	__vo uint32_t TDT0R;				/**/
	__vo uint32_t TDL0R;				/**/
	__vo uint32_t TDH0R;				/**/
	__vo uint32_t TI1R;					/**/
	__vo uint32_t TDT1R;				/**/
	__vo uint32_t TDH1R;				/**/
	__vo uint32_t TI2R;					/**/
	__vo uint32_t TDT2R;				/**/
	__vo uint32_t TDLR2;				/**/
	__vo uint32_t TDH2R;				/**/
	__vo uint32_t RI0R;					/**/
	__vo uint32_t RDT0R;				/**/
	__vo uint32_t RDH0R;				/**/
	__vo uint32_t RI1R;					/**/
	__vo uint32_t RDT1R;				/**/
	__vo uint32_t RDL1R;				/**/
	__vo uint32_t RDH1R;				/**/
	__vo uint32_t RESERVED0[2];			/**/
	__vo uint32_t FS1R;					/**/
	__vo uint32_t RESERVED1;			/**/
	__vo uint32_t FFA1R;				/**/
	__vo uint32_t RESERVED2;			/**/
	__vo uint32_t FA1R;					/**/
	__vo uint32_t RESERVED3[2];			/**/
	__vo uint32_t F0R1;					/**/
	__vo uint32_t F0R2;					/**/
	__vo uint32_t F1R1;					/**/
	__vo uint32_t F1R2;					/**/
	__vo uint32_t RESERVED4[51];		/**/
	__vo uint32_t F27R1;				/**/
	__vo uint32_t F27R2;				/**/

}CAN_RegDef_t;

#define CAN1	( ( CAN_RegDef_t*) CAN1_BASEADDR )
#define CAN2	( ( CAN_RegDef_t*) CAN2_BASEADDR )


/*>>>OTG_FS/OTG_HS Structure<<<*/
//TODO ADD RESERVERD
typedef struct{

	__vo uint32_t GOTGCTL;				/**/
	__vo uint32_t GOTGINT;				/**/
	__vo uint32_t GAHBCFG;				/**/
	__vo uint32_t GUSBCFG;				/**/
	__vo uint32_t GRSTCTL;				/**/
	__vo uint32_t GINTSTS;				/**/
	__vo uint32_t GINTMSK;				/**/
	__vo uint32_t GRXSTSR;				/**/
	__vo uint32_t GRXSTSP;				/**/
	__vo uint32_t GRXFSIZ;				/**/
	__vo uint32_t DIEPTXF0;				/**/
	__vo uint32_t HNPTXSTS;				/**/
	__vo uint32_t GCCFG;				/**/
	__vo uint32_t CID;					/**/
	__vo uint32_t GLPMCFG;				/**/
	__vo uint32_t HPTXFSIZ;				/**/
	__vo uint32_t DIEPTXF[2];			/**/
	__vo uint32_t RESERVED0[3];			/**/
	__vo uint32_t DIEPTXF5;				/**/
	__vo uint32_t RESERVED1[3];			/**/
	__vo uint32_t DIEPTXF7;				/**/
	__vo uint32_t HCFG;					/**/
	__vo uint32_t HFIR;					/**/
	__vo uint32_t HFNUM;				/**/
	__vo uint32_t HPTXSTS;				/**/
	__vo uint32_t HAINT;				/**/
	__vo uint32_t HAINTMASK;			/**/
	__vo uint32_t HPRT;					/**/
	__vo uint32_t HCCHAT0;				/**/
	__vo uint32_t HCSPLT0;				/**/
	__vo uint32_t HCINT0;				/**/
	__vo uint32_t HCINTMSK0;			/**/
	__vo uint32_t HCTSIZ0;				/**/
	__vo uint32_t HCDMA0;				/**/
	__vo uint32_t HCCHAR1;				/**/
	__vo uint32_t HCSPLT1;				/**/
	__vo uint32_t HCINT1;				/**/
	__vo uint32_t HCINTMSK1;			/**/
	__vo uint32_t HCTSIZ1;				/**/
	__vo uint32_t HCDMA1;				/**/
	__vo uint32_t RESERVED2[75];		/**/
	__vo uint32_t HCCHAR11;				/**/
	__vo uint32_t HCSPLT11;				/**/
	__vo uint32_t HCINT11;				/**/
	__vo uint32_t HCINTMSK11;			/**/
	__vo uint32_t HCTSIZ11;				/**/
	__vo uint32_t HCDMA11;				/**/
	__vo uint32_t RESERVED3[27];		/**/
	__vo uint32_t HCCHAR15;				/**/
	__vo uint32_t HCSPLT15;				/**/
	__vo uint32_t HCINT15;				/**/
	__vo uint32_t HCINTMSK15;			/**/
	__vo uint32_t HCTSIZ15;				/**/
	__vo uint32_t HCDMA15;				/**/
	__vo uint32_t DCFG;					/**/
	__vo uint32_t DCTL;					/**/
	__vo uint32_t DSTS;					/**/
	__vo uint32_t DIEPMSK;				/**/
	__vo uint32_t DOEPMSK;				/**/
	__vo uint32_t DAINT;				/**/
	__vo uint32_t DAINTMSK;				/**/
	__vo uint32_t DVBUSDIS;				/**/
	__vo uint32_t DVBUSPULSE;			/**/
	__vo uint32_t DTHRCTL;				/**/
	__vo uint32_t DIEPEMPMSK;			/**/
	__vo uint32_t DEACHINT;				/**/
	__vo uint32_t DEACHINTMSK;			/**/
	__vo uint32_t HS_DIEPEACHMSK1;		/**/
	__vo uint32_t HS_DOEPEACHMSK1;		/**/
	__vo uint32_t DIEPCTL0;				/**/
	__vo uint32_t DIEPINT0;				/**/
	__vo uint32_t DIEPTSIZ0;			/**/
	__vo uint32_t DIEPDMA;				/**/
	__vo uint32_t DTXFSTS0;				/**/
	__vo uint32_t DIEPCTL1;				/**/
	__vo uint32_t DIEPINT1;				/**/
	__vo uint32_t DIEPTSIZ1;			/**/
	__vo uint32_t DTXFSTS1;				/**/
	__vo uint32_t DIEPCTL2;				/**/
	__vo uint32_t DIEPCTL5;				/**/
	__vo uint32_t DIEPINT5;				/**/
	__vo uint32_t DTXFSTS5;				/**/
	__vo uint32_t DIEPCTL7;				/**/
	__vo uint32_t DIEPTSIZ5;			/**/
	__vo uint32_t DIEPINT7;				/**/
	__vo uint32_t DIEPTSIZ7;			/**/
	__vo uint32_t DTXFSTS7;				/**/
	__vo uint32_t DOEPCTL0;				/**/
	__vo uint32_t DOEPINT0;				/**/
	__vo uint32_t DOEPTSIZ0;			/**/
	__vo uint32_t DOEPDMA0;				/**/
	__vo uint32_t DOEPCTL1;				/**/
	__vo uint32_t DOEPINT1;				/**/
	__vo uint32_t DOEPTSIZ1;			/**/
	__vo uint32_t DOEPDMA1;				/**/
	__vo uint32_t DOEPCTL5;				/**/
	__vo uint32_t DOEPINT5;				/**/
	__vo uint32_t DOEPTSIZ5;			/**/
	__vo uint32_t DOEPCTL8;				/**/
	__vo uint32_t DOEPINT8;				/**/
	__vo uint32_t DOEPTSIZ8;			/**/
	__vo uint32_t DOEPMA8;				/**/
	__vo uint32_t PCGCCTL;				/**/

}USB_OTG_RegDef_t;

#define USB_OTG_FS	( ( USB_OTG_RegDef_t*) USB_OTG_FS_BASEADDR )
#define USB_OTG_HS	( ( USB_OTG_RegDef_t*) USB_OTG_HS_BASEADDR )


/*>>>HDMI Structure<<<*/

typedef struct{

	__vo uint32_t CR;				/**/
	__vo uint32_t CFGR;				/**/
	__vo uint32_t TXDR;				/**/
	__vo uint32_t RXDR;				/**/
	__vo uint32_t ISR;				/**/
	__vo uint32_t IER;				/**/

}HDMI_RegDef_t;

#define HDMI	( ( HDMI_RegDef_t*) HDMI_CEC_BASEADDR )


/*>>>Debug Structure<<<*/

typedef struct{

	__vo uint32_t IDCODE;				/**/
	__vo uint32_t CR;					/**/
	__vo uint32_t APB1_FZ;				/**/
	__vo uint32_t APB2_FZ;				/**/


}Debug_RegDef_t;

//#define DEBUG	( ( Debug_RegDef_t*) DBG_BASEADDR )


#endif /* INC_STM32F446XX_H_ */
