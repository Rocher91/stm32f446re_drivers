
#include "stm32f446xx_I2C_Driver.h"
#include "stm32f446xx_Clocks.h"


void I2C_GenerateStartCondition(I2C_RegDef_t *pI2Cx) //OK
{
    pI2Cx->CR[0] |= ( 1 << I2C_CR1_START);
}

void I2C_ExecuteAddressPhaseWrite( I2C_RegDef_t *pI2Cx, uint8_t slaveAddress ) //OK
{
    slaveAddress = ( slaveAddress << 1 );
    slaveAddress &= ~(0x01);                //SlaveAddr is Slave address + r/nw bit=0

    pI2Cx->DR = slaveAddress;

}

void I2C_ExecuteAddressPhaseRead( I2C_RegDef_t *pI2Cx, uint8_t slaveAddress ) //OK
{
    slaveAddress = ( slaveAddress << 1 );
    slaveAddress |= 0x01;                   //SlaveAddr is Slave address + r/nw bit=1

    pI2Cx->DR = slaveAddress;

}

void I2C_ClearADDRFlag(I2C_Handle_t *pI2CHandle) //OK
{ 
	uint32_t dummy_read = 0;
	
	//Check for device mode
	if( pI2CHandle->pI2Cx->SR[1] & ( 1 << I2C_SR2_MSL) )
	{
			//device in master mode
			if ( pI2CHandle->TxRxState == I2C_BUSY_IN_RX  )
			{
				if( pI2CHandle->RxSize == 1)
				{
					//first disable the ack
					I2C_ManageAcking(pI2CHandle->pI2Cx,DISABLE);
					
					// Clear the ADDR Flag
					dummy_read = pI2CHandle->pI2Cx->SR[0];
					dummy_read = pI2CHandle->pI2Cx->SR[1];
					(void)dummy_read;
				}	
			}
			else
			{
				//device in slave mode
				// Clear the ADDR Flag
					dummy_read = pI2CHandle->pI2Cx->SR[0];
					dummy_read = pI2CHandle->pI2Cx->SR[1];
					(void)dummy_read;
				
			}
	}
	else
	{
		// Clear the ADDR Flag
		dummy_read = pI2CHandle->pI2Cx->SR[0];
		dummy_read = pI2CHandle->pI2Cx->SR[1];
		(void)dummy_read;
	}
}

void I2C_GenerateStopCondition(I2C_RegDef_t *pI2Cx) //OK
{
    pI2Cx->CR[0] |= ( 1 << I2C_CR1_STOP);
}


void I2C_SlaveEnableDisableCallbackEvents(I2C_RegDef_t *pI2Cx,uint8_t Enable_Disable) //OK
{
    if(Enable_Disable == ENABLE)
    {
           pI2Cx->CR[1] |= ( 1 << I2C_CR2_ITEVTEN);
           pI2Cx->CR[1] |= ( 1 << I2C_CR2_ITBUFEN);
           pI2Cx->CR[1] |= ( 1 << I2C_CR2_ITERREN);
    }else
    {
           pI2Cx->CR[1] &= ~( 1 << I2C_CR2_ITEVTEN);
           pI2Cx->CR[1] &= ~( 1 << I2C_CR2_ITBUFEN);
           pI2Cx->CR[1] &= ~( 1 << I2C_CR2_ITERREN);
    }

}

void I2C_PeripheralControl( I2C_RegDef_t *pI2Cx, uint8_t Enable_Disable ) //OK
{
    if (Enable_Disable == ENABLE)
    {
        pI2Cx->CR[0] |= ( 1 << I2C_CR1_PE ); 
    }
    else
    {
        pI2Cx->CR[0] &= ~( 1 << I2C_CR1_PE ); 
    }
}

