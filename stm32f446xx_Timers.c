
#ifndef INC_STM32F446XX_TIMERS_DRIVER_H_
#define INC_STM32F446XX_TIMERS_DRIVER_H_

#include "stm32f446xx_Timers.h"
#include "stm32f446xx_NVIC.h"


void TIM_2_5_PerCLKControl( General_Purpose_Timers_2_5_RegDef_t *pTIMx, uint8_t Enable_Disable ){
	
	if( Enable_Disable == ENABLE){


		if( pTIMx == TIM2 ){
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
	}
	else if ( Enable_Disable == DISABLE ){

		if( pTIMx == TIM2 ){
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
	}
}

void TIM_1_8_PerCLKControl( Advanced_Control_Timers_RegDef_t *pTIMx, uint8_t Enable_Disable ){
	
	if( Enable_Disable == ENABLE){


		if( pTIMx == TIM1 ){
			TIM1_PCLCK_EN();
		}
		else if( pTIMx == TIM8 ){
			TIM8_PCLCK_EN();
		}
	}
	else if ( Enable_Disable == DISABLE ){

		if( pTIMx == TIM1 ){
			TIM1_PCLCK_DIS();
		}
		else if( pTIMx == TIM8 ){
			TIM8_PCLCK_DIS();
		}
	
	}
}

void TIM_9_14_PerCLKControl( General_Purpose_Timers_9_14_RegDef_t *pTIMx, uint8_t Enable_Disable ){
	
	if( Enable_Disable == ENABLE){


		if( pTIMx == TIM9 ){
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

		if( pTIMx == TIM9 ){
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

void TIM_6_7_PerCLKControl( Basic_Timers_RegDef_t *pTIMx, uint8_t Enable_Disable ){
	
	if( Enable_Disable == ENABLE){

		if( pTIMx == TIM6 ){
			TIM6_PCLCK_EN();
		}
		else if( pTIMx == TIM7 ){
			TIM7_PCLCK_EN();
		}
	}
	else if ( Enable_Disable == DISABLE ){

		if( pTIMx == TIM6 ){
			TIM6_PCLCK_DIS();
		}
		else if( pTIMx == TIM7 ){
			TIM7_PCLCK_DIS();
		}
	}
}





void TIM_Basic_TimeBase(TIM_Basic_Handle_t* pTIMHandle){

	if ( pTIMHandle->pTIMx == TIM2 || pTIMHandle->pTIMx == TIM3 || pTIMHandle->pTIMx == TIM4 || pTIMHandle->pTIMx == TIM5  ){
		
		TIM_2_5_PerCLKControl( pTIMHandle->pTIMx, ENABLE );
	}
	else if (pTIMHandle->pTIMx == TIM6 || pTIMHandle->pTIMx == TIM7){
		TIM_6_7_PerCLKControl( pTIMHandle->pTIMx, ENABLE );
	}
	else if (pTIMHandle->pTIMx == TIM1 || pTIMHandle->pTIMx == TIM8){
		TIM_1_8_PerCLKControl( pTIMHandle->pTIMx, ENABLE );
	}
	else if (pTIMHandle->pTIMx == TIM9 || pTIMHandle->pTIMx == TIM10 || pTIMHandle->pTIMx == TIM11 || pTIMHandle->pTIMx == TIM12 || pTIMHandle->pTIMx == TIM13  || pTIMHandle->pTIMx == TIM14 ){
		TIM_9_14_PerCLKControl( pTIMHandle->pTIMx, ENABLE );
	}
	
	
	
	
	pTIMHandle->pTIMx->ARR = pTIMHandle->TIM_TimeBase.TIM_Period;
	pTIMHandle->pTIMx->PSC = pTIMHandle->TIM_TimeBase.TIM_Preescaler;
	pTIMHandle->pTIMx->EGR |= (0x01);
	
}

void TIM_Basic_Init(Basic_Timers_RegDef_t* pTIMx,uint8_t enable){

	if (enable == ENABLE){
		
		pTIMx->CR[0] |= (1 << TIMx_CR1_CEN);
		

	}
	else if (enable == DISABLE){
		
		pTIMx->CR[0] &= (uint32_t)~(1 << TIMx_CR1_CEN);
		
	}
}

void TIM_Basic_ITConfig(General_Purpose_Timers_2_5_RegDef_t* pTIMx,uint16_t IT_type,uint8_t enable){

	if(enable == ENABLE){
		
		if (IT_type == 1){
			
			pTIMx->DIER |= (0x01 << TIMx_DIER_UIE);
		}
		else if (IT_type == 2){
			
			pTIMx->DIER |= (0x01 << TIMx_DIER_CC1IE);
		}
		else if (IT_type == 3){
			
			pTIMx->DIER |= (0x01 << TIMx_DIER_CC2IE);
		}
		else if (IT_type == 4){
			
			pTIMx->DIER |= (0x01 << TIMx_DIER_CC3IE);
		}
		else if (IT_type == 5){
			
			pTIMx->DIER |= (0x01 << TIMx_DIER_CC4IE);
		}
		else if (IT_type == 6){
			
			pTIMx->DIER |= (0x01 << TIMx_DIER_COMIE);
		}
		else if (IT_type == 7){
			
			pTIMx->DIER |= (0x01 << TIMx_DIER_TIE);
		}
		else if (IT_type == 8){
			
			pTIMx->DIER |= (0x01 << TIMx_DIER_BIE);
		}
		else if (IT_type == 8){
			
			pTIMx->DIER |= (0x01 << TIMx_DIER_UDE);
		}
		else if (IT_type == 9){
			
			pTIMx->DIER |= (0x01 << TIMx_DIER_CC1DE);
		}
		else if (IT_type == 10){
			
			pTIMx->DIER |= (0x01 << TIMx_DIER_CC2DE);
		}
		else if (IT_type == 11){
			
			pTIMx->DIER |= (0x01 << TIMx_DIER_CC3DE);
		}
		else if (IT_type == 12){
			
			pTIMx->DIER |= (0x01 << TIMx_DIER_CC4DE);
		}
		else if (IT_type == 13){
			
			pTIMx->DIER |= (0x01 << TIMx_DIER_COMDE);
		}
		else if (IT_type == 14){
			
			pTIMx->DIER |= (0x01 << TIMx_DIER_TDE);
		}
		
		
	}
	else if ( enable == DISABLE){
		
		if (IT_type == 1){
			
			pTIMx->DIER &= ~(0x01 << TIMx_DIER_UIE);
		}
		else if (IT_type == 2){
			
			pTIMx->DIER &= ~(0x01 << TIMx_DIER_CC1IE);
		}
		else if (IT_type == 3){
			
			pTIMx->DIER &= ~(0x01 << TIMx_DIER_CC2IE);
		}
		else if (IT_type == 4){
			
			pTIMx->DIER &= ~(0x01 << TIMx_DIER_CC3IE);
		}
		else if (IT_type == 5){
			
			pTIMx->DIER &= ~(0x01 << TIMx_DIER_CC4IE);
		}
		else if (IT_type == 6){
			
			pTIMx->DIER &= ~(0x01 << TIMx_DIER_COMIE);
		}
		else if (IT_type == 7){
			
			pTIMx->DIER &= ~(0x01 << TIMx_DIER_TIE);
		}
		else if (IT_type == 8){
			
			pTIMx->DIER &= ~(0x01 << TIMx_DIER_BIE);
		}
		else if (IT_type == 8){
			
			pTIMx->DIER &= ~(0x01 << TIMx_DIER_UDE);
		}
		else if (IT_type == 9){
			
			pTIMx->DIER &= ~(0x01 << TIMx_DIER_CC1DE);
		}
		else if (IT_type == 10){
			
			pTIMx->DIER &= ~(0x01 << TIMx_DIER_CC2DE);
		}
		else if (IT_type == 11){
			
			pTIMx->DIER &= ~(0x01 << TIMx_DIER_CC3DE);
		}
		else if (IT_type == 12){
			
			pTIMx->DIER &= ~(0x01 << TIMx_DIER_CC4DE);
		}
		else if (IT_type == 13){
			
			pTIMx->DIER &= ~(0x01 << TIMx_DIER_COMDE);
		}
		else if (IT_type == 14){
			
			pTIMx->DIER &= ~(0x01 << TIMx_DIER_TDE);
		}
		
	}
}







void TIM_IRQHandling( TIM_Basic_Handle_t *pTIMHandle ){
	
	uint8_t i =0;
	
	uint8_t list[] = { 	
											TIMx_DIER_UIE ,TIMx_DIER_CC1IE , TIMx_DIER_CC2IE , TIMx_DIER_CC3IE , TIMx_DIER_CC4IE , TIMx_DIER_COMIE , 
											TIMx_DIER_TIE , TIMx_DIER_BIE , TIMx_DIER_UDE , TIMx_DIER_CC1DE , TIMx_DIER_CC2DE , TIMx_DIER_CC3DE , 
											TIMx_DIER_CC4DE , TIMx_DIER_COMDE , TIMx_DIER_TDE 
										};
	
	for (i=0;i<15;i++){
			
		if( TIM_GetStatus( pTIMHandle->pTIMx,(0x01 << list[i])) ){
			TIM_ClearITPendingBit( pTIMHandle->pTIMx, TIMx_DIER_UIE);
			
		}
	}
	
}

void TIM_ClearITPendingBit(General_Purpose_Timers_2_5_RegDef_t *pTIMx,uint16_t FlagName){
	
	uint8_t i =0;
	
	uint8_t list[] = { 	
											TIMx_SR_UIF ,TIMx_SR_CC1IF , TIMx_SR_CC2IF , TIMx_SR_CC3IF , TIMx_SR_CC4IF , TIMx_SR_COMIF , 
											TIMx_SR_TIF , TIMx_SR_BIF , TIMx_SR_CC1OF , TIMx_SR_CC2OF , TIMx_SR_CC3OF , TIMx_SR_CC4OF  
										};
	
	for (i=0;i<12;i++){
			
		if ( FlagName == (0x01 << list[i]) ){
			pTIMx->SR &= (uint32_t)~( 0X01 << list[i]);
		}						
	}								
										
		
}
uint8_t TIM_GetStatus(General_Purpose_Timers_2_5_RegDef_t *pTIMx,uint16_t IT_type){
	
	uint16_t IT_STatus = 0;
	uint16_t IT_Enable = 0;
	
	IT_STatus = ( pTIMx->SR & IT_type );
	IT_Enable = ( pTIMx->DIER & IT_type );
	
	
	if (IT_STatus != (uint16_t)0x00 && IT_Enable != (uint16_t)0x00 )
		return SET;
	else
		return RESET;
}




__attribute__((weak))void TIM_EventCallback(TIM_Basic_Handle_t* pTIMHandle,TIM_Event_t event){

}

#endif

