
#include "stm32f446xx_WWDG_Driver.h"


void WWDG_Init(WWDG_Config_t* WWDG_Config){
	
		uint32_t temp_reg = 0;
	
		//Habilitar CLock
		WWDG_PCLCK_EN();
		
		//Set Prescaler
		temp_reg = WWDG->CFR;
		temp_reg &= (uint32_t)~(0x03 << WWDG_CFR_WDGTB);
		temp_reg |= (uint32_t)WWDG_Config->WWDG_prescaler << WWDG_CFR_WDGTB;
		WWDG->CFR = temp_reg;
	
		//Set Counter
		temp_reg = WWDG->CR;
		temp_reg &= (uint32_t)~(0x7F);
		temp_reg |= (uint32_t)WWDG_Config->WWDG_Counter & 0x7F;
		WWDG->CR = temp_reg;
	
		//Set Window
		temp_reg = WWDG->CFR;
		temp_reg &= (uint32_t)~(0x7F);
		temp_reg |= (uint32_t)WWDG_Config->WWWDG_Window & 0x7F;
		WWDG->CFR = temp_reg;
	
		
	
}
void WWDG_DeInit(void){
	RESET_WWDG();
}
void WWDG_Enable(uint8_t Status){
	
	if( Status == ENABLE ) {
		WWDG->CR |= (uint32_t)(1 << WWDG_CR_WDGA);
	}
	else if( Status == DISABLE ) {
		WWDG->CR &= (uint32_t)~(1 << WWDG_CR_WDGA);
	}
}
void WWDG_Refresh(WWDG_Config_t* WWDG_Config){
	
	uint32_t temp_reg = 0;
	temp_reg = WWDG->CR;
	
	temp_reg &= (uint32_t)~(0x7F);
	temp_reg |= WWDG_Config->WWDG_Counter & 0x7F;
	WWDG->CR = temp_reg;
	
}
void WWDG_ITConfig(uint8_t Status){
	
	if( Status == ENABLE ) {
		WWDG->CFR |= (uint32_t)(1 << WWDG_CFR_EWI);
	}
	else if( Status == DISABLE ) {
		WWDG->CFR &= (uint32_t)~(1 << WWDG_CFR_EWI);
	
	}
}
uint8_t WWDG_GetFlag(void){
	return (WWDG->SR & 0x01);
}

