#ifndef __LED_H__
#define __LED_H__

#define LED1_ON				GPIOC->BRR = GPIO_Pin_13
#define LED1_OFF			GPIOC->BSRR = GPIO_Pin_13
#define LED1_SW				GPIOC->ODR=GPIOC->ODR^GPIO_Pin_13

#define LED2_ON				GPIOC->BRR = GPIO_Pin_14
#define LED2_OFF			GPIOC->BSRR = GPIO_Pin_14
#define LED2_SW				GPIOC->ODR=GPIOC->ODR^GPIO_Pin_14

#define LED3_ON				GPIOB->BRR = GPIO_Pin_9
#define LED3_OFF			GPIOB->BSRR = GPIO_Pin_9
#define LED3_SW				GPIOB->ODR=GPIOB->ODR^GPIO_Pin_9

void led_init(void);
void led_process(void);

#endif