void I2C_PerCLKControl( I2C_RegDef_t *pI2Cx, uint8_t Enable_Disable )
{
    if( Enable_Disable == ENABLE) //OK
    {
        if( pI2Cx == I2C1)
        {
            I2C1_PCLCK_EN();
        }
        else if( pI2Cx == I2C2)
        {
            I2C2_PCLCK_EN();
        }
        else if( pI2Cx == I2C3)
        {
            I2C3_PCLCK_EN();
        }

    }
    else
    {
         if( pI2Cx == I2C1)
        {
            I2C1_PCLCK_DIS();
        }
        else if( pI2Cx == I2C2)
        {
            I2C2_PCLCK_DIS();
        }
        else if( pI2Cx == I2C3)
        {
            I2C3_PCLCK_DIS();
        }
    }
}

/*
 * Init and De-init
 */

void I2C_Init(I2C_Handle_t *pI2CHandle ) //OK
{
    uint32_t tempreg    = 0;

    //Enable Clock I2C
    I2C_PerCLKControl(pI2CHandle->pI2Cx,ENABLE);
    
    // ACK Control Register
    tempreg |= ( pI2CHandle->I2C_Config.I2C_ACK_Control << I2C_CR1_ACK );
    pI2CHandle->pI2Cx->CR[0] = tempreg;

    // Set Freq Bus
    tempreg = 0;
    tempreg |= RCC_getSysClk()/1000000U; //RCC_GetAHBClk
    pI2CHandle->pI2Cx->CR[1] = ( tempreg & 0x3F );

    // Set Address
    tempreg = 0;
	tempreg |= ( pI2CHandle->I2C_Config.I2C_DeviceAddress << I2C_OAR1_ADD_7_1 );
	tempreg |=  (1 << 14);

    pI2CHandle->pI2Cx->OAR[0] |=  tempreg;

    // CCR Calculations

    uint16_t ccr_value = 0;
    tempreg = 0;

    if (pI2CHandle->I2C_Config.I2C_SCL_Speed <= I2C_SCL_SPEED_SM)
    {
        //mode is standard mode
        // TSCL = 2*CCR*TPCLK1
        // CCR = Tscl/2*TPCLK1 = FPCLK1/ 2* Fscl

        ccr_value   = ( RCC_getSysClk() / ( 2 * pI2CHandle->I2C_Config.I2C_SCL_Speed ) ); //RCC_GetAHBClk
        tempreg     |= (ccr_value & 0xFFF);

    }
    else
    {
        //mode is fast mode

        // DUTY = 0 --> CCR = FPCLK1/ 3 * Fscl
        // DUTY = 1 --> CCR = FPCLK1/ 25 * Fscl

        tempreg |= (1 << I2C_F_S);
        tempreg |= ( pI2CHandle->I2C_Config.I2C_FM_DutyCycle << I2C_DUTY );

        if ( pI2CHandle->I2C_Config.I2C_FM_DutyCycle == I2C_FM_DUTY_2)
        {
            ccr_value   = ( RCC_getSysClk() / ( 3 * pI2CHandle->I2C_Config.I2C_SCL_Speed ) ); //RCC_GetAHBClk
        }
        else
        {
            ccr_value   = ( RCC_getSysClk() / ( 25 * pI2CHandle->I2C_Config.I2C_SCL_Speed ) ); //RCC_GetAHBClk
        }
        
        tempreg |= (ccr_value & 0xFFF);
    }

    pI2CHandle->pI2Cx->CCR = tempreg;

    // Trise/TPCLK ==> (FPCLK*Trise(max))+1
    if (pI2CHandle->I2C_Config.I2C_SCL_Speed <= I2C_SCL_SPEED_SM)
    {
        //mode is standard mode
        tempreg = ( RCC_getSysClk() / 1000000U ) + 1; //RCC_GetAHBClk
    }
    else
    {
        //mode is fast
        tempreg = ( ( RCC_getSysClk() * 300 ) / 1000000000U ) + 1; //RCC_GetAHBClk
    }

    pI2CHandle->pI2Cx->TRISE = (tempreg & 0x3F); 

}

