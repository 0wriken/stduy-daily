#include "main.h"
static void dog_delay(u32 time)
{
	time *=42;//42为1微妙
	while(time)
	{
		time--;
	}
}
int main(void)
{
	while(1)
	{
		u8 buf[100]="HELLO DMA;";
		dam2_stream7_init(buf,(u8 *)&USART1->DR,strlen((char *)buf)); 
		dog_delay(500000);
	}
	//led_init();//初始化LED
	//key_init();//初始化按键
	//uart_init(115200);//初始化串
//	pwm_led_init();
//	pwm_out_init();
//	pwm_in_init();
//	
	
//  tim10_interrupt(500);
	//time_interrupt(1000);
	//usart_string();//字符串发送
	//uart_char();//字符发送
	//key_interrupt_init();
	//soft_interrupt_init();
	//EXTI->SWIER|=(0x1<<1);//触发软件中断
	//watchdog_init();//设置看门狗喂狗时间为1秒
	//dog_delay(10000);//延时1秒，看门狗即刻复位
//	 systick_init(1000);	
//	systick_interrupt(500);
//	while(1)
//	{
////		GPIOA->ODR^=(0X1<<6);
////		systick_init(500);
//	
//	}//避免CPU跑飞

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
