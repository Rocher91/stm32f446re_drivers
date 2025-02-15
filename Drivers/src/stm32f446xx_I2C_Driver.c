
#include "stm32f446xx_I2C_Driver.h"
#include "stm32f446xx_Clocks.h"


void I2C_PeripheralControl( I2C_RegDef_t *pI2Cx, uint8_t Enable_Disable )
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
    if( Enable_Disable == ENABLE)
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

void I2C_Init(I2C_Handle_t *pI2CHandle )
{
    uint32_t tempreg    = 0;

    //Enable Clock I2C
    I2C_PerCLKControl(pI2CHandle->pI2Cx,ENABLE);
    
    // ACK Control Register
    tempreg |= ( pI2CHandle->I2C_Config.I2C_ACK_Control << I2C_CR1_ACK );
    pI2CHandle->pI2Cx->CR[0] = tempreg;

    // Set Freq Bus
    tempreg = 0;
    tempreg = RCC_GetAPB1Clk()/1000000U;
    pI2CHandle->pI2Cx->CR[1] |= ( tempreg & 0x3F );

    // Set Address
    tempreg = 0;
    tempreg |= pI2CHandle->I2C_Config.I2C_DeviceAddress;
    pI2CHandle->pI2Cx->OAR[0] |= ( tempreg << I2C_OAR1_ADD_7_1 ) ;
    pI2CHandle->pI2Cx->OAR[0] |= (1 << 14) ;

    // CCR Calculations

    uint16_t ccr_value = 0;
    tempreg = 0;

    if (pI2CHandle->I2C_Config.I2C_SCL_Speed <= I2C_SCL_SPEED_SM)
    {
        //mode is standard mode
        // TSCL = 2*CCR*TPCLK1
        // CCR = Tscl/2*TPCLK1 = FPCLK1/ 2* Fscl

        ccr_value   = ( RCC_GetAHBClk() / ( 2 * pI2CHandle->I2C_Config.I2C_SCL_Speed ) );
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
            ccr_value   = ( RCC_GetAHBClk() / ( 3 * pI2CHandle->I2C_Config.I2C_SCL_Speed ) );
        }
        else
        {
            ccr_value   = ( RCC_GetAHBClk() / ( 25 * pI2CHandle->I2C_Config.I2C_SCL_Speed ) );
        }
        
        tempreg |= (ccr_value & 0xFFF);
    }

    pI2CHandle->pI2Cx->CCR = tempreg;

    // Trise/TPCLK ==> (FPCLK*Trise(max))+1
    if (pI2CHandle->I2C_Config.I2C_SCL_Speed <= I2C_SCL_SPEED_SM)
    {
        //mode is standard mode
        tempreg = ( RCC_GetAHBClk() / 1000000U ) + 1;
    }
    else
    {
        //mode is fast
        tempreg = ( ( RCC_GetAHBClk() * 300 ) / 1000000000U ) + 1;
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

uint8_t I2C_GetFlagStatus(I2C_RegDef_t *pI2Cx, uint32_t FlagName)
{
    if( pI2Cx->SR[0] & FlagName)
    {
        return FLAG_SET;
    }
    return FLAG_RESET; 
}

static void I2C_ExecuteAddressPhaseWrite( I2C_RegDef_t *pI2Cx, uint8_t slaveAddress )
{
    slaveAddress = ( slaveAddress << 1 );
    slaveAddress &= ~(0x01);

    pI2Cx->DR = slaveAddress;

}

static void I2C_ExecuteAddressPhaseRead( I2C_RegDef_t *pI2Cx, uint8_t slaveAddress )
{
    slaveAddress = ( slaveAddress << 1 );
    slaveAddress |= 0x01;

    pI2Cx->DR = slaveAddress;

}

static void I2C_ClearADDRFlag(I2C_RegDef_t *pI2Cx)
{   
		uint32_t dummyRead = 0;
	
    dummyRead = pI2Cx->SR[0];
    dummyRead = pI2Cx->SR[1];

    (void) dummyRead;
}

static void I2C_GenerateStopCondition(I2C_RegDef_t *pI2Cx)
{
    pI2Cx->CR[0] |= ( 1 << I2C_CR1_STOP);
}

static void I2C_GenerateStartCondition(I2C_RegDef_t *pI2Cx)
{
    pI2Cx->CR[0] |= ( 1 << I2C_CR1_START);
}

void I2C_ManageAcking(I2C_RegDef_t *pI2Cx,uint8_t Enable_Disable)
{
	if( Enable_Disable == ENABLE)
	{
		pI2Cx->CR[0] |= ( 1 << I2C_CR1_ACK);
	}
	else
	{	
		//Disable ACK
		pI2Cx->CR[0] &= ~( 1 << I2C_CR1_ACK);
	}
}
void I2C_MasterSendData( I2C_Handle_t *pI2CHandle, uint8_t *pTxBuffer, uint8_t Len, uint8_t slaveAddress, uint8_t Sr )
{
    //1. Generate the START Condition.
    I2C_GenerateStartCondition(pI2CHandle->pI2Cx);

    //2. Confirm that start generation is completed by checking the SB flag in the SR1.
    // NOTE: Until SB is cleared SCL will be stretched ( pulled to LOW ).
    while( I2C_GetFlagStatus( pI2CHandle->pI2Cx, I2C_SB_FLAG ) );

    //3.Send the address of the slave with r/nw bit set to w(0) ( total 8 bits ).
    I2C_ExecuteAddressPhaseWrite( pI2CHandle->pI2Cx, slaveAddress );

    //4.Confirm that adddress phase is completed by checking the ADDR flag in the SR1.
    while( I2C_GetFlagStatus( pI2CHandle->pI2Cx, I2C_ADDR_FLAG ) );

    //5.Clear the ADDR flag according to its software sequence
    // NOTE: Until ADDR is cleared SCL will be stretched ( pulled to LOW ).
    I2C_ClearADDRFlag(pI2CHandle->pI2Cx);

    //6.Send the data until Len becomes 0.
    while( Len > 0 )
    {
        while( !I2C_GetFlagStatus( pI2CHandle->pI2Cx, I2C_ADDR_FLAG ) ); //Wait till TXE is set 
        pI2CHandle->pI2Cx->DR = *pTxBuffer;
        pTxBuffer++;
        Len--;
    }

    //7.When Len becomes zero wait for TXE = 1 and BTF=1 before generating the STOP condition
    // NOTE: TXE:1 , BTF= 1 , means that both SR and DR are empty and next transmission should begin
    //when BTF=1 SCL will be stretched (pulled to LOW).
    while( I2C_GetFlagStatus( pI2CHandle->pI2Cx, I2C_TxE_FLAG ) );

    while( I2C_GetFlagStatus( pI2CHandle->pI2Cx, I2C_BTF_FLAG ) );

    //8. Generate STOP condition and master need not to wait for the completion of stop condition.
    // NOTE: generating STOP, automatically clears the BTF.
		
		if( Sr == I2C_DISABLE_SR )
		{
			I2C_GenerateStopCondition( pI2CHandle->pI2Cx );
		}
		
    



}

void I2C_MasterReceiveData( I2C_Handle_t *pI2CHandle, uint8_t *pRxBuffer, uint8_t Len, uint8_t slaveAddress , uint8_t Sr)
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
        I2C_ClearADDRFlag(pI2CHandle->pI2Cx);
			
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
				I2C_ClearADDRFlag(pI2CHandle->pI2Cx);
			
        //read the data until Len becomes zero.
			while( !I2C_GetFlagStatus( pI2CHandle->pI2Cx, I2C_RxNE_FLAG ) ){} //Wait till RxNE is set 
			
        for( uint32_t i = Len; i>0 ; i--)
        {
            //wait until RxNE becomes 1
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

void I2C_ScanBus(I2C_Handle_t *pI2CHandle )
{
    uint8_t address = 0;
    uint8_t devices_addresses[127] = { 0 };
    

    for ( address = 0 ; address < 128 ; address++)
    {
        if ( I2C_GetFlagStatus( pI2CHandle->pI2Cx, I2C_ADDR_FLAG ) )
        {
            devices_addresses[address] = address;
					
						//clear the ADDR flag.
						I2C_ClearADDRFlag(pI2CHandle->pI2Cx);
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


uint8_t I2C_MasterSendDataIT( I2C_Handle_t *pI2CHandle, uint8_t *pTxBuffer, uint8_t Len, uint8_t slaveAddress, uint8_t Sr)
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
uint8_t I2C_MasterReceiveDataIT( I2C_Handle_t *pI2CHandle, uint8_t *pRxBuffer, uint8_t Len, uint8_t slaveAddress , uint8_t Sr)
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


void I2C_IRQInterruptConfig( uint8_t IRQNumber, uint8_t Enable_Disable)
{

}

void I2C_IRQConfigPriority( uint8_t IRQNumber, uint32_t IRQPriority )
{

}