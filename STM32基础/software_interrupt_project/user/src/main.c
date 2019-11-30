#include "main.h"
int main(void)
{
	led_init();//初始化LED
	key_init();//初始化按键
	
	uart_init(115200);//初始化串口
	//usart_string();//字符串发送
	//uart_char();//字符发送
	key_interrupt_init();
	soft_interrupt_init();
	EXTI->SWIER|=(0x1<<1);//触发软件中断
	printf("the i is %d\n",i);
	while(1)
	{}//避免CPU跑飞

//	while(1)
//	{
//		if((GPIOA->IDR&(0x1<<0)==0)&&n==0)//按键PA0按下
//			
//		{
//			n=1;
//			GPIOC->BSRRH|=0x3<<4;
//			GPIOA->BSRRH|=0x3<<6;		//灯亮
//		}
//		if((GPIOA->IDR&(0x1<<0)==0)&&n==1)//按键PA0按下
//		{
//			n=0;
//			GPIOC->BSRRL|=0X3<<4;
//			GPIOA->BSRRL|=0x3<<6;	//灯灭
//		}
//		if((GPIOE->IDR&(0x1<<2)==0)==0)//按键PE2按下
//		{
//			while(1)
//		{
//			 GPIOA->BSRRL|=0x1<<7;  //流水灯
//			GPIOC->BSRRH|=0x1<<4;
//			delay(10000);			//延时
//			GPIOC->BSRRL|=0x1<<4;
//			GPIOC->BSRRH|=0x1<<5;
//			delay(10000);
//			GPIOC->BSRRL|=0x1<<5;
//			GPIOA->BSRRH|=0x1<<6;
//			delay(10000);
//			GPIOA->BSRRL|=0x1<<6;
//			GPIOA->BSRRH|=0x1<<7;
//			delay(10000);
//		}
//		
//		}
//		
//	}
}
