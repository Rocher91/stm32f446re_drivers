#ifndef INC_STM32F446XX_TIM_DRIVER_H_
#define INC_STM32F446XX_TIM_DRIVER_H_

#include "stm32f446xx.h"

typedef struct{
	
	uint16_t 		TIM_Preescaler;
	uint32_t 		TIM_Period;
	
}TIM_TimeBase_t;

typedef struct{
	
	General_Purpose_Timers_2_5_RegDef_t* pTIMx;
	TIM_TimeBase_t TIM_TimeBase;
	
}TIM_Basic_Handle_t;


/*
 * IRQ Configuration and ISR handling
 */
void TIM_ClearITPendingBit(General_Purpose_Timers_2_5_RegDef_t *pTIMx,uint16_t FlagName);
uint8_t TIM_GetStatus(General_Purpose_Timers_2_5_RegDef_t *pTIMx,uint16_t FlagName);

void TIM_IRQInterruptConfig( uint8_t IRQNumber, uint8_t Enable_Disable);
void TIM_IRQConfigPriority( uint8_t IRQNumber, uint32_t IRQPriority );
void TIM_IRQHandling( TIM_Basic_Handle_t *pTIMHandle );


void TIM_PerCLKControl( General_Purpose_Timers_2_5_RegDef_t *pTIMx, uint8_t Enable_Disable );
void TIM_Basic_TimeBase(TIM_Basic_Handle_t* pTIMHandle);
void TIM_Basic_ITConfig(General_Purpose_Timers_2_5_RegDef_t* pTIMx,uint16_t IT_type,uint8_t enable);
void TIM_Basic_DeInit(General_Purpose_Timers_2_5_RegDef_t* pTIMx);
void TIM_Basic_Init(General_Purpose_Timers_2_5_RegDef_t* pTIMx,uint8_t enable);

/*
* @Advance_Timers_
*/

//.. TIMx_CR1
#define TIMx_CR1_CEN 	0
#define TIMx_CR1_UDIS 1
#define TIMx_CR1_URS 	2
#define TIMx_CR1_OPM 	3
#define TIMx_CR1_DIR 	4
#define TIMx_CR1_CMS 	5
#define TIMx_CR1_ARPE 7
#define TIMx_CR1_CKD 	8

//.. TIMx_CR2
#define TIMx_CR2_CCCPC 	0
#define TIMx_CR2_CCUS 	2
#define TIMx_CR2_CCDS 	3
#define TIMx_CR2_MMS 		4
#define TIMx_CR2_TI1S 	7
#define TIMx_CR2_OIS1 	8
#define TIMx_CR2_OIS1N 	9
#define TIMx_CR2_OIS2 	10
#define TIMx_CR2_OIS2N 	11
#define TIMx_CR2_OIS3 	12
#define TIMx_CR2_OIS3N 	13
#define TIMx_CR2_OIS4 	14

//.. TIMx_SMCR
#define TIMx_SMCR_SMS 	0
#define TIMx_SMCR_TS 		4
#define TIMx_SMCR_MSM 	7
#define TIMx_SMCR_ETF 	8
#define TIMx_SMCR_ETPS 	12
#define TIMx_SMCR_ECE 	14
#define TIMx_SMCR_ETP 	15

//.. TIMx_DIER
#define TIMx_DIER_UIE 	0
#define TIMx_DIER_CC1IE 1
#define TIMx_DIER_CC2IE 2
#define TIMx_DIER_CC3IE 3
#define TIMx_DIER_CC4IE 4
#define TIMx_DIER_COMIE 5
#define TIMx_DIER_TIE 	6
#define TIMx_DIER_BIE 	7
#define TIMx_DIER_UDE 	8
#define TIMx_DIER_CC1DE 9
#define TIMx_DIER_CC2DE 10
#define TIMx_DIER_CC3DE 11
#define TIMx_DIER_CC4DE 12
#define TIMx_DIER_COMDE 13
#define TIMx_DIER_TDE 	14

//.. TIMx_SR
#define TIMx_SR_UIF 	0
#define TIMx_SR_CC1IF 1
#define TIMx_SR_CC2IF 2
#define TIMx_SR_CC3IF 3
#define TIMx_SR_CC4IF 4
#define TIMx_SR_COMIF 5
#define TIMx_SR_TIF 	6
#define TIMx_SR_BIF 	7
#define TIMx_SR_CC1OF 9
#define TIMx_SR_CC2OF 10
#define TIMx_SR_CC3OF 11
#define TIMx_SR_CC4OF 12

