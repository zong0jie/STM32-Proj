#include "beep.h"

void BEEP_Init() {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitTypeDef gpioInit;
	gpioInit.GPIO_Pin = GPIO_Pin_5;
	gpioInit.GPIO_Mode = GPIO_Mode_Out_PP;
	gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &gpioInit);
	GPIO_SetBits(GPIOB, GPIO_Pin_5);
}