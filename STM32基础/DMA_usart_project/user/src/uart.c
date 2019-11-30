#include "uart.h"
u8 res=0;
static u8 recieve_buf[20]={0};
u8 *buf;
u8 buf1[20]={0};
static u32 n=0;
/*
***********************************************************************************************
* 函数功能：初始化串口
* 函数形参: None
* 函数返回值: None
* 备注: None
* 作者: wriken
* 时间: 2019-08-08
* 修改作者: None
* 修改时间: None
***********/
void uart_init(u32 B)
{
	float USARTDIV_1=0;
	u16 DIV_MAN=0;
	u16 DIV_FRA=0;
	RCC->AHB1ENR|=(0x1<<0);    //时钟使能
	GPIOA->MODER&=~(0xf<<2*9);	
	GPIOA->MODER|=(0xA<<2*9);  // 模式复用
	GPIOA->AFR[1]&=(0xff<<4*(9-8));
	GPIOA->AFR[1]|=(0x77<<4*(9-8)); //复用功能为UART
	GPIOA->OTYPER&=~(0x1<<9);       //PA9推挽
	GPIOA->PUPDR&=~(0xf<<2*9);      //PA9PA10上下拉
	GPIOA->OSPEEDR&=~(0x3<<2*9);    //PA9速度
	
	
	RCC->APB2ENR|=(0x1<<4);    //时钟使能
	USART1->CR1&=(0x3<<2);		
	USART1->CR1|=(0x3<<2);    //收发使能
	USART1->CR1 |= (0X1 << 13);//使能USART1
	USART1->CR2&=~(0x3<<12);//设置发送接收使能，停止位0.5
	
	USARTDIV_1=(float)84000000ul/(16*B);//波特率
	DIV_MAN=(u16)USARTDIV_1;     //整数部分
	DIV_FRA=(USARTDIV_1-DIV_MAN)*16+(float)0.5; //小数部分4舍5入
	USART1->BRR=(DIV_MAN<<4)|DIV_FRA;  //波特率写入寄存器
//	u32 i=0;
//	NVIC_SetPriorityGrouping(7-2);//抢占位
//	i= NVIC_EncodePriority(7 - 2, 2, 2);//抢占与响应优先级
//	NVIC_SetPriority(USART1_IRQn, i);//中断类型
//	//外设寄存器

//	//NVIC中断使能*/
//	NVIC_EnableIRQ(USART1_IRQn);
//	USART1->CR1|=(0X1<<5);//接收中断使能标志位
}

///*
//***********************************************************************************************
//* 函数功能：串口接收字符串
//* 函数形参: None
//* 函数返回值: None
//* 备注: None
//* 作者: wriken
//* 时间: 2019-08-06
//* 修改作者: None
//* 修改时间: None
//***********/
//u8 *uart_recive(void)//接收
//{
//	u16 i=0;
//	
//	 do
//	{
//		while(!(USART1->SR&(0x1<<5)));//时间条件
//		recieve_buf[i++]=USART1->DR;
//		
//	}while(USART1->DR!='\n');
//	return recieve_buf;
//	//return USART1->DR;
//}
///***********************************************************************************************
//* 函数功能：串口接收字符
//* 函数形参: None
//* 函数返回值: None
//* 备注: None
//* 作者: wriken
//* 时间: 2019-08-06
//* 修改作者: None
//* 修改时间: None
//***********/
//u8 uart_recive_data(void)//接收
//{
//	
//		while(!(USART1->SR&(0x1<<5)));//时间条件	
//		return USART1->DR;
//}
///*
//***********************************************************************************************
//* 函数功能：串口发送字符
//* 函数形参: None
//* 函数返回值: None
//* 备注: None
//* 作者: wriken
//* 时间: 2019-08-08
//* 修改作者: None
//* 修改时间: None
//***********/
//void uart_send_data(u8 send_data)
//{	
//		while(!(USART1->SR&(0x1<<6)));//时间条件
//		USART1->DR=send_data;

//}
///*
/***********************************************************************************************
* 函数功能：串口发送字符串
* 函数形参: None
* 函数返回值: None
* 备注: None
* 作者: wriken
* 时间: 2019-08-08
* 修改作者: None
* 修改时间: None
***********/
void uart_send(u8 *send_buf)//发送
{
	
	
	do
		{	
		while(!(USART1->SR&(0x1<<6)));//时间条件
		USART1->DR=*send_buf;

		send_buf++;
	}while((char)*send_buf!='\0');
}
/***********************************************************************************************
* 函数功能:中断服务函数
* 函数形参: None
* 函数返回值: None
* 备注: None
* 作者: wriken
* 时间: 2019-08-10
* 修改作者: None
* 修改时间: None
***********/
void USART1_IRQHandler(void)
{
			recieve_buf[n]=USART1->DR;
			n++;
		if(recieve_buf[n-1]=='\n')
		{
		uart_send(recieve_buf);
		recieve_buf[n-2]='\0';
			n=0;
		}
		USART1->SR&=~(0x1<<5);
}

