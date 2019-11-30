#include "key_interrupt.h"
u32 inter0,inter2,inter3,inter4;
void key_interrupt_init(void)
{
	RCC->APB2ENR|=(0x1<<14);
	SYSCFG->EXTICR[0]&=~(0XF<<4*0);//�ⲿ�ж�PA0
	SYSCFG->EXTICR[0]&=~(0xff<<4*2);//PE2,3
	SYSCFG->EXTICR[0]|=(0x44<<4*2);//�ⲿ�ж�PE23;
	SYSCFG->EXTICR[1]&=~(0xf<<0);//PE4��
	SYSCFG->EXTICR[1]|=(0x4<<0);//�ⲿ�ж�PE4;
	EXTI->FTSR&=~(0x1<<0);
	EXTI->RTSR|=(0X1<<0);//PA0������
	EXTI->RTSR&=~(0X7<<2);
	EXTI->FTSR|=(0x7<<2);//PE23�½���
	EXTI->EMR&=~(0x1<<0);	//�¼����ιر�
	EXTI->EMR&=~(0x7<<2);
	EXTI->SWIER&=~(0xff<<0);//����жϹر�
	EXTI->IMR|=(0x1<<0);  //�ж����δ�
	EXTI->IMR|=(0x7<<2);
	


	
	NVIC_SetPriorityGrouping(7-2);//��ռλ
	inter0=NVIC_EncodePriority(7-2,0, 0);//��ռ����Ӧ���ȼ�
	NVIC_SetPriority(EXTI0_IRQn, inter0);//�ж�����
	NVIC_EnableIRQ(EXTI0_IRQn);
	
	inter2=NVIC_EncodePriority(7-2,1, 1);//��ռ����Ӧ���ȼ�
	NVIC_SetPriority(EXTI2_IRQn, inter2);//�ж�����
	NVIC_EnableIRQ(EXTI2_IRQn);
	
	inter3=NVIC_EncodePriority(7-2,2, 2);//��ռ����Ӧ���ȼ�
	NVIC_SetPriority(EXTI3_IRQn, inter3);//�ж�����
	NVIC_EnableIRQ(EXTI3_IRQn);
	
	inter4=NVIC_EncodePriority(7-2,3, 3);//��ռ����Ӧ���ȼ�
	NVIC_SetPriority(EXTI4_IRQn, inter4);//�ж�����
	NVIC_EnableIRQ(EXTI4_IRQn);
	
}
static void key_delay(u32 time)
{
	time *=42;//42Ϊ1΢��
	while(time)
	{
		time--;
	}
}
void   EXTI0_IRQHandler()//��׼�жϺ�����
{
	if(EXTI->PR&(0x1<<0))//�ж��жϱ�־λ
	{
		key_delay(1000);  //��������
		if(GPIOA->IDR&(0x1<<0))  //PA0�����ش�����������Ϊ��
		{
			GPIOA->ODR^=0x1<<6;	
			EXTI->PR|=(0x1<<0);  //�жϱ�־λд1�Զ����
		}
	}
}
void EXTI2_IRQHandler()
{
	if(EXTI->PR&(0x1<<2))
	{
		key_delay(1000);
		if(GPIOE->IDR&(0x1<<2))
		{
			GPIOA->ODR^=0x1<<7;	
			EXTI->PR|=(0x1<<2);
		}
	}
}
void EXTI3_IRQHandler()
{
	if(EXTI->PR&(0x1<<3))
	{
		key_delay(1000);
		if(GPIOE->IDR&(0x1<<3))
		{
			GPIOC->ODR^=0x1<<4;	
			EXTI->PR|=(0x1<<3);
		}
	}
}
void EXTI4_IRQHandler()
{
	if(EXTI->PR&(0x1<<4))
	{
		key_delay(1000);
		if(GPIOE->IDR&(0x1<<4))
		{
			GPIOC->ODR^=0x1<<5;
			EXTI->PR|=(0x1<<4);
		}
	}
}

	