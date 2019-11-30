#include "usart.h"
/*
***********************************************************************************************
* 函数功能:串口初始化
* 函数形参: 波特率
* 函数返回值: None
* 备注: None
* 作者: wriken
* 时间: 2019-08-21
* 修改作者: None
* 修改时间: None
***********/
void usart_init(u32 boad)
{
	float USARTDIV_2=0;
	u16 DIV_MAN=0;
	u16 DIV_FRA=0;
	
	RCC->APB2ENR|=(0x1<<2);
	GPIOA->CRL&=~(0XFF<<2*4);
	GPIOA->CRL|=(0X3<<8);
	GPIOA->CRL|=(0X2<<10);//GPIOA->CRL|=(0X4B<<2*4);
	GPIOA->CRL&=~(0X3<<12);//PA2复用输出，PA3浮空输入
	GPIOA->CRL&=~(0X3<<14);

	RCC->APB1ENR|=(0X1<<17);
	USART2->CR1=0;
	USART2->CR1|=(0X3<<2);
	USART2->CR1|=(0X3<<4);//打开接收中断使能
	USART2->CR2=0;
	
	NVIC_SetPriority(USART2_IRQn,NVIC_EncodePriority(7-2,1,2));

	NVIC_EnableIRQ(USART2_IRQn);//打开NVIC响应
	

	USARTDIV_2=(float)36000000ul/(16*boad);//波特率
	DIV_MAN=USARTDIV_2;     //整数部分
	DIV_FRA=(USARTDIV_2-DIV_MAN)*16+(float)0.5; //小数部分4舍5入
	USART2->BRR=(DIV_MAN<<4)|DIV_FRA;  //波特率写入寄存器
	USART2->CR1|=(0X1<<13);//打开使能
}
/*
***********************************************************************************************
* 函数功能:串口接收函数
* 函数形参: None
* 函数返回值: u8
* 备注: None
* 作者: wriken
* 时间: 2019-08-21
* 修改作者: None
* 修改时间: None
***********/
u8 uart_recive_data(void)//接收
{
	
		while(!(USART2->SR&(0x1<<5)));//时间条件	
		return USART2->DR;
}
/*
***********************************************************************************************
* 函数功能:串口发送函数
* 函数形参: None
* 函数返回值: None
* 备注: None
* 作者: wriken
* 时间: 2019-08-21
* 修改作者: None
* 修改时间: None
***********/
void uart_send_data(u8 send_data)//发送
{	
		while(!(USART2->SR&(0x1<<6)));//时间条件
		USART2->DR=send_data;
}
/*
***********************************************************************************************
* 函数功能:串口中断函数
* 函数形参: None
* 函数返回值: None
* 备注: None
* 作者: wriken
* 时间: 2019-08-21
* 修改作者: None
* 修改时间: None
***********/
void USART2_IRQHandler()
{
	if(USART2->SR&(0x1<<5))
	{
		uart_send_data(uart_recive_data());
	}
//if(USART2->SR&(0X1<<4))
//{
//	
//}
}
