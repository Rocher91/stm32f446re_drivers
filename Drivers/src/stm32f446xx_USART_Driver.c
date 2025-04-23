/*
 * stm32f446xx_USART_Driver.c
 *
 *  Created on: April 23, 2025
 *      Author: Xavier.Rocher
 */


#include "stm32f446xx_USART_Driver.h"
#include "stm32f446xx_Clocks.h"


/*********************************************************************
 * @fn      		  - USART_Init
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
void USART_Init(USART_Handle_t *pUSARTHandle)
{

	//Temporary variable
	uint32_t tempreg=0;

/******************************** Configuration of CR1******************************************/

	//Implement the code to enable the Clock for given USART peripheral
	 USART_PeripheralClockControl(pUSARTHandle->pUSARTx,ENABLE);

	//Enable USART Tx and Rx engines according to the USART_Mode configuration item
	if ( pUSARTHandle->USART_Config.Mode == USART_MODE_ONLY_RX)
	{
		//Implement the code to enable the Receiver bit field 
		tempreg|= (1 << USART_CR1_RE);
	}
    else if (pUSARTHandle->USART_Config.Mode == USART_MODE_ONLY_TX)
	{
		//Implement the code to enable the Transmitter bit field 
		tempreg |= ( 1 << USART_CR1_TE );

	}
    else if (pUSARTHandle->USART_Config.Mode == USART_MODE_TXRX)
	{
		//Implement the code to enable the both Transmitter and Receiver bit fields 
		tempreg |= ( ( 1 << USART_CR1_TE) | ( 1 << USART_CR1_RE) );
	}

    //Implement the code to configure the Word length configuration item 
	tempreg |= pUSARTHandle->USART_Config.WordLength << USART_CR1_M ;


    //Configuration of parity control bit fields
	if ( pUSARTHandle->USART_Config.ParityControl == USART_PARITY_EN_EVEN)
	{
		//Implement the code to enale the parity control 
		tempreg |= ( 1 << USART_CR1_PCE);

		//Implement the code to enable EVEN parity 
		//Not required because by default EVEN parity will be selected once you enable the parity control 
        tempreg &= ~( 1 << USART_CR1_PS);


	}else if (pUSARTHandle->USART_Config.ParityControl == USART_PARITY_EN_ODD )
	{
		//Implement the code to enable the parity control 
	    tempreg |= ( 1 << USART_CR1_PCE);

	    //Implement the code to enable ODD parity 
	    tempreg |= ( 1 << USART_CR1_PS);

	}

   //Program the CR1 register 
	pUSARTHandle->pUSARTx->CR[0] = tempreg;

/******************************** Configuration of CR2******************************************/

	tempreg=0;

	//Implement the code to configure the number of stop bits inserted during USART frame transmission 
	tempreg |= pUSARTHandle->USART_Config.N_StopBits << USART_CR2_STOP;

	//Program the CR2 register 
	pUSARTHandle->pUSARTx->CR[1] = tempreg;

/******************************** Configuration of CR3******************************************/

	tempreg=0;
	
	//Configuration of USART hardware flow control 
	if ( pUSARTHandle->USART_Config.HW_FlowControl == USART_HW_FLOW_CONTROL_CTS)
	{
		//Implement the code to enable CTS flow control 
		tempreg |= ( 1 << USART_CR3_CTSE);


	}else if (pUSARTHandle->USART_Config.HW_FlowControl == USART_HW_FLOW_CONTROL_RTS)
	{
		//Implement the code to enable RTS flow control 
		tempreg |= ( 1 << USART_CR3_RTSE);

	}else if (pUSARTHandle->USART_Config.HW_FlowControl == USART_HW_FLOW_CONTROL_CTS_RTS)
	{
		//Implement the code to enable both CTS and RTS Flow control 
		tempreg |= ( ( 1 << USART_CR3_CTSE) | ( 1 << USART_CR3_RTSE) );
	}


	pUSARTHandle->pUSARTx->CR[2] = tempreg;

/******************************** Configuration of BRR(Baudrate register)******************************************/

	//Implement the code to configure the baud rate
	//We will cover this in the lecture. No action required here 
	
	USART_SetBaudRate(pUSARTHandle->pUSARTx, pUSARTHandle->USART_Config.Baudrate);

}

