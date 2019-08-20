#include "bat.h"
#include "includes.h"

static void bat_power_en_port_config(void);

void bat_init(void)
{
	bat_power_en_port_config();
	
	
}

static void bat_power_en_port_config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	POWER_EN_OFF;
}

#define SHUT_DOWN_HOLD_MS		1000

void bat_shut_down_process(void)
{
	static uint8_t start_flag = 0;
	static uint32_t start_cnt = 0;
	
	if(btn_power_active())
	{
		if(start_flag == 0)
		{
			start_cnt = timebase.cnt;
			start_flag = 1;
		}
		else
		{
			if(timebase.cnt-start_cnt > SHUT_DOWN_HOLD_MS)
			{
				POWER_EN_OFF;
				
				LED1_OFF;
				LED2_OFF;
				LED3_OFF;
				
				while(1);
			}
		}
	}
	else
	{
		start_flag = 0;
		start_cnt = 0;
	}
}



