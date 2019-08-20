#include "timebase.h"
#include "includes.h"

#define TIMEBASE_TICKS_PER_SEC			1000

timebase_type timebase = {
	0
};

void timebase_init(void)
{
	uint32_t cnts;
	RCC_ClocksTypeDef rcc_clocks;
	
	RCC_GetClocksFreq(&rcc_clocks);
	
    cnts = rcc_clocks.HCLK_Frequency/TIMEBASE_TICKS_PER_SEC;
	
	SysTick_Config(cnts);
}

void systick_deinit(void)
{
	SysTick->CTRL = 0;
	SysTick->VAL = 0;
	SysTick->LOAD = 0;
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	timebase.cnt += 1;
}

