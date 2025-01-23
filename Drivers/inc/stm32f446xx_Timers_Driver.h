#ifndef INC_STM32F446XX_TIMS_DRIVER_H_
#define INC_STM32F446XX_TIMS_DRIVER_H_

#include "stm32f446xx.h"

#define TIM_IS_ADV_TIMER(x) ( ( ( x ) == TIM1 ) || ( ( x ) == TIM8 ) )

#define TIM_IS_BASIC_TIMER(x) ( ( ( x ) == TIM6 ) || ( ( x ) == TIM7 ) )

#define TIM_IS_GP_TIMER(x) 		(((x) == TIM2 ) || ( (x) == TIM3 ) || ( (x) == TIM4 ) || ( (x) == TIM5 ) ||\
															 ((x) == TIM9 ) || ( (x) == TIM10 ) || ( (x) == TIM11 ) || ( (x) == TIM12 ) ||\
															 ((x) == TIM13 ) || ( (x) == TIM14 ) \
															)


/*
	**No-channels:
			- Basic Timers(16 bits)	: TIM10,TIM11,TIM13,TIM14.
	
	-> CH1,CH2:
			- GP Timers (16 bits)	: TIM9 y TIM12 / TIM3 y TIM4.
			- GP Timers (32 bits)	: TIM2 y TIM5.
			- ADV Timers (16 bits): TIM1 y TIM8.
			
	-> CH2,CH3:
			- GP Timers (16 bits)	: TIM3 y TIM4.
			- GP Timers (32 bits)	: TIM2 y TIM5.
			- ADV Timers (16 bits): TIM1 y TIM8.
	
	-> CH1,CH2,CH3,CH4:
			- GP Timers (16 bits)	: TIM y TIM4.
			- GP Timers (32 bits)	: TIM2 y TIM5.
			- ADV Timers (16 bits): TIM1 y TIM8.
*/

#define TIM_HAS_CH1(x)  ((( x ) != TIM6 ) && ( ( x ) != TIM7 ))

#define TIM_HAS_CH2(x)  ((( x ) == TIM1 ) || ( ( x ) == TIM8 ) ||\
												 (( x ) == TIM2 ) || ( ( x ) == TIM3 ) || ( ( x ) == TIM4 ) || ( ( x ) == TIM5 ) ||\
												 (( x ) == TIM9 ) || ( ( x ) == TIM12 ) \
												)

#define TIM_HAS_CH3(x) ( (( x ) == TIM1 ) || ( ( x ) == TIM8 ) ||\
												 (( x ) == TIM2 ) || ( ( x ) == TIM3 ) ||\
												 (( x ) == TIM4 ) || ( ( x ) == TIM5 ) \
											 )
															
#define TIM_HAS_CH4(x) ( (( x ) == TIM1 ) || ( ( x ) == TIM8 ) ||\
												 (( x ) == TIM2 ) || ( ( x ) == TIM3 ) ||\
												 (( x ) == TIM4 ) || ( ( x ) == TIM5 ) \
											 )
											 

#define TIM_HAS_MS_FUNCTIONALITY(x) ( (( x ) == TIM2 ) || ( ( x ) == TIM3 ) ||\
																		(( x ) == TIM4 ) || ( ( x ) == TIM5 ) ||\
																		(( x ) == TIM1 ) || ( ( x ) == TIM8 ) \
																		)
											 
typedef enum{
	
	TIM_CounterMode_CenterAlign1 	= 1,
	TIM_CounterMode_CenterAlign2 	= 2,
	TIM_CounterMode_CenterAlign3 	= 3,
	TIM_CounterMode_UP 						= 4,
	TIM_CounterMode_DOWN 					= 5
	
}TIM_CounterMode_t;

typedef enum{
	TIM_ICSelection_Direct 		= 1,
	TIM_ICSelection_Indirect 	= 2,
	TIM_ICSelection_TRC 			= 3,

}TIM_ICSelection_t;

typedef enum{
	TIM_CH1,
	TIM_CH2,
	TIM_CH3,
	TIM_CH4
}TIM_Channels_t;

