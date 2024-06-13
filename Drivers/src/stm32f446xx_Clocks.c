#include "stm32f446xx_Clocks.h"


//TODO
/************************************************************************************************************************
 *																																																											*
 *		@brief 		Configura el External High Speed Oscillator (HSE).																											*	
 *																																																											*
 *		@note			Posteriormente a la habilitacion del HSE (RCC_HSE_ON o RCC_HSE_Bypass),																	*
 *							la aplicacion debe esperar a que haga set el flag HSERDY antes de usarlo																*
 *							como clock.																																															*
 *																																																											*
 *		@param		HSE_Status: estado del HSE, cuyos valores pueder ser:																										*
 *																																																											*	
 *								@arg RCC_HSE_OFF: Deshabilita el HSE. El flag HSERDY se resetea despues de 6 ciclos de reloj.					*
 *								@arg RCC_HSE_ON: 	Habilita el HSE.																																		*		
 *								@arg RCC_HSE_BYP: Habilita el HSE para ser usado por un clock externo.																*
 *																																																											*
 *		@retval		None																																																		*
 *																																																											*
 ************************************************************************************************************************/
 
void RCC_HSEConfig(RCC_HSE_Status_t HSE_Status){
	
	/******************************
	 * RCC_CR->HSEON 		= 0
	 * RCC_CR->HSEBYP 	= 0
	 * RCC_CR->CSSON 		= 0
	 ******************************/
	
	RCC->CR &= (uint32_t)~( (1 << RCC_CR_HSEON) | (1 << RCC_HSE_BYP)| (1 << RCC_CR_CSSON) );
	
	if( HSE_Status == RCC_HSE_ON ){
			
		RCC->CR |= (1 << RCC_CR_HSEON) ;
	}
	else if( HSE_Status == RCC_HSE_BYP ){
		
		RCC->CR |= ( (1 << RCC_CR_HSEBYP) | (1<<RCC_CR_HSEON) ) ;	
	}
	
}

void RCC_LSEConfig(RCC_LSE_Status_t LSE_Status){
	
	//Habilitar Escritura
	PWR_PCLCK_EN();
	PWR->CR |= ( 1<< PWR_CR_DBP );
	
	/******************************
	 * RCC_BDCR->LSEBYP 	= 0
	 * RCC_BDCR->LSEON 		= 0
	 * RCC_BDCR->LSEMOD 	= 0
	 ******************************/
	RCC->BDCR &= ~( (1 << RCC_BDCR_LSEBYP) | (1 << RCC_BDCR_LSEON)| (1 << RCC_BDCR_LSEMOD) );
	
	if( LSE_Status == RCC_LSE_ON ){
			
			RCC->CR |= (1 << RCC_BDCR_LSEON) ;
	}
	else if( LSE_Status == RCC_LSE_BYP ){
			
			RCC->CR |= ( (1 << RCC_BDCR_LSEBYP) | (1<<RCC_BDCR_LSEON) ) ;	
	}
}


void RCC_PLLConfig(RCC_PLL_Source_t PLL_Source,uint32_t PLLM,uint32_t PLLN,uint32_t PLLP,uint32_t PLLQ,uint32_t PLLR){
	
	uint32_t temp_RCC_PLLCFGR = RCC->PLLCFGR;
	
	//ASSERT_TRUE(IS_VALID_PLLM_VAL(PLLM));
	//ASSERT_TRUE(IS_VALID_PLLM_VAL(PLLN));
	//ASSERT_TRUE(IS_VALID_PLLM_VAL(PLLP));
	//ASSERT_TRUE(IS_VALID_PLLM_VAL(PLLQ));
	//ASSERT_TRUE(IS_VALID_PLLM_VAL(PLLR));
	
	temp_RCC_PLLCFGR = ( PLLM | ( PLLN << RCC_PLLCFGR_PLLN )| ( ( ( PLLP >> 1 ) - 1 ) << RCC_PLLCFGR_PLLP ) | ( PLL_Source << RCC_PLLCFGR_PLLSRC ) |(PLLQ << RCC_PLLCFGR_PLLQ ) | ( PLLR << RCC_PLLCFGR_PLLR ) );
	
	RCC->PLLCFGR = temp_RCC_PLLCFGR;
}

void RCC_HSI_Enable(uint8_t status){
	
	if(status == ENABLE ){
		RCC->CR |= (1<<RCC_CR_HSION);
	}
	else if(status == DISABLE ){
		RCC->CR &= ~(1<<RCC_CR_HSION);
	}
}
void RCC_LSI_Enable(uint8_t status){
	if(status == ENABLE ){
		RCC->CR |= (1<<RCC_CSR_LSION);
	}
	else if(status == DISABLE ){
		RCC->CR &= ~(1<<RCC_CSR_LSION);
	}
}
void RCC_PLL_Enable(uint8_t status){
	
	if(status == ENABLE ){
		RCC->CR |= (1<<RCC_CR_PLLON);
	}
	else if(status == DISABLE ){
		RCC->CR &= ~(1<<RCC_CR_PLLON);
	}

}

