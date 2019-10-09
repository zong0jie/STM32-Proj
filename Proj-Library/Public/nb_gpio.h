#ifndef _nb_gpio_H
#define _nb_gpio_H

#include "nb_base.h"

void GPIOx_Out_Init(GPIO_TypeDef* GPIOx);
void GPIOx_Out_Init_with_Pin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void GPIOx_Init_with_Pin_Mode(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIOMode_TypeDef GPIOMOde);
void GPIO_PinRemap(uint32_t GPIO_Remap);

#endif