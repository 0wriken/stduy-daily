#include "watchdog.h"
void watchdog_init(void)
{
RCC->CR|=(0x1<<0);//����LSIʱ��
while(!RCC->CSR&(0x1<<1)) //�ȴ�LSIʱ��׼������
{
	
}
IWDG->KR|=(0x5555<<0);//ȥ��PR,RLR��д����
IWDG->PR|=2;//16��Ƶ��2500HZ
IWDG->RLR=2500;//����ֵΪ2500����λʱ��1��
IWDG->KR|=0XAAAA;//��һ��ι��
IWDG->KR|=0XCCCC;//�������Ź�
}

