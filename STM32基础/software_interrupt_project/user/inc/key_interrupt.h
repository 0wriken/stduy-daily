#ifndef  KEY_INTERRUPT_H
#define  KEY_INTERRUPT_H
#include "stm32f4xx.h"
extern  u32 i ;
static void key_delay(u32 time);
void key_interrupt_init(void);
void soft_interrupt_init(void);
#endif
