
#ifndef INC_STM32F446XX_TIMERS_DRIVER_H_
#define INC_STM32F446XX_TIMERS_DRIVER_H_

#include "stm32f446xx_Timers.h"


void TIM_PerCLKControl( General_Purpose_Timers_2_5_RegDef_t *pTIMx, uint8_t Enable_Disable ){
	
	if( Enable_Disable == ENABLE){

		if( pTIMx == TIM1 ){
			TIM1_PCLCK_EN();
		}
		else if( pTIMx == TIM2 ){
			TIM2_PCLCK_EN();
		}
		else if( pTIMx == TIM3 ){
			TIM3_PCLCK_EN();
		}
		else if( pTIMx == TIM4 ){
			TIM4_PCLCK_EN();
		}
		else if( pTIMx == TIM5 ){
			TIM5_PCLCK_EN();
		}
		else if( pTIMx == TIM6 ){
			TIM6_PCLCK_EN();
		}
		else if( pTIMx == TIM7 ){
			TIM7_PCLCK_EN();
		}
		else if( pTIMx == TIM8 ){
			TIM8_PCLCK_EN();
		}
		else if( pTIMx == TIM9 ){
			TIM9_PCLCK_EN();
		}
		else if( pTIMx == TIM10 ){
			TIM10_PCLCK_EN();
		}
		else if( pTIMx == TIM11 ){
			TIM11_PCLCK_EN();
		}
		else if( pTIMx == TIM12 ){
			TIM12_PCLCK_EN();
		}
		else if( pTIMx == TIM13 ){
			TIM13_PCLCK_EN();
		}
		else if( pTIMx == TIM14 ){
			TIM14_PCLCK_EN();
		}
	}
	else if ( Enable_Disable == DISABLE ){

		if( pTIMx == TIM1 ){
			TIM1_PCLCK_DIS();
		}
		else if( pTIMx == TIM2 ){
			TIM2_PCLCK_DIS();
		}
		else if( pTIMx == TIM3 ){
			TIM3_PCLCK_DIS();
		}
		else if( pTIMx == TIM4 ){
			TIM4_PCLCK_DIS();
		}
		else if( pTIMx == TIM5 ){
			TIM5_PCLCK_DIS();
		}
		else if( pTIMx == TIM6 ){
			TIM6_PCLCK_DIS();
		}
		else if( pTIMx == TIM7 ){
			TIM7_PCLCK_DIS();
		}
		else if( pTIMx == TIM8 ){
			TIM8_PCLCK_DIS();
		}
		else if( pTIMx == TIM9 ){
			TIM9_PCLCK_DIS();
		}
		else if( pTIMx == TIM10 ){
			TIM10_PCLCK_DIS();
		}
		else if( pTIMx == TIM11 ){
			TIM11_PCLCK_DIS();
		}
		else if( pTIMx == TIM12 ){
			TIM12_PCLCK_DIS();
		}
		else if( pTIMx == TIM13 ){
			TIM13_PCLCK_DIS();
		}
		else if( pTIMx == TIM14 ){
			TIM14_PCLCK_DIS();
		}
	}

}
void TIM_Basic_TimeBase(TIM_Basic_Handle_t* pTIMHandle){

	TIM_PerCLKControl(pTIMHandle->pTIMx,ENABLE);
	
	pTIMHandle->pTIMx->ARR = pTIMHandle->TIM_TimeBase.TIM_Period;
	pTIMHandle->pTIMx->PSC = pTIMHandle->TIM_TimeBase.TIM_Preescaler;
	
	pTIMHandle->pTIMx->EGR |= (0x01<<0);
	
}

void TIM_Basic_Init(General_Purpose_Timers_2_5_RegDef_t* pTIMx,uint8_t enable){

	if (enable == ENABLE){
	

	}
	else if (enable == ENABLE){
		

		
	}
}

