
#include "stm32f446xx_SPI_Driver.h"


static void spi_txe_interrupt_handle(SPI_Handle_t* pSPIHandle){
	
	//2. check the DFF bit in CR1
			if( (pSPIHandle->pSPIx->CR[0]&(1<< SPI_CR1_DFF )) ){	//OK
			
			
				//16 bit DFF
				// 1. Load the data in to DR
				pSPIHandle->pSPIx->DR = *( (uint16_t *) pSPIHandle->pTxBuffer );
				//pSPIHandle->TxLen--;
				//pSPIHandle->TxLen--;
				pSPIHandle->TxLen-=2;
				
				(uint16_t *) pSPIHandle->pTxBuffer++;
				
			}
			else{
				//8 bit DFF
				pSPIHandle->pSPIx->DR = *pSPIHandle->pTxBuffer;
				pSPIHandle->TxLen--;
				pSPIHandle->pTxBuffer++;
			}
			if(pSPIHandle->TxLen == 0){
				
				//TxLen is zero, co close the SPI transmission and inform the application that
				// Tx is over.

				SPI_CloseTransmission(pSPIHandle);
				SPI_ApplicationEventCallback(pSPIHandle,SPI_EVENT_TX_CMPLT);
				
			}
}
static void spi_rxne_interrupt_handle(SPI_Handle_t* pSPIHandle){

		if( (pSPIHandle->pSPIx->CR[0]&(1<< SPI_CR1_DFF )) ){	//OK
			
			
				//16 bit DFF
				// 1. Load the data in to DR
				*( (uint16_t *) pSPIHandle->pRxBuffer ) = (uint16_t) pSPIHandle->pSPIx->DR;
			
				pSPIHandle->RxLen-=2;
				pSPIHandle->pRxBuffer--;
				pSPIHandle->pRxBuffer--;
				
			}
			else{
				//8 bit DFF
				*(pSPIHandle->pRxBuffer ) = (uint8_t) pSPIHandle->pSPIx->DR;
				pSPIHandle->RxLen--;
				pSPIHandle->pRxBuffer++;
			}
			if(pSPIHandle->RxLen == 0){
				
				//RxLen is zero, co close the SPI transmission and inform the application that
				// Rx is over.
				SPI_CloseReception(pSPIHandle);
				SPI_ApplicationEventCallback(pSPIHandle,SPI_EVENT_RX_CMPLT);
				
			}
}
static void spi_ovr_err_interrupt_handle(SPI_Handle_t* pSPIHandle){

	uint8_t temp = 0;
	
	// 1. Clear the Ovr flag 
	if (pSPIHandle->TxState != SPI_BUSY_TX){
		
		temp = pSPIHandle->pSPIx->DR;
		temp = pSPIHandle->pSPIx->SR;
	}
	(void)temp;
	// 2. Inform the application
	SPI_ApplicationEventCallback(pSPIHandle,SPI_EVENT_OVR_ERR);
}

void SPI_ClearOVRFlag(SPI_RegDef_t *pSPIx){
	
	uint8_t temp = 0;
	
	temp = pSPIx->DR;
	temp = pSPIx->SR;
	
	(void)temp;
	
	
}

void SPI_CloseTransmission(SPI_Handle_t* pSPIHandle){
				
	// Tx is over.
	pSPIHandle->pSPIx->CR[1] &= ~(1 << SPI_CR2_TXBUFFER_EMPTY_INTERRUPT_ENABLE);
	pSPIHandle->pTxBuffer = NULL;
	pSPIHandle->TxLen = 0;
	pSPIHandle->TxState = SPI_READY;
 }

