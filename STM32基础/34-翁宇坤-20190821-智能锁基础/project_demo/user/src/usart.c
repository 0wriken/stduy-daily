#include "usart.h"
/*
***********************************************************************************************
* ��������:���ڳ�ʼ��
* �����β�: ������
* ��������ֵ: None
* ��ע: None
* ����: wriken
* ʱ��: 2019-08-21
* �޸�����: None
* �޸�ʱ��: None
***********/
void usart_init(u32 boad)
{
	float USARTDIV_2=0;
	u16 DIV_MAN=0;
	u16 DIV_FRA=0;
	
	RCC->APB2ENR|=(0x1<<2);
	GPIOA->CRL&=~(0XFF<<2*4);
	GPIOA->CRL|=(0X3<<8);
	GPIOA->CRL|=(0X2<<10);//GPIOA->CRL|=(0X4B<<2*4);
	GPIOA->CRL&=~(0X3<<12);//PA2���������PA3��������
	GPIOA->CRL&=~(0X3<<14);

	RCC->APB1ENR|=(0X1<<17);
	USART2->CR1=0;
	USART2->CR1|=(0X3<<2);
	USART2->CR1|=(0X3<<4);//�򿪽����ж�ʹ��
	USART2->CR2=0;
	
	NVIC_SetPriority(USART2_IRQn,NVIC_EncodePriority(7-2,1,2));

	NVIC_EnableIRQ(USART2_IRQn);//��NVIC��Ӧ
	

	USARTDIV_2=(float)36000000ul/(16*boad);//������
	DIV_MAN=USARTDIV_2;     //��������
	DIV_FRA=(USARTDIV_2-DIV_MAN)*16+(float)0.5; //С������4��5��
	USART2->BRR=(DIV_MAN<<4)|DIV_FRA;  //������д��Ĵ���
	USART2->CR1|=(0X1<<13);//��ʹ��
}
/*
***********************************************************************************************
* ��������:���ڽ��պ���
* �����β�: None
* ��������ֵ: u8
* ��ע: None
* ����: wriken
* ʱ��: 2019-08-21
* �޸�����: None
* �޸�ʱ��: None
***********/
u8 uart_recive_data(void)//����
{
	
		while(!(USART2->SR&(0x1<<5)));//ʱ������	
		return USART2->DR;
}
/*
***********************************************************************************************
* ��������:���ڷ��ͺ���
* �����β�: None
* ��������ֵ: None
* ��ע: None
* ����: wriken
* ʱ��: 2019-08-21
* �޸�����: None
* �޸�ʱ��: None
***********/
void uart_send_data(u8 send_data)//����
{	
		while(!(USART2->SR&(0x1<<6)));//ʱ������
		USART2->DR=send_data;
}
/*
***********************************************************************************************
* ��������:�����жϺ���
* �����β�: None
* ��������ֵ: None
* ��ע: None
* ����: wriken
* ʱ��: 2019-08-21
* �޸�����: None
* �޸�ʱ��: None
***********/
void USART2_IRQHandler()
{
	if(USART2->SR&(0x1<<5))
	{
		uart_send_data(uart_recive_data());
	}
//if(USART2->SR&(0X1<<4))
//{
//	
//}
}
