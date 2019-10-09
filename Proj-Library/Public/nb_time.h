#ifndef _nb_time_H
#define _nb_time_H

#include "nb_base.h"

void EXTI_TIMxUpdate_Init(TIM_TypeDef* TIMx, u16 pre, u16 psc, uint16_t TIM_CounterMode);
void TIM3PWM_Init(u16 pre, u16 psc);
void TIMxPWM_Init(TIM_TypeDef* TIMx, u8 OCnum, u16 pre, u16 psc, uint16_t TIM_OCPolarity);

#endif