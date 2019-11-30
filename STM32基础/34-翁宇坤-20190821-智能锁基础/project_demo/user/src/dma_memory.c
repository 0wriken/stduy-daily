#include "dma_memory.h"
void dma1_channel2_init(u8 *m_addr,u8 *p_addr,u8 data_num)
{
	RCC->AHBENR|=(0x1<<0);
	DMA1_Channel2->CCR&=~(0XFF<<0);
	DMA1_Channel2->CCR|=(0x1<<14);//�����洢�����洢��
	DMA1_Channel2->CCR|=(0x1<<12);//���ȼ�Ϊ��
	DMA1_Channel2->CCR|=(0x3<<6);//��ַ��������
	DMA1_Channel2->CCR|=(0x3<<1);//���������ȫ�ж�

	DMA1_Channel2->CNDTR&=~(0XFF<<0);
	DMA1_Channel2->CNDTR=data_num;//���������ַ����
	DMA1_Channel2->CPAR=(u32)m_addr;
	DMA1_Channel2->CMAR=(u32)p_addr;	
	
	NVIC_SetPriority(DMA1_Channel2_IRQn,NVIC_EncodePriority(7-2,0,1));

	NVIC_EnableIRQ(DMA1_Channel2_IRQn);//��NVIC��Ӧ
	
	DMA1_Channel2->CCR|=(0x1<<0);//����ͨ��
}	
void DMA1_Channel2_IRQHandler()
{
	if(DMA1->ISR&(0X1<<6))
	{
		DMA1->IFCR|=(0X1<<6);
		GPIOB->ODR&=~(0x1<<6);//�봫����ɵ��
	}
	if(DMA1->ISR&(0X1<<5))
	{
		DMA1->IFCR|=(0X1<<5);
		GPIOB->ODR&=~(0x1<<8);
	}
}
