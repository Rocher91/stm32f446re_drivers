
#include "stm32f446xx_Systick_Driver.h"


void Systick_Init(Systick_Config_t* Systick_config){

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

}