void RCC_MCO1Config(RCC_MCO1_Source_t MCO1_Source, RCC_MCO1_Prescaler_t MCO1_Presc){
	
	uint32_t temp_RCC_CFGR = RCC->CFGR;
	
	//Limpiar el valor del campo MCO1. 
	temp_RCC_CFGR &= ~( 0x03 << RCC_CFGR_MCO1);
	
	// Settear bits de source 
	temp_RCC_CFGR |= ( MCO1_Source << RCC_CFGR_MCO1);
	
	//Limpiar Bits de prescaler
	temp_RCC_CFGR &= ~( 0x07 << RCC_CFGR_MCO1PRE);
	
	// Setear bits prescaler
	temp_RCC_CFGR |= ( MCO1_Presc << RCC_CFGR_MCO1PRE);
	
	RCC->CFGR = temp_RCC_CFGR;
}

uint32_t RCC_GetAPB1_TimerClk(void){

	uint32_t rcc_cfgr_ppre1;
	rcc_cfgr_ppre1 = (RCC->CFGR >> RCC_CFGR_PPRE1) & 0x07;
	
	if(rcc_cfgr_ppre1 == 1){
		return RCC_GetAPB1Clk();
	}
	return RCC_GetAPB1Clk()*2;
}

uint32_t RCC_GetAPB2_TimerClk(void){

	uint32_t rcc_cfgr_ppre2;
	rcc_cfgr_ppre2 = (RCC->CFGR >> RCC_CFGR_PPRE2) & 0x07;
	
	if(rcc_cfgr_ppre2 == 1){
		return RCC_GetAPB2Clk();
	}
	return RCC_GetAPB2Clk()*2;
}

void RCC_MCO2Config(RCC_MCO2_Source_t MCO2_Source, RCC_MCO2_Prescaler_t MCO2_Presc){
	
	uint32_t temp_RCC_CFGR = RCC->CFGR;
	
	//Limpiar Bits de source
	temp_RCC_CFGR &= ~( 0x03 << RCC_CFGR_MC02);
	
	// Settear bits de source 
	temp_RCC_CFGR |= ( MCO2_Source << RCC_CFGR_MC02);
	
	//Limpiar Bits de prescaler
	temp_RCC_CFGR &= ~( 0x07 << RCC_CFGR_MCO2PRE);
	
	// Setear bits prescaler
	temp_RCC_CFGR |= ( MCO2_Presc << RCC_CFGR_MCO2PRE);
	
	RCC->CFGR = temp_RCC_CFGR;
}

void RCC_WaitForClkRdy(RCC_Clock_t clk){
	
	if(clk == RCC_Clock_HSI){
		while(!(RCC->CR & (1 << RCC_CR_HSIRDY)));
	}
	else if(clk == RCC_Clock_HSE){
		while(!(RCC->CR & (1 << RCC_CR_HSERDY)));
	}
	else if(clk == RCC_Clock_PLL){
		while(!(RCC->CR & (1 << RCC_CR_PLLRDY)));
	}
	else if(clk == RCC_Clock_LSE){	
		while(!(RCC->BDCR & (1 << RCC_BDCR_LSERDY)));
	}

}
void RCC_SysclkConfig(RCC_SysClk_Source_t Sysclk_Src){
	
	uint32_t temp_RCC_CFGR = RCC->CFGR;

	temp_RCC_CFGR &= ~(0x03 << RCC_CFGR_SW);
	temp_RCC_CFGR |= (Sysclk_Src << RCC_CFGR_SW);
	
	RCC->CFGR = temp_RCC_CFGR;
}

RCC_SysClk_Source_t RCC_getSysclkSorce(void){
	
	uint32_t SWS;
	
	SWS = (RCC_SysClk_Source_t)((RCC->CFGR & 0x0C) >> RCC_CFGR_SW );
	
	return SWS;
}

void RCC_AHB1CkConfig(RCC_AHB_Prescaler_t AHB_Presc){
	
	uint32_t temp_RCC_CFGR = RCC->CFGR;
	
	temp_RCC_CFGR &= ~(0x0F << RCC_CFGR_HPRE);
	temp_RCC_CFGR |= (AHB_Presc << RCC_CFGR_HPRE);
	
	RCC->CFGR = temp_RCC_CFGR;
}
void RCC_APBlCkConfig(RCC_APB_Prescaler_t APB_Presc){
	
	uint32_t temp_RCC_CFGR = RCC->CFGR;
	
	temp_RCC_CFGR &= ~(0x07 << RCC_CFGR_PPRE1);
	temp_RCC_CFGR |= (APB_Presc << RCC_CFGR_PPRE1);
	
	RCC->CFGR = temp_RCC_CFGR;
}
void RCC_APB2CkConfig(RCC_APB_Prescaler_t APB_Presc){
	
	uint32_t temp_RCC_CFGR = RCC->CFGR;
	
	temp_RCC_CFGR &= ~(0x07 << RCC_CFGR_PPRE2);
	temp_RCC_CFGR |= (APB_Presc << RCC_CFGR_PPRE2);
	
	RCC->CFGR = temp_RCC_CFGR;
}


