#include "key.h"
/*
***********************************************************************************************
* ��������:����PA0,PE2
* �����β�: None
* ��������ֵ: None
* ��ע: None
* ����: wriken
* ʱ��: 2019-08-06
* �޸�����: None
* �޸�ʱ��: None
***********/
void key_init()
{
	//��ʼ������PA0;
	RCC->AHB1ENR|=(0x1<<0);//����ʱ��ʹ��
	GPIOA->MODER&=~(0x3<<2*0);//ģʽ�Ĵ�����0
	GPIOA->MODER|=(0x0<<2*0);//����Ϊ����ģʽ
	GPIOA->PUPDR&=~(0x3<<2*0);//����
	//��ʼ������PE23;
	RCC->AHB1ENR|=(0x1<<4);//ͬ��
	GPIOE->MODER&=~(0xf<<2*2);
	GPIOE->MODER|=(0x00<<2*2);
	GPIOE->PUPDR&=~(0xf<<2*2);
	//��ʼ������PE4;
	RCC->AHB1ENR|=(0x1<<4);
	GPIOE->MODER&=~(0x3<<2*4);
	GPIOE->PUPDR&=~(0xf<<2*4);
}
static void key_delay(u32 time)
{
	time *=42;//42Ϊ1΢��
	while(time)
	{
		time--;
	}
}