//.. TIMx_EGR
#define TIMx_EGR_UG 	0
#define TIMx_EGR_CC1G 1
#define TIMx_EGR_CC2G 2
#define TIMx_EGR_CC3G 3
#define TIMx_EGR_CC4G 4
#define TIMx_EGR_COMG 5
#define TIMx_EGR_TG 	6
#define TIMx_EGR_BG 	7


//.. TIMx_CCMR1
#define TIMx_CCMR1_CC1S 	0
#define TIMx_CCMR1_OC1FE 	2
#define TIMx_CCMR1_OC1PE 	3
#define TIMx_CCMR1_OC1M 	4
#define TIMx_CCMR1_OC1CE 	7
#define TIMx_CCMR1_CC3S 	8
#define TIMx_CCMR1_OC2FE 	10
#define TIMx_CCMR1_OC2PE 	11
#define TIMx_CCMR1_OC2M 	12
#define TIMx_CCMR1_OC2CE 	15

//.. TIMx_CCMR2
#define TIMx_CCMR2_CC3S 	0
#define TIMx_CCMR2_OC3FE 	2
#define TIMx_CCMR2_OC3PE 	3
#define TIMx_CCMR2_OC3M 	4
#define TIMx_CCMR2_OC3CE 	7
#define TIMx_CCMR2_CC4S 	8
#define TIMx_CCMR2_OC4FE 	10
#define TIMx_CCMR2_OC4PE 	11
#define TIMx_CCMR2_OC4M 	12
#define TIMx_CCMR2_OC4CE 	15
	

//.. TIMx_CCER
#define TIMx_CCER_CC1E 		0
#define TIMx_CCER_CC1P 		1
#define TIMx_CCER_CC1NE 	2
#define TIMx_CCER_CC1NP 	3
#define TIMx_CCER_CC2E 		4
#define TIMx_CCER_CC2P 		5
#define TIMx_CCER_CC2NE 	6
#define TIMx_CCER_CC2NP 	7
#define TIMx_CCER_CC3E 		8
#define TIMx_CCER_CC3P 		9
#define TIMx_CCER_CC3NE 	10
#define TIMx_CCER_CC3NP 	11
#define TIMx_CCER_CC4E 		12
#define TIMx_CCER_CC4P 		13


//.. TIMx_BDTR
#define TIMx_BDTR_DTG 		0
#define TIMx_BDTR_LOCK 		8
#define TIMx_BDTR_OSSI 		10
#define TIMx_BDTR_OSSR 		11
#define TIMx_BDTR_BKE 		12
#define TIMx_BDTR_BKP 		13
#define TIMx_BDTR_AOE 		14
#define TIMx_BDTR_MOE 		15

//.. TIMx_DCR
#define TIMx_DCR_DBA 			0
#define TIMx_DCR_DBL 			8

//.. TIM2_OR
#define TIM2_OR_ITR1_RMP 	10

//.. TIM5_OR
#define TIM5_OR_TI4_RMP 	6

//.. TIM11_OR
#define TIM11_OR_TI1_RMP 	0


#define TRIGGER_DMA_INTERRUPT 						1
#define CAPTURE_COMP1_DMA_INTERRUPT 			2
#define CAPTURE_COMP2_DMA_INTERRUPT 			3
#define CAPTURE_COMP3_DMA_INTERRUPT 			4
#define CAPTURE_COMP4_DMA_INTERRUPT 			5
#define UPDATE_DMA_REQUEST 								6
#define TRIGGER_INTERRUPT 								7
#define CAPTURE_COMP1_INTERRUPT 					8
#define CAPTURE_COMP2_INTERRUPT 					9
#define CAPTURE_COMP3_INTERRUPT 					10
#define CAPTURE_COMP4_INTERRUPT 					11
#define UPDATE_INTERRUPT 									12


#define CAPTURE_COMPARE4_OVERCAPTURE_FLAG		12
#define CAPTURE_COMPARE3_OVERCAPTURE_FLAG		8
#define CAPTURE_COMPARE2_OVERCAPTURE_FLAG		7
#define CAPTURE_COMPARE1_OVERCAPTURE_FLAG		9
#define TRIGGER_INTERRUPT_FLAG							6
#define CAPTURE_COMPARE4_INTERRUPT_FLAG			4
#define CAPTURE_COMPARE3_INTERRUPT_FLAG			3
#define CAPTURE_COMPARE2_INTERRUPT_FLAG			2
#define CAPTURE_COMPARE1_INTERRUPT_FLAG			1
#define UPDATE_INTERRUPT_FLAG								0



#endif