/*
 * stm32f446xx_USART_Driver.h
 *
 *  Created on: April 23, 2025
 *      Author: Xavier.Rocher
 */

#ifndef INC_STM32F446XX_UART_DRIVER_H_
#define INC_STM32F446XX_UART_DRIVER_H_

#include "stm32f446xx.h"

typedef struct{

	uint8_t Mode;
	uint32_t Baudrate;
	uint8_t N_StopBits;
	uint8_t WordLength;
	uint8_t ParityControl;
	uint8_t HW_FlowControl;
	
}USART_Config_t;


typedef struct{

	USART_RegDef_t *pUSARTx;
	USART_Config_t  USART_Config;
	uint8_t *pTxBuffer;
	uint8_t *pRxBuffer;
	uint32_t TxLen;
	uint32_t RxLen;
	uint8_t TxBusyState;
	uint8_t RxBusyState;
	
}USART_Handle_t;

/*
*@USART_Mode
*Possible options for USART_Mode
*/
#define USART_MODE_ONLY_TX 	0
#define USART_MODE_ONLY_RX 	1
#define USART_MODE_TXRX 		2

/*
*@USART_Baudrate
*Possible options for USART_Baudrate
*/

#define USART_BAUDRATE_1200 		1200
#define USART_BAUDRATE_2400 		2400
#define USART_BAUDRATE_9600 		9600
#define USART_BAUDRATE_19200 		19200
#define USART_BAUDRATE_38400 		38400
#define USART_BAUDRATE_57600 		57600
#define USART_BAUDRATE_115200 	115200
#define USART_BAUDRATE_230400 	230400
#define USART_BAUDRATE_460800 	460800
#define USART_BAUDRATE_921600 	921600
#define USART_BAUDRATE_2M 			2000000
#define USART_BAUDRATE_3M 			3000000


/*
 *@USART_WordLength
 *Possible options for USART_WordLength
 */
#define USART_WORDLEN_8BITS  0
#define USART_WORDLEN_9BITS  1


/*
*@USART_ParityControl
*Possible options for USART_ParityControl
*/

#define USART_PARITY_DISABLE 		0
#define USART_PARITY_EN_ODD 		1
#define USART_PARITY_EN_EVEN 		2

/*
*@USART_ParityControl
*Possible options for USART_ParityControl
*/

#define USART_STOPBITS_0_5 		1
#define USART_STOPBITS_1 			0
#define USART_STOPBITS_1_5 		2
#define USART_STOPBITS_2			3

/*
*@USART_HW_FlowControl
*Possible options for USART_HW_FlowControl
*/

#define USART_HW_FLOW_CONTROL_NONE 			0
#define USART_HW_FLOW_CONTROL_CTS 			1
#define USART_HW_FLOW_CONTROL_RTS 			2
#define USART_HW_FLOW_CONTROL_CTS_RTS 	3

#define USART_TXE_FLAG  					(1<<USART_SR_TXE)
#define USART_RXNE_FLAG  					(1<<USART_SR_RXNE)
#define USART_PARITY_CONTROL_FLAG (1<<USART_CR1_PCE)
#define USART_TX_COMPLETE_FLAG  	(1<<USART_SR_TC)

/*
 * Application states
 */
#define USART_BUSY_IN_RX 1
#define USART_BUSY_IN_TX 2
#define USART_READY 0


#define 	USART_EVENT_TX_CMPLT   0
#define		USART_EVENT_RX_CMPLT   1
#define		USART_EVENT_IDLE      2
#define		USART_EVENT_CTS       3
#define		USART_EVENT_PE        4
#define		USART_ERREVENT_FE     	5
#define		USART_ERREVENT_NF    	 6
#define		USART_ERREVENT_ORE    	7


/******************************************************************************************
 *								APIs supported by this driver
 *		 For more information about the APIs check the function definitions
 ******************************************************************************************/

/*
 * Peripheral Clock setup
 */
void USART_PeripheralClockControl( USART_RegDef_t * pUSARTx, uint8_t Enable );

/*
 * Init and De-init
 */
void USART_Init(USART_Handle_t *pUSARTHandle);
void USART_DeInit(USART_RegDef_t *pUSARTx);


void USART_SetBaudRate(USART_RegDef_t *pUSARTx, uint32_t BaudRate);

/*
 * Data Send and Receive
 */
void USART_SendData(USART_Handle_t *pUSARTHandle, uint8_t *pTxBuffer, uint32_t Len);
void USART_ReceiveData(USART_Handle_t *pUSARTHandle, uint8_t *pRxBuffer, uint32_t Len);
uint8_t USART_SendDataIT(USART_Handle_t *pUSARTHandle,uint8_t *pTxBuffer, uint32_t Len);
uint8_t USART_ReceiveDataIT(USART_Handle_t *pUSARTHandle, uint8_t *pRxBuffer, uint32_t Len);

/*
 * IRQ Configuration and ISR handling
 */
void USART_IRQInterruptConfig(uint8_t IRQNumber, uint8_t Enable);
void USART_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void USART_IRQHandling(USART_Handle_t *pHandle);

/*
 * Other Peripheral Control APIs
 */
void USART_PeripheralControl( USART_RegDef_t * pUSARTx, uint8_t Enable );
uint8_t USART_GetFlagStatus( USART_RegDef_t * pUSARTx, uint8_t StatusFlagName );
void USART_ClearFlagStatus( USART_RegDef_t * pUSARTx, uint8_t StatusFlagName );

/*
 * Application callback
 */
void USART_ApplicationEventCallback(USART_Handle_t *pUSARTHandle,uint8_t AppEv);


#endif /* INC_STM32F446XX_UART_DRIVER_H_ */