void I2C_DeInit( I2C_Handle_t *pI2CHandle )
{
    if( pI2CHandle->pI2Cx == I2C1 )
    {
		RESET_I2C1();
	}
    else if( pI2CHandle->pI2Cx == I2C2 )
    {
		RESET_I2C2();
	}
    else if( pI2CHandle->pI2Cx == I2C3 )
    {
		RESET_I2C3();
	}

}

uint8_t I2C_GetFlagStatus(I2C_RegDef_t *pI2Cx, uint32_t FlagName) //OK
{
    if( pI2Cx->SR[0] & FlagName)
    {
        return FLAG_SET;
    }
    return FLAG_RESET; 
}

void I2C_MasterReceiveData( I2C_Handle_t *pI2CHandle, uint8_t *pRxBuffer, uint8_t Len, uint8_t slaveAddress , uint8_t Sr) //OK
{
    //1. Generate the START condition.
	I2C_GenerateStartCondition(pI2CHandle->pI2Cx);
	
    //2. Confirm that start generation is completed by checking the SB flag in the SR1
    // NOTE: Until SB is cleared SCL will be stretched (pulled to LOW).
	while( I2C_GetFlagStatus( pI2CHandle->pI2Cx, I2C_SB_FLAG ) );
		
    //3. Send the address of the slave with r/nw bit set ro R(1) (total 8 bits).
	I2C_ExecuteAddressPhaseRead( pI2CHandle->pI2Cx, slaveAddress );
	
    //4. wait until address phase is completed by checking the ADDR flag in the SR1.
	while( I2C_GetFlagStatus( pI2CHandle->pI2Cx, I2C_ADDR_FLAG ) ){}

    //procedure to read only 1 byte from slave.
    if ( Len == 1)
    {
        //Disable Acking
        I2C_ManageAcking(pI2CHandle->pI2Cx,I2C_ACK_DISABLE);

        //Clear the ADDR flag.
        I2C_ClearADDRFlag(pI2CHandle);
			
        //wait RxNE becomes 1.
        while( !I2C_GetFlagStatus( pI2CHandle->pI2Cx, I2C_RxNE_FLAG ) ); //Wait till RxNE is set 

        //generate STOP condition.
        if ( Sr == I2C_DISABLE_SR)
        {
            I2C_GenerateStopCondition(pI2CHandle->pI2Cx);
        }
        
        
        //read data in to buffer.
        *pRxBuffer = pI2CHandle->pI2Cx->DR;

    }

    // procedure to read data from slave when Len>1
    if ( Len > 1)
    {
        //clear the ADDR flag.
		I2C_ClearADDRFlag(pI2CHandle);
			
        //read the data until Len becomes zero.
        for( uint32_t i = Len; i>0 ; i--)
        {	
			//wait until RxNE becomes 1
			while( !I2C_GetFlagStatus( pI2CHandle->pI2Cx, I2C_RxNE_FLAG ) ); //Wait till RxNE is set 

            if( i == 2) //if last 2 bytes are remaining
            {
                //Disable Acking
                I2C_ManageAcking(pI2CHandle->pI2Cx,DISABLE);

                //generate STOP condition
                if ( Sr == I2C_DISABLE_SR)
                {
                    I2C_GenerateStopCondition(pI2CHandle->pI2Cx);
                }
            }
						
            //read the data from data register in to buffer
			*pRxBuffer = pI2CHandle->pI2Cx->DR;
						
            //increment the buffer address
			pRxBuffer++;
        }
    }

    //re-enable ACKing	
    if( pI2CHandle->I2C_Config.I2C_ACK_Control == I2C_ACK_ENABLE)
    {
        I2C_ManageAcking(pI2CHandle->pI2Cx,ENABLE);
    }
		
}

void I2C_ManageAcking(I2C_RegDef_t *pI2Cx,uint8_t Enable_Disable) //OK
{
	if( Enable_Disable == I2C_ACK_ENABLE )
	{
		pI2Cx->CR[0] |= ( 1 << I2C_CR1_ACK);
	}
	else
	{	
		//Disable ACK
		pI2Cx->CR[0] &= ~( 1 << I2C_CR1_ACK);
	}
}


