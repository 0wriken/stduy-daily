#include "main.h"
u8 buf[100]="hello world\r\n";
u8 buf1[100]="bye bye my love\r\n";
int main(void)
{		
	
	led_init();
	key_init();
//		usart_init(115200);
//pwm_out_init();//���񰴼������벢���Ƶ�
//	pwm_in_init();//������
//	/*ͨ�ö�ʱ������ʱ����*/
//	while(1)
//	{	
//		time_init(50000);
//		GPIOB->ODR^=(0x5<<6);//�͵�ƽ���	
//	}
////	/*�������Ƶ�Ƴ���*/
//		while(1)
//		{
//		if(!(GPIOB->IDR&(0X1<<7)))
//		{
//		key_delay(50000);
//		if(!(GPIOB->IDR&(0X1<<7)))
//		GPIOB->ODR^=(0x5<<6);//�͵�ƽ���	
//		}
//	}
//		/*DMA�������ݵ�����USART*/
//		dma1_stream7_init((u8 *)buf,(u8 *)&USART2->DR,(u16)strlen((char *)buf));
//			/*DMA���������ɴ洢�����洢��*/
//			dma1_channel2_init(buf,buf1,strlen((char *)buf));
			while(1)
			{}
}



