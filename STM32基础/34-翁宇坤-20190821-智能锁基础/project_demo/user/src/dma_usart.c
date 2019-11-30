#include "dma_usart.h"
u32 flag1=0;
void dma1_stream7_init(u8 *m_addr,u8 *p_addr,u16 data_num)
{
		usart_init(115200);
		RCC->AHBENR|=(0x1<<0);
		DMA1_Channel7->CCR&=~(0XFF<<0);
		DMA1_Channel7->CCR|=(0X1<<12);//优先级为高
		DMA1_Channel7->CCR|=(0x1<<7);//存储器地址增量
		DMA1_Channel7->CCR|=(0x1<<4);//数据由存储器读
		DMA1_Channel7->CCR|=(0x1<<1);//传输完成中断
		DMA1_Channel7->CCR|=(0x1<<0);//通道开启
		DMA1_Channel7->CNDTR&=~(0XFF<<0);
		DMA1_Channel7->CNDTR=data_num;//数据项与地址配置
		DMA1_Channel7->CPAR=(u32)p_addr;
		DMA1_Channel7->CMAR=(u32)m_addr;
		NVIC_SetPriority(DMA1_Channel7_IRQn,NVIC_EncodePriority(7-2,1,2));

		NVIC_EnableIRQ(DMA1_Channel7_IRQn);//打开NVIC响应
		USART2->CR3|=(0X1<<7);
		while(!flag1)
	{
		;
	}
	flag1=0;
	DMA1_Channel7->CCR|=(0X1<<0);//开启
	
}
void DMA1_Channel7_IRQHandler()
{
	if(DMA1->ISR&(0x1<<25))
	{
		DMA1->IFCR|=(0x1<<25);
		flag1=1;
	}
}








