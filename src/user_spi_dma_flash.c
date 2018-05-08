/*
 * user_spi_dma_flash.c
 *
 *  Created on: 2018年5月8日
 *      Author: guo
 */

#include "user_spi_dma_flash.h"

#include "stm32f10x_dma.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_flash.h"
#include "ctype.h"
#include "string.h"
uint32_t Tx_Buffer[256];
uint32_t Rx_Buffer[256];

void Tx_Buffer_init(void){
#if 0
	for(int i = 0; i < sizeof(Tx_Buffer)/sizeof(uint32_t); i++){
		Tx_Buffer[i] = i;
	}
#else
	memset(Tx_Buffer, 0, sizeof(Tx_Buffer));
	memset(Rx_Buffer, 0, sizeof(Rx_Buffer));
#endif
}


void dma_config(void){
	DMA_InitTypeDef DMA_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	DMA_DeInit(DMA1_Channel2); //将DMA的通道x寄存器重设为缺省值
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&SPI1->DR; //该参数用以定义DMA 外设基地址
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)Rx_Buffer; //该参数用以定义DMA  内存基地址

	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC; //外设作为数据传输的来源
	DMA_InitStructure.DMA_BufferSize = sizeof(Rx_Buffer)/sizeof(uint32_t);
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //外设地址寄存器递增
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//设定了外设数据宽度
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; //用来设定内存地址寄存器递增与否
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;//设置了DMA的工作模式, 工作在正常缓存模式;
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh; //设定DMA通道x的软件优先级/DMA通道x拥有非常高优先级
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable; //使能DMA通道的内存到内存传输/DMA 通道x没有设置为内存到内存传输
	DMA_Init(DMA1_Channel2, &DMA_InitStructure);

	DMA_DeInit(DMA1_Channel3);
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&SPI1->DR;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)Tx_Buffer;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_InitStructure.DMA_BufferSize = 256;
	DMA_Init(DMA1_Channel3, &DMA_InitStructure);

	DMA_Cmd(DMA1_Channel2, ENABLE);
	DMA_Cmd(DMA1_Channel3, ENABLE);
}


void spi_dma_page_write(u32 write_addr){


}


