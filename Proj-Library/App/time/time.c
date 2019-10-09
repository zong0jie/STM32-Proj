#include "time.h"
#include "led.h"

/**
* 通用定时器的update定时中断
* 定时时间周期 公式：
* Tout=(per*(psc+1))/Tclk
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
* @param TIMx 通用定时器有 TIM2, TIM3, TIM4, TIM5 这4个，具体看stm32中文手册
* @param pre 是 自动重载寄存器的值
* @param psc 是预分频系数 1-65535, 方法里面会自动-1
* @param TIM_CounterMode 一般有 @ref TIM_CounterMode_Up 等
*/
void TIMx_Init_Update(TIM_TypeDef* TIMx, u16 pre, u16 psc, uint16_t TIM_CounterMode) {
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

void TIM4_IRQHandler(void) {
	if(TIM_GetITStatus(TIM4, TIM_IT_Update)) {
		led8 = !led8;
	}
	TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
}
	