void I2C_MasterSendData(I2C_Handle_t *pI2CHandle,uint8_t *pTxbuffer, uint32_t Len, uint8_t SlaveAddr,uint8_t Sr) //OK
{
	// 1. Generate the START condition
	I2C_GenerateStartCondition(pI2CHandle->pI2Cx);

	//2. confirm that start generation is completed by checking the SB flag in the SR1
	//   Note: Until SB is cleared SCL will be stretched (pulled to LOW)
	while( !  I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_SB_FLAG)   );

	//3. Send the address of the slave with r/nw bit set to w(0) (total 8 bits )
	I2C_ExecuteAddressPhaseWrite(pI2CHandle->pI2Cx,SlaveAddr);

	//4. Confirm that address phase is completed by checking the ADDR flag in teh SR1
	while( !  I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_ADDR_FLAG)   );

	//5. clear the ADDR flag according to its software sequence
	//   Note: Until ADDR is cleared SCL will be stretched (pulled to LOW)
	I2C_ClearADDRFlag(pI2CHandle);

	//6. send the data until len becomes 0

	while(Len > 0)
	{
		while(! I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_TxE_FLAG) ); //Wait till TXE is set
		pI2CHandle->pI2Cx->DR = *pTxbuffer;
		pTxbuffer++;
		Len--;
	}

	//7. when Len becomes zero wait for TXE=1 and BTF=1 before generating the STOP condition
	//   Note: TXE=1 , BTF=1 , means that both SR and DR are empty and next transmission should begin
	//   when BTF=1 SCL will be stretched (pulled to LOW)

	while(! I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_TxE_FLAG) );

	while(! I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_BTF_FLAG) );


	//8. Generate STOP condition and master need not to wait for the completion of stop condition.
	//   Note: generating STOP, automatically clears the BTF
	if(Sr == I2C_DISABLE_SR )
		I2C_GenerateStopCondition(pI2CHandle->pI2Cx);

}


void I2C_ScanBus(I2C_Handle_t *pI2CHandle )
{
    uint8_t address = 0;
    uint8_t devices_addresses[127] = { 0 };
    
		
		
    for ( address = 0 ; address < 128 ; address++)
    {		
				//1. Generate the START condition.
				I2C_GenerateStartCondition(pI2CHandle->pI2Cx);
			
				//2. Confirm that start generation is completed by checking the SB flag in the SR1
				// NOTE: Until SB is cleared SCL will be stretched (pulled to LOW).
				while( I2C_GetFlagStatus( pI2CHandle->pI2Cx, I2C_SB_FLAG ) );
			
        if ( I2C_GetFlagStatus( pI2CHandle->pI2Cx, I2C_ADDR_FLAG ) )
        {
            devices_addresses[address] = address;
					
						//clear the ADDR flag.
						I2C_ClearADDRFlag(pI2CHandle);
        }
    }
}


/*********************************************************************
 * @fn      		  - I2C_MasterSendDataIT
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -  Complete the below code . Also include the function prototype in header file

 */


uint8_t I2C_MasterSendDataIT( I2C_Handle_t *pI2CHandle, uint8_t *pTxBuffer, uint8_t Len, uint8_t slaveAddress, uint8_t Sr) //OK
{

	uint8_t busystate = pI2CHandle->TxRxState;

	if( (busystate != I2C_BUSY_IN_TX) && (busystate != I2C_BUSY_IN_RX))
	{
		pI2CHandle->pTxBuffer   = pTxBuffer;
		pI2CHandle->TxLen       = Len;
		pI2CHandle->TxRxState   = I2C_BUSY_IN_TX;
		pI2CHandle->DevAddress  = slaveAddress;
		pI2CHandle->Sr          = Sr;

		//Implement code to Generate START Condition
		I2C_GenerateStartCondition(pI2CHandle->pI2Cx);

		//Implement the code to enable ITBUFEN Control Bit
		pI2CHandle->pI2Cx->CR[1] |= ( 1 << I2C_CR2_ITBUFEN);

		//Implement the code to enable ITEVFEN Control Bit
		pI2CHandle->pI2Cx->CR[1] |= ( 1 << I2C_CR2_ITEVTEN);

		//Implement the code to enable ITERREN Control Bit
		pI2CHandle->pI2Cx->CR[1] |= ( 1 << I2C_CR2_ITERREN);

	}

	return busystate;

}

