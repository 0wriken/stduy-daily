#include "time.h"
#include "uart.h"
u32 inter6=0;
u32 hour=0,min=0,sec=0;
u32 buff[100]={0};
/***********************************************************************************************
* 函数功能：基本定时器中断初始化
* 函数形参: 32位毫秒
* 函数返回值: None
* 备注: None
* 作者: wriken
* 时间: 2019-08-14
* 修改作者: None
* 修改时间: None
***********/
void time_interrupt(u32 nms)
{
	RCC->APB1ENR |= 0X1 << 5;		//开启TIM6的时钟
	
TIM7->PSC = 8400 - 1;			//进行8400分频，计数器时钟为10KHz
	TIM7->CNT = 0;					//清空计数器的值
	TIM7->ARR = nms * 10 - 1;		//延时为毫秒级
	TIM7->EGR |= 0X1 << 0;			//设置一次UG位
	TIM7->SR &= ~(0X1 << 0);		//清除一次更新标志位(防止出错)
	TIM7->DIER|=(0X1<<0);
	TIM7->CR1 = 0;					//清空控制寄存器1的值
	TIM7->CR1 |= 0X0 << 3;			//定时完成以后自动停止计数
	TIM7->CR1 |= 0X1 << 0;			//开启计数器
	NVIC_SetPriorityGrouping(7-2);//抢占位
	inter6=NVIC_EncodePriority(7-2,0, 0);//抢占与响应优先级
	NVIC_SetPriority(TIM7_IRQn, inter6);//中断类型
	NVIC_EnableIRQ(TIM7_IRQn);	

}
/***********************************************************************************************
* 函数功能：定时中断处理函数实现万年历
* 函数形参: None
* 函数返回值: None
* 备注: None
* 作者: wriken
* 时间: 2019-08-14
* 修改作者: None
* 修改时间: None
***********/
void TIM7_IRQHandler (void)
{
	if(TIM7->SR&(0X1<<0))
	{
		TIM7->SR&=~(0X1<<0);
		sprintf(buff,"%02d:%02d:%02d\r\n",hour,min,sec);
		
		 uart_send((char *)buff);
		sec+=1;
		if(sec>=60)
		{
			sec%=60;
			min+=1;
		}
		if(min>=60)
		{
			min%=60;
			hour+=1;
		}
		
	}
	
}
