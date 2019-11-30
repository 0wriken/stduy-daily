#include "pwm_in.h"
u32 key_flag=0;
u32 count=0;
/*
***********************************************************************************************
* 函数功能:PWM输入
* 函数形参: None
* 函数返回值: None
* 备注: None
* 作者: wriken
* 时间: 2019-08-21
* 修改作者: None
* 修改时间: None
***********/ 
void pwm_in_init(void)
{
		RCC->APB2ENR|=(0X1<<3);
		GPIOB->CRL&=~(0X3<<28);
		GPIOB->CRL|=(0x1<<30);//初始化PB7按键输入 TIM4 CH2
		
		RCC->APB1ENR|=(0x1<<2);//PB7  TIM4_CH2
	
		TIM4->SMCR&=~(0X7<<0);		//清除
		TIM4->SMCR&=~(0X1<<14);//时钟源选择系统时钟源，禁止外部时钟模式 2
		
		TIM4->PSC=3600-1;//分频器1HZ
		TIM4->ARR=10000;//
		TIM4->CNT=0;    //清除计数数值
		TIM4->EGR|=(0X1<<0);  //打开计数器使能
		TIM4->SR&=~(0X1<<0);	//清除标志位
		
		TIM4->CR1=0;					//清除

		TIM4->CR1|=(0X1<<0);	//打开定时使能

		TIM4->CCMR1=0;
		TIM4->CCMR1|=(0X1<<8);//IC2 TI2
		TIM4->CCER&=~(0xff<<0);
		TIM4->CCER&=~(0X1<<5);//捕获上
		TIM4->CCER|=(0X1<<4);//捕获输入
		TIM4->EGR&=~(0X1<<2);//硬件置1，不让软件清0
		TIM4->SMCR&=~(0X7<<0);
		TIM4->SMCR&=~(0X7<<4);
		TIM4->SMCR|=(0X6<<4);  //输入源TI2FP2
		TIM4->SMCR|=(0X4<<0);//复用功能位复位模式
		
		TIM4->DIER|=(0X1<<2);//捕获中断使能
		TIM4->DIER|=(0X1<<0);//计时使能中断
		
		NVIC_SetPriority(TIM4_IRQn,NVIC_EncodePriority(7-2,1,2));

		NVIC_EnableIRQ(TIM4_IRQn);//打开NVIC响应
}
/*
***********************************************************************************************
* 函数功能:捕获按键输入
* 函数形参: None
* 函数返回值: None
* 备注: None
* 作者: wriken
* 时间: 2019-08-21
* 修改作者: None
* 修改时间: None
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
			TIM4->SR&=~(0X1<<2);  //第一次上升沿
			key_delay(50000);//消抖
			if(key_flag==1)
				key_flag=0;
			else   //第一次下降沿
			{
						key_flag=1;
				if(count>=1)
					GPIOB->ODR|=(0x1<<8);
			count=0;
				
			}
			
		}
}
	


