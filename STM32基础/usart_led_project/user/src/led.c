#include "led.h"
/*
***********************************************************************************************
* 函数功能:LED灯初始化
* 函数形参: None
* 函数返回值: None
* 备注: None
* 作者: wriken
* 时间: 2019-08-06
* 修改作者: None
* 修改时间: None
***********/
void led_init(void)
{
	/*初始化PC4,PC5*/
	RCC->AHB1ENR|=(0x1<<2);//时钟寄存器初始化
	GPIOC->MODER&=~(0xf<<2*4);//模式寄存器清0
	GPIOC->MODER|=(0x5<<2*4);//模式寄存器设为输出
	GPIOC->OTYPER&=~(0x3<<4);//输出类型位推挽
	GPIOC->PUPDR&=~(0Xf<<2*4);//浮空
	GPIOC->OSPEEDR&=~(0Xf<<2*4);//速度位2M
	GPIOC->ODR|=(0x3<<4);   //输出数据寄存器写入数据1
	
	/*初始化PA6,PA7*/
	RCC->AHB1ENR|=(0x1<<0); //同上
	GPIOA->MODER&=~(0xf<<2*6);
	GPIOA->MODER|=(0x5<<2*6);
	GPIOA->OTYPER&=~(0x3<<6);
	GPIOA->PUPDR&=~(0Xf<<2*6);
	GPIOA->OSPEEDR&=~(0Xf<<2*6);
	GPIOA->ODR|=(0x3<<6);
}
