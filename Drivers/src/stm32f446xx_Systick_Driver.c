
#include "stm32f446xx_Systick_Driver.h"


void Systick_Init(Systick_Config_t* Systick_config){
	
	Systick_Enable(DISABLE);
	
	SYSTICK->CSR &= (uint32_t)~( 1 << SYSTICK_CSR_CLKSOURCE);
	SYSTICK->CSR |= (uint32_t)( Systick_config->Systick_Clock_Source << SYSTICK_CSR_ENABLE);
	
	SYSTICK->RVR = Systick_config->Systick_Period;
	SYSTICK->CVR = 0;
	
}

void Systick_Enable(uint8_t status){
	
	if( status == ENABLE){
		SYSTICK->CSR |= (uint32_t)( 1 << SYSTICK_CSR_ENABLE);
		
	}
	else if ( status == DISABLE){
		SYSTICK->CSR &= (uint32_t)~( 1 << SYSTICK_CSR_ENABLE);
	
	}
}

void Systick_ITConfig(uint8_t status){
	
	if( status == ENABLE){
		SYSTICK->CSR |= (uint32_t)( 1 << SYSTICK_CSR_TICKINT);
		
	}
	else if ( status == DISABLE){
		SYSTICK->CSR &= (uint32_t)~( 1 << SYSTICK_CSR_TICKINT);
	
	}		
}

uint32_t Systick_GetCounter(void){
	
	return SYSTICK->CVR;
}
void Systick_SetPeriod(uint32_t value){
	
	SYSTICK->RVR = value;
}
uint8_t Systick_GetCountFlag(void){
	
	return ( ( SYSTICK->CSR &(1 << SYSTICK_CSR_COUNTFLAG)) != 0);
}
uint32_t Systick_GetCalib(void){

	return SYSTICK->CALIB;
}


