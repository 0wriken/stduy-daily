#include "dma_usart.h"
u32 flag1=0;
void dma1_stream7_init(u8 *m_addr,u8 *p_addr,u16 data_num)
{
		usart_init(115200);
		RCC->AHBENR|=(0x1<<0);
		DMA1_Channel7->CCR&=~(0XFF<<0);
		DMA1_Channel7->CCR|=(0X1<<12);//���ȼ�Ϊ��
		DMA1_Channel7->CCR|=(0x1<<7);//�洢����ַ����
		DMA1_Channel7->CCR|=(0x1<<4);//�����ɴ洢����
		DMA1_Channel7->CCR|=(0x1<<1);//��������ж�
		DMA1_Channel7->CCR|=(0x1<<0);//ͨ������
		DMA1_Channel7->CNDTR&=~(0XFF<<0);
		DMA1_Channel7->CNDTR=data_num;//���������ַ����
		DMA1_Channel7->CPAR=(u32)p_addr;
		DMA1_Channel7->CMAR=(u32)m_addr;
		NVIC_SetPriority(DMA1_Channel7_IRQn,NVIC_EncodePriority(7-2,1,2));

		NVIC_EnableIRQ(DMA1_Channel7_IRQn);//��NVIC��Ӧ
		USART2->CR3|=(0X1<<7);
		while(!flag1)
	{
		;
	}
	flag1=0;
	DMA1_Channel7->CCR|=(0X1<<0);//����
	
}
void DMA1_Channel7_IRQHandler()
{
	if(DMA1->ISR&(0x1<<25))
	{
		DMA1->IFCR|=(0x1<<25);
		flag1=1;
	}
}








