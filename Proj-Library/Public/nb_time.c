#include "nb_time.h"
#include "nb_gpio.h"



void TIMxUpdate_Init(TIM_TypeDef* TIMx, u16 pre, u16 psc, uint16_t TIM_CounterMode);

/**
* 通用定时器的update定时中断
* 定时时间周期 公式：
* Tout=(per*(psc))/Tclk
*
* 可以通过类似 @ref TIM4_IRQHandler ，来执行相应的中断内容，代码类似如下：
*
void TIM4_IRQHandler(void) {
	if(TIM_GetITStatus(TIM4, TIM_IT_Update)) {
		//TODO
	}
	TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
}
*
* 注意如果漏写了上述中断执行方法，很可能程序会挂起，单片机没反应
*
* @param TIMx 通用定时器有 TIM2, TIM3, TIM4, TIM5 这4个，具体看stm32中文手册
* 基本定时器是TIM6, TIM7。高级定时器是TIM1和TIM8。基本定时器无法输出PWM
* @param pre 是 自动重载寄存器的值
* @param psc 是预分频系数 1-65535, 方法里面会自动-1
* @param TIM_CounterMode 一般有 @ref TIM_CounterMode_Up 等
*/
void EXTI_TIMxUpdate_Init(TIM_TypeDef* TIMx, u16 pre, u16 psc, uint16_t TIM_CounterMode) {
	uint8_t timx_IRQn;
	
	if(TIMx == TIM2) {
		timx_IRQn = TIM2_IRQn;
	} else if(TIMx == TIM3) {
		timx_IRQn = TIM3_IRQn;
	} else if(TIMx == TIM4) {
		timx_IRQn = TIM4_IRQn;
	} else if(TIMx == TIM5) {
		timx_IRQn = TIM5_IRQn;
	}
	TIMxUpdate_Init(TIMx, pre, psc, TIM_CounterMode);
	
	//配置中断处理NVIC
	NVIC_InitTypeDef nvicInit;
	nvicInit.NVIC_IRQChannel = timx_IRQn;//中断源
	nvicInit.NVIC_IRQChannelPreemptionPriority = 2;
	nvicInit.NVIC_IRQChannelSubPriority = 3;
	nvicInit.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvicInit);
	
	//清除原来定时器可能存在的状态
	TIM_ClearITPendingBit(TIMx, TIM_IT_Update);
	//开启时钟
	TIM_Cmd(TIMx, ENABLE);
}

void TIMxUpdate_Init(TIM_TypeDef* TIMx, u16 pre, u16 psc, uint16_t TIM_CounterMode) {
	uint32_t rcc_APB1Periph;
	uint8_t timx_IRQn;
	
	if(TIMx == TIM2) {
		rcc_APB1Periph = RCC_APB1Periph_TIM2;
		timx_IRQn = TIM2_IRQn;
	} else if(TIMx == TIM3) {
		rcc_APB1Periph = RCC_APB1Periph_TIM3;
		timx_IRQn = TIM3_IRQn;
	} else if(TIMx == TIM4) {
		rcc_APB1Periph = RCC_APB1Periph_TIM4;
		timx_IRQn = TIM4_IRQn;
	} else if(TIMx == TIM5) {
		rcc_APB1Periph = RCC_APB1Periph_TIM5;
		timx_IRQn = TIM5_IRQn;
	}
	
	RCC_APB1PeriphClockCmd(rcc_APB1Periph, ENABLE);

	TIM_TimeBaseInitTypeDef timeInit;
	//timeInit.TIM_RepetitionCounter  高级定时器特有
	
	//自动重载寄存器的值，似乎是TIMx_ARR的值
	timeInit.TIM_Period = pre;
	
	psc--;
	//预分频系数，用于PSC。1-65535，这里设定的值会+1，也就是设置0实际是1
	timeInit.TIM_Prescaler = psc;
	
	/**
	* 以上
	* 根据自动重载值和预分频系数，可以计算定时时间周期
	* 公式：Tout= ((per)*(psc+1))/Tclk
	* Tclk:定时器的输入时钟频率，一般是72Mhz
	*/
	
	timeInit.TIM_ClockDivision = TIM_CKD_DIV1;//对输入信号进行采样分频，没有输入信号就不需要设置这个
	timeInit.TIM_CounterMode = TIM_CounterMode;
	
	TIM_TimeBaseInit(TIMx, &timeInit);
	
	//这里使用了更新中断 TIM_IT_Update，还有CC1，CC2等是比较中断
	TIM_ITConfig(TIMx, TIM_IT_Update, ENABLE);
	//总共这几种中断类型
	//A．更新：计数器向上溢出/向下溢出，计数器初始化(通过软件或者内部/外部触发)
	//B．触发事件(计数器启动、停止、初始化或者由内部/外部触发计数)
	//C．输入捕获
	//D．输出比较
}