/*********************************************************************
 * @fn      		  - I2C_MasterReceiveDataIT
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              - Complete the below code . Also include the fn prototype in header file

 */
uint8_t I2C_MasterReceiveDataIT( I2C_Handle_t *pI2CHandle, uint8_t *pRxBuffer, uint8_t Len, uint8_t slaveAddress , uint8_t Sr) //OK
{

	uint8_t busystate = pI2CHandle->TxRxState;

	if( (busystate != I2C_BUSY_IN_TX) && (busystate != I2C_BUSY_IN_RX))
	{
		pI2CHandle->pRxBuffer   = pRxBuffer;
		pI2CHandle->RxLen       = Len;
		pI2CHandle->TxRxState   = I2C_BUSY_IN_RX;
		pI2CHandle->RxSize      = Len; //Rxsize is used in the ISR code to manage the data reception 
		pI2CHandle->DevAddress  = slaveAddress;
		pI2CHandle->Sr          = Sr;

		//Implement code to Generate START Condition
		I2C_GenerateStartCondition(pI2CHandle->pI2Cx);

		//Implement the code to enable ITBUFEN Control Bit
		pI2CHandle->pI2Cx->CR[1] |= ( 1 << I2C_CR2_ITBUFEN);

		//Implement the code to enable ITEVFEN Control Bit
		pI2CHandle->pI2Cx->CR[1] |= ( 1 << I2C_CR2_ITEVTEN);

		//Implement the code to enable ITERREN Control Bit
		pI2CHandle->pI2Cx->CR[1] |= ( 1 << I2C_CR2_ITERREN);
		
	}

	return busystate;
}

static void I2C_MasterHandleTxEInterrupt( I2C_Handle_t *pI2CHandle ) //OK
{
	if( pI2CHandle->TxLen > 0 )
	{
		//1. Load the data in to DR.
		pI2CHandle->pI2Cx->DR = *(pI2CHandle->pTxBuffer);
		
		//2. decrement the TxLen
		pI2CHandle->TxLen--;
		
		//3. Increment the buffer address
		pI2CHandle->pTxBuffer++;
	}
}
static void I2C_MasterHandleRxNEInterrupt( I2C_Handle_t *pI2CHandle ) //OK
{
	
	//We have to do the data reception
		if( pI2CHandle->RxLen == 1)
		{
			*pI2CHandle->pRxBuffer = pI2CHandle->pI2Cx->DR;
			pI2CHandle->RxLen--;
		}
		else if( pI2CHandle->RxLen > 1)
		{
			if( pI2CHandle->RxLen == 2)
			{
				//Clear the ack bit
				I2C_ManageAcking(pI2CHandle->pI2Cx,DISABLE);
			}
			
			//read DR
			*pI2CHandle->pRxBuffer = pI2CHandle->pI2Cx->DR;
			pI2CHandle->pRxBuffer++;
			pI2CHandle->RxLen--;
		}
		
		if( pI2CHandle->RxLen == 0)
		{
			//close the I2C data reception and notify the application.
			
			//1. Generate the stop condition.
			if (pI2CHandle->Sr == I2C_DISABLE_SR)
			{
				I2C_GenerateStopCondition( pI2CHandle->pI2Cx );
				
			}

			//2. Close the I2C Rx.
			I2C_CloseReceiveData(pI2CHandle);

			//3. Notify the application.
			I2C_ApplicationEventCallback(pI2CHandle,I2C_EV_RX_CMPLTE);
		}

}


