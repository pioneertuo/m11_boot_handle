#include "sys.h"
#include "includes.h"

typedef void(*reset_handler_type)(void);

sys_type sys;

void sys_init(void)
{	
	sys.pit_connect_ok = 0;
}

//复位用到的外设
void sys_periph_deinit(void)
{	
	GPIO_DeInit(GPIOA);
	GPIO_DeInit(GPIOB);
	
	TIM_DeInit(TIM15);
}

void sys_jump_to_app(uint32_t app_addr)
{
	reset_handler_type reset_handler;
	
	reset_handler = (reset_handler_type)*(__IO uint32_t*)(app_addr+4);
	
	__set_MSP(*(__IO uint32_t*) app_addr);	
	
	reset_handler();
	
	while(1);
}


