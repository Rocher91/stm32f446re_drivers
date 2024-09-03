
#include "stm32f446xx_IWDG_Driver.h"


void IWDG_Init(IWDG_Config_t* IWDG_Config ){
	
	IWDG_Enable(ENABLE);
	IWDG_WriteAcces(ENABLE);
	
	while(IWDG_GetFlag(IWDG_StatusFlag_PVU));
	IWDG_setPrescaler(IWDG_Config->IWD_prescaler);
	
	while(IWDG_GetFlag(IWDG_StatusFlag_RVU));
	IWDG_setPrescaler(IWDG_Config->IWDG_Period);
	
	while(IWDG->SR & 0x03);
}
void IWDG_Enable(uint8_t status ){
	
	if(status == ENABLE){
		IWDG->KR |= IWDG_ENABLE_KEY;
	}
	else if(status == DISABLE){ 
		IWDG->KR = IWDG_DISABLE_KEY;
	}
}
void IWDG_WriteAcces(uint8_t status ){
	
	if(status == ENABLE){
		IWDG->KR = IWDG_WRITEACCES_KEY;
	}
	else if(status == DISABLE){ 
		IWDG->KR = IWDG_DISABLE_KEY;
	}
	
}
void IWDG_setPrescaler(IWDG_Prescaler_t prescaler ){
	IWDG->PR = (prescaler & 0x07);
}
void IWDG_setPeriod(uint32_t period ){
	IWDG->RLR = (period & 0x7F);
}
uint8_t IWDG_GetFlag(IWDG_StatusFlag_t flag ){
	return (IWDG->SR & (1 << flag));
}
void IWDG_Refresh( void ){
	IWDG->KR = IWDG_RELOAD_KEY;
}


