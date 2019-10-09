#ifndef _nb_tick_H
#define _nb_tick_H

#include "nb_base.h"

void SysTick_Init();
void delay_us(u32 nus);
void delay_ms(u16 nms);

#endif