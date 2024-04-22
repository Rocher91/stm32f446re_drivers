
#include "stm32f446xx_NVIC.h"

void IRQInterruptConfig( uint8_t IRQNumber, uint8_t Enable_Disable){

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

void IRQConfigPriority( uint8_t IRQNumber, uint32_t IRQPriority ){

	// 1. first lets find out the ipr register.
	uint8_t iprx = IRQNumber / 4;
	uint8_t iprx_section = IRQNumber % 4;

	uint8_t shift_amount = ( 8 * iprx_section )+ ( 8 - NO_PR_BITS_IMPLEMENTED );

	*(NVIC_IPR_BASE + iprx  ) |= ( IRQPriority << shift_amount );
}

/********************************************************************************
 * @fn		- GPIO_IRQHandling
 *
 * @brief	-
 *
 * @param[in]
 * @param[in]
 *
 * @return
 *
 * @Note
 *
 * */
void IRQHandling( uint8_t PinNumber ){

	// Clear the EXTI PR register corresponding to th epin number.

	if( EXTI->PR & ( 1 << PinNumber)){

		//Clear
		EXTI->PR |= ( 1 << PinNumber );
	}
}
