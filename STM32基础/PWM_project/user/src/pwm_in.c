#include "pwm_in.h"
u32 inter8=0;
void pwm_in_init()
{
	RCC->AHB1ENR|=(0x1<<0); //ͬ��
	GPIOA->MODER&=~(0x3<<2*1);
	GPIOA->MODER|=(0x2<<2*1);
	GPIOA->PUPDR&=~(0X3<<2*1);
	GPIOA->AFR[0]&=~(0XF<<4*1);
	GPIOA->AFR[0]|=(0X1<<4*1);//tim2����



	RCC->APB1ENR|=(0X1<<0);
	TIM2->SMCR&=~(0X7<<0);
	TIM2->SMCR&=~(0X1<<14);//ʱ��Դ
	TIM2->PSC=83;//1M
	TIM2->ARR=0xffffff-1;//
	TIM2->CNT=0;
	TIM2->EGR|=(0X1<<0);//
	TIM2->SR&=~(0X1<<0);
	TIM2->CR1=0;
	TIM2->CR1|=(0X1<<0);

	TIM2->CCMR1=0;
	TIM2->CCMR1|=(0X1<<8);//CC1SΪ����ģʽӳ��IC2,TI2
	TIM2->CCMR1|=(0X2<<0);//CC1SΪ����ģʽӳ��IC1��TI2
	TIM2->CCER&=~(0xff<<0);
	TIM2->CCER|=(0X1<<4);//IC2����ʹ�ܣ������ش���
	TIM2->CCER|=(0X1<<0);//
	TIM2->CCER|=(0X1<<1);//IC1����ʹ�ܣ��½��ش���
	TIM2->EGR&=~(0X1<<1);//Ӳ����1
	TIM2->SMCR|=(0X6<<4);
	TIM2->SMCR|=(0X4<<0);//�����봥����ʽ
	TIM2->DIER|=(0X1<<2);//ʹ���ж�
	NVIC_SetPriorityGrouping(7-2);//��ռλ
	inter8=NVIC_EncodePriority(7-2,0, 0);//��ռ����Ӧ���ȼ�
	NVIC_SetPriority(TIM2_IRQn, inter8);//�ж�����
	NVIC_EnableIRQ(TIM2_IRQn);

}
void TIM2_IRQHandler()	
	{
	
		if(TIM2->SR&(0X1<<10))
		{
			TIM2->SR&=~(0X1<<2);
			TIM2->SR&=~(0X1<<10);//�ظ������벶���־λ
			if(TIM2->CCR2==999)
				GPIOC->BSRRH|=0X1<<4;
		}

	}
