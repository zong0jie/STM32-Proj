#include "nb_exti.h"

/**
* 初始化引脚的GPIO复用AFIO中断
* 如果绑定多个不同的GPIOx口，这里只需要初始化一次
*/
void EXTI_GPIO_Init() {
	//输入引脚复用 进行重映射时 需要开启AFIO 时钟 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	//设置中断分组，0-4组，划分几位给Primer优先级，几位给Sub优先级
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
}

/**
* 把某个GPIO口绑定到相应的EXTI_Linex上去
* 可以通过 @ref EXTI3_IRQHandler()，来执行相应的中断内容，代码类似如下：
*
void EXTI3_IRQHandler() {
	//某个EXTI线路使能并且中断了
	if(EXTI_GetITStatus(EXTI_Line3)) {
		//TODO
	}
	EXTI_ClearITPendingBit(EXTI_Line3);
}
*
* @param GPIOx
* @param GPIO_PinSource 类似 GPIO_PinSource0 这种
*/
void EXTI_ENABLE_GPIO_PIN(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, EXTITrigger_TypeDef triggerType) {
	uint8_t gpioPortSource;
	if(GPIOx == GPIOA) {
		gpioPortSource = GPIO_PortSourceGPIOA;
	}	else if(GPIOx == GPIOB) {
		gpioPortSource = GPIO_PortSourceGPIOB;
	}	else if(GPIOx == GPIOC) {
		gpioPortSource = GPIO_PortSourceGPIOC;
	}	else if(GPIOx == GPIOD) {
		gpioPortSource = GPIO_PortSourceGPIOD;
	}	else if(GPIOx == GPIOE) {
		gpioPortSource = GPIO_PortSourceGPIOE;
	}	else if(GPIOx == GPIOF) {
		gpioPortSource = GPIO_PortSourceGPIOF;
	}	else if(GPIOx == GPIOG) {
		gpioPortSource = GPIO_PortSourceGPIOG;
	}
	
	uint8_t gpioPinSource;
	uint8_t extix_IRQn;
	uint32_t extiLine;
	if(GPIO_Pin == GPIO_Pin_0) {
		gpioPinSource = GPIO_PinSource0;
		extix_IRQn = EXTI0_IRQn;
		extiLine = EXTI_Line0;
	} else if(GPIO_Pin == GPIO_Pin_1) {
		gpioPinSource = GPIO_PinSource1;
		extix_IRQn = EXTI1_IRQn;
		extiLine = EXTI_Line1;
	} else if(GPIO_Pin == GPIO_Pin_2) {
		gpioPinSource = GPIO_PinSource2;
		extix_IRQn = EXTI2_IRQn;
		extiLine = EXTI_Line2;
	} else if(GPIO_Pin == GPIO_Pin_3) {
		gpioPinSource = GPIO_PinSource3;
		extix_IRQn = EXTI3_IRQn;
		extiLine = EXTI_Line3;
	} else if(GPIO_Pin == GPIO_Pin_4) {
		gpioPinSource = GPIO_PinSource4;
		extix_IRQn = EXTI4_IRQn;
		extiLine = EXTI_Line4;
	} else if(GPIO_Pin == GPIO_Pin_5) {
		gpioPinSource = GPIO_PinSource5;
		extix_IRQn = EXTI9_5_IRQn;
		extiLine = EXTI_Line5;
	} else if(GPIO_Pin == GPIO_Pin_6) {
		gpioPinSource = GPIO_PinSource6;
		extix_IRQn = EXTI9_5_IRQn;
		extiLine = EXTI_Line6;
	} else if(GPIO_Pin == GPIO_Pin_7) {
		gpioPinSource = GPIO_PinSource7;
		extix_IRQn = EXTI9_5_IRQn;
		extiLine = EXTI_Line7;
	} else if(GPIO_Pin == GPIO_Pin_8) {
		gpioPinSource = GPIO_PinSource8;
		extix_IRQn = EXTI9_5_IRQn;
		extiLine = EXTI_Line8;
	} else if(GPIO_Pin == GPIO_Pin_9) {
		gpioPinSource = GPIO_PinSource9;
		extix_IRQn = EXTI9_5_IRQn;
		extiLine = EXTI_Line9;
	} else if(GPIO_Pin == GPIO_Pin_10) {
		gpioPinSource = GPIO_PinSource10;
		extix_IRQn = EXTI15_10_IRQn;
		extiLine = EXTI_Line10;
	} else if(GPIO_Pin == GPIO_Pin_11) {
		gpioPinSource = GPIO_PinSource11;
		extix_IRQn = EXTI15_10_IRQn;
		extiLine = EXTI_Line11;
	} else if(GPIO_Pin == GPIO_Pin_12) {
		gpioPinSource = GPIO_PinSource12;
		extix_IRQn = EXTI15_10_IRQn;
		extiLine = EXTI_Line12;
	} else if(GPIO_Pin == GPIO_Pin_13) {
		gpioPinSource = GPIO_PinSource13;
		extix_IRQn = EXTI15_10_IRQn;
		extiLine = EXTI_Line13;
	} else if(GPIO_Pin == GPIO_Pin_14) {
		gpioPinSource = GPIO_PinSource14;
		extix_IRQn = EXTI15_10_IRQn;
		extiLine = EXTI_Line14;
	} else if(GPIO_Pin == GPIO_Pin_15) {
		gpioPinSource = GPIO_PinSource15;
		extix_IRQn = EXTI15_10_IRQn;
		extiLine = EXTI_Line15;
	}
	
	//使能GPIO某个引脚，把这个引脚映射到对应的外部中断线路上
	GPIO_EXTILineConfig(gpioPortSource, gpioPinSource);
	
	//针对本中断，设置对应的抢占优先级和响应优先级，并绑定到指定的EXTI线上
	NVIC_InitTypeDef nvicInit;
	nvicInit.NVIC_IRQChannel = extix_IRQn;//中断源
	nvicInit.NVIC_IRQChannelPreemptionPriority = 2;
	nvicInit.NVIC_IRQChannelSubPriority = 3;
	nvicInit.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvicInit);
	
	//配置具体某根EXTI线的检测模式，上升沿下降沿等
	EXTI_InitTypeDef extiInit;
	extiInit.EXTI_Line = extiLine;
	extiInit.EXTI_Mode = EXTI_Mode_Interrupt;
	extiInit.EXTI_Trigger = triggerType;
	extiInit.EXTI_LineCmd = ENABLE;
	EXTI_Init(&extiInit);
}

