
#include "stm32f446xx_SPI_Driver.h"

/*********************************************************************
 * @fn      		  - SPI_PerCLKControl
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -

 */
 
void SPI_PerCLKControl( SPI_RegDef_t *pSPIx, uint8_t Enable_Disable ){
	
	if (Enable_Disable == ENABLE){
		
		if (pSPIx == SPI1){
				SPI1_PCLCK_EN();
		}
		else if (pSPIx == SPI2){
				SPI2_PCLCK_EN();
		}
		else if (pSPIx == SPI3){
				SPI3_PCLCK_EN();
		}
		else if (pSPIx == SPI4){
				SPI4_PCLCK_EN();
		}
	}
	else if (Enable_Disable == DISABLE){
	
		if (pSPIx == SPI1){
				SPI1_PCLCK_DIS();
		}
		else if (pSPIx == SPI2){
				SPI2_PCLCK_DIS();
		}
		else if (pSPIx == SPI3){
				SPI3_PCLCK_DIS();
		}
		else if (pSPIx == SPI4){
				SPI4_PCLCK_DIS();
		}
	}
	
}



/*********************************************************************
 * @fn      		  - SPI_Init
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -

 */

void SPI_Init(SPI_Handle_t *pSPIHandle ){
	
	uint32_t tempreg = 0;
	
	SPI_PerCLKControl(pSPIHandle->pSPIx,ENABLE); //OK
	
	//1. Configure the device Mode
	
	tempreg |=  (uint32_t)(pSPIHandle->SPICOnfig.SPI_DeviceMode << SPI_CR1_MASTER_SELECTION) ; //OK
	
	//2. Configure the BusConfig
	
	if( pSPIHandle->SPICOnfig.SPI_BusConfig == SPI_BUS_CONFIG_FULL_DUPLEX ){	//OK
		
		//BIDI Mode should be cleared
		tempreg &= (uint32_t) ~(1<<SPI_CR1_BIDIMODE);	//OK
		
	}
	else if( pSPIHandle->SPICOnfig.SPI_BusConfig == SPI_BUS_CONFIG_HALF_DUPLEX ){	//OK
		
		//BIDI Mode should be set
		tempreg |= (1<<SPI_CR1_BIDIMODE);		//OK
	}
	else if( pSPIHandle->SPICOnfig.SPI_BusConfig == SPI_BUS_CONFIG_SIMPLEX_RXONLY){	//OK
		
		//BIDI Mode should be cleared
		tempreg &= (uint32_t) ~(1<<SPI_CR1_BIDIMODE);	//OK
		//RXONLY bit must be set
		tempreg |= (1<<SPI_CR1_RXONLY);		//OK
	
	}
	
	
	//3. Configure the CPHA
	tempreg |= (uint32_t)( pSPIHandle->SPICOnfig.SPI_CPHA << SPI_CR1_CPHA );	//OK
	
	//4. Configure the CPOL
	tempreg |= (uint32_t)( pSPIHandle->SPICOnfig.SPI_CPOL << SPI_CR1_CPOL );	//OK
	
	//5. Configure the DFF
	tempreg |= (uint32_t)( pSPIHandle->SPICOnfig.SPI_DFF << SPI_CR1_DFF );	//OK
	
	//6. Configure the SMM
	tempreg |= (uint32_t)( pSPIHandle->SPICOnfig.SPI_SSM << SPI_CR1_SSM );	//OK
	
	//7. Configure the Baudrate
	tempreg |= (uint32_t)( pSPIHandle->SPICOnfig.SPI_SclkSpeed << SPI_CR1_BAUDRATE );	//OK

	
	pSPIHandle->pSPIx->CR[0] = tempreg;
		
}
void SPI_DeInit( SPI_RegDef_t *pSPIx ){

}


/*
 * Data Send and Receive
 */
	
void SPI_Write(SPI_RegDef_t *pSPIx , uint8_t *pTxBuffer,uint32_t Len){
		
		while(Len>0){
			
			//1. Wait until TXE is set
			
			while( SPI_getFlagSTatus(pSPIx,SPI_TXBUFFER_EMPTY_FLAG) == FLAG_RESET );  //OK
			
			//2. check the DFF bit in CR1
			if( (pSPIx->CR[0]&(1<< SPI_CR1_DFF )) ){	//OK
			
			
				//16 bit DFF
				// 1. Load the data in to DR
				pSPIx->DR = *( (uint16_t *) pTxBuffer );
				//Len-=2;
				Len--;
				Len--;
				
				(uint16_t *) pTxBuffer++;
				
			}
			else{
				//8 bit DFF
				pSPIx->DR = *pTxBuffer;
				Len--;
				pTxBuffer++;
			}
			
		}
		
	}