///*
//函数功能：printf
//函数形参：无
//返回值：无
//备注：无
//*/
//#pragma import(__use_no_semihosting_swi) //取消半主机状态

//struct __FILE { int handle; /* Add whatever you need here */ };
//FILE __stdout;

//int fputc(int ch, FILE *f) 
//{
//	while((USART1->SR &(0X01<<7))==0)
//	{
//		;  //等待之前的数据发送完毕
//	}
//		USART1->DR=ch;
//  return (ch);
//}

//int ferror(FILE *f) {
//  /* Your implementation of ferror */
//  return EOF;
//}


//void _ttywrch(int ch) {
//  while((USART1->SR &(0X01<<7))==0);
//		USART1->DR=ch;
//}


//void _sys_exit(int return_code) {
//label:  goto label;  /* endless loop */
//}
///***********************************************************************************************
//* 函数功能：串口接收字符串判断
//* 函数形参: None
//* 函数返回值: None
//* 备注: None
//* 作者: wriken
//* 时间: 2019-08-08
//* 修改作者: None
//* 修改时间: None
//***********/

//void usart_string()
//{	while(1)
//	{
//		u32 i=0;
//		buf = uart_recive();
//		printf("**********%s",buf);
//		while(*buf!='\r')
//		{
//			buf++;
//			i++;
//		}
//		*buf=0;
//		buf-=i;
//		uart_send(buf);
//		if(strcmp((char *)buf,"open_led1")==0)   //比较接收到的数据
//		{
//			GPIOA->BSRRH|=0x1<<6;
//		}
//		if(strcmp((char *)buf,"open_led2")==0)
//		{
//				GPIOC->BSRRH|=0x1<<4;	
//		}
//		if(strcmp((char *)buf,"open_led3")==0)
//		{
//			GPIOC->BSRRH|=0x1<<5;
//		}
//		if(strcmp((char *)buf,"open_led4")==0)
//		{
//			GPIOA->BSRRH|=0x1<<7;
//		}
//		if(strcmp((char *)buf,"open_led")==0)
//		{
//			GPIOA->BSRRH|=0x3<<6;
//			GPIOC->BSRRH|=0X3<<4;
//		}
//		else if(strcmp((char *)buf,"close_led")==0)
//		{
//			GPIOA->BSRRL|=0x3<<6;
//			GPIOC->BSRRL|=0x3<<4;
//		}
//	}

//}
///***********************************************************************************************
//* 函数功能：串口接收字符判断
//* 函数形参: None
//* 函数返回值: None
//* 备注: None
//* 作者: wriken
//* 时间: 2019-08-08
//* 修改作者: None
//* 修改时间: None
//***********/
//void uart_char()
//{
//	while(1)
//	{
//		u32 i=0;
//	memset((char *)buf1,0,strlen((char *)buf1));
//	do
//	{
//		buf1[i]=uart_recive_data();
//		uart_send_data(buf1[i]);
//		i++;
//	}while(buf1[i-1]!='\n');    //串口收发数据
//		buf1[i-2] = 0;
//		printf("**********%s",buf1);
//		if(strcmp((char *)buf1,"open_led1")==0)   //比较接收到的数据
//		{
//			GPIOA->BSRRH|=0x1<<6;
//		}
//		else if(strcmp((char *)buf1,"close_led1")==0)
//		{
//			GPIOA->BSRRL|=0x1<<6;
//		}
//		if(strcmp((char *)buf1,"open_led2")==0)
//		{
//				GPIOC->BSRRH|=0x1<<4;	
//		}
//		else if(strcmp((char *)buf1,"close_led2")==0)
//		{
//			GPIOC->BSRRL|=0x1<<4;
//		}
//		if(strcmp((char *)buf1,"open_led3")==0)
//		{
//			GPIOC->BSRRH|=0x1<<5;
//		}
//		else if(strcmp((char *)buf1,"close_led1")==0)
//		{
//			GPIOC->BSRRL|=0x1<<5;
//		}
//		if(strcmp((char *)buf1,"open_led4")==0)
//		{
//			GPIOA->BSRRH|=0x1<<7;
//		}
//		else if(strcmp((char *)buf1,"close_led1")==0)
//		{
//			GPIOA->BSRRL|=0x1<<7;
//		}
//		if(strcmp((char *)buf1,"open_led")==0)
//		{
//			GPIOA->BSRRH|=0x3<<6;
//			GPIOC->BSRRH|=0X3<<4;
//		}
//		else if(strcmp((char *)buf1,"close_led")==0)
//		{
//			GPIOA->BSRRL|=0x3<<6;
//			GPIOC->BSRRL|=0x3<<4;
//		}
//	}

//}

