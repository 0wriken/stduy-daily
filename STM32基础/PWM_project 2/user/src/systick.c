#include "systick.h"
void systick_init(u32 nms)
{
		SysTick->CTRL&=~(0Xf<<0);//���
		SysTick->CTRL|=(0X0<<2); //ʱ��ԴΪ21M
		SysTick->VAL =0;  //��ռ���ֵ
		SysTick->LOAD|=nms*21000;  //����ֵΪ21000����21M��1����
		if(nms>0xffffff/21000)     //24λ���ļ���ʱ��
			return ;
		SysTick->CTRL|=(0x1<<0);   //�򿪵δ�ʱ��
		while(!(SysTick->CTRL&(0X1<<16)));//ʱ�䲻�ɳ���800����
		SysTick->CTRL&=~(0x1<<0);   //ʱ�䵽��ֹͣ�δ�ʱ���Ĺ���
}
void systick_interrupt(u32 nms)
{
		SysTick->CTRL&=~(0Xf<<0);
		SysTick->CTRL|=(0X0<<2);
		SysTick->VAL=0;
		SysTick->LOAD|=nms*21000;
		if(nms>0xffffff/21000)
			return ;
		SysTick->CTRL|=(0x1<<0);	
		SysTick->CTRL|=(0x1<<1);   //�򿪵δ�ʱ�����ж�ʹ��λ
}
void SysTick_Handler(void)
{
		SysTick->VAL=0;//�����־λ
	
	GPIOC->ODR^=(0x1<<4);  //����LED�Ƶ�����
		
} 

