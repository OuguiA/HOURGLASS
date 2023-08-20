#include "stm32f10x.h"    // Device header
#include "hourGlass.h"
extern struct hourglass hg;
extern uint8_t flag_status;
void Timer_Init(){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	TIM_InternalClockConfig(TIM2);
	
	TIM_TimeBaseInitTypeDef TIM_TimeInitStructure;
	TIM_TimeInitStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;
	TIM_TimeInitStructure.TIM_CounterMode = TIM_CounterMode_Up ;
	TIM_TimeInitStructure.TIM_Period = 9999;
	TIM_TimeInitStructure.TIM_Prescaler = 7199;
	TIM_TimeInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeInitStructure);
	
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM2, DISABLE);
}
void TIM2_IRQHandler(){
		if(TIM_GetITStatus(TIM2, TIM_IT_Update) == SET){
			TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
			flag_status = 1;
			TIM_Cmd(TIM2, DISABLE);
			}
}
