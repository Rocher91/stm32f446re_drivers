/*
 * stm32f446xx_Gpio_Driver.h
 *
 *  Created on: Jul 28, 2023
 *      Author: Xavier.Rocher
 */

#ifndef INC_STM32F446XX_GPIO_DRIVER_H_
#define INC_STM32F446XX_GPIO_DRIVER_H_

#include "stm32f446xx.h"


typedef struct{

	uint8_t GPIO_PinNumber;			/*< POSSIBLE VALUES FROM @GPIO PINS >*/
	uint8_t GPIO_PinMode;			/*< POSSIBLE VALUES FROM @GPIO MODER >*/
	uint8_t GPIO_PinSpeed;			/*< POSSIBLE VALUES FROM @GPIO SPEEDR >*/
	uint8_t GPIO_PinPupdControl;	/*< POSSIBLE VALUES FROM @GPIO PUPDR >*/
	uint8_t GPIO_PinOPType;			/*< POSSIBLE VALUES FROM @GPIO OTYPER >*/
	uint8_t GPIO_PinAltFuncMode;	/*< POSSIBLE VALUES FROM @GPIO ALTERNATE >*/

}GPIO_PinConfig_t;



typedef struct{

	GPIO_RegDef_t *pGPIOx;
	GPIO_PinConfig_t GPIO_PinConfig;

}GPIO_Handle_t;

/* GPIO pin  */

#define GPIO_PIN_0			0
#define GPIO_PIN_1			1
#define GPIO_PIN_2			2
#define GPIO_PIN_3			3
#define GPIO_PIN_4			4
#define GPIO_PIN_5			5
#define GPIO_PIN_6			6
#define GPIO_PIN_7			7
#define GPIO_PIN_8			8
#define GPIO_PIN_9			9
#define GPIO_PIN_10			10
#define GPIO_PIN_11			11
#define GPIO_PIN_12			12
#define GPIO_PIN_13			13
#define GPIO_PIN_14			14
#define GPIO_PIN_15			15


#define NUCLEO_PORT_LED		GPIOA
#define NUCLEO_PIN_LED		GPIO_PIN_5

#define NUCLEO_PORT_BUTTON	GPIOC
#define NUCLEO_PIN_BUTTON	GPIO_PIN_13

/* GPIO MODER -- 187 -- rm0390 */

#define GPIO_MODE_INPUT				0
#define GPIO_MODE_OUTPUT			1
#define GPIO_MODE_ALTERNATE			2
#define GPIO_MODE_ANALOG			3

#define GPIO_MODE_IT_FALLING		4
#define GPIO_MODE_IT_RISING			5
#define GPIO_MODE_IT_RISING_FALLING	6

/* GPIO OSPEEDR -- 188 -- rm0390 */

#define GPIO_LOW_SPEED				0
#define GPIO_MEDIUM_SPEED			1
#define GPIO_FAST_SPEED				2
#define GPIO_HIGH_SPEED				3

/* GPIO OTYPER -- 188 -- rm0390 */
#define GPIO_PUSH_PULL		0
#define GPIO_OPEN_DRAIN		1


/* GPIO PUPDR -- 189 -- rm0390 */
#define GPIO_NPUPD		0
#define GPIO_PU			1
#define GPIO_PD			2

/* GPIO AFRL -- 192 -- rm0390 */
#define GPIO_AF0		0
#define GPIO_AF1		1
#define GPIO_AF2		2
#define GPIO_AF3		3
#define GPIO_AF4		4
#define GPIO_AF5		5
#define GPIO_AF6		6
#define GPIO_AF7		7
#define GPIO_AF8		8
#define GPIO_AF9		9
#define GPIO_AF10		10
#define GPIO_AF11		11
#define GPIO_AF12		12
#define GPIO_AF13		13
#define GPIO_AF14		14
#define GPIO_AF15		15


//Peripheral Clock Setup
void GPIO_PerCLKControl( GPIO_RegDef_t *pGPIOx, uint8_t Enable_Disable );

//Init&Deint
void GPIO_Init( GPIO_Handle_t *pGPIOHandle );
void GPIO_DeInit( GPIO_RegDef_t *pGPIOx );

//Write/Read Data
uint8_t GPIO_ReadFromInputPin( GPIO_RegDef_t *pGPIOx ,uint8_t PinNumber );
uint16_t GPIO_ReadFromInputPort( GPIO_RegDef_t *pGPIOx );
void GPIO_WriteTouOutPutPin( GPIO_RegDef_t *pGPIOx , uint8_t PinNumber, uint8_t value);
void GPIO_WriteTouOutPutPort( GPIO_RegDef_t *pGPIOx ,uint8_t value );
void GPIO_ToggleOutputPin( GPIO_RegDef_t *pGPIOx , uint8_t PinNumber );

//IRQ Configuration and ISR handling
void GPIO_IRQInterruptConfig( uint8_t IRQNumber, uint8_t Enable_Disable);
void GPIO_IRQConfigPriority( uint8_t IRQNumber, uint32_t IRQPriority );
void GPIO_IRQHandling( uint8_t PinNumber );


#endif /* INC_STM32F446XX_GPIO_DRIVER_H_ */
