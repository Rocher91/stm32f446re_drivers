

#include "stm32f446xx_Timers_Driver.h"
#include "stm32f446xx_NVIC.h"


void TIM_ClockController( TIM_RegDef_t *pTIMx, uint8_t Enable_Disable ){
	
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



void TIM_TimeBase_Init(TIM_handle_t* pTIMHandle){

	
	TIM_ClockController( pTIMHandle->pTIMx, ENABLE );
	
	pTIMHandle->pTIMx->ARR = pTIMHandle->TIM_TimeBase.TIM_Period;
	pTIMHandle->pTIMx->PSC = pTIMHandle->TIM_TimeBase.TIM_Preescaler;
	pTIMHandle->pTIMx->EGR |= (0x01<<TIMx_EGR_UG);
	
}

void TIM_Init(TIM_RegDef_t* pTIMx,uint8_t enable){

	if (enable == ENABLE){
		
		pTIMx->CR[0] |= (1 << TIMx_CR1_CEN);

	}
	else if (enable == DISABLE){
		
		pTIMx->CR[0] &= (uint32_t)~(1 << TIMx_CR1_CEN);
		
	}
}

void TIM_ITConfig(TIM_RegDef_t* pTIMx,uint16_t IT_type,uint8_t enable){

	if(enable == ENABLE){
			pTIMx->DIER |= (0x01 << IT_type);
	}
	else if ( enable == DISABLE){
			pTIMx->DIER &= (uint32_t)~(0x01 << IT_type);
	}

}


void TIM_IRQHandling( TIM_handle_t *pTIMHandle ){

		if( TIM_GetStatus( pTIMHandle->pTIMx,(uint16_t)(0x01 << TIMx_DIER_UIE)) ){
			TIM_ClearITPendingBit( pTIMHandle->pTIMx, (uint16_t)(0x01 << TIMx_DIER_UIE));
			TIM_EventCallback( pTIMHandle, TIM_EVENT_UI);
		}
	
}

void TIM_ClearITPendingBit(TIM_RegDef_t *pTIMx,uint16_t TIM_IT){

	pTIMx->SR &= (uint16_t)~( TIM_IT );
							
}
uint8_t TIM_GetStatus(TIM_RegDef_t *pTIMx,uint16_t TIM_IT){
	
	uint16_t IT_STatus = 0;
	uint16_t IT_Enable = 0;
	
	IT_STatus = ( pTIMx->SR & TIM_IT );
	IT_Enable = ( pTIMx->DIER & TIM_IT );
	
	
	if (IT_STatus != (uint16_t)0x00 && IT_Enable != (uint16_t)0x00 )
		return SET;
	else
		return RESET;
}










