#include "dma_usart.h"
u32 flag1=0;
void  dam2_stream7_init(u8 *m_addr,u8 *p_addr,u16 data_num)
{
	uart_init(115200);

	RCC->AHB1ENR|=(0x1<<22);//打开DMA2的时钟使能	
	
	DMA2_Stream7->CR&=~(0x1<<0);  //关闭数据流
	while(DMA2_Stream7->CR&(0X1<<0));//等待数据流关闭

	/*单次传输，不采用双缓冲，低优先级，外设增量与PSIZE相关
	存储器大小与外设数据大小都为1个字节*/
	DMA2_Stream7->CR|=(0x4<<25);//选择通道4
	DMA2_Stream7->CR |= 0X1 << 16;	//优先级选择中等
	DMA2_Stream7->CR|=(0x1<<10);//存储器的地址要递增
	DMA2_Stream7->CR|=(0x1<<6);//传输方向位存储器到外设
	DMA2_Stream7->FCR&=~(0x1<<2);//使用直接模式

	DMA2_Stream7->NDTR&=~(0XFF<<0);
	DMA2_Stream7->NDTR=data_num;//数据项的数目
	
	DMA2_Stream7->PAR=(u32)p_addr;//外设地址
	DMA2_Stream7->M0AR=(u32)m_addr; //存储器的地址	
	
	NVIC_SetPriority(DMA2_Stream7_IRQn,NVIC_EncodePriority(7-2,1,2));
	DMA2_Stream7->CR|=(0X1<<4);//传输完成中断
	
	NVIC_EnableIRQ(DMA2_Stream7_IRQn);//打开NVIC响应
	
	
	DMA2_Stream7->CR|=(0X1<<0);//开启外设DMA
	


	USART1->CR3|=1<<7;//打开USART的DMA发送使能位
	
	while(!flag1)
	{
		;
	}
	flag1=0;
	DMA2_Stream7->CR|=(0X1<<0);//开启
	

}


void DMA2_Stream7_IRQHandler()
{

	if(DMA2->HISR&(0X1<<27))//判断传输完成
	{
		DMA2->HIFCR|=(0x1<<27);//清除标志位
		flag1=1;
		
	}
}



