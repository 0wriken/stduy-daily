#include "delay.h"
/*
***********************************************************************************************
* 函数功能：延时
* 函数形参: None
* 函数返回值: None
* 备注: None
* 作者: wriken
* 时间: 2019-08-06
* 修改作者: None
* 修改时间: None
***********/
void delay(u16 time)//形参传入数据控制时间
{    
   u16 i=0;  
   while(time--)
   {
      i=10000;  //自定义控制时间长短
      while(i--); 
   }
}
