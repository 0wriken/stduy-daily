#include "systick.h"
void systick_init(u32 nms)
{
		SysTick->CTRL&=~(0Xf<<0);
		SysTick->CTRL|=(0X0<<2);
		SysTick->VAL =0;
		SysTick->LOAD|=nms*21000;
		if(nms>0xffffff/21000)
			return ;
		SysTick->CTRL|=(0x1<<0);
		while(!(SysTick->CTRL&(0X1<<16)));//时间不可超过800毫秒
		SysTick->CTRL&=~(0x1<<0);
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
		SysTick->CTRL|=(0x1<<1);
		while(!(SysTick->CTRL&(0X1<<16)));
}
void SysTick_Handler(void)
{
//	if((SysTick->CTRL&(0X1<<16)))
//	{}
		SysTick->VAL=0;
	
	GPIOC->ODR^=(0x1<<4);
		
} 

