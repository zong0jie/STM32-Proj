#include "key.h"
#include "nb_sys.h"
#include "led.h"

void KEY_Init() {
	GPIOx_Init_with_Pin_Mode(GPIOA, GPIO_Pin_0, GPIO_Mode_IPD);
	GPIOx_Init_with_Pin_Mode(GPIOE, GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4, GPIO_Mode_IPU);
	
	EXTI_GPIO_Init();
	EXTI_ENABLE_GPIO_PIN(GPIOA, GPIO_Pin_0, EXTI_Trigger_Rising); 
	EXTI_ENABLE_GPIO_PIN(GPIOE, GPIO_Pin_2, EXTI_Trigger_Falling); 
	EXTI_ENABLE_GPIO_PIN(GPIOE, GPIO_Pin_3, EXTI_Trigger_Falling); 
	EXTI_ENABLE_GPIO_PIN(GPIOE, GPIO_Pin_4, EXTI_Trigger_Falling);
}

/**
* mode为0，单次扫描
* mode为1，连续扫描
*/
u8 KEY_Scan(u8 mode) {
	//静态变量，状态会保存
	if(Key_Up==1||Key_Down==0||Key_Left==0||Key_Right==0) {
		delay_ms(10);
		if(Key_Up==1) {
			return K_U;
		} else if(Key_Down == 0) {
			return K_D;
		} else if(Key_Left == 0) {
			return K_L;
		} else if(Key_Right == 0) {
			return K_R;
		}
	}
	return 0;
}

void Light_Led(u8 key) {
	switch(key) {
			case K_U:
				led1 = 0; break;
			case K_D:
				led1 = 1; break;
			case K_L:
				led2 = 0; break;
			case K_R:
				led2 = 1; break;
			default:
				break;
		}
}

void EXTI0_IRQHandler() {
	//某个EXTI线路使能并且中断了
	u8 key;
	if(EXTI_GetITStatus(EXTI_Line0)) {
		key = KEY_Scan(0);
		Light_Led(key);
	}
	//清除中断标志
	EXTI_ClearITPendingBit(EXTI_Line0);
}

void EXTI2_IRQHandler() {
	//某个EXTI线路使能并且中断了
	u8 key;
	if(EXTI_GetITStatus(EXTI_Line2)) {
		key = KEY_Scan(0);
		Light_Led(key);
	}
	EXTI_ClearITPendingBit(EXTI_Line2);
}

void EXTI3_IRQHandler() {
	//某个EXTI线路使能并且中断了
	u8 key;
	if(EXTI_GetITStatus(EXTI_Line3)) {
		key = KEY_Scan(0);
		Light_Led(key);
	}
	EXTI_ClearITPendingBit(EXTI_Line3);
}

void EXTI4_IRQHandler() {
	//某个EXTI线路使能并且中断了
	u8 key;
	if(EXTI_GetITStatus(EXTI_Line4)) {
		key = KEY_Scan(0);
		Light_Led(key);
	}
	EXTI_ClearITPendingBit(EXTI_Line4);
}
