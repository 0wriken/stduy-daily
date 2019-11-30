#ifndef SYSTICK_H_
#define SYSTICK_H_
#include "stm32f4xx.h"
void systick_init(u32 nms);
void systick_interrupt(u32 nms);
#endif
