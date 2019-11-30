#include "systick.h"
void systick_init(u32 nms)
{
		SysTick->CTRL&=~(0Xf<<0);//清空
		SysTick->CTRL|=(0X0<<2); //时钟源为21M
		SysTick->VAL =0;  //清空计数值
		SysTick->LOAD|=nms*21000;  //重载值为21000，在21M下1毫秒
		if(nms>0xffffff/21000)     //24位最大的计数时间
			return ;
		SysTick->CTRL|=(0x1<<0);   //打开滴答定时器
		while(!(SysTick->CTRL&(0X1<<16)));//时间不可超过800毫秒
		SysTick->CTRL&=~(0x1<<0);   //时间到，停止滴答定时器的工作
}
void systick_interrupt(u32 nms)
{
		SysTick->CTRL&=~(0Xf<<0);
		SysTick->CTRL|=(0X0<<2);
		SysTick->VAL=0;
		SysTick->LOAD|=nms*21000;
		if(nms>0xffffff/21000)
			return ;
		SysTick->CTRL|=(0x1<<0);	
		SysTick->CTRL|=(0x1<<1);   //打开滴答定时器的中断使能位
}
void SysTick_Handler(void)
{
		SysTick->VAL=0;//清除标志位
	
	GPIOC->ODR^=(0x1<<4);  //控制LED灯的亮灭
		
} 

