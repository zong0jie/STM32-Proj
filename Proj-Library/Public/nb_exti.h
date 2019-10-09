#ifndef _nb_exti_H
#define _nb_exti_H

#include "nb_base.h"

/** 初始化中断，因为系统存在同名方法，因此这里最后加上 _NB 作为区分 */
void EXTI_GPIO_Init();

/**
* 把某个GPIO口绑定中断
* @param GPIOx
* @param GPIO_PinSource 类似 GPIO_PinSource0 这种
*/
void EXTI_ENABLE_GPIO_PIN(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, EXTITrigger_TypeDef triggerType);

#endif