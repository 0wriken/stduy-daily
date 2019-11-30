#ifndef USART_H_
#define USART_H_
#include "stm32f10x.h"
void usart_init(u32 boad);
u8 uart_recive_data(void);//½ÓÊÕ
void uart_send_data(u8 send_data);//·¢ËÍ

#endif




