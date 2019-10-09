#include "nb_gpio.h"


void RCC_GPIO_Enable(GPIO_TypeDef* GPIOx) {
	uint32_t RCC_APB2Periph;
	if(GPIOx == GPIOA) {
		RCC_APB2Periph = RCC_APB2Periph_GPIOA;
	}	else if(GPIOx == GPIOB) {
		RCC_APB2Periph = RCC_APB2Periph_GPIOB;
	}	else if(GPIOx == GPIOC) {
		RCC_APB2Periph = RCC_APB2Periph_GPIOC;
	}	else if(GPIOx == GPIOD) {
		RCC_APB2Periph = RCC_APB2Periph_GPIOD;
	}	else if(GPIOx == GPIOE) {
		RCC_APB2Periph = RCC_APB2Periph_GPIOE;
	}	else if(GPIOx == GPIOF) {
		RCC_APB2Periph = RCC_APB2Periph_GPIOF;
	}	else if(GPIOx == GPIOG) {
		RCC_APB2Periph = RCC_APB2Periph_GPIOG;
	}
	RCC_APB2PeriphClockCmd(RCC_APB2Periph, ENABLE);
}

/** GPIO口的初始化 */
void GPIOx_Out_Init(GPIO_TypeDef* GPIOx) {
	RCC_GPIO_Enable(GPIOx);
	GPIO_InitTypeDef gpioInit;
	gpioInit.GPIO_Pin = GPIO_Pin_All;
	gpioInit.GPIO_Mode = GPIO_Mode_Out_PP;
	gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOx, &gpioInit);
	GPIO_SetBits(GPIOC, GPIO_Pin_All);
}
/** GPIO口的初始化 */
void GPIOx_Out_Init_with_Pin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {
	RCC_GPIO_Enable(GPIOx);
	GPIO_InitTypeDef gpioInit;
	gpioInit.GPIO_Pin = GPIO_Pin;
	gpioInit.GPIO_Mode = GPIO_Mode_Out_PP;
	gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOx, &gpioInit);
	GPIO_SetBits(GPIOC, GPIO_Pin);
}

/** GPIO口的初始化 */
void GPIOx_Init_with_Pin_Mode(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIOMode_TypeDef GPIOMOde) {
	RCC_GPIO_Enable(GPIOx);
	GPIO_InitTypeDef gpioInit;
	gpioInit.GPIO_Pin = GPIO_Pin;
	gpioInit.GPIO_Mode = GPIOMOde;
	gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOx, &gpioInit);
	GPIO_SetBits(GPIOC, GPIO_Pin);
}

void GPIO_PinRemap(uint32_t GPIO_Remap) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap, ENABLE);
}
