#include "pwm_in.h"
u32 key_flag=0;
u32 count=0;
/*
***********************************************************************************************
* ��������:PWM����
* �����β�: None
* ��������ֵ: None
* ��ע: None
* ����: wriken
* ʱ��: 2019-08-21
* �޸�����: None
* �޸�ʱ��: None
***********/ 
void pwm_in_init(void)
{
		RCC->APB2ENR|=(0X1<<3);
		GPIOB->CRL&=~(0X3<<28);
		GPIOB->CRL|=(0x1<<30);//��ʼ��PB7�������� TIM4 CH2
		
		RCC->APB1ENR|=(0x1<<2);//PB7  TIM4_CH2
	
		TIM4->SMCR&=~(0X7<<0);		//���
		TIM4->SMCR&=~(0X1<<14);//ʱ��Դѡ��ϵͳʱ��Դ����ֹ�ⲿʱ��ģʽ 2
		
		TIM4->PSC=3600-1;//��Ƶ��1HZ
		TIM4->ARR=10000;//
		TIM4->CNT=0;    //���������ֵ
		TIM4->EGR|=(0X1<<0);  //�򿪼�����ʹ��
		TIM4->SR&=~(0X1<<0);	//�����־λ
		
		TIM4->CR1=0;					//���

		TIM4->CR1|=(0X1<<0);	//�򿪶�ʱʹ��

		TIM4->CCMR1=0;
		TIM4->CCMR1|=(0X1<<8);//IC2 TI2
		TIM4->CCER&=~(0xff<<0);
		TIM4->CCER&=~(0X1<<5);//������
		TIM4->CCER|=(0X1<<4);//��������
		TIM4->EGR&=~(0X1<<2);//Ӳ����1�����������0
		TIM4->SMCR&=~(0X7<<0);
		TIM4->SMCR&=~(0X7<<4);
		TIM4->SMCR|=(0X6<<4);  //����ԴTI2FP2
		TIM4->SMCR|=(0X4<<0);//���ù���λ��λģʽ
		
		TIM4->DIER|=(0X1<<2);//�����ж�ʹ��
		TIM4->DIER|=(0X1<<0);//��ʱʹ���ж�
		
		NVIC_SetPriority(TIM4_IRQn,NVIC_EncodePriority(7-2,1,2));

		NVIC_EnableIRQ(TIM4_IRQn);//��NVIC��Ӧ
}
/*
***********************************************************************************************
* ��������:���񰴼�����
* �����β�: None
* ��������ֵ: None
* ��ע: None
* ����: wriken
* ʱ��: 2019-08-21
* �޸�����: None
* �޸�ʱ��: None
***********/
void TIM4_IRQHandler ()
{
		if(TIM4->SR&(0X1<<0))
		{
			TIM4->SR&=~(0X1<<0);
			if(key_flag==1)
				count++;
			else
			{
					GPIOB->ODR&=~(0x1<<8);
			}
		}
		if(TIM4->SR&(0X1<<2))
		{	
			TIM4->SR&=~(0X1<<2);  //��һ��������
			key_delay(50000);//����
			if(key_flag==1)
				key_flag=0;
			else   //��һ���½���
			{
						key_flag=1;
				if(count>=1)
					GPIOB->ODR|=(0x1<<8);
			count=0;
				
			}
			
		}
}
	