void I2C_CloseReceiveData(I2C_Handle_t *pI2CHandle) //OK
{
		//Implement the code to disable ITBUFEN Control Bit
		pI2CHandle->pI2Cx->CR[1] &= ~( 1 << I2C_CR2_ITBUFEN);
	
		//Implement the code to disable ITBUFEN Control Bit
		pI2CHandle->pI2Cx->CR[1] &= ~( 1 << I2C_CR2_ITEVTEN);
	
		pI2CHandle->TxRxState 	= I2C_READY;
		pI2CHandle->pRxBuffer 	= NULL;
		pI2CHandle->RxLen 		= 0;
		pI2CHandle->TxLen 		= 0;
		pI2CHandle->RxSize 		= 0;
		
		if(pI2CHandle->I2C_Config.I2C_ACK_Control == I2C_ACK_ENABLE)
		{
			I2C_ManageAcking(pI2CHandle->pI2Cx,ENABLE);
		}

}

void I2C_CloseSendData(I2C_Handle_t *pI2CHandle) //OK
{
		//Implement the code to disable ITBUFEN Control Bit
		pI2CHandle->pI2Cx->CR[1] &= ~( 1 << I2C_CR2_ITBUFEN);
	
		//Implement the code to disable ITBUFEN Control Bit
		pI2CHandle->pI2Cx->CR[1] &= ~( 1 << I2C_CR2_ITEVTEN);
	
		pI2CHandle->TxRxState 	= I2C_READY;
		pI2CHandle->pRxBuffer 	= NULL;
		pI2CHandle->RxLen 		= 0;
		pI2CHandle->RxSize 		= 0;
}


void I2C_SlaveSendData(I2C_RegDef_t *pI2C,uint8_t data) //OK
{
	pI2C->DR = data;
}

uint8_t I2C_SlaveReceiveData(I2C_RegDef_t *pI2C) //OK
{
    return (uint8_t) pI2C->DR;
}



