#include "main.h"
static void dog_delay(u32 time)
{
	time *=42;//42Ϊ1΢��
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
	//led_init();//��ʼ��LED
	//key_init();//��ʼ������
	//uart_init(115200);//��ʼ����
//	pwm_led_init();
//	pwm_out_init();
//	pwm_in_init();
//	
	
//  tim10_interrupt(500);
	//time_interrupt(1000);
	//usart_string();//�ַ�������
	//uart_char();//�ַ�����
	//key_interrupt_init();
	//soft_interrupt_init();
	//EXTI->SWIER|=(0x1<<1);//��������ж�
	//watchdog_init();//���ÿ��Ź�ι��ʱ��Ϊ1��
	//dog_delay(10000);//��ʱ1�룬���Ź����̸�λ
//	 systick_init(1000);	
//	systick_interrupt(500);
//	while(1)
//	{
////		GPIOA->ODR^=(0X1<<6);
////		systick_init(500);
//	
//	}//����CPU�ܷ�

//	while(1)
//	{
//		if((GPIOA->IDR&(0x1<<0)==0)&&n==0)//����PA0����
//			
//		{
//			n=1;
//			GPIOC->BSRRH|=0x3<<4;
//			GPIOA->BSRRH|=0x3<<6;		//����
//		}
//		if((GPIOA->IDR&(0x1<<0)==0)&&n==1)//����PA0����
//		{
//			n=0;
//			GPIOC->BSRRL|=0X3<<4;
//			GPIOA->BSRRL|=0x3<<6;	//����
//		}
//		if((GPIOE->IDR&(0x1<<2)==0)==0)//����PE2����
//		{
//			while(1)
//		{
//			 GPIOA->BSRRL|=0x1<<7;  //��ˮ��
//			GPIOC->BSRRH|=0x1<<4;
//			delay(10000);			//��ʱ
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