void SPI_CloseReception(SPI_Handle_t* pSPIHandle){
				
	// Rx is over.
	pSPIHandle->pSPIx->CR[1] &= ~(1 << SPI_CR2_RXBUFFER_NEMPTY_INTERRUPT_ENABLE);
	pSPIHandle->pRxBuffer = NULL;
	pSPIHandle->RxLen = 0;
	pSPIHandle->RxState = SPI_READY;
 }
 
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
void SPI_DeInit( SPI_Handle_t *pSPIHandle ){
	
	if(pSPIHandle->pSPIx == SPI1){
		RESET_SPI1();
	}
	else if(pSPIHandle->pSPIx == SPI2){
		RESET_SPI2();
	}
	else if(pSPIHandle->pSPIx == SPI3){
		RESET_SPI3();
	}
	else if(pSPIHandle->pSPIx == SPI4){
		RESET_SPI4();
	}
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


void SPI_WriteIT(SPI_Handle_t *pSPIHandle , uint8_t *pTxBuffer,uint32_t Len){
	
	uint8_t state = pSPIHandle->TxState;
	
	if(state != SPI_BUSY_TX ){
	
		//1. Save the TXBuffer address and Len information in some global variables.
		
		pSPIHandle->pTxBuffer = pTxBuffer;
		pSPIHandle->TxLen 		= Len;
		
		//2. Mark the SPI state as busy in transmission so that no other code can take over some SPPI peripheral until transmission is over.
		
		pSPIHandle->TxState = SPI_BUSY_TX;
		
		
		//3. Enable the TXEIE contol bit to get interrupt whenever TXE flag is set in SR.
		
		pSPIHandle->pSPIx->CR[1] |= (1<< SPI_CR2_TXBUFFER_EMPTY_INTERRUPT_ENABLE);
		
		//4. Data Transmission will be handled by the ISR code.
	}
	
	
}
void SPI_ReadIT(SPI_Handle_t *pSPIHandle,uint8_t *pRxBuffer,uint32_t Len){
		
	uint8_t state = pSPIHandle->RxState;
	
	if(state != SPI_BUSY_RX ){
	
		//1. Save the TXBuffer address and Len information in some global variables.
		
		pSPIHandle->pRxBuffer = pRxBuffer;
		pSPIHandle->RxLen 		= Len;
		
		//2. Mark the SPI state as busy in transmission so that no other code can take over some SPPI peripheral until transmission is over.
		
		pSPIHandle->RxState = SPI_BUSY_RX;
		
		
		//3. Enable the TXEIE contol bit to get interrupt whenever TXE flag is set in SR.
		
		pSPIHandle->pSPIx->CR[1] |= (1<< SPI_CR2_RXBUFFER_NEMPTY_INTERRUPT_ENABLE);
		
		//4. Data Transmission will be handled by the ISR code.
	}
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
 
	uint8_t temp1=0,temp2=0;
	
		//first lets check for TXE
		
	temp1 = pSPIHandle->pSPIx->SR & (1 << SPI_SR_TXBUFFER_EMPTY);
	temp2 = pSPIHandle->pSPIx->CR[1] & (1 << SPI_CR2_TXBUFFER_EMPTY_INTERRUPT_ENABLE);
	
	if( temp1 && temp2 ){
	
		//handle TXE		
		spi_txe_interrupt_handle(pSPIHandle);

	}
	
	temp1 = pSPIHandle->pSPIx->SR & (1 << SPI_SR_RXBUFFER_NEMPTY);
	temp2 = pSPIHandle->pSPIx->CR[1] & (1 << SPI_CR2_RXBUFFER_NEMPTY_INTERRUPT_ENABLE);
	
	if( temp1 && temp2 ){
	
		//handle TXE		
		spi_rxne_interrupt_handle(pSPIHandle);

	}
	// check for ovr flag
	temp1 = pSPIHandle->pSPIx->SR & (1 << SPI_SR_OVERRUN);
	temp2 = pSPIHandle->pSPIx->CR[1] & (1 << SPI_CR2_ERROR_INTERRUPT_ENABLE);
	
	if( temp1 && temp2 ){
	
		//handle TXE		
		spi_ovr_err_interrupt_handle(pSPIHandle);

	}
	
	
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
 
__weak void SPI_ApplicationEventCallback(SPI_Handle_t*pSPIHandle,uint8_t AppEv){}