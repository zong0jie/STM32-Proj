#include "led.h"
#include "nb_sys.h"


void LED_Init() {
	GPIOx_Out_Init_with_Pin(GPIOC, LED_PIN);
	EXTI_TIMxUpdate_Init(TIM4, 5, 36000, TIM_CounterMode_Up);
	
	GPIOx_Init_with_Pin_Mode(GPIOC, GPIO_Pin_7, GPIO_Mode_AF_PP);
	GPIO_PinRemap(GPIO_FullRemap_TIM3);
	
	TIMxPWM_Init(TIM3, 2, 500, 72, TIM_OCPolarity_Low);
}

void TIM4_IRQHandler(void) {
//	if(TIM_GetITStatus(TIM4, TIM_IT_Update)) {
//		led8=!led8;
//	}
//	TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	
	if(!TIM_GetITStatus(TIM4, TIM_IT_Update)) {
		return;
	}
	static u8 fx = 0;
	static u16 i = 0;
	if(fx == 0){
		i++;
		if(i==300) fx =1;
	} else {
		i--;
		if(i==0) fx = 0;
	}
	TIM_SetCompare2(TIM3, i);
	TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
}