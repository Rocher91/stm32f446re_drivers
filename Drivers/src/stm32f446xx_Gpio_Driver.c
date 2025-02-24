/*
 * stm32f446xx_Gpio_Driver.c
 *
 *  Created on: Jul 28, 2023
 *      Author: Xavier.Rocher
 */


#include "stm32f446xx_Gpio_Driver.h"


//Peripheral Clock Setup
/********************************************************************************
 * @fn		- GPIO_PerCLKControl
 *
 * @brief	-
 *
 * @param[in]	- Base address of GPIO peripheral
 * @param[in]	-	Enable or Disable macro
 *
 * @return
 *
 * @Note
 *
 * */
void GPIO_PerCLKControl( GPIO_RegDef_t *pGPIOx, uint8_t Enable_Disable ){

	if( Enable_Disable == ENABLE){

		if( pGPIOx == GPIOA ){
			GPIOA_PCLCK_EN();
		}
		else if( pGPIOx == GPIOB ){
			GPIOB_PCLCK_EN();
		}
		else if( pGPIOx == GPIOC ){
			GPIOC_PCLCK_EN();
		}
		else if( pGPIOx == GPIOD ){
			GPIOD_PCLCK_EN();
		}
		else if( pGPIOx == GPIOE ){
			GPIOE_PCLCK_EN();
		}
		else if( pGPIOx == GPIOF ){
			GPIOF_PCLCK_EN();
		}
		else if( pGPIOx == GPIOG ){
			GPIOG_PCLCK_EN();
		}
		else if( pGPIOx == GPIOH ){
			GPIOH_PCLCK_EN();
		}
	}
	else if ( Enable_Disable == DISABLE ){

		if( pGPIOx == GPIOA ){
			GPIOA_PCLCK_DIS();
		}
		else if( pGPIOx == GPIOB ){
			GPIOB_PCLCK_DIS();
		}
		else if( pGPIOx == GPIOC ){
			GPIOC_PCLCK_DIS();
		}
		else if( pGPIOx == GPIOD ){
			GPIOD_PCLCK_DIS();
		}
		else if( pGPIOx == GPIOE ){
			GPIOE_PCLCK_DIS();
		}
		else if( pGPIOx == GPIOF ){
			GPIOF_PCLCK_DIS();
		}
		else if( pGPIOx == GPIOG ){
			GPIOG_PCLCK_DIS();
		}
		else if( pGPIOx == GPIOH ){
			GPIOH_PCLCK_DIS();
		}
	}
}


//Init&Deint
/********************************************************************************
 * @fn		- GPIO_Init
 *
 * @brief	-
 *
 * @param[in]	-
 * @param[in]	-
 *
 * @return		- none
 *
 * @Note		- none
 *
 * */
void GPIO_Init( GPIO_Handle_t *pGPIOHandle ){

	uint32_t temp 		= 0;
	uint8_t temp1 		= 0;
	uint8_t temp2 		= 0;
	uint8_t portcode 	= 0;

	
	GPIO_PerCLKControl( pGPIOHandle->pGPIOx, ENABLE );
	
	//1. Configure the mode of GPIO pin.

	if( pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG ){

		temp = (uint32_t) pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << ( 2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );

		pGPIOHandle->pGPIOx->MODER &= (uint32_t) ~( 0x03 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );
		pGPIOHandle->pGPIOx->MODER |= temp;
	}
	else{

		if( pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FALLING ){

			// 1. Configure FTSR

			EXTI->FTSR |= ( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );
			// CLear RTSR bit
			EXTI->RTSR &= ~( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );
		}
		else if( pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RISING ){
			// 1. Configure RTSR
			EXTI->RTSR |= ( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );
			EXTI->FTSR &= ~( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );
		}
		else if( pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RISING_FALLING ){
			// 1. Configure FTSR and RTSR.

			EXTI->FTSR |= ( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );
			EXTI->RTSR |= ( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );
		}

		//2.Configure the GPIO port selection selection in SYSCFG_EXTICR.

		temp1 = ( pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 4 ) ;
		temp2 = ( pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 4 ) ;
		portcode = GPIO_BASEADDR_TO_CODE( pGPIOHandle->pGPIOx );

		SYSCFG_PCLCK_EN();
		SYSCFGR->EXTICR[ temp1] = (uint32_t) portcode <<( temp2 * 4) ;

		//3. Enable the EXTI interrupt delivery using IMR.

		EXTI->IMR |= ( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );


	}
	 temp = 0;

	//2. Configure the speed.

	 temp = (uint32_t) pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << ( 2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );

	 pGPIOHandle->pGPIOx->OSPEEDER &= (uint32_t) ~( 0x03 << ( 2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber ) );
	 pGPIOHandle->pGPIOx->OSPEEDER |= temp;

	 temp = 0;

	//3. Configure the PUPD settings.

	 temp = (uint32_t) pGPIOHandle->GPIO_PinConfig.GPIO_PinPupdControl << ( 2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );

	 pGPIOHandle->pGPIOx->PUPDR &= (uint32_t) ~( 0x03 << ( 2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber ) );
	 pGPIOHandle->pGPIOx->PUPDR |= temp;

	 temp = 0;

	//4. Configure the OPType of GPIO pin.
	 temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );

	 pGPIOHandle->pGPIOx->OTYPER &= ~( 0x01 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );
	 pGPIOHandle->pGPIOx->OTYPER |= temp;

	temp = 0;
	//5. Configure the alternate functionality GPIO pin.
	if( pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ALTERNATE ){

		temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 8;
		temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8;

		pGPIOHandle->pGPIOx->AFR[temp1] &= (uint32_t) ~( 0xF << ( 4 * temp2) );
		pGPIOHandle->pGPIOx->AFR[temp1] |= (uint32_t) ( pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFuncMode << ( 4 * temp2) );

	}

}
void GPIO_DeInit( GPIO_RegDef_t *pGPIOx ){


		if( pGPIOx == GPIOA ){
			RESET_GPIOA();
		}
		else if( pGPIOx == GPIOB ){
			RESET_GPIOB();
		}
		else if( pGPIOx == GPIOC ){
			RESET_GPIOC();
		}
		else if( pGPIOx == GPIOD ){
			RESET_GPIOD();
		}
		else if( pGPIOx == GPIOE ){
			RESET_GPIOE();
		}
		else if( pGPIOx == GPIOF ){
			RESET_GPIOF();
		}
		else if( pGPIOx == GPIOG ){
			RESET_GPIOG();
		}
		else if( pGPIOx == GPIOH ){
			RESET_GPIOH();
		}


}

