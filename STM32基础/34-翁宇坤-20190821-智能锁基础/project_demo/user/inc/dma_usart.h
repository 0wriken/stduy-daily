#ifndef DMA_USART_H_
#define DMA_USART_H_
#include "stm32f10x.h"
#include "usart.h"

void dma1_stream7_init(u8 *m_addr,u8 *p_addr,u16 data_num);

#endif

