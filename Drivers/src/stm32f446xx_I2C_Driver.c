
#include "stm32f446xx_I2C_Driver.h"


void I2C_PeripheralControl( I2C_RegDef_t *pI2Cx, uint8_t Enable_Disable )
{
    if (Enable_Disable == ENABLE)
    {
        pI2Cx->CR[0] |= ( 1 << I2C_CR1_PE ); 
    }
    else
    {
        pI2Cx->CR[0] &= ~( 1 << I2C_CR1_PE ); 
    }
}

/*
 * Init and De-init
 */

void I2C_Init(I2C_Handle_t *pI2CHandle )
{

}

void I2C_DeInit( I2C_Handle_t *pI2Cx )
{

}