void TIM3PWM_Init(u16 pre, u16 psc) {
	GPIOx_Init_with_Pin_Mode(GPIOC, GPIO_Pin_6, GPIO_Mode_AF_PP);
	GPIO_PinRemap(GPIO_FullRemap_TIM3);
	
	TIMxUpdate_Init(TIM3, pre, psc, TIM_CounterMode_Up);
	
	TIM_OCInitTypeDef timeOcInit;
	timeOcInit.TIM_OCMode = TIM_OCMode_PWM1;
	timeOcInit.TIM_OCPolarity = TIM_OCPolarity_Low;//输出极性，输出有效是高电平还是低电平
	timeOcInit.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OC1Init(TIM3, &timeOcInit);
	
	TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM3, ENABLE);
	
	TIM_Cmd(TIM3, ENABLE);
}

/**
* 
* 注意，在pwm调节时，当选择了特定的定时器 TIMx 通道 OCnum，后面也要设置相应的 TIM_SetComparex()方法
* 譬如设置 TIM3 OCnum 设置为2，那么后面循环/中断中也要设置 @ref TIM_SetCompare2(TIM3, compareNum)
* 
* @param TIMx 选择哪个定时器，目前只支持通用定时器，这四个 TIM2, TIM3, TIM4, TIM5
* @param OCnum 每个定时器有4个通道，可以设置1-4
* @param pre 是 自动重载寄存器的值
* @param psc 是预分频系数 1-65535, 方法里面会自动-1
* @param TIM_OCPolarity 高电平还是低电平有效 @ref TIM_OCPolarity_Low
*/
void TIMxPWM_Init(TIM_TypeDef* TIMx, u8 OCnum, u16 pre, u16 psc, uint16_t TIM_OCPolarity) {	
	TIMxUpdate_Init(TIMx, pre, psc, TIM_CounterMode_Up);
	
	TIM_OCInitTypeDef timeOcInit;
	timeOcInit.TIM_OCMode = TIM_OCMode_PWM1;
	timeOcInit.TIM_OCPolarity = TIM_OCPolarity;//输出极性，输出有效是高电平还是低电平
	timeOcInit.TIM_OutputState = TIM_OutputState_Enable;
	
	if(OCnum==1){
		TIM_OC1Init(TIMx, &timeOcInit);
		TIM_OC1PreloadConfig(TIMx,TIM_OCPreload_Enable);
	} else if(OCnum==2) {
		TIM_OC2Init(TIMx, &timeOcInit);
		TIM_OC2PreloadConfig(TIMx,TIM_OCPreload_Enable);
	} else if(OCnum==3) {
		TIM_OC3Init(TIMx, &timeOcInit);
		TIM_OC3PreloadConfig(TIMx,TIM_OCPreload_Enable);
	} else if(OCnum==4) {
		TIM_OC4Init(TIMx, &timeOcInit);
		TIM_OC4PreloadConfig(TIMx,TIM_OCPreload_Enable);
	}
	
	TIM_ARRPreloadConfig(TIMx, ENABLE);
	
	TIM_Cmd(TIMx, ENABLE);
}