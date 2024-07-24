#ifndef INC_STM32F446XX_NVIC_DRIVER_H_
#define INC_STM32F446XX_NVIC_DRIVER_H_

#include "stm32f446xx.h"

void IRQInterruptConfig( uint8_t IRQNumber, uint8_t Enable_Disable);
void IRQConfigPriority( uint8_t IRQNumber, uint32_t IRQPriority );
void IRQHandling( uint8_t PinNumber );

#endif
