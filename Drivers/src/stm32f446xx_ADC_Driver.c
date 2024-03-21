/*
 * stm32f446xx_ADC_Driver.c
 *
 *  Created on: Aug 7, 2023
 *      Author: Xavier.Rocher
 */


#include "stm32f446xx_ADC_Driver.h"




void ADC_Init(GPIO_RegDef_t* pGPIOx , ADC_RegDef_t  *pADCx ,uint8_t nChannel,uint8_t nConversions  ){

	/***Configure the ADC GPIO pin***/

	//Enable Clock GPIOx

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

	//Set the mode GPIO to analog
	pGPIOx->MODER |= ( 0x03 << nChannel );

	//Enable Clock ADCx
	if( pADCx == ADC1 ){
		ADC1_PCLCK_EN();
	}
	else if( pADCx == ADC2 ){
		ADC2_PCLCK_EN();
	}
	else if( pADCx == ADC3 ){
		ADC3_PCLCK_EN();
	}

	//Conversion sequence start
	pADCx->SQR[2]  |= ADC_CHANNEL_VALUE( nChannel );

	//Conversion sequence length
	pADCx->SQR[0]  |= ( ADC_N_CONVERSION( nConversions ) << 20 ) ;

	//Enable ADC module
	pADCx->CR[1] |= ( 0x01 << 0);


}


void start_ADC_Conversion( void ){

	//Start ADC Conversion
	ADC1->CR[1] |= ( 0x01 << 30 );

}

uint32_t adc_read( void ){

	/*Wait for conversion to be complete*/
	while( !(ADC1->SR & ( 0x01 << 1)) );

	/*Read conversion result*/
	return (ADC1->DR);
}
