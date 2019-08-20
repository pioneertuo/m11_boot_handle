#include "btn.h"
#include "includes.h"

#define BTN_POWER_IN	(GPIOB->IDR&GPIO_Pin_3)
#define BTN_CENTER_IN	(GPIOA->IDR&GPIO_Pin_7)

static void btn_port_config(void);


void btn_init(void)
{
	btn_port_config();
}

static void btn_port_config(void)
{	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	
	//power
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//center
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

uint8_t btn_power_active(void)
{
	if(BTN_POWER_IN == 0){
		return 1;
	}
	else{
		return 0;
	}
}

uint8_t btn_center_active(void)
{
	if(BTN_CENTER_IN == 0){
		return 1;
	}
	else{
		return 0;
	}
}


