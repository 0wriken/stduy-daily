#include "main.h"
int main(void)
{
	led_init();//��ʼ��LED
	key_init();//��ʼ������
	
	uart_init(115200);//��ʼ������
	//usart_string();//�ַ�������
	//uart_char();//�ַ�����
	key_interrupt_init();
	soft_interrupt_init();
	EXTI->SWIER|=(0x1<<1);//��������ж�
	printf("the i is %d\n",i);
	while(1)
	{}//����CPU�ܷ�

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