void I2C_EV_IRQHandling(I2C_Handle_t *pI2CHandle) //OK
{
	//Interrupt handling for both master and slave mode of a device

	uint32_t temp1, temp2, temp3;

	temp1   = pI2CHandle->pI2Cx->CR[1] & ( 1 << I2C_CR2_ITEVTEN) ;
	temp2   = pI2CHandle->pI2Cx->CR[1] & ( 1 << I2C_CR2_ITBUFEN) ;

	temp3  = pI2CHandle->pI2Cx->SR[0] & ( 1 << I2C_SR1_SB);
	//1. Handle For interrupt generated by SB event
	//	Note : SB flag is only applicable in Master mode
	if(temp1 && temp3)
	{
		//The interrupt is generated because of SB event
		//This block will not be executed in slave mode because for slave SB is always zero
		//In this block lets executed the address phase
		if(pI2CHandle->TxRxState == I2C_BUSY_IN_TX)
		{
			I2C_ExecuteAddressPhaseWrite(pI2CHandle->pI2Cx,pI2CHandle->DevAddress);
		}else if (pI2CHandle->TxRxState == I2C_BUSY_IN_RX )
		{
			I2C_ExecuteAddressPhaseRead(pI2CHandle->pI2Cx,pI2CHandle->DevAddress);
		}
	}

	temp3  = pI2CHandle->pI2Cx->SR[0] & ( 1 << I2C_SR1_ADDR);
	//2. Handle For interrupt generated by ADDR event
	//Note : When master mode : Address is sent
	//		 When Slave mode   : Address matched with own address
	if(temp1 && temp3)
	{
		// interrupt is generated because of ADDR event
		I2C_ClearADDRFlag(pI2CHandle);
	}

	temp3  = pI2CHandle->pI2Cx->SR[0] & ( 1 << I2C_SR1_BTF);
	//3. Handle For interrupt generated by BTF(Byte Transfer Finished) event
	if(temp1 && temp3)
	{
		//BTF flag is set
		if(pI2CHandle->TxRxState == I2C_BUSY_IN_TX)
		{
			//make sure that TXE is also set .
			if(pI2CHandle->pI2Cx->SR[0] & ( 1 << I2C_SR1_TxE) )
			{
				//BTF, TXE = 1
				if(pI2CHandle->TxLen == 0 )
				{
					//1. generate the STOP condition
					if(pI2CHandle->Sr == I2C_DISABLE_SR)
						I2C_GenerateStopCondition(pI2CHandle->pI2Cx);

					//2. reset all the member elements of the handle structure.
					I2C_CloseSendData(pI2CHandle);

					//3. notify the application about transmission complete
					I2C_ApplicationEventCallback(pI2CHandle,I2C_EV_TX_CMPLTE);

				}
			}

		}else if (pI2CHandle->TxRxState == I2C_BUSY_IN_RX )
		{
			;
		}
	}

	temp3  = pI2CHandle->pI2Cx->SR[0] & ( 1 << I2C_SR1_STOPF);
	//4. Handle For interrupt generated by STOPF event
	// Note : Stop detection flag is applicable only slave mode . For master this flag will never be set
	//The below code block will not be executed by the master since STOPF will not set in master mode
	if(temp1 && temp3)
	{
		//STOF flag is set
		//Clear the STOPF ( i.e 1) read SR1 2) Write to CR1 )

		pI2CHandle->pI2Cx->CR[0] |= 0x0000;

		//Notify the application that STOP is detected
		I2C_ApplicationEventCallback(pI2CHandle,I2C_EV_STOP);
	}


	temp3  = pI2CHandle->pI2Cx->SR[0] & ( 1 << I2C_SR1_TxE);
	//5. Handle For interrupt generated by TXE event
	if(temp1 && temp2 && temp3)
	{
		//Check for device mode
		if(pI2CHandle->pI2Cx->SR[1] & ( 1 << I2C_SR2_MSL))
		{
			//TXE flag is set
			//We have to do the data transmission
			if(pI2CHandle->TxRxState == I2C_BUSY_IN_TX)
			{
				I2C_MasterHandleTxEInterrupt(pI2CHandle);
			}
		}else
		{
			//slave
			//make sure that the slave is really in transmitter mode
		    if(pI2CHandle->pI2Cx->SR[1] & ( 1 << I2C_SR2_TRA))
		    {
		    	I2C_ApplicationEventCallback(pI2CHandle,I2C_EV_DATA_REQ);
		    }
		}
	}

	temp3  = pI2CHandle->pI2Cx->SR[0] & ( 1 << I2C_SR1_RxNE);
	//6. Handle For interrupt generated by RXNE event
	if(temp1 && temp2 && temp3)
	{
		//check device mode .
		if(pI2CHandle->pI2Cx->SR[1] & ( 1 << I2C_SR2_MSL))
		{
			//The device is master

			//RXNE flag is set
			if(pI2CHandle->TxRxState == I2C_BUSY_IN_RX)
			{
				I2C_MasterHandleRxNEInterrupt(pI2CHandle);

			}

		}else
		{
			//slave
			//make sure that the slave is really in receiver mode
			if(!(pI2CHandle->pI2Cx->SR[1] & ( 1 << I2C_SR2_TRA)))
			{
				I2C_ApplicationEventCallback(pI2CHandle,I2C_EV_DATA_RCV);
			}
		}
	}
}



void I2C_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi) //OK
{

	if(EnorDi == ENABLE)
	{
		if(IRQNumber <= 31)
		{
			//program ISER0 register
			*NVIC_ISER0 |= ( 1 << IRQNumber );

		}else if(IRQNumber > 31 && IRQNumber < 64 ) //32 to 63
		{
			//program ISER1 register
			*NVIC_ISER1 |= ( 1 << (IRQNumber % 32) );
		}
		else if(IRQNumber >= 64 && IRQNumber < 96 )
		{
			//program ISER2 register //64 to 95
			*NVIC_ISER3 |= ( 1 << (IRQNumber % 64) );
		}
	}else
	{
		if(IRQNumber <= 31)
		{
			//program ICER0 register
			*NVIC_ICER0 |= ( 1 << IRQNumber );
		}else if(IRQNumber > 31 && IRQNumber < 64 )
		{
			//program ICER1 register
			*NVIC_ICER1 |= ( 1 << (IRQNumber % 32) );
		}
		else if(IRQNumber >= 6 && IRQNumber < 96 )
		{
			//program ICER2 register
			*NVIC_ICER3 |= ( 1 << (IRQNumber % 64) );
		}
	}

}

