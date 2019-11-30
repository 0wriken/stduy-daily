#include "key_interrupt.h"
extern u32 i= 0;
u32 inter0,inter1,inter2,inter3,inter4;
void key_interrupt_init(void)
{
	RCC->APB2ENR|=(0x1<<14);
	SYSCFG->EXTICR[0]&=~(0XF<<0);//PA0
	SYSCFG->EXTICR[0]&=~(0xff<<8);//PE2,3
	SYSCFG->EXTICR[0]|=(0x44<<8);//PE23;
	SYSCFG->EXTICR[1]&=~(0xf<<0);//PE4；
	SYSCFG->EXTICR[1]|=(0x4<<0);//PE4;
	EXTI->FTSR&=~(0x1<<0);
	EXTI->RTSR|=(0X1<<0);//PA0上升沿
	EXTI->RTSR&=~(0X7<<2);
	EXTI->FTSR|=(0x7<<2);//PE23下降沿
	EXTI->EMR&=~(0x1<<0);	//事件屏蔽关闭
	EXTI->EMR&=~(0x7<<2);
	EXTI->SWIER&=~(0xff<<0);//软件中断关闭
	EXTI->IMR|=(0x1<<0);  //中断屏蔽打开
	EXTI->IMR|=(0x7<<2);
	


	
	NVIC_SetPriorityGrouping(7-2);//抢占位
	inter0=NVIC_EncodePriority(7-2,0, 0);//抢占与响应优先级
	NVIC_SetPriority(EXTI0_IRQn, inter0);//中断类型
	NVIC_EnableIRQ(EXTI0_IRQn);
	
	inter2=NVIC_EncodePriority(7-2,1, 1);//抢占与响应优先级
	NVIC_SetPriority(EXTI2_IRQn, inter2);//中断类型
	NVIC_EnableIRQ(EXTI2_IRQn);
	
	inter3=NVIC_EncodePriority(7-2,2, 2);//抢占与响应优先级
	NVIC_SetPriority(EXTI3_IRQn, inter3);//中断类型
	NVIC_EnableIRQ(EXTI3_IRQn);
	
	inter4=NVIC_EncodePriority(7-2,3, 3);//抢占与响应优先级
	NVIC_SetPriority(EXTI4_IRQn, inter4);//中断类型
	NVIC_EnableIRQ(EXTI4_IRQn);
	
}
void soft_interrupt_init()
{
	EXTI->FTSR&=~(0x1<<1);
	EXTI->RTSR&=~(0x1<<1);
	EXTI->EMR&=~(0x1<<1);	//事件屏蔽关闭
	EXTI->SWIER&=~(0x1<<1);//软件中断关闭
	EXTI->IMR&=~(0x1<<1);  //中断屏蔽打开
	NVIC_SetPriorityGrouping(7-2);//抢占位
	inter1=NVIC_EncodePriority(7-2,0, 0);//抢占与响应优先级
	NVIC_SetPriority(EXTI0_IRQn, inter0);//中断类型
	NVIC_EnableIRQ(EXTI1_IRQn);        //PA1
	
}
static void key_delay(u32 time)
{
	time *=42;//42为1微妙
	while(time)
	{
		time--;
	}
}
void   EXTI1_IRQHandler()
{
	if(EXTI->PR&(0x1<<7))
	{
		EXTI->PR&=~(0X1<<7);
		i++;
	}
}
void   EXTI0_IRQHandler()
{
	if(EXTI->PR&(0x1<<0))
	{
		key_delay(1000);
		if(GPIOA->IDR&(0x1<<0))
		{
			GPIOA->ODR^=0x1<<6;	
			EXTI->PR|=(0x1<<0);
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
		if(GPIOE->IDR & (0x1<<4))
		{
			GPIOC->ODR^=0x1<<5;
			EXTI->PR|=(0x1<<4);
		}
	}
}
