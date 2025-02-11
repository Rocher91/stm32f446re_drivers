

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
	
	if( !TIM_IS_BASIC_TIMER( pTIMHandle->pTIMx ) )
	{
		if( pTIMHandle->TIM_TimeBase.TIM_CounterMode == TIM_CounterMode_UP )
		{
			pTIMHandle->pTIMx->CR[0] &= (uint32_t) ~(0x03 << TIMx_CR1_CMS );
			pTIMHandle->pTIMx->CR[0] &= (uint32_t) ~(0x01 << TIMx_CR1_DIR );
		}
		else if( pTIMHandle->TIM_TimeBase.TIM_CounterMode == TIM_CounterMode_DOWN )
		{
			pTIMHandle->pTIMx->CR[0] &= (uint32_t) ~(0x03 << TIMx_CR1_CMS );
			pTIMHandle->pTIMx->CR[0] |= (uint32_t) (0x01 << TIMx_CR1_DIR );
		}	
		else
		{
			pTIMHandle->pTIMx->CR[0] &= (uint32_t) ~(0x03 << TIMx_CR1_CMS );
			pTIMHandle->pTIMx->CR[0] |= (uint32_t) pTIMHandle->TIM_TimeBase.TIM_CounterMode << TIMx_CR1_CMS;
			
		}
			
	}
	
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
		
		if( TIM_GetStatus( pTIMHandle->pTIMx,(uint16_t)(0x01 << TIMx_DIER_CC1IE)) ){
			TIM_ClearITPendingBit( pTIMHandle->pTIMx, (uint16_t)(0x01 << TIMx_DIER_CC1IE));
			TIM_EventCallback( pTIMHandle, TIM_EVENT_CC1I);
		}
		
		if( TIM_GetStatus( pTIMHandle->pTIMx,(uint16_t)(0x01 << TIMx_DIER_CC2IE)) ){
			TIM_ClearITPendingBit( pTIMHandle->pTIMx, (uint16_t)(0x01 << TIMx_DIER_CC2IE));
			TIM_EventCallback( pTIMHandle, TIM_EVENT_CC2I);
		}
		
		if( TIM_GetStatus( pTIMHandle->pTIMx,(uint16_t)(0x01 << TIMx_DIER_CC3IE)) ){
			TIM_ClearITPendingBit( pTIMHandle->pTIMx, (uint16_t)(0x01 << TIMx_DIER_CC3IE));
			TIM_EventCallback( pTIMHandle, TIM_EVENT_CC3I);
		}
		
		if( TIM_GetStatus( pTIMHandle->pTIMx,(uint16_t)(0x01 << TIMx_DIER_CC4IE)) ){
			TIM_ClearITPendingBit( pTIMHandle->pTIMx, (uint16_t)(0x01 << TIMx_DIER_CC4IE));
			TIM_EventCallback( pTIMHandle, TIM_EVENT_CC4I);
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






/*Input Capture*/


void TIM_ICInit(TIM_handle_t* pTIMHandle){
	
	uint32_t temp_CCMRx = 0;
	uint32_t temp_CCER = 0;
	
	ASSERT_FALSE( TIM_IS_BASIC_TIMER( pTIMHandle->pTIMx ) );
	TIM_ClockController( pTIMHandle->pTIMx, ENABLE );
	
	//TIM_TimeBase_Init( pTIMHandle );
	
	if ( pTIMHandle->TIM_InputCapture.TIM_Channel == TIM_CH1 )
	{
		
		//Reset del bit CC1E para desabilitar el canal
		pTIMHandle->pTIMx->CCER &= (uint32_t) ~(1 << TIMx_CCER_CC1E);
		
		temp_CCMRx = pTIMHandle->pTIMx->CCMR[0];
		temp_CCER  = pTIMHandle->pTIMx->CCER;
		
		// Configurar entradada en registro CCMR1
		temp_CCMRx &= (uint32_t) ~(0x03 << TIMx_CCMR1_CC1S);
		temp_CCMRx |= (uint32_t) (pTIMHandle->TIM_InputCapture.TIM_IC_Selection << TIMx_CCMR1_CC1S);
		
		//COnfigurar filtro en registro CCMR1
		
		temp_CCMRx &= (uint32_t) ~(0x0F << TIMx_CCMR1_IC1F);
		temp_CCMRx |= (uint32_t) (pTIMHandle->TIM_InputCapture.TIM_IC_Filter << TIMx_CCMR1_IC1F);
		
		// COnfigurar Prescaleer
		
		temp_CCMRx &= (uint32_t) ~(0x03 << TIMx_CCMR1_IC1PSC);
		temp_CCMRx |= (uint32_t) (pTIMHandle->TIM_InputCapture.TIM_IC_Prescaler << TIMx_CCMR1_IC1PSC);
		
		// Polaridad en registro CCER
		
		temp_CCER  &= (uint32_t) ~((1 << TIMx_CCER_CC1P)|(1 << TIMx_CCER_CC1NP));
		
		if( pTIMHandle->TIM_InputCapture.TIM_IC_Polarity == TIM_ICPolarity_RE ){
				
				// CCN1P = 0 y CC1P = 0
				// Ya lo estan nada que hacer
		}
		else if( pTIMHandle->TIM_InputCapture.TIM_IC_Polarity == TIM_ICPolarity_FE ){
				
				// CCN1P = 0 y CC1P = 1
				
			temp_CCER |= (1 << TIMx_CCER_CC1P);
			
		}
		else if( pTIMHandle->TIM_InputCapture.TIM_IC_Polarity == TIM_ICPolarity_RRE ){
				
				// CCN1P = 1 y CC1P = 1
				temp_CCER |= (1 << TIMx_CCER_CC1P) | (1 << TIMx_CCER_CC1NP);
				
		}
		
		//Habilitar el canal
		temp_CCER |= (1 << TIMx_CCER_CC1E);
		
		pTIMHandle->pTIMx->CCMR[0] = temp_CCMRx;
		pTIMHandle->pTIMx->CCER = temp_CCER;
		
		
	}
	else if ( pTIMHandle->TIM_InputCapture.TIM_Channel == TIM_CH2 )
	{
		ASSERT_TRUE( TIM_HAS_CH2( pTIMHandle->pTIMx ) );
		
		//Reset del bit CC1E para desabilitar el canal
		pTIMHandle->pTIMx->CCER &= (uint32_t) ~(1 << TIMx_CCER_CC2E);
		
		temp_CCMRx = pTIMHandle->pTIMx->CCMR[0];
		temp_CCER  = pTIMHandle->pTIMx->CCER;
		
		// Configurar entradada en registro CCMR1
		temp_CCMRx &= (uint32_t) ~(0x03 << TIMx_CCMR1_CC1S);
		temp_CCMRx |= (uint32_t) (pTIMHandle->TIM_InputCapture.TIM_IC_Selection << TIMx_CCMR1_CC2S);
		
		//COnfigurar filtro en registro CCMR1
		
		temp_CCMRx &= (uint32_t) ~(0x0F << TIMx_CCMR1_IC1F);
		temp_CCMRx |= (uint32_t) (pTIMHandle->TIM_InputCapture.TIM_IC_Filter << TIMx_CCMR1_IC2F);
		
		// COnfigurar Prescaleer
		
		temp_CCMRx &= (uint32_t) ~(0x03 << TIMx_CCMR1_IC1PSC);
		temp_CCMRx |= (uint32_t) (pTIMHandle->TIM_InputCapture.TIM_IC_Prescaler << TIMx_CCMR1_IC2PSC);
		
		// Polaridad en registro CCER
		
		temp_CCER  &= (uint32_t) ~((1 << TIMx_CCER_CC1P)|(1 << TIMx_CCER_CC2NP));
		
		if( pTIMHandle->TIM_InputCapture.TIM_IC_Polarity == TIM_ICPolarity_RE ){
				
				// CCN1P = 0 y CC1P = 0
				// Ya lo estan nada que hacer
		}
		else if( pTIMHandle->TIM_InputCapture.TIM_IC_Polarity == TIM_ICPolarity_FE ){
				
				// CCN1P = 0 y CC1P = 1
				
			temp_CCER |= (1 << TIMx_CCER_CC2P);
			
		}
		else if( pTIMHandle->TIM_InputCapture.TIM_IC_Polarity == TIM_ICPolarity_RRE ){
				
				// CCN1P = 1 y CC1P = 1
				temp_CCER |= (1 << TIMx_CCER_CC2P) | (1 << TIMx_CCER_CC2NP);
				
		}
		
		//Habilitar el canal
		temp_CCER |= (1 << TIMx_CCER_CC2E);
		
		pTIMHandle->pTIMx->CCMR[0] = temp_CCMRx;
		pTIMHandle->pTIMx->CCER = temp_CCER;
		
	}
	else if ( pTIMHandle->TIM_InputCapture.TIM_Channel == TIM_CH3 )
	{
		ASSERT_TRUE( TIM_HAS_CH2( pTIMHandle->pTIMx ) );
		
			//Reset del bit CC1E para desabilitar el canal
		pTIMHandle->pTIMx->CCER &= (uint32_t) ~(1 << TIMx_CCER_CC3E);
		
		temp_CCMRx = pTIMHandle->pTIMx->CCMR[1];
		temp_CCER  = pTIMHandle->pTIMx->CCER;
		
		// Configurar entradada en registro CCMR1
		temp_CCMRx &= (uint32_t) ~(0x03 << TIMx_CCMR1_CC1S);
		temp_CCMRx |= (uint32_t) (pTIMHandle->TIM_InputCapture.TIM_IC_Selection << TIMx_CCMR2_CC3S);
		
		//COnfigurar filtro en registro CCMR1
		
		temp_CCMRx &= (uint32_t) ~(0x0F << TIMx_CCMR1_IC1F);
		temp_CCMRx |= (uint32_t) (pTIMHandle->TIM_InputCapture.TIM_IC_Filter << TIMx_CCMR2_IC3F);
		
		// COnfigurar Prescaleer
		
		temp_CCMRx &= (uint32_t) ~(0x03 << TIMx_CCMR1_IC1PSC);
		temp_CCMRx |= (uint32_t) (pTIMHandle->TIM_InputCapture.TIM_IC_Prescaler << TIMx_CCMR2_IC3PSC);
		
		// Polaridad en registro CCER
		
		temp_CCER  &= (uint32_t) ~((1 << TIMx_CCER_CC1P)|(1 << TIMx_CCER_CC2NP));
		
		if( pTIMHandle->TIM_InputCapture.TIM_IC_Polarity == TIM_ICPolarity_RE ){
				
				// CCN1P = 0 y CC1P = 0
				// Ya lo estan nada que hacer
		}
		else if( pTIMHandle->TIM_InputCapture.TIM_IC_Polarity == TIM_ICPolarity_FE ){
				
				// CCN1P = 0 y CC1P = 1
				
			temp_CCER |= (1 << TIMx_CCER_CC2P);
			
		}
		else if( pTIMHandle->TIM_InputCapture.TIM_IC_Polarity == TIM_ICPolarity_RRE ){
				
				// CCN1P = 1 y CC1P = 1
				temp_CCER |= (1 << TIMx_CCER_CC3P) | (1 << TIMx_CCER_CC3NP);
				
		}
		
		//Habilitar el canal
		temp_CCER |= (1 << TIMx_CCER_CC2E);
		
		pTIMHandle->pTIMx->CCMR[1] = temp_CCMRx;
		pTIMHandle->pTIMx->CCER = temp_CCER;
	}
	else if ( pTIMHandle->TIM_InputCapture.TIM_Channel == TIM_CH4 )
	{
		ASSERT_TRUE( TIM_HAS_CH2( pTIMHandle->pTIMx ) );
		
		//Reset del bit CC1E para desabilitar el canal
		pTIMHandle->pTIMx->CCER &= (uint32_t) ~(1 << TIMx_CCER_CC4E);
		
		temp_CCMRx = pTIMHandle->pTIMx->CCMR[1];
		temp_CCER  = pTIMHandle->pTIMx->CCER;
		
		// Configurar entradada en registro CCMR1
		temp_CCMRx &= (uint32_t) ~(0x03 << TIMx_CCMR1_CC1S);
		temp_CCMRx |= (uint32_t) (pTIMHandle->TIM_InputCapture.TIM_IC_Selection << TIMx_CCMR2_CC4S);
		
		//COnfigurar filtro en registro CCMR1
		
		temp_CCMRx &= (uint32_t) ~(0x0F << TIMx_CCMR1_IC1F);
		temp_CCMRx |= (uint32_t) (pTIMHandle->TIM_InputCapture.TIM_IC_Filter << TIMx_CCMR2_IC4F);
		
		// COnfigurar Prescaleer
		
		temp_CCMRx &= (uint32_t) ~(0x03 << TIMx_CCMR1_IC1PSC);
		temp_CCMRx |= (uint32_t) (pTIMHandle->TIM_InputCapture.TIM_IC_Prescaler << TIMx_CCMR2_IC4PSC);
		
		// Polaridad en registro CCER
		
		temp_CCER  &= (uint32_t) ~((1 << TIMx_CCER_CC4P)|(1 << TIMx_CCER_CC4NP));
		
		if( pTIMHandle->TIM_InputCapture.TIM_IC_Polarity == TIM_ICPolarity_RE ){
				
				// CCN1P = 0 y CC1P = 0
				// Ya lo estan nada que hacer
		}
		else if( pTIMHandle->TIM_InputCapture.TIM_IC_Polarity == TIM_ICPolarity_FE ){
				
				// CCN1P = 0 y CC1P = 1
				
			temp_CCER |= (1 << TIMx_CCER_CC4P);
			
		}
		else if( pTIMHandle->TIM_InputCapture.TIM_IC_Polarity == TIM_ICPolarity_RRE ){
				
				// CCN1P = 1 y CC1P = 1
				temp_CCER |= (1 << TIMx_CCER_CC4P) | (1 << TIMx_CCER_CC4NP);
				
		}
		
		//Habilitar el canal
		temp_CCER |= (1 << TIMx_CCER_CC4E);
		
		pTIMHandle->pTIMx->CCMR[1] = temp_CCMRx;
		pTIMHandle->pTIMx->CCER = temp_CCER;
	}
	
	
	

}


uint32_t TIM_GetCounter(TIM_RegDef_t* pTIMx){
	return pTIMx->CNT;
}

void TIM_SetCounter(TIM_RegDef_t* pTIMx,uint32_t counter){
 pTIMx->CNT = counter;
}
uint32_t TIM_GetCapture(TIM_RegDef_t* pTIMx,TIM_Channels_t TIM_Channel){
	
	uint32_t  Capture = 0;
	
	ASSERT_FALSE( TIM_IS_BASIC_TIMER( pTIMx ) );
	
	if ( TIM_Channel == TIM_CH1){
		
		Capture =  pTIMx->CCR[0];
	}
	else if ( TIM_Channel == TIM_CH2){
		
		ASSERT_TRUE(TIM_HAS_CH2(pTIMx));
		Capture = pTIMx->CCR[1];
	}
	else if ( TIM_Channel == TIM_CH3){
		
		ASSERT_TRUE(TIM_HAS_CH3(pTIMx));
		Capture = pTIMx->CCR[2];
	}
	else if ( TIM_Channel == TIM_CH4){
		
		ASSERT_TRUE(TIM_HAS_CH4(pTIMx));
		Capture = pTIMx->CCR[3];
	}
		return Capture;
}

void TIM_SetCompare(TIM_RegDef_t* pTIMx,TIM_Channels_t TIM_Channel,uint32_t value){
	
	ASSERT_FALSE( TIM_IS_BASIC_TIMER( pTIMx ) );
	
	if ( TIM_Channel == TIM_CH1){
		
		pTIMx->CCR[0]= value;
	}
	else if ( TIM_Channel == TIM_CH2){
		
		ASSERT_TRUE(TIM_HAS_CH2(pTIMx));
		pTIMx->CCR[1]= value;
	}
	else if ( TIM_Channel == TIM_CH3){
		
		ASSERT_TRUE(TIM_HAS_CH3(pTIMx));
		pTIMx->CCR[2]= value;
	}
	else if ( TIM_Channel == TIM_CH4){
		
		ASSERT_TRUE(TIM_HAS_CH4(pTIMx));
		pTIMx->CCR[3]= value;
	}
		
}



void TIM_OCInit(TIM_handle_t* pTIMHandle){
	
	uint32_t temp_CCMRx = 0;
	uint32_t temp_CCER = 0;
	
	ASSERT_FALSE( TIM_IS_BASIC_TIMER( pTIMHandle->pTIMx ) );
	
	//TIM_TimeBase_Init( pTIMHandle );
	TIM_ClockController( pTIMHandle->pTIMx, ENABLE );
	
	if ( pTIMHandle->TIM_InputCapture.TIM_Channel == TIM_CH1 ){
			
		//Reset del bit CC1E para deshabilitar el canal
		pTIMHandle->pTIMx->CCER &= (uint32_t)~(1 << TIMx_CCER_CC1E);
		
		temp_CCMRx = pTIMHandle->pTIMx->CCMR[0];
		temp_CCER = pTIMHandle->pTIMx->CCER;
		
		//Configurar el modo salida  en CCMR1
		temp_CCMRx &= (uint32_t)~(0x03 << TIMx_CCMR1_CC1S);
		
		//Configurar el modo de salida en registro CCMR
		temp_CCMRx &= (uint32_t)~(0x07 << TIMx_CCMR1_OC1M);
		temp_CCMRx |= (uint32_t)(pTIMHandle->TIM_OutputCompare.TIM_Channel << TIMx_CCMR1_OC1M);
		
		temp_CCER &= (uint32_t)~(0x01 << TIMx_CCER_CC1P);
		temp_CCER |= (uint32_t)(pTIMHandle->TIM_OutputCompare.TIM_OC_Polarity << TIMx_CCER_CC1P);
		
		pTIMHandle->pTIMx->CCER |= (uint32_t)(1 << TIMx_CCER_CC1E);
		
		//Actualizar registro CCMR1
		pTIMHandle->pTIMx->CCMR[0] = temp_CCMRx;
		
		//Configurar CCR1 con el valor de pulso 
		pTIMHandle->pTIMx->CCR[0] = pTIMHandle->TIM_OutputCompare.TIM_Pulse;
		
		//Actualizar registro CCER
		pTIMHandle->pTIMx->CCER |= temp_CCER;
		
	}
	else if ( pTIMHandle->TIM_InputCapture.TIM_Channel == TIM_CH2 ){
		
		ASSERT_TRUE( TIM_HAS_CH2( pTIMHandle->pTIMx ) );
		
		//Reset del bit CC1E para deshabilitar el canal
		pTIMHandle->pTIMx->CCER &= (uint32_t)~(1 << TIMx_CCER_CC1E);
		
		temp_CCMRx = pTIMHandle->pTIMx->CCMR[0];
		temp_CCER = pTIMHandle->pTIMx->CCER;
		
		//Configurar el modo salida  en CCMR1
		temp_CCMRx &= (uint32_t)~(0x03 << TIMx_CCMR1_CC2S);
		
		//Configurar el modo de salida en registro CCMR
		temp_CCMRx &= (uint32_t)~(0x07 << TIMx_CCMR1_OC2M);
		temp_CCMRx |= (uint32_t)(pTIMHandle->TIM_OutputCompare.TIM_Channel << TIMx_CCMR1_OC2M);
		
		temp_CCER &= (uint32_t)~(0x01 << TIMx_CCER_CC1P);
		temp_CCER |= (uint32_t)(pTIMHandle->TIM_OutputCompare.TIM_OC_Polarity << TIMx_CCER_CC2P);
		
		pTIMHandle->pTIMx->CCER |= (uint32_t)(1 << TIMx_CCER_CC2E);
		
		
		//Actualizar registro CCMR1
		pTIMHandle->pTIMx->CCMR[0] = temp_CCMRx;
		
		//Configurar CCR1 con el valor de pulso 
		pTIMHandle->pTIMx->CCR[1] = pTIMHandle->TIM_OutputCompare.TIM_Pulse;
		
		
		//Actualizar registro CCER
		pTIMHandle->pTIMx->CCER |= temp_CCER;
		
	}
	else if ( pTIMHandle->TIM_InputCapture.TIM_Channel == TIM_CH3 ){
		
		ASSERT_TRUE( TIM_HAS_CH3( pTIMHandle->pTIMx ) );
		
		//Reset del bit CC1E para deshabilitar el canal
		pTIMHandle->pTIMx->CCER &= (uint32_t)~(1 << TIMx_CCER_CC3E);
		
		temp_CCMRx = pTIMHandle->pTIMx->CCMR[1];
		temp_CCER = pTIMHandle->pTIMx->CCER;
		
		//Configurar el modo salida  en CCMR1
		temp_CCMRx &= (uint32_t)~(0x03 << TIMx_CCMR2_CC3S);
		
		//Configurar el modo de salida en registro CCMR
		temp_CCMRx &= (uint32_t)~(0x07 << TIMx_CCMR2_OC3M);
		temp_CCMRx |= (uint32_t)(pTIMHandle->TIM_OutputCompare.TIM_Channel << TIMx_CCMR2_OC3M);
		
		temp_CCER &= (uint32_t)~(0x01 << TIMx_CCER_CC1P);
		temp_CCER |= (uint32_t)(pTIMHandle->TIM_OutputCompare.TIM_OC_Polarity << TIMx_CCER_CC3P);
		
		pTIMHandle->pTIMx->CCER |= (uint32_t)(1 << TIMx_CCER_CC3E);
		
		
		//Actualizar registro CCMR2
		pTIMHandle->pTIMx->CCMR[1] = temp_CCMRx;
		
		//Configurar CCR1 con el valor de pulso 
		pTIMHandle->pTIMx->CCR[2] = pTIMHandle->TIM_OutputCompare.TIM_Pulse;
		
		
		//Actualizar registro CCER
		pTIMHandle->pTIMx->CCER |= temp_CCER;
		
	}
	else if ( pTIMHandle->TIM_InputCapture.TIM_Channel == TIM_CH4 ){
		
		ASSERT_TRUE( TIM_HAS_CH4( pTIMHandle->pTIMx ) );
		
		//Reset del bit CC1E para deshabilitar el canal
		pTIMHandle->pTIMx->CCER &= (uint32_t)~(1 << TIMx_CCER_CC4E);
		
		temp_CCMRx = pTIMHandle->pTIMx->CCMR[1];
		temp_CCER = pTIMHandle->pTIMx->CCER;
		
		//Configurar el modo salida  en CCMR1
		temp_CCMRx &= (uint32_t)~(0x03 << TIMx_CCMR2_CC4S);
		
		//Configurar el modo de salida en registro CCMR
		temp_CCMRx &= (uint32_t)~(0x07 << TIMx_CCMR2_OC4M);
		temp_CCMRx |= (uint32_t)(pTIMHandle->TIM_OutputCompare.TIM_Channel << TIMx_CCMR2_OC4M);
		
		temp_CCER &= (uint32_t)~(0x01 << TIMx_CCER_CC4P);
		temp_CCER |= (uint32_t)(pTIMHandle->TIM_OutputCompare.TIM_OC_Polarity << TIMx_CCER_CC4P);
		
		pTIMHandle->pTIMx->CCER |= (uint32_t)(1 << TIMx_CCER_CC4E);
		
		
		//Actualizar registro CCMR1
		pTIMHandle->pTIMx->CCMR[1] = temp_CCMRx;
		
		//Configurar CCR1 con el valor de pulso 
		pTIMHandle->pTIMx->CCR[3] = pTIMHandle->TIM_OutputCompare.TIM_Pulse;
		
		
		//Actualizar registro CCER
		pTIMHandle->pTIMx->CCER |= temp_CCER;
		
	}

}

void TIM_InputTrigger(TIM_RegDef_t* pTIMx,TIM_Trigger_t trigger){
	
	uint16_t temp_SMCR = 0;
	ASSERT_TRUE(TIM_HAS_MS_FUNCTIONALITY(pTIMx));
	
	temp_SMCR = (uint16_t)pTIMx->SMCR;
	
	temp_SMCR &= (uint32_t)~(0x07 << TIMx_SMCR_TS);
	temp_SMCR |= (uint32_t)(trigger << TIMx_SMCR_TS);
	
	pTIMx->SMCR = temp_SMCR;
}

void TIM_SlaveMode(TIM_RegDef_t* pTIMx, TIM_Slave_t mode){
	
	uint16_t temp_SMCR = 0;
	ASSERT_TRUE(TIM_HAS_MS_FUNCTIONALITY(pTIMx));
	
	temp_SMCR = (uint16_t)pTIMx->SMCR;
	
	temp_SMCR &= (uint32_t)~(0x07 << TIMx_SMCR_TS);
	temp_SMCR |= (uint32_t)(mode << TIMx_SMCR_TS);
	
	pTIMx->SMCR = temp_SMCR;
	
}


void TIM_MasterTriggerOutput(TIM_RegDef_t* pTIMx, TIM_MasterOutput_t output){

	uint16_t temp_CR2 = 0;
	ASSERT_TRUE(TIM_HAS_MS_FUNCTIONALITY(pTIMx));
	
	temp_CR2 = (uint16_t)pTIMx->CR[1];
	
	temp_CR2 &= (uint32_t)~(0x07 << TIMx_CR2_MMS);
	temp_CR2 |= (uint32_t)(output << TIMx_CR2_MMS);
	
	pTIMx->CR[1] = temp_CR2;
}

void TIM_EventCallback(TIM_handle_t* pTIMHandle,TIM_Event_t event){

}


