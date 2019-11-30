#include "pwm_in.h"
u32 inter8=0;
void pwm_in_init()
{
	RCC->AHB1ENR|=(0x1<<0); 
	GPIOA->MODER&=~(0x3<<2*1); 
	GPIOA->MODER|=(0x2<<2*1);//打开复用输入功能
	GPIOA->PUPDR&=~(0X3<<2*1);
	GPIOA->AFR[0]&=~(0XF<<4*1);
	GPIOA->AFR[0]|=(0X1<<4*1);//TIM2输入

	
	RCC->APB1ENR|=(0X1<<0);
	TIM2->SMCR&=~(0X7<<0);
	TIM2->SMCR&=~(0X1<<14);//外设时钟源
	TIM2->PSC=83;//分屏后频率为1M
	TIM2->ARR=0xffffff-1;//最大计数长度
	TIM2->CNT=0;
	TIM2->EGR|=(0X1<<0); //一次UG更新
	TIM2->SR&=~(0X1<<0); //清除更新中断标志位
	TIM2->CR1=0;   
	TIM2->CR1|=(0X1<<0); //开启定时器使能
	TIM2->CCMR1=0;
	TIM2->CCMR1|=(0X1<<1);//映射IC1,TI2

	TIM2->CCER&=~(0xff<<0);
	TIM2->CCER|=(0X1<<0);//IC1捕获使能，上升沿触发
	TIM2->EGR&=~(0X1<<1);//硬件置1，不让软件清0
	TIM2->SMCR|=(0X6<<4);  //从模式为复位功能
	TIM2->SMCR|=(0X4<<0);//复用与触发方式
	TIM2->DIER|=(0X1<<1);//IC1使能中断
	NVIC_SetPriorityGrouping(7-2);//抢占位
	inter8=NVIC_EncodePriority(7-2,0, 0);//抢占与响应优先级
	NVIC_SetPriority(TIM2_IRQn, inter8);//中断类型
	NVIC_EnableIRQ(TIM2_IRQn);
	TIM2->CCER|=(0X1<<1);//IC1捕获下降沿触发
}
	void TIM2_IRQHandler()	
	{
	
		if(TIM2->SR&(0X1<<9))  //判断重复捕获标志位
		{
			TIM2->SR&=~(0X1<<1);
			TIM2->SR&=~(0X1<<9);//重复捕获与捕获标志位
			if(TIM2->CCR1==999)			//判断计数次数是否达到一个周期
				GPIOC->BSRRH|=0X1<<4;
		}

	}
