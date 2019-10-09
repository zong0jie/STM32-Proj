#include "nb_sys.h"
#include "led.h"
#include "beep.h"
#include "key.h"


int main() {
	RCC_HSE_Config(RCC_PLLSource_HSE_Div1, RCC_PLLMul_4);
	SysTick_Init();
	LED_Init();
	KEY_Init();
	
//	TIM3PWM_Init(500, 72);//2K
//	
//	u8 fx = 0;
//	u16 i = 0;
	while(1){
//		if(fx == 0){
//			i++;
//			if(i==300) fx =1;
//		} else {
//			i--;
//			if(i==0) fx = 0;
//		}
//		TIM_SetCompare1(TIM3, i);
//		delay_ms(10);
	}
}