typedef enum{
	TIM_ICPolarity_RE,
	TIM_ICPolarity_FE,
	TIM_ICPolarity_RRE,

}TIM_ICPolarity_t;

typedef enum{
	TIM_OCPolarity_Active_HIGH,
	TIM_OCPolarity_Active_LOW,
}TIM_OCPolarity_t;

typedef enum{
	TIM_OCMode_Frozen,
	TIM_OCMode_Active,
	TIM_OCMode_Inactive,
	TIM_OCMode_Toggle,
	TIM_OCMode_Force_Inactive,
	TIM_OCMode_Force_Active,
	TIM_OCMode_PWM1,
	TIM_OCMode_PWM2
	
}TIM_OC_Modes_t;

typedef enum{
	TIM_ICPrescaler_NONE,
	TIM_ICPrescaler_2,
	TIM_ICPrescaler_4,
	TIM_ICPrescaler_8,

}TIM_ICPrescaler_t;

typedef enum{
	
	TIM_ICFilter_NONE,
	TIM_ICFilter_Fck_int_2,
	TIM_ICFilter_Fck_int_4,
	TIM_ICFilter_Fck_int_8,
	TIM_ICFilter_Fdts_div2_6,
	TIM_ICFilter_Fdts_div2_8,
	TIM_ICFilter_Fdts_div4_6,
	TIM_ICFilter_Fdts_div4_8,
	TIM_ICFilter_Fdts_div8_6,
	TIM_ICFilter_Fdts_div8_8,
	TIM_ICFilter_Fdts_div16_5,
	TIM_ICFilter_Fdts_div16_6,
	TIM_ICFilter_Fdts_div16_8,
	TIM_ICFilter_Fdts_div32_5,
	TIM_ICFilter_Fdts_div32_6,
	TIM_ICFilter_Fdts_div32_8

}TIM_ICFilter_t;

typedef struct{
	uint16_t TIM_Preescaler; 
	uint32_t TIM_Period;		// ARR	
	TIM_CounterMode_t TIM_CounterMode;
	
}TIM_TimeBase_t;


typedef struct{
	TIM_Channels_t     TIM_Channel;
	TIM_ICPolarity_t   TIM_IC_Polarity;
	TIM_ICSelection_t  TIM_IC_Selection;
	TIM_ICPrescaler_t  TIM_IC_Prescaler;
	TIM_ICFilter_t     TIM_IC_Filter;
	
}TIM_InputCapture_t;

typedef struct{
	TIM_Channels_t     	TIM_Channel;
	TIM_OC_Modes_t   		TIM_OC_Mode;
	TIM_OCPolarity_t   	TIM_OC_Polarity;
	uint32_t     				TIM_Pulse;
	
}TIM_OutputCompare_t;

typedef struct{
	
	TIM_RegDef_t* pTIMx;
	TIM_TimeBase_t TIM_TimeBase;
	TIM_InputCapture_t TIM_InputCapture;
	TIM_OutputCompare_t TIM_OutputCompare;
	
}TIM_handle_t;

typedef enum{
	
	TIM_EVENT_UI,
	TIM_EVENT_CC1I,
	TIM_EVENT_CC2I,
	TIM_EVENT_CC3I,
	TIM_EVENT_CC4I,
	TIM_EVENT_COMI,
	TIM_EVENT_TI,
	TIM_EVENT_BI,
	TIM_EVENT_CC10,
	TIM_EVENT_CC20,
	TIM_EVENT_CC30,
	TIM_EVENT_CC40

}TIM_Event_t;

typedef enum{
	
	TIM_Trigger_Internal_0,
	TIM_Trigger_Internal_1,
	TIM_Trigger_Internal_2,
	TIM_Trigger_Internal_3,
	TIM_Trigger_Edge_Detector_TI1,
	TIM_Trigger_Filtered_Timer_Input_1,
	TIM_Trigger_Filtered_Timer_Input_2,
	TIM_Trigger_External,

}TIM_Trigger_t;

