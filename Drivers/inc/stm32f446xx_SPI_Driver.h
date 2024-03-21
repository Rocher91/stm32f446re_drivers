#ifndef INC_STM32F446XX_SPI_DRIVER_H_
#define INC_STM32F446XX_SPI_DRIVER_H_

#include "stm32f446xx.h"

typedef struct{

	uint8_t SPI_DeviceMode;
	uint8_t SPI_BusConfig;
	uint8_t SPI_SclkSpeed;
	uint8_t SPI_DFF;
	uint8_t SPI_CPOL;
	uint8_t SPI_CPHA;
	uint8_t SPI_SSM;
	
}SPI_Config_t;

typedef struct{

	SPI_RegDef_t* pSPIx;
	SPI_Config_t SPICOnfig;
}SPI_Handle_t;

/*
* @SPI_DeviceMode
*/

#define SPI_DEVICE_MODE_MASTER 	1
#define SPI_DEVICE_MODE_SLAVE 	0

/*
* @SPI_BusConfig
*/

#define SPI_BUS_CONFIG_FULL_DUPLEX 		1
#define SPI_BUS_CONFIG_HALF_DUPLEX 		2
#define SPI_BUS_CONFIG_SIMPLEX_RXONLY 4

/*
* @SPI_SclkSpeed
*/

#define SPI_SPICLK_PCLK_DIV_2			0
#define SPI_SPICLK_PCLK_DIV_4			1
#define SPI_SPICLK_PCLK_DIV_8			2
#define SPI_SPICLK_PCLK_DIV_16		3
#define SPI_SPICLK_PCLK_DIV_32		4
#define SPI_SPICLK_PCLK_DIV_64		5
#define SPI_SPICLK_PCLK_DIV_128		6
#define SPI_SPICLK_PCLK_DIV_256		7


/*
* @SPI_DFF
*/

#define SPI_DFF_8BITS 	0
#define SPI_DFF_16BITS 	1

/*
* @SPI_CPOL
*/

#define SPI_CPOL_HIGH 	0
#define SPI_CPOL_LOW 		1

/*
* @SPI_CPHA
*/

#define SPI_CPHA_HIGH 	0
#define SPI_CPHA_LOW 		1

/*
* @SPI_SSM
*/

#define SPI_SSM_HW 		0
#define SPI_SSM_SW		1


/*
 * Peripheral Clock Setup
 */
void SPI_PerCLKControl( SPI_RegDef_t *pSPIx, uint8_t Enable_Disable );

/*
 * Init and De-init
 */

void SPI_Init(SPI_Handle_t *pSPIHandle );
void SPI_DeInit( SPI_RegDef_t *pSPIx );


/*
 * Data Send and Receive
 */
	
	void SPI_Write(SPI_RegDef_t *pSPIx , uint8_t *pTxBuffer,uint32_t Len);
	void SPI_Read(SPI_RegDef_t *pSPIx,uint8_t *pRxBuffer,uint32_t Len);

/*
 * IRQ Configuration and ISR handling
 */
 
void SPI_IRQInterruptConfig( uint8_t IRQNumber, uint8_t Enable_Disable);
void SPI_IRQConfigPriority( uint8_t IRQNumber, uint32_t IRQPriority );
void SPI_IRQHandling( SPI_Handle_t *pSPIHandle );

 /*
 * Other Peripheral Control APIs
 */
 
 uint8_t SPI_getFlagSTatus(SPI_RegDef_t *pSPIx,uint32_t FlagName);
 
#endif