void SPI_Read(SPI_RegDef_t *pSPIx,uint8_t *pRxBuffer,uint32_t Len){
		
		while(Len >0){
			
			//1. Wait until RXNE is non empty
			
			while( SPI_getFlagSTatus(pSPIx,SPI_RXBUFFER_EMPTY_FLAG) == FLAG_SET );  
			
			//2. check the DFF bit in CR1
			if( (pSPIx->CR[0]&(1<< SPI_CR1_DFF )) ){
				
				*((uint16_t*)pRxBuffer)	= pSPIx->DR;
				Len-=2;
				
				(uint16_t*)pRxBuffer++;
			}
			else{
				
					//8 bit DFF
					*(pRxBuffer)	= pSPIx->DR;
					Len--;
					pRxBuffer++;
			}
		}


}


void SPI_WriteIT(SPI_RegDef_t *pSPIx , uint8_t *pTxBuffer,uint32_t Len){
	
}
void SPI_ReadIT(SPI_RegDef_t *pSPIx,uint8_t *pRxBuffer,uint32_t Len){

}

/*
 * IRQ Configuration and ISR handling
 */
 
//IRQ Configuration and ISR handling
/********************************************************************************
 * @fn			- GPIO_IRQInterruptConfig
 *
 * @brief		-
 *
 * @param[in]	-	IRQNumber
 * @param[in]	-	Enable_Disable
 *
 * @return
 *
 * @Note
 *
 * */
void SPI_IRQInterruptConfig( uint8_t IRQNumber, uint8_t Enable_Disable){

	if( Enable_Disable == ENABLE){

		if( IRQNumber <= 31){
			//Program ISER0 register
			*NVIC_ISER0 |= (1 << IRQNumber);
		}
		else if( IRQNumber > 31 && IRQNumber < 64 ){

			//Program ISER1 register
			*NVIC_ISER1 |= (1 << ( IRQNumber % 32) );
		}
		else if( IRQNumber >= 64 && IRQNumber < 96 ){

			//Program ISER2 register
			*NVIC_ISER2 |= (1 << ( IRQNumber % 64 ) );

		}
	}else{

		if( IRQNumber <= 31){

			//Program ICER0 register
			*NVIC_ICER0 |= (1 << IRQNumber);
		}
		else if( IRQNumber > 31 && IRQNumber < 64 ){

			//Program ICER1 register
			*NVIC_ICER1 |= (1 << ( IRQNumber % 32 ) );
		}
		else if( IRQNumber >= 64 && IRQNumber < 96 ){

			//Program ICER2 register
			*NVIC_ICER2 |= (1 << ( IRQNumber % 64 ) );

		}

	}

}

/********************************************************************************
 * @fn		- GPIO_IRQConfigPriority
 *
 * @brief	-
 *
 * @param[in]		-	IRQNumber
 * @param[in]		-	IRQPriority
 *
 * @return
 *
 * @Note
 *
 * */

void SPI_IRQConfigPriority( uint8_t IRQNumber, uint32_t IRQPriority ){

	// 1. first lets find out the ipr register.
	uint8_t iprx = IRQNumber / 4;
	uint8_t iprx_section = IRQNumber % 4;

	uint8_t shift_amount = ( 8 * iprx_section )+ ( 8 - NO_PR_BITS_IMPLEMENTED );

	*(NVIC_IPR_BASE + iprx  ) |= ( IRQPriority << shift_amount );
}

/********************************************************************************
 * @fn		- GPIO_IRQHandling
 *
 * @brief	-
 *
 * @param[in]
 * @param[in]
 *
 * @return
 *
 * @Note
 *
 * */
void SPI_IRQHandling( SPI_Handle_t *pSPIHandle ){
 
	
}


uint8_t SPI_getFlagSTatus(SPI_RegDef_t *pSPIx,uint32_t FlagName){	
	
	if(  pSPIx->SR & FlagName ){	
		return FLAG_SET;
	}
	else{
		return FLAG_RESET;
	}
 }

 
void SPI_Enable(SPI_RegDef_t *pSPIx,uint8_t enable){
	
	 if (enable){
			pSPIx->CR[0] |= (1<<SPI_CR1_ENABLE);	//OK
	 }
	 else{
			pSPIx->CR[0] &= ~(1<<SPI_CR1_ENABLE);	//OK
	 }
 }

void SPI_SSIConfig(SPI_RegDef_t *pSPIx,uint8_t enable){
	
	if (enable == ENABLE){
		pSPIx->CR[0] |= (1<<SPI_CR1_SSI);	//OK
	}
	else{
		pSPIx->CR[0] &= ~(1<<SPI_CR1_SSI);	//OK
	}
}

void SPI_SSOECOnfig(SPI_RegDef_t *pSPIx,uint8_t enable){

	if (enable == ENABLE){
		pSPIx->CR[1] |= (1<<SPI_CR2_SS_ENABLE);	//OK
	}
	else{
		pSPIx->CR[1] &= ~(1<<SPI_CR2_SS_ENABLE);	//OK
	}
}
 