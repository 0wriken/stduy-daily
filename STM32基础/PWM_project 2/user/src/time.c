#include "time.h"
#include "uart.h"
u32 inter6=0;
u32 hour=0,min=0,sec=0;
u32 buff[100]={0};
/***********************************************************************************************
* �������ܣ�������ʱ���жϳ�ʼ��
* �����β�: 32λ����
* ��������ֵ: None
* ��ע: None
* ����: wriken
* ʱ��: 2019-08-14
* �޸�����: None
* �޸�ʱ��: None
***********/
void time_interrupt(u32 nms)
{
	RCC->APB1ENR |= 0X1 << 5;		//����TIM6��ʱ��
	
TIM7->PSC = 8400 - 1;			//����8400��Ƶ��������ʱ��Ϊ10KHz
	TIM7->CNT = 0;					//��ռ�������ֵ
	TIM7->ARR = nms * 10 - 1;		//��ʱΪ���뼶
	TIM7->EGR |= 0X1 << 0;			//����һ��UGλ
	TIM7->SR &= ~(0X1 << 0);		//���һ�θ��±�־λ(��ֹ����)
	TIM7->DIER|=(0X1<<0);       //�򿪼���ʹ��
	TIM7->CR1 = 0;					//��տ��ƼĴ���1��ֵ
	TIM7->CR1 |= 0X0 << 3;			//��ʱ����Ժ󲻻��Զ�ֹͣ����
	TIM7->CR1|=(0X1<<2);         //�������Դֻ�м���������
	TIM7->CR1 |= 0X1 << 0;			//����������
	NVIC_SetPriorityGrouping(7-2);//��ռλ
	inter6=NVIC_EncodePriority(7-2,0, 0);//��ռ����Ӧ���ȼ�
	NVIC_SetPriority(TIM7_IRQn, inter6);//�ж�����
	NVIC_EnableIRQ(TIM7_IRQn);	  //�����жϺ���ʹ��

}
void tim10_interrupt(u32 nms)
{
	RCC->APB2ENR |= 0X1 << 17;		//����TIM6��ʱ��
	
	TIM10->PSC = 16800 - 1;			//����8400��Ƶ��������ʱ��Ϊ10KHz
	TIM10->CNT = 0;					//��ռ�������ֵ
	TIM10->ARR = nms * 10 - 1;		//��ʱΪ���뼶
	TIM10->EGR |= 0X1 << 0;			//����һ��UGλ
	TIM10->SR &= ~(0X1 << 0);		//���һ�θ��±�־λ(��ֹ����)
	
	TIM10->CR1 = 0;					//��տ��ƼĴ���1��ֵ
	TIM10->CR1 |= 0X0 << 3;			//��ʱ����Ժ󣬲����Զ�ֹͣ����


	NVIC_SetPriorityGrouping(7-2);//��ռλ
	inter6=NVIC_EncodePriority(7-2,0, 0);//��ռ����Ӧ���ȼ�
	NVIC_SetPriority(TIM1_UP_TIM10_IRQn, inter6);//�ж�����
	NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);	
	TIM10->DIER|=(0X1<<0);      //���ж�ʹ��
	TIM10->CR1 |= 0X1 << 0;			//����������
}
void TIM1_UP_TIM10_IRQHandler()
{
	if(TIM10->SR&(0X1<<0))
	{
		TIM10->SR&=~(0X1<<0);
		GPIOA->ODR^=(0X1<<7);
	}
		
}


/***********************************************************************************************
* �������ܣ���ʱ�жϴ�����ʵ��������
* �����β�: None
* ��������ֵ: None
* ��ע: None
* ����: wriken
* ʱ��: 2019-08-14
* �޸�����: None
* �޸�ʱ��: None
***********/
void TIM7_IRQHandler (void)
{
	if(TIM7->SR&(0X1<<0))  //�жϱ�־λ
	{
		TIM7->SR&=~(0X1<<0);//�����־λ
		sprintf((char *)buff,"%02d:%02d:%02d\r\n",hour,min,sec);
		
		 uart_send((u8 *)buff);
		sec+=1;
		if(sec>=60)
		{
			sec%=60;
			min+=1;
		}
		if(min>=60)
		{
			min%=60;
			hour+=1;
		}
		
	}
	
}
