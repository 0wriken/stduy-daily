#include "led.h"
/*
***********************************************************************************************
* ��������:LED�Ƴ�ʼ��
* �����β�: None
* ��������ֵ: None
* ��ע: None
* ����: wriken
* ʱ��: 2019-08-06
* �޸�����: None
* �޸�ʱ��: None
***********/
void led_init(void)
{
	/*��ʼ��PC4,PC5*/
	RCC->AHB1ENR|=(0x1<<2);//ʱ�ӼĴ�����ʼ��
	GPIOC->MODER&=~(0xf<<2*4);//ģʽ�Ĵ�����0
	GPIOC->MODER|=(0x5<<2*4);//ģʽ�Ĵ�����Ϊ���
	GPIOC->OTYPER&=~(0x3<<4);//�������λ����
	GPIOC->PUPDR&=~(0Xf<<2*4);//����
	GPIOC->OSPEEDR&=~(0Xf<<2*4);//�ٶ�λ2M
	GPIOC->ODR|=(0x3<<4);   //������ݼĴ���д������1
	
	/*��ʼ��PA6,PA7*/
	RCC->AHB1ENR|=(0x1<<0); //ͬ��
	GPIOA->MODER&=~(0xf<<2*6);
	GPIOA->MODER|=(0x5<<2*6);
	GPIOA->OTYPER&=~(0x3<<6);
	GPIOA->PUPDR&=~(0Xf<<2*6);
	GPIOA->OSPEEDR&=~(0Xf<<2*6);
	GPIOA->ODR|=(0x3<<6);
}