typedef enum{
	
	TIM_Slave_Mode_Disabled,
	TIM_Slave_Encoder_Mode_1,
	TIM_Slave_Encoder_Mode_2,
	TIM_Slave_Encoder_Mode_3,
	TIM_Slave_Reset_Mode,
	TIM_Slave_Gated_Mode,
	TIM_Slave_Trigger_Mode,
	TIM_Slave_External_Mode1

}TIM_Slave_t;

typedef enum{
	
	TIM_MasterOutput_Reset,
	TIM_MasterOutput_Enable,
	TIM_MasterOutput_Update,
	TIM_MasterOutput_Compare_Pulse,
	TIM_MasterOutput_OC1REF,
	TIM_MasterOutput_OC2REF,
	TIM_MasterOutput_OC3REF,
	TIM_MasterOutput_OC4REF,

}TIM_MasterOutput_t;

/************APIS************/

void TIM_ClockController(TIM_RegDef_t* pTIMx,uint8_t enable); // Enable clock TIMER
void TIM_TimeBase_Init(TIM_handle_t* pTIM_Handle); // Configuraciones TIMER
void TIM_ClearITPendingBit(TIM_RegDef_t *pTIMx,uint16_t TIM_IT);
uint8_t TIM_GetStatus(TIM_RegDef_t *pTIMx,uint16_t TIM_IT);
void TIM_IRQHandling( TIM_handle_t *pTIMHandle );


uint32_t TIM_GetCounter(TIM_RegDef_t* pTIMx);
void TIM_SetCounter(TIM_RegDef_t* pTIMx,uint32_t counter);
uint32_t TIM_GetCapture(TIM_RegDef_t* pTIMx,TIM_Channels_t TIM_Channel);
void TIM_SetCompare(TIM_RegDef_t* pTIMx,TIM_Channels_t TIM_Channel,uint32_t value);



void TIM_ITConfig(TIM_RegDef_t* pTIMx,uint16_t IT_type,uint8_t enable);
void TIM_Init(TIM_RegDef_t* pTIMx,uint8_t enable);
void TIM_DeInit(TIM_RegDef_t* pTIMx);
void TIM_EventCallback(TIM_handle_t* pTIMHandle,TIM_Event_t event);

/*Input Capture*/
void TIM_ICInit(TIM_handle_t* pTIMHandle);
void TIM_OCInit(TIM_handle_t* pTIMHandle);


//Configurar esclavo
void TIM_InputTrigger(TIM_RegDef_t* pTIMx,TIM_Trigger_t trigger);
void TIM_SlaveMode(TIM_RegDef_t* pTIMx, TIM_Slave_t mode);

//Configurar Maestro
void TIM_MasterTriggerOutput(TIM_RegDef_t* pTIMx, TIM_MasterOutput_t output);


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
#define TIMx_CCMR1_CC1S 		0
#define TIMx_CCMR1_IC1PSC 	2
#define TIMx_CCMR1_OC1FE 		2
#define TIMx_CCMR1_OC1PE 		3
#define TIMx_CCMR1_OC1M 		4
#define TIMx_CCMR1_IC1F 		4
#define TIMx_CCMR1_OC1CE 		7
#define TIMx_CCMR1_CC2S 		8
#define TIMx_CCMR1_IC2PSC 	10
#define TIMx_CCMR1_OC2FE 		10
#define TIMx_CCMR1_OC2PE 		11
#define TIMx_CCMR1_IC2F			12
#define TIMx_CCMR1_OC2M 		12
#define TIMx_CCMR1_OC2CE 		15

//.. TIMx_CCMR2
#define TIMx_CCMR2_CC3S 	0
#define TIMx_CCMR2_IC3PSC 2
#define TIMx_CCMR2_OC3FE 	2
#define TIMx_CCMR2_OC3PE 	3
#define TIMx_CCMR2_OC3M 	4
#define TIMx_CCMR2_IC3F 	4
#define TIMx_CCMR2_OC3CE 	7
#define TIMx_CCMR2_CC4S 	8
#define TIMx_CCMR2_OC4FE 	10
#define TIMx_CCMR2_IC4PSC 10
#define TIMx_CCMR2_OC4PE 	11
#define TIMx_CCMR2_IC4F 	12
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
#define TIMx_CCER_CC4NP 	15


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