//Write/Read Data
/********************************************************************************
 * @fn		- GPIO_DeInit
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
uint8_t GPIO_ReadFromInputPin( GPIO_RegDef_t *pGPIOx ,uint8_t PinNumber ){

	uint8_t value = 0x00;

	value = (uint8_t) ( ( pGPIOx->IDR >> PinNumber ) & ( 0x01 << 0) );

	return value;
}

/********************************************************************************
 * @fn		- GPIO_ReadFromInputPin
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

uint16_t GPIO_ReadFromInputPort( GPIO_RegDef_t *pGPIOx ){

	uint16_t value = 0x00;

	value = (uint16_t) ( pGPIOx->IDR & 0x00FF );

	return value;
}

/********************************************************************************
 * @fn		- GPIO_ReadFromInputPort
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
void GPIO_WriteTouOutPutPin( GPIO_RegDef_t *pGPIOx , uint8_t PinNumber, uint8_t value){

	if( value == SET){
		pGPIOx->BSRR |= (uint32_t) ( 0x01 << PinNumber );
	}
	else if ( value == RESET ){
		pGPIOx->BSRR |= (uint32_t) ( (0x01 << 16) << PinNumber );
	}
}

/********************************************************************************
 * @fn		- GPIO_WriteTouOutPutPin
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
void GPIO_WriteTouOutPutPort( GPIO_RegDef_t *pGPIOx ,uint8_t value ){

	pGPIOx->ODR = (uint32_t) ( 0xFFFF & value );
}

/********************************************************************************
 * @fn		- GPIO_ToggleOutputPin
 *
 * @brief	-
 *
 * @param[in]	-	*pGPIOx
 * @param[in]	-	PinNumber
 *
 * @return
 *
 * @Note
 *
 * */
void GPIO_ToggleOutputPin( GPIO_RegDef_t *pGPIOx , uint8_t PinNumber ){

	pGPIOx->ODR ^= (uint32_t) ( 0x01 << PinNumber );
}

//IRQ Configuration and ISR handling
/********************************************************************************
 * @fn			- GPIO_IRQInterruptConfig
 *
 * @brief		-
 *
 * @param[in]	-	IRQNumber
 * @param[in]	-	Enable_Disable
 *
 * @return
 *
 * @Note
 *
 * */
void GPIO_IRQInterruptConfig( uint8_t IRQNumber, uint8_t Enable_Disable){

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

void GPIO_IRQConfigPriority( uint8_t IRQNumber, uint32_t IRQPriority ){

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
void GPIO_IRQHandling( uint8_t PinNumber ){

	// Clear the EXTI PR register corresponding to th epin number.

	if( EXTI->PR & ( 1 << PinNumber)){

		//Clear
		EXTI->PR |= ( 1 << PinNumber );
	}
}
