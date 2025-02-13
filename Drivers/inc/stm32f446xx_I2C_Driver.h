#ifndef INC_STM32F446XX_I2C_DRIVER_H_
#define INC_STM32F446XX_I2C_DRIVER_H_

#include "stm32f446xx.h"


typedef struct{

    uint32_t    I2C_SCL_Speed;
    uint8_t     I2C_DeviceAddress;
    uint8_t     I2C_ACK_Control;
    uint16_t    I2C_FM_DutyCycle;

} I2C_Config_t;


typedef struct 
{
    I2C_RegDef_t    *pI2Cx;
    I2C_Config_t    I2C_Config;
    uint8_t         *pTxBuffer;
    uint8_t         *pRxBuffer;
    uint8_t         TxLen;
    uint8_t         RxLen;
    uint8_t         TxRxState;
    uint8_t         DevAddress;
    uint32_t        RxSize;
    uint8_t         Sr;

}I2C_Handle_t;

/* I2C_SCL_Speed*/
#define I2C_SCL_SPEED_SM    100000
#define I2C_SCL_SPEED_FM2k  200000
#define I2C_SCL_SPEED_FM4K  400000

/* I2C_ACK_Control*/
#define I2C_ACK_ENABLE      1
#define I2C_ACK_DISABLE     0

/* I2C_FM_DutyCycle*/
#define I2C_FM_DUTY_2       0
#define I2C_FM_DUTY_16_9    1


//.. I2C_CR1
#define I2C_CR1_PE 				0
#define I2C_CR1_SMBUS 			1
#define I2C_CR1_SMBTYPE 		3
#define I2C_CR1_ENARP 			4
#define I2C_CR1_ENPEC 			5
#define I2C_CR1_ENGC 			6
#define I2C_CR1_NOSTRETCH 	    7	
#define I2C_CR1_START 			8
#define I2C_CR1_STOP 			9
#define I2C_CR1_ACK 			10
#define I2C_CR1_POS 			11
#define I2C_CR1_PEC 			12
#define I2C_CR1_ALERT 			13
#define I2C_CR1_SWRST 			15

//.. I2C_CR2
#define I2C_CR2_FREQ 			0
#define I2C_CR2_ITERREN 		8
#define I2C_CR2_ITEVTEN 		9
#define I2C_CR2_ITBUFEN 		10
#define I2C_CR2_DMAEN 			11
#define I2C_CR2_LAST 		    12

//.. I2C_OAR1
#define I2C_OAR1_ADD0 			0
#define I2C_OAR1_ADD_7_1		1
#define I2C_OAR1_ADD_9_8 		8
#define I2C_OAR1_ADDMODE 		15


//.. I2C_OAR2
#define I2C_OAR2_ENDUAL 		0
#define I2C_OAR2_ADD2_7_1		1


//.. I2C_DR
#define I2C_DR 					0

//.. I2C_SR1
#define I2C_SR1_SB 				0
#define I2C_SR1_ADDR 			1
#define I2C_SR1_BTF 			2
#define I2C_SR1_ADD10 			3
#define I2C_SR1_STOPF 			4
#define I2C_SR1_RxNE 			6
#define I2C_SR1_TxE 			7
#define I2C_SR1_BERR 			8
#define I2C_SR1_ARLO 			9
#define I2C_SR1_AF 				10
#define I2C_SR1_OVR 			11
#define I2C_SR1_PECERR 			12
#define I2C_SR1_TIMEOUT 		14
#define I2C_SR1_SMBALERT 		15

//.. I2C_SR2
#define I2C_SR2_MSL 			0
#define I2C_SR2_BUSY 			1
#define I2C_SR2_TRA 			2
#define I2C_SR2_GENCALL 		4
#define I2C_SR2_SMBDEFAULT 	    5
#define I2C_SR2_SMBHOST 		6
#define I2C_SR2_DUALF 			7
#define I2C_SR2_PEC_7_0 		8

//.. I2C_CCR
#define I2C_CCR 				0
#define I2C_DUTY 				14
#define I2C_F_S 				15

//.. I2C_TRISE
#define I2C_TRISE_5_0 			0

//.. I2C_FLTR
#define I2C_FLTR_DNF 			0
#define I2C_FLTR_ANOFF 			4


