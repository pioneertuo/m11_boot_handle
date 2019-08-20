#include "delay.h"
#include "includes.h"

static void delay_1ms(void);

void delay_init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM15, ENABLE);
	
	TIM_TimeBaseStructure.TIM_Period = 1000-1;
	TIM_TimeBaseStructure.TIM_Prescaler = 72-1;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM15, &TIM_TimeBaseStructure);
	
	TIM_ARRPreloadConfig(TIM15, ENABLE);
}

static void delay_1ms(void)
{
	TIM15->CNT = 0;
	TIM15->SR = ~TIM_FLAG_Update;
	
	TIM15->CR1 |= TIM_CR1_CEN;
	while((TIM15->SR&TIM_FLAG_Update) == RESET);
	TIM15->CR1 &= ~TIM_CR1_CEN;
}

void delay_ms(uint32_t ms)
{
	uint32_t i;
	
	for(i=0; i<ms; i++){
		delay_1ms();
	}
}

