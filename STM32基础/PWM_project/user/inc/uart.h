#ifndef UART_H_
#define UART_H_
#include "stm32f4xx.h"
#include "stdio.h"
#include <string.h>
void uart_init(u32 B);
u8 *uart_recive(void);
u8 uart_recive_data(void);
void uart_send(u8 *send_buf);
void uart_send_data(u8 send_data);
void usart_string(void);
void uart_char(void);
#endif
