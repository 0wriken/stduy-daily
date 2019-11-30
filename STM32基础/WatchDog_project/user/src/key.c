#include "key.h"
/*
***********************************************************************************************
* 函数功能:按键PA0,PE2
* 函数形参: None
* 函数返回值: None
* 备注: None
* 作者: wriken
* 时间: 2019-08-06
* 修改作者: None
* 修改时间: None
***********/
void key_init()
{
	//初始化按键PA0;
	RCC->AHB1ENR|=(0x1<<0);//设置时钟使能
	GPIOA->MODER&=~(0x3<<2*0);//模式寄存器清0
	GPIOA->MODER|=(0x0<<2*0);//设置为输入模式
	GPIOA->PUPDR&=~(0x3<<2*0);//浮空
	//初始化按键PE23;
	RCC->AHB1ENR|=(0x1<<4);//同上
	GPIOE->MODER&=~(0xf<<2*2);
	GPIOE->MODER|=(0x00<<2*2);
	GPIOE->PUPDR&=~(0xf<<2*2);
	//初始化按键PE4;
	RCC->AHB1ENR|=(0x1<<4);
	GPIOE->MODER&=~(0x3<<2*4);
	GPIOE->PUPDR&=~(0xf<<2*4);
}
static void key_delay(u32 time)
{
	time *=42;//42为1微妙
	while(time)
	{
		time--;
	}
}
