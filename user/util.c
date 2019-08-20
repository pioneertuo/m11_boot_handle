#include "util.h"
#include "includes.h"

void nvic_set(uint8_t ch, uint8_t pre, uint8_t sub)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitStructure.NVIC_IRQChannel = ch;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = pre;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = sub;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure); 
}

void nvic_disable(uint8_t ch)
{
	NVIC->ICER[ch>>0x05] = (uint32_t)0x01<<(ch&(uint8_t)0x1F);
}

float sgn(float val)
{
	if(val > 0){
		return 1;
	}
	else if(val < 0){
		return -1;
	}
	else{
		return 0;
	}
}

uint8_t calc_sum(uint8_t *buf, uint16_t len)
{
	uint16_t i;
	uint8_t sum = 0;
	
	for(i=0; i<len; i++){
		sum += buf[i];
	}
	
	return sum;
}
