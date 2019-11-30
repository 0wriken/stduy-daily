#include "main.h"
u8 buf[100]="hello world\r\n";
u8 buf1[100]="bye bye my love\r\n";
int main(void)
{		
	
	led_init();
	key_init();
//		usart_init(115200);
//pwm_out_init();//捕获按键的输入并控制灯
//	pwm_in_init();//呼吸灯
//	/*通用定时器的延时功能*/
//	while(1)
//	{	
//		time_init(50000);
//		GPIOB->ODR^=(0x5<<6);//低电平输出	
//	}
////	/*按键控制点灯程序*/
//		while(1)
//		{
//		if(!(GPIOB->IDR&(0X1<<7)))
//		{
//		key_delay(50000);
//		if(!(GPIOB->IDR&(0X1<<7)))
//		GPIOB->ODR^=(0x5<<6);//低电平输出	
//		}
//	}
//		/*DMA搬运数据到外设USART*/
//		dma1_stream7_init((u8 *)buf,(u8 *)&USART2->DR,(u16)strlen((char *)buf));
//			/*DMA搬运数据由存储器到存储器*/
//			dma1_channel2_init(buf,buf1,strlen((char *)buf));
			while(1)
			{}
}



