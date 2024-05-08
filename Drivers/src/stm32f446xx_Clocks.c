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
 *								@arg RCC_HSE_OFF: Deshabilita el HSE. el flag HSERDY se resetea despues de 6 ciclos de reloj.					*
 *								@arg RCC_HSE_ON: 	Habilita el HSE.																																		*		
 *								@arg RCC_HSE_BYP: Habilita el HSE para ser usado por un clock externo.																*
 *																																																											*
 *		@retval		None																																																		*
 *																																																											*
 ************************************************************************************************************************/
 
void RCC_HSEConfig(RCC_HSE_Status_t HSE_Status){
	
	// Limpiar los bits del HSE antes de configurarlo ( RCC_HSE_OFF )
	RCC->CR &= ~( (1 << RCC_CR_HSEON) | (1 << RCC_HSE_BYP)| (1 << RCC_CR_CSSON) );
	
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
	
	// Limpiar los bits del LSE antes de configurarlo ( RCC_LSE_OFF )
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
	
	ASSERT_TRUE(IS_VALID_PLLM_VAL(PLLM));
	ASSERT_TRUE(IS_VALID_PLLM_VAL(PLLN));
	ASSERT_TRUE(IS_VALID_PLLM_VAL(PLLP));
	ASSERT_TRUE(IS_VALID_PLLM_VAL(PLLQ));
	ASSERT_TRUE(IS_VALID_PLLM_VAL(PLLR));
	
	
	temp_RCC_PLLCFGR = ( PLLM | ( PLLN<<RCC_PLLCFGR_PLLN )| (((PLLP>>1)-1)<<RCC_PLLCFGR_PLLP) | ( PLL_Source << RCC_PLLCFGR_PLLSRC) |(PLLQ<<RCC_PLLCFGR_PLLQ)|(PLLR<<RCC_PLLCFGR_PLLR) );
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

void RCC_MCO1Config(RCC_MCO1_Source_t MCO1_Source, RCC_MCO1_Prescaler_t MCO1_Prescaler){
	
	uint32_t temp_RCC_CFGR = RCC->CFGR;
	
	//Limpiar Bits de source
	temp_RCC_CFGR &= ~( 0x03 << RCC_CFGR_MCO1);
	
	// Settear bits de source 
	temp_RCC_CFGR |= ( MCO1_Source << RCC_CFGR_MCO1);
	
	//Limpiar Bits de prescaler
	temp_RCC_CFGR &= ~( 0x07 << RCC_CFGR_MCO1PRE);
	
	// Setear bits prescaler
	temp_RCC_CFGR |= ( MCO1_Prescaler << RCC_CFGR_MCO1PRE);
	
	RCC->CFGR = temp_RCC_CFGR;
}

void RCC_MCO2Config(RCC_MCO2_Source_t MCO2_Source, RCC_MCO2_Prescaler_t MCO2_Prescaler){
	
	uint32_t temp_RCC_CFGR = RCC->CFGR;
	
	//Limpiar Bits de source
	temp_RCC_CFGR &= ~( 0x03 << RCC_CFGR_MC02);
	
	// Settear bits de source 
	temp_RCC_CFGR |= ( MCO2_Source << RCC_CFGR_MC02);
	
	//Limpiar Bits de prescaler
	temp_RCC_CFGR &= ~( 0x07 << RCC_CFGR_MCO1PRE);
	
	// Setear bits prescaler
	temp_RCC_CFGR |= ( MCO2_Prescaler << RCC_CFGR_MCO2PRE);
	
	RCC->CFGR = temp_RCC_CFGR;
}

void RCC_WaitForClkRdy(RCC_Clock_t clk){
	
	if(clk == RCC_Clock_HSI){
		while(!RCC->CR & (1 << RCC_CR_HSIRDY));
	}
	else if(clk == RCC_Clock_HSE){
		while(!RCC->CR & (1 << RCC_CR_HSERDY));
	}
	else if(clk == RCC_Clock_PLL){
		while(!RCC->CR & (1 << RCC_CR_PLLRDY));
	}
	else if(clk == RCC_Clock_LSE){
		
		//Habilitar Escritura
		PWR_PCLCK_EN();
		PWR->CR |= ( 1<< PWR_CR_DBP );
		while(!RCC->BDCR & (1 << RCC_BDCR_LSERDY));
	}
}
void RCC_SysclkConfig(RCC_SysClk_Source_t Sysclk_Src){
	
	uint32_t temp_RCC_CFGR = 0;
	temp_RCC_CFGR = RCC->CFGR;
	
	//Limpiar bits de source
	temp_RCC_CFGR &= ~(0x03 << RCC_CFGR_SW);
	
	//Setear bits de source
	temp_RCC_CFGR |= (0x03 << RCC_CFGR_SW);
	
	RCC->CFGR = temp_RCC_CFGR;
	
	
}

RCC_SysClk_Source_t RCC_getSysclkSorce(void){
	
	uint32_t SWS;
	
	SWS = (RCC->CFGR & 0x0C) >> RCC_CFGR_SW;
	
	return (RCC_SysClk_Source_t)SWS;
}




