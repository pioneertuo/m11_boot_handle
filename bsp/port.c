#include "port.h"
#include "includes.h"

static void pwm_en_port_config(void);

#define PWM_ON					GPIOA->BSRR = GPIO_Pin_11
#define PWM_OFF					GPIOA->BRR = GPIO_Pin_11

void port_init(void)
{
    pwm_en_port_config();
}

static void pwm_en_port_config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	
	//PA11 - PWM_EN
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	PWM_OFF;
}

