#include "pwm_out.h"
u32 flag=0;
u32 a=0;
/*
***********************************************************************************************
* 函数功能:比较输出PWM
* 函数形参: None
* 函数返回值: None
* 备注: None
* 作者: wriken
* 时间: 2019-08-21
* 修改作者: None
* 修改时间: None
***********/
void pwm_out_init()
{
	RCC->APB2ENR|=(0X1<<3);
	//PB6  TIM4_CH1
	GPIOB->CRL|=(0X2<<4*6);
	GPIOB->CRL|=(0x2<<(4*6+2));//复用输出为TIM4
	
	RCC->APB1ENR|=(0x1<<2);//PB6  TIM4_CH1
	
	TIM4->SMCR&=~(0X7<<0);		//清除
	TIM4->SMCR&=~(0X1<<14);//时钟源选择系统时钟源，禁止外部时钟模式 2
	
	TIM4->PSC=36;//分频器1HZ
	TIM4->ARR=1000-1;//定时时间为1毫秒
	TIM4->CNT=0;    //清除计数数值
	TIM4->EGR|=(0X1<<0);  //打开计数器使能
	TIM4->SR&=~(0X1<<0);	//清除标志位
	
	TIM4->CR1=0;					//清除
	TIM4->DIER|=(0X1<<0);	//打开中断使能
	TIM4->CR1|=(0X1<<0);	//打开定时使能
	TIM4->CR1&=~(0x1<<1); //配置1次UG位
	TIM4->CR1&=~(0X1<<3);  //定时时间到不会停止、
	
	NVIC_SetPriority(TIM4_IRQn,NVIC_EncodePriority(7-2,1,2));

	NVIC_EnableIRQ(TIM4_IRQn);//打开NVIC响应
	
}
/*
***********************************************************************************************
* 函数功能:中断服务呼吸灯
* 函数形参: None
* 函数返回值: None
* 备注: None
* 作者: wriken
* 时间: 2019-08-21
* 修改作者: None
* 修改时间: None
***********/
//void TIM4_IRQHandler ()
//{
//	if(TIM4->SR&(0X1<<0))
//	{
//			if(a<1000&&flag==0)   //亮度最亮到最暗
//		{
//			TIM4->SR&=~(0X1<<0); //定时标志位清0
//			TIM4->CCR1=a-1;//占空比	
//			a++;
//			flag=0;
//			if(a==1000)
//				flag=1;
//		}
//		if(a<1001&&flag==1)   //亮度由最暗到最亮
//		{
//			TIM4->SR&=~(0X1<<0);
//			TIM4->CCR1=a-1;//占空比
//			a--;
//			flag=1;
//			if(a==0)
//				flag=0;  //亮灭标志位
//		}
//	}
//	TIM4->CCMR1&=~(0xff<<0);
//	TIM4->CCMR1|=(0X6<<4);
//	TIM4->CCER&=~(0XFF<<0);
//	TIM4->CCER|=(0X1<<0);
//	
//}


