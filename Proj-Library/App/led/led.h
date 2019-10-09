#ifndef _led_H
#define _led_H
#include "nb_sys.h"

void LED_Init();

#define led1 PCout(0)
#define led2 PCout(1)
#define led3 PCout(2)
#define led4 PCout(3)
#define led5 PCout(4)
#define led6 PCout(5)
#define led7 PCout(6)
#define led8 PCout(7)

#define LED_PIN GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6
#define LED_Breath GPIO_Pin_7

#endif