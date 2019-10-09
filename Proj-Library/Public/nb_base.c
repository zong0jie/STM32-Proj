#include "nb_base.h"


u8 SYSCLK=72;

/**
* 自定义系统时间（可以修改时钟）
* 设定单片机的频率，是否分频，以及倍频
* div RCC_PLLSource_HSI_Div2 是否分频，分频就变慢，不分频72Mhz，分频36Mhz
* pllm RCC_PLLMul_6 倍频
*/
void RCC_HSE_Config(u32 div,u32 pllm) {
	RCC_DeInit(); //将外设RCC寄存器重设为缺省值
	RCC_HSEConfig(RCC_HSE_ON);//设置外部高速晶振（HSE）
	//等待HSE起振
	if(RCC_WaitForHSEStartUp()==SUCCESS) {
	
		RCC_HCLKConfig(RCC_SYSCLK_Div1);//设置AHB时钟（HCLK）
		RCC_PCLK1Config(RCC_HCLK_Div2);//设置低速AHB时钟（PCLK1）
		RCC_PCLK2Config(RCC_HCLK_Div1);//设置高速AHB时钟（PCLK2）
		RCC_PLLConfig(div,pllm);//设置PLL时钟源及倍频系数
		RCC_PLLCmd(ENABLE); //使能或者失能PLL
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY)==RESET);//检查指定的RCC标志位设置与否,PLL就绪
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);//设置系统时钟（SYSCLK）
		while(RCC_GetSYSCLKSource()!=0x08);//返回用作系统时钟的时钟源,0x08：PLL作为系统时钟
	}
	u8 divReal = 1;
	if(div == RCC_PLLSource_HSE_Div2) {
		divReal = 2;
	}
	u8 externalClock = 9; 
	switch (pllm) {
		case RCC_PLLMul_2:
			externalClock = 2;
			break;
		case RCC_PLLMul_3:
			externalClock = 3;
			break;
		case RCC_PLLMul_4:
			externalClock = 4;
			break;
		case RCC_PLLMul_5:
			externalClock = 5;
			break;
		case RCC_PLLMul_6:
			externalClock = 6;
			break;
		case RCC_PLLMul_7:
			externalClock = 7;
			break;
		case RCC_PLLMul_8:
			externalClock = 8;
			break;
		case RCC_PLLMul_9:
			externalClock = 9;
			break;
		case RCC_PLLMul_10:
			externalClock = 10;
			break;
		case RCC_PLLMul_11:
			externalClock = 11;
			break;
		case RCC_PLLMul_12:
			externalClock = 12;
			break;
		case RCC_PLLMul_13:
			externalClock = 13;
			break;
		case RCC_PLLMul_14:
			externalClock = 14;
			break;
		case RCC_PLLMul_15:
			externalClock = 15;
			break;
		case RCC_PLLMul_16:
			externalClock = 16;
			break;
		default:
			externalClock = 9;
			break;
	}
	SYSCLK = 8/divReal*externalClock;
}

