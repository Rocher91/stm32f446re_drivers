/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Xavier Rocher
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c)
 * All rights reserved.
 *
 ******************************************************************************
 */

#include "stm32f446xx.h"
#include "stm32f446xx_NVIC.h"

void DMA2_MemToMem_Config(void);
void DMA2_Transfer_Start(uint32_t src_buff, uint32_t dest_buff, uint32_t len);


void DMA2_MemToMem_Config(void)
{
	/* Enable CLock acces to DMA Module. */
	DMA2_PCLCK_EN();
	
	/* Disable DMA Strem. */
	DMA2->S0CR &= (uint32_t)~( 0x01 << DMA_SxCR_EN ); 
	
	/* Wait until STream is disabled. */
	while( ( DMA2->S0CR & ( 0x01 << DMA_SxCR_EN ) ) );
	
	/* Configure DMA parameters */
	
	//Set MSIZE Memory data Size to half word
	DMA2->S0CR |= ( MSIZE_HALF_WORD << DMA_SxCR_MSIZE);
	
	//Set PSIZE Peripheral data Size to half word
	DMA2->S0CR |= ( PSIZE_HALF_WORD << DMA_SxCR_PSIZE);
	
	// Enable peripheral addr increment
	DMA2->S0CR |= ( MEM_PINC_INCREMENT << DMA_SxCR_PINC);
	
	// Enable memory addr increment
	DMA2->S0CR |= ( MEM_INC_INCREMENT << DMA_SxCR_MINC);
	
	// Select Mem to Mem 
	DMA2->S0CR |= ( TRANSFER_MEMORY_TO_MEMORY << DMA_SxCR_DIR);
	
	//Transfer Complete Interrup Enabled
	//DMA2->S0CR |= ( TRANSFER_COMPLETE_INTERRUPT_ENABLE << DMA_SxCR_TCIE);
	
	//Transfer Error Interrup Enabled
	//DMA2->S0CR |= ( TRANSFER_ERROR_INTERRUPT_ENABLE << DMA_SxCR_TEIE);
	
	//Direct Mode Interrup Enabled
	//DMA2->S0CR |= ( DIRECT_MODE_ERROR_INTERRUPT_DISABLE << DMA_SxCR_DMEIE);
	
	/* Disable direct Mode. */
	
	DMA2->S0FCR |= ( DIRECT_MODE_DISABLE << DMA_SxFCR_DMDIS);
	
	/* Set DMA FIFO Threshold. */
	
	DMA2->S0FCR |= ( FULL_FIFO << DMA_SxFCR_FTH);
	
	/* Enable DMA Interrupt in NVIC. */
	IRQInterruptConfig( IRQ_DMA2_STREAM_0, ENABLE);
	
	
}


void DMA2_Transfer_Start(uint32_t src_buff, uint32_t dest_buff, uint32_t len)
{
	// Set peripheral Address
	DMA2->S0PAR = src_buff;
	
	// Set memory Address
	DMA2->S0M0AR = dest_buff;
	
	// Set transfer len
	DMA2->S0NDTR = len;
	
	// Enable DMA Stream
	DMA2->S0CR |= ( 0x01 << DMA_SxCR_EN ); 
}

int main(void)
{
	
	
				


}