void I2C_IRQPriorityConfig(uint8_t IRQNumber,uint32_t IRQPriority) //OK
{
	//1. first lets find out the ipr register
	uint8_t iprx = IRQNumber / 4;
	uint8_t iprx_section  = IRQNumber %4 ;

	uint8_t shift_amount = ( 8 * iprx_section) + ( 8 - NO_PR_BITS_IMPLEMENTED) ;

	*(   NVIC_IPR_BASE + iprx ) |=  ( IRQPriority << shift_amount );

}

/*********************************************************************
 * @fn      		  - I2C_ER_IRQHandling
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

 void I2C_ER_IRQHandling(I2C_Handle_t *pI2CHandle) //OK
 {
 
     uint32_t temp1,temp2;
 
     //Know the status of  ITERREN control bit in the CR2
     temp2 = (pI2CHandle->pI2Cx->CR[1]) & ( 1 << I2C_CR2_ITERREN);
 
 
 /***********************Check for Bus error************************************/ 
     temp1 = (pI2CHandle->pI2Cx->SR[0]) & ( 1<< I2C_SR1_BERR);
     if(temp1  && temp2 )
     {
         //This is Bus error
         
         //Implement the code to clear the buss error flag 
         pI2CHandle->pI2Cx->SR[0] &= ~( 1 << I2C_SR1_BERR);
         
         //Implement the code to notify the application about the error 
        I2C_ApplicationEventCallback(pI2CHandle,I2C_ERROR_BERR);
     }
 
 /***********************Check for arbitration lost error************************************/ 
     temp1 = (pI2CHandle->pI2Cx->SR[0]) & ( 1 << I2C_SR1_ARLO );
     if(temp1  && temp2)
     {
         //This is arbitration lost error
         
         //Implement the code to clear the arbitration lost error flag
         pI2CHandle->pI2Cx->SR[0] &= ~( 1 << I2C_SR1_ARLO);

         //Implement the code to notify the application about the error 
         I2C_ApplicationEventCallback(pI2CHandle,I2C_ERROR_ARLO);
     }
 
 /***********************Check for ACK failure  error************************************/ 
 
     temp1 = (pI2CHandle->pI2Cx->SR[0]) & ( 1 << I2C_SR1_AF);
     if(temp1  && temp2)
     {
         //This is ACK failure error
         
         //Implement the code to clear the ACK failure error flag
         pI2CHandle->pI2Cx->SR[0] &= ~( 1 << I2C_SR1_AF);

         //Implement the code to notify the application about the error 
         I2C_ApplicationEventCallback(pI2CHandle,I2C_ERROR_AF);
     }
 
 /***********************Check for Overrun/underrun error************************************/
     temp1 = (pI2CHandle->pI2Cx->SR[0]) & ( 1 << I2C_SR1_OVR);
     if(temp1  && temp2)
     {
         //This is Overrun/underrun
         
         //Implement the code to clear the Overrun/underrun error flag
         pI2CHandle->pI2Cx->SR[0] &= ~( 1 << I2C_SR1_OVR);

         //Implement the code to notify the application about the error 
         I2C_ApplicationEventCallback(pI2CHandle,I2C_ERROR_OVR);
     }
 
 /***********************Check for Time out error************************************/
     temp1 = (pI2CHandle->pI2Cx->SR[0]) & ( 1 << I2C_SR1_TIMEOUT);
     if(temp1  && temp2)
     {
         //This is Time out error
         
         //Implement the code to clear the Time out error flag
         pI2CHandle->pI2Cx->SR[0] &= ~( 1 << I2C_SR1_TIMEOUT);

         //Implement the code to notify the application about the error
         I2C_ApplicationEventCallback(pI2CHandle,I2C_ERROR_TIMEOUT); 
     }
 
 }

 

 
 