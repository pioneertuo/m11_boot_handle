#include "led.h"
#include "includes.h"

static void led_port_config(void);
static void led_single_on(uint8_t index);

void led_init(void)
{	
	led_port_config();
}

static void led_port_config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	LED1_OFF;
	LED2_OFF;
	LED3_OFF;
}

static void led_single_on(uint8_t index)
{
	switch(index)
	{
		case 1:
			LED1_ON;
			LED2_OFF;
			LED3_OFF;
			break;
		case 2:
			LED1_OFF;
			LED2_ON;
			LED3_OFF;
			break;
		case 3:
			LED1_OFF;
			LED2_OFF;
			LED3_ON;
			break;
		case 4:
			LED1_OFF;
			LED2_OFF;
			LED3_OFF;
			break;
	}
}

void led_process(void)
{
	uint8_t led_index;
	
	led_index = (timebase.cnt%1000)/250+1;
	
	led_single_on(led_index);
}