//FLAGS I2C

#define I2C_SB_FLAG                ( 1 << I2C_SR1_SB )
#define I2C_ADDR_FLAG              ( 1 << I2C_SR1_ADDR )
#define I2C_BTF_FLAG               ( 1 << I2C_SR1_BTF )
#define I2C_ADD10_FLAG             ( 1 << I2C_SR1_ADD10 )
#define I2C_STOPF_FLAG             ( 1 << I2C_SR1_STOPF )
#define I2C_RxNE_FLAG              ( 1 << I2C_SR1_RxNE )
#define I2C_TxE_FLAG              ( 1 << I2C_SR1_TxE )
#define I2C_BERR_FLAG              ( 1 << I2C_SR1_BERR )
#define I2C_ARLO_FLAG              ( 1 << I2C_SR1_ARLO )
#define I2C_AF_FLAG                ( 1 << I2C_SR1_AF )
#define I2C_OVR_FLAG               ( 1 << I2C_SR1_OVR )
#define I2C_PEC_ERROR_FLAG         ( 1 << I2C_SR1_PECERR )
#define I2C_TIMEOUT_FLAG           ( 1 << I2C_SR1_TIMEOUT )
#define I2C_SMB_ALERT_FLAG         ( 1 << I2C_SR1_SMBALERT )
#define I2C_SB_FLAG                ( 1 << I2C_SR1_SB )

#define I2C_ENABLE_SR		    SET
#define I2C_DISABLE_SR		    RESET


#define I2C_READY               0
#define I2C_BUSY_IN_TX          1
#define I2C_BUSY_IN_RX          2


void I2C_PerCLKControl( I2C_RegDef_t *pI2Cx, uint8_t Enable_Disable );

/*
 * Init and De-init
 */

void I2C_Init(I2C_Handle_t *pI2CHandle );
void I2C_DeInit( I2C_Handle_t *pI2Cx );


/*
 * Data Send and Receive
 */

static void I2C_GenerateStartCondition(I2C_RegDef_t *pI2Cx);
static void I2C_GenerateStopCondition(I2C_RegDef_t *pI2Cx);
static void I2C_ExecuteAddressPhaseWrite( I2C_RegDef_t *pI2Cx, uint8_t slaveAddress );
static void I2C_ExecuteAddressPhaseRead( I2C_RegDef_t *pI2Cx, uint8_t slaveAddress );
static void I2C_ClearADDRFlag(I2C_RegDef_t *pI2Cx);

void I2C_MasterSendData( I2C_Handle_t *pI2CHandle, uint8_t *pTxBuffer, uint8_t Len, uint8_t slaveAddress, uint8_t Sr);
void I2C_MasterReceiveData( I2C_Handle_t *pI2CHandle, uint8_t *pRxBuffer, uint8_t Len, uint8_t slaveAddress , uint8_t Sr);

uint8_t I2C_MasterSendDataIT( I2C_Handle_t *pI2CHandle, uint8_t *pTxBuffer, uint8_t Len, uint8_t slaveAddress, uint8_t Sr);
uint8_t I2C_MasterReceiveDataIT( I2C_Handle_t *pI2CHandle, uint8_t *pRxBuffer, uint8_t Len, uint8_t slaveAddress , uint8_t Sr);

void I2C_ScanBus(I2C_Handle_t *pI2CHandle );

void I2C_ManageAcking(I2C_RegDef_t *pI2Cx,uint8_t Enable_Disable);
/*
 * IRQ Configuration and ISR handling
 */
 
void I2C_IRQInterruptConfig( uint8_t IRQNumber, uint8_t Enable_Disable);
void I2C_IRQConfigPriority( uint8_t IRQNumber, uint32_t IRQPriority );


 /*
 * Other Peripheral Control APIs
 */
 
void I2C_PeripheralControl(I2C_RegDef_t *pI2Cx,uint8_t Enable);
uint8_t I2C_GetFlagStatus(I2C_RegDef_t *pI2Cx, uint32_t FlagName);


 
 /*
	Application Callback
 */
void I2C_ApplicationEventCallback(I2C_Handle_t*pI2CHandle,uint8_t AppEv);

#endif