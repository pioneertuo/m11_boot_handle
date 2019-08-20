#ifndef __BAT_H__
#define __BAT_H__

#include <stdint.h>

#define POWER_EN_OFF			GPIOA->BRR = GPIO_Pin_15
#define POWER_EN_ON				GPIOA->BSRR = GPIO_Pin_15
#define POWER_EN_STAT			(GPIOA->ODR&GPIO_Pin_15)

void bat_init(void);
void bat_shut_down_process(void);

#endif