void TIM_Basic_ITConfig(General_Purpose_Timers_2_5_RegDef_t* pTIMx,uint16_t IT_type,uint8_t enable){

	if(enable == ENABLE){
		
	
		
	}
	else if ( enable == DISABLE){
		
		
	}
}




void TIM_IRQInterruptConfig( uint8_t IRQNumber, uint8_t Enable_Disable){

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

void TIM_IRQConfigPriority( uint8_t IRQNumber, uint32_t IRQPriority ){

	// 1. first lets find out the ipr register.
	uint8_t iprx = IRQNumber / 4;
	uint8_t iprx_section = IRQNumber % 4;

	uint8_t shift_amount = ( 8 * iprx_section )+ ( 8 - NO_PR_BITS_IMPLEMENTED );

	*(NVIC_IPR_BASE + iprx  ) |= ( IRQPriority << shift_amount );
}


void TIM_IRQHandling( TIM_Basic_Handle_t *pTIMHandle ){

	
}

void TIM_ClearITPendingBit(General_Purpose_Timers_2_5_RegDef_t *pTIMx,uint16_t FlagName){
	
	if ( FlagName == UPDATE_INTERRUPT_FLAG ){
		pTIMx->SR &= (uint32_t)~( 0X01 << UPDATE_INTERRUPT_FLAG);
	}
	else if ( FlagName == TRIGGER_INTERRUPT_FLAG ){
		pTIMx->SR &= (uint32_t)~( 0X01 << TRIGGER_INTERRUPT_FLAG );
	}
	else if ( FlagName == CAPTURE_COMPARE1_OVERCAPTURE_FLAG ){
		pTIMx->SR &= (uint32_t)~( 0X01 << CAPTURE_COMPARE1_OVERCAPTURE_FLAG );
	}
	else if ( FlagName == CAPTURE_COMPARE2_OVERCAPTURE_FLAG ){
		pTIMx->SR &= (uint32_t)~( 0X01 << CAPTURE_COMPARE2_OVERCAPTURE_FLAG );
	}
	else if ( FlagName == CAPTURE_COMPARE3_OVERCAPTURE_FLAG ){
		pTIMx->SR &= (uint32_t)~( 0X01 << CAPTURE_COMPARE3_OVERCAPTURE_FLAG );
	}
	else if ( FlagName == CAPTURE_COMPARE4_OVERCAPTURE_FLAG ){
		pTIMx->SR &= (uint32_t)~( 0X01 << CAPTURE_COMPARE4_OVERCAPTURE_FLAG );
	}
	else if ( FlagName == CAPTURE_COMPARE1_INTERRUPT_FLAG ){
		pTIMx->SR &= (uint32_t)~( 0X01 << CAPTURE_COMPARE1_INTERRUPT_FLAG );
	}
	else if ( FlagName == CAPTURE_COMPARE2_INTERRUPT_FLAG ){
		pTIMx->SR &= (uint32_t)~( 0X01 << CAPTURE_COMPARE2_INTERRUPT_FLAG);
	}
	else if ( FlagName == CAPTURE_COMPARE3_INTERRUPT_FLAG ){
		pTIMx->SR &= (uint32_t)~( 0X01 << CAPTURE_COMPARE3_INTERRUPT_FLAG );
	}
	else if ( FlagName == CAPTURE_COMPARE4_INTERRUPT_FLAG ){
		pTIMx->SR &= (uint32_t)~( 0X01 << CAPTURE_COMPARE4_INTERRUPT_FLAG );
	}
		
}
uint8_t TIM_GetStatus(General_Purpose_Timers_2_5_RegDef_t *pTIMx,uint16_t FlagName){
	
	uint16_t IT_STatus = 0;
	uint16_t IT_Enable = 0;
	
	IT_STatus = ( pTIMx->SR & FlagName );
	IT_Enable = ( pTIMx->DIER & FlagName );
	
	
	if (IT_STatus != (uint16_t)0x00 && IT_Enable != (uint16_t)0x00 )
		return SET;
	else
		return RESET;
}




#endif