/*********************************************************************
 * @fn      		  - USART_PeripheralClockControl
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
void USART_PeripheralClockControl( USART_RegDef_t * pUSARTx, uint8_t Enable )
{
   if ( Enable == ENABLE)
   {
        if ( pUSARTx == USART1 )
        {
            USART1_PCLCK_EN();
        }
        else if ( pUSARTx == USART2)
        {
            USART2_PCLCK_EN();
        }
        else if ( pUSARTx == USART3)
        {
            USART3_PCLCK_EN();
        }
        else if ( pUSARTx == USART4)
        {
            UART4_PCLCK_EN();
        }
        else if ( pUSARTx ==USART5 )
        {
            UART5_PCLCK_EN();
        }
        else if ( pUSARTx == USART6 )
        {
            USART6_PCLCK_EN();
        }
   }
   else if ( Enable == DISABLE)
   {
        if ( pUSARTx == USART1 )
        {
            USART1_PCLCK_DIS();
        }
        else if ( pUSARTx == USART2)
        {
            USART2_PCLCK_DIS();
        }
        else if ( pUSARTx == USART3)
        {
            USART3_PCLCK_DIS();
        }
        else if ( pUSARTx == USART4)
        {
            UART4_PCLCK_DIS();
        }
        else if ( pUSARTx ==USART5 )
        {
            UART5_PCLCK_DIS();
        }
        else if ( pUSARTx == USART6 )
        {
            USART6_PCLCK_DIS();
        }
    }
}
/*********************************************************************
 * @fn      		  - USART_DeInit
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
void USART_DeInit(USART_RegDef_t *pUSARTx)
{
	 if( pUSARTx == USART1 )
    {
		RESET_USART1();
	}
    else if( pUSARTx == USART2 )
    {
		RESET_UART2();
	}
  else if( pUSARTx == USART3 )
  {
		RESET_UART3();
	}
	else if( pUSARTx == USART4 )
  {
		RESET_UART4();
	}
	else if( pUSARTx == USART5 )
  {
		RESET_UART5();
	}
	else if( pUSARTx == USART6 )
  {
		RESET_USART6();
	}
}

void USART_SetBaudRate(USART_RegDef_t *pUSARTx, uint32_t BaudRate)
{

	//Variable to hold the APB clock
	uint32_t PCLKx;

	uint32_t usartdiv;

	//variables to hold Mantissa and Fraction values
	uint32_t M_part,F_part;

  uint32_t tempreg=0;

  //Get the value of APB bus clock in to the variable PCLKx
  if(pUSARTx == USART1 || pUSARTx == USART6)
  {
	   //USART1 and USART6 are hanging on APB2 bus
	   PCLKx = RCC_GetAPB2Clk();
  }else
  {
	   PCLKx = RCC_GetAPB1Clk();
  }

  //Check for OVER8 configuration bit
  if(pUSARTx->CR[0] & (1 << USART_CR1_OVER8))
  {
	   //OVER8 = 1 , over sampling by 8
	   usartdiv = ((25 * PCLKx) / (2 *BaudRate));
  }else
  {
	   //over sampling by 16
	   usartdiv = ((25 * PCLKx) / (4 *BaudRate));
  }

  //Calculate the Mantissa part
  M_part = usartdiv/100;

  //Place the Mantissa part in appropriate bit position . refer USART_BRR
  tempreg |= M_part << 4;

  //Extract the fraction part
  F_part = (usartdiv - (M_part * 100));

  //Calculate the final fractional
  if(pUSARTx->CR[0] & ( 1 << USART_CR1_OVER8))
   {
	  //OVER8 = 1 , over sampling by 8
	  F_part = ((( F_part * 8)+ 50) / 100)& ((uint8_t)0x07);

   }else
   {
	   //over sampling by 16
	   F_part = ((( F_part * 16)+ 50) / 100) & ((uint8_t)0x0F);

   }

  //Place the fractional part in appropriate bit position . refer USART_BRR
  tempreg |= F_part;

  //copy the value of tempreg in to BRR register
  pUSARTx->BRR = tempreg;
}

/*********************************************************************
 * @fn      		  - USART_SendData
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

void USART_SendData(USART_Handle_t *pUSARTHandle, uint8_t *pTxBuffer, uint32_t Len)
{

	uint16_t *pdata;
   //Loop over until "Len" number of bytes are transferred
	for(uint32_t i = 0 ; i < Len; i++)
	{
		//Implement the code to wait until TXE flag is set in the SR
		while(! USART_GetFlagStatus(pUSARTHandle->pUSARTx,USART_TXE_FLAG));

         //Check the USART_WordLength item for 9BIT or 8BIT in a frame
		if(pUSARTHandle->USART_Config.WordLength == USART_WORDLEN_9BITS)
		{
			//if 9BIT, load the DR with 2bytes masking the bits other than first 9 bits 
			pdata = (uint16_t*) pTxBuffer;
			pUSARTHandle->pUSARTx->DR = (*pdata & (uint16_t)0x01FF);
			
			//check for USART_ParityControl
			if(pUSARTHandle->USART_Config.ParityControl == USART_PARITY_DISABLE)
			{
				//No parity is used in this transfer. so, 9bits of user data will be sent
				//Implement the code to increment pTxBuffer twice 
				pTxBuffer++;
				pTxBuffer++;
			}
			else
			{
				//Parity bit is used in this transfer . so , 8bits of user data will be sent
				//The 9th bit will be replaced by parity bit by the hardware
				pTxBuffer++;
			}
		}
		else
		{
			//This is 8bit data transfer 
			pUSARTHandle->pUSARTx->DR = (*pTxBuffer  & (uint8_t)0xFF);
			
			//Implement the code to increment the buffer address
			pTxBuffer++;
		}
	}

	//Implement the code to wait till TC flag is set in the SR
	while( ! USART_GetFlagStatus(pUSARTHandle->pUSARTx,USART_TX_COMPLETE_FLAG));
}


/*********************************************************************
 * @fn      		  - USART_ReceiveData
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
void USART_ReceiveData(USART_Handle_t *pUSARTHandle, uint8_t *pRxBuffer, uint32_t Len)
{
   //Loop over until "Len" number of bytes are transferred
	for(uint32_t i = 0 ; i < Len; i++)
	{
		//Implement the code to wait until RXNE flag is set in the SR
		while(! USART_GetFlagStatus(pUSARTHandle->pUSARTx,USART_RXNE_FLAG));

		//Check the USART_WordLength to decide whether we are going to receive 9bit of data in a frame or 8 bit
		if(pUSARTHandle->USART_Config.WordLength == USART_WORDLEN_9BITS)
		{
			//We are going to receive 9bit data in a frame

			//check are we using USART_ParityControl control or not
			if(pUSARTHandle->USART_Config.ParityControl == USART_PARITY_DISABLE )
			{
				//No parity is used. so, all 9bits will be of user data

				//read only first 9 bits. so, mask the DR with 0x01FF
				*((uint16_t*) pRxBuffer) = (pUSARTHandle->pUSARTx->DR  & (uint16_t)(0x01FF));

				//Now increment the pRxBuffer two times
				pRxBuffer++;
				pRxBuffer++;
			}
			else
			{
				//Parity is used, so, 8bits will be of user data and 1 bit is parity
				 *pRxBuffer = (pUSARTHandle->pUSARTx->DR  & (uint8_t)0xFF);
				 
				 //Increment the pRxBuffer
				pRxBuffer++;
			}
		}
		else
		{
			//We are going to receive 8bit data in a frame

			//check are we using USART_ParityControl control or not
			if(pUSARTHandle->USART_Config.ParityControl == USART_PARITY_DISABLE)
			{
				//No parity is used , so all 8bits will be of user data

				//read 8 bits from DR
				 *pRxBuffer = pUSARTHandle->pUSARTx->DR;
			}

			else
			{
				//Parity is used, so , 7 bits will be of user data and 1 bit is parity

				//read only 7 bits , hence mask the DR with 0X7F
				 *pRxBuffer = (uint8_t) (pUSARTHandle->pUSARTx->DR  & (uint8_t)0x7F);

			}

			//increment the pRxBuffer
			pRxBuffer++;
		}
	}

}

/*********************************************************************
 * @fn      		  - USART_SendDataIT
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
uint8_t USART_SendDataIT(USART_Handle_t *pUSARTHandle,uint8_t *pTxBuffer, uint32_t Len)
{

}

/*********************************************************************
 * @fn      		  - USART_ReceiveDataIT
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
uint8_t USART_ReceiveDataIT(USART_Handle_t *pUSARTHandle, uint8_t *pRxBuffer, uint32_t Len)
{

}


/*********************************************************************
 * @fn      		  - USART_IRQInterruptConfig
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
void USART_IRQInterruptConfig(uint8_t IRQNumber, uint8_t Enable)
{

}

/*********************************************************************
 * @fn      		  - USART_IRQPriorityConfig
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
void USART_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority)
{

}

/*********************************************************************
 * @fn      		  - USART_IRQHandling
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
void USART_IRQHandling(USART_Handle_t *pHandle)
{

}


/*********************************************************************
 * @fn      		  - USART_PeripheralControl
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
void USART_PeripheralControl( USART_RegDef_t * pUSARTx, uint8_t Enable )
{

}

/*********************************************************************
 * @fn      		  - USART_GetFlagStatus
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
uint8_t USART_GetFlagStatus( USART_RegDef_t * pUSARTx, uint8_t StatusFlagName )
{
		if( pUSARTx->SR & StatusFlagName )
    {
        return FLAG_SET;
    }
    return FLAG_RESET; 
}

/*********************************************************************
 * @fn      		  - USART_ClearFlagStatus
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
void USART_ClearFlagStatus( USART_RegDef_t * pUSARTx, uint8_t StatusFlagName )
{
		pUSARTx->SR &= ~(1 << StatusFlagName);
}