uint32_t RCC_getSysClk(void){
	
	uint32_t PLL_src 			= 0;
	uint32_t PLL_M 				= 0;
	uint32_t PLL_N 				= 0;
	uint32_t PLL_VCO 			= 0;
	uint32_t PLL_P 				= 0;
	uint32_t PLL_R 				= 0;
	uint32_t freq 				= 0;
	uint32_t rcc_cfgr_sws = 0;
	
	
	
	rcc_cfgr_sws = (RCC->CFGR) & 0x03;
	
	if( rcc_cfgr_sws == 0 ){
	
		//HSI 
		freq = HSI_FREQ;
	}
	else if( rcc_cfgr_sws == 1 ){
		//HSE
		freq = HSE_FREQ;
	}
	else if( rcc_cfgr_sws == 2 ){
		
		/*****************PLL_P********************
					PLL_VCO = (PLL_src / PLLM)* PLLN
					SYSCLK 	=  PLL_VCO / PLLP
		*******************************************/
		
		PLL_src = ( RCC->PLLCFGR >> RCC_PLLCFGR_PLLSRC )& 0x01;
		PLL_M 	= ( RCC->PLLCFGR & 0x3F);
		PLL_M 	= ( (RCC->PLLCFGR<< RCC_PLLCFGR_PLLN) & 0x1FF);
		
		if( PLL_src == PLL_SRC_HSE ){
			//HSE es la fuente de reloj del PLL
			PLL_VCO = ( HSE_FREQ / PLL_M ) * PLL_N;
		}
		else if( PLL_src == PLL_SRC_HSI ){
			//HSI es la fuente de reloj del PLL
			PLL_VCO = ( HSI_FREQ / PLL_M ) * PLL_N;
		}
		
		
		PLL_P 	= ((RCC->PLLCFGR >> RCC_PLLCFGR_PLLP ) & 0x03 + 1 )* 2;
		
		freq = PLL_VCO / PLL_P;
	}
	else if( rcc_cfgr_sws == 3 ){
		
		/*****************PLL_R********************
					PLL_VCO = (PLL_src / PLLM)* PLLN
					SYSCLK 	=  PLL_VCO / PLLR
		*******************************************/
		
		
		PLL_src = ( RCC->PLLCFGR >> RCC_PLLCFGR_PLLSRC )& 0x01;
		PLL_M 	= ( RCC->PLLCFGR & 0x3F);
		PLL_M 	= ( (RCC->PLLCFGR<< RCC_PLLCFGR_PLLN) & 0x1FF);
		
		if( PLL_src){
			PLL_VCO = (HSE_FREQ/PLL_M)*PLL_N;
		}
		else{
			PLL_VCO = (HSI_FREQ/PLL_M)*PLL_N;
		}
		
		PLL_R = ((RCC->PLLCFGR >> RCC_PLLCFGR_PLLR ) & 0x07);
		
		freq 	= PLL_VCO / PLL_R;
	}
	
	
	return freq;
}
uint32_t RCC_GetAHBClk(void){
	
	uint32_t rcc_cfgr_hpre 	= 0;
	uint16_t prescaler 			= 0;
	
	rcc_cfgr_hpre = ( RCC->CFGR >> RCC_CFGR_HPRE ) & 0x0F;
	prescaler = AHB_Prescaler[rcc_cfgr_hpre];
	
	return  ( RCC_getSysClk() / prescaler );
}
uint32_t RCC_GetAPB1Clk(void){
	
	uint32_t rcc_cfgr_ppre1 	= 0;
	uint16_t prescaler 				= 0;
	
	rcc_cfgr_ppre1 = ( RCC->CFGR >> RCC_CFGR_PPRE1 ) & 0x07;
	prescaler = APB_Prescaler[rcc_cfgr_ppre1];
	
	return  ( RCC_getSysClk() / prescaler );
}
uint32_t RCC_GetAPB2Clk(void){
	
	uint32_t rcc_cfgr_ppre2 	= 0;
	uint16_t prescaler 				= 0;
	
	rcc_cfgr_ppre2 = ( RCC->CFGR >> RCC_CFGR_PPRE2 ) & 0x07;
	prescaler = APB_Prescaler[rcc_cfgr_ppre2];
	
	return  ( RCC_getSysClk() / prescaler );
	
}

void setLatencyFlash(uint8_t latency){

	FLASH->ACR |= (latency << 0) ;
}



