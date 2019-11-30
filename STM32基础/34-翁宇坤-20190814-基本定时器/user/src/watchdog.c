#include "watchdog.h"
void watchdog_init(void)
{
RCC->CR|=(0x1<<0);//开启LSI时钟
while(!RCC->CSR&(0x1<<1)) //等待LSI时钟准备就绪
{
	
}
IWDG->KR|=(0x5555<<0);//去除PR,RLR的写保护
IWDG->PR|=2;//16分频，2500HZ
IWDG->RLR=2500;//计数值为2500，复位时间1秒
IWDG->KR|=0XAAAA;//第一次喂狗
IWDG->KR|=0XCCCC;//启动看门狗
}

