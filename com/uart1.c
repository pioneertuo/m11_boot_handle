#include "uart1.h"
#include "includes.h"

static fifo_type uart1_fifo = {
	0,
	0,
	{0},
};

void uart1_init(void)
{	
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	//PB6 - USART1_TX
	//PB7 - USART1_RX
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_7);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_7);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);
	
	USART_OverrunDetectionConfig(USART1, USART_OVRDetection_Disable);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
	USART_Cmd(USART1, ENABLE);
	
	//清除RXNE标志位
	USART1->RQR |= USART_Request_RXFRQ;
	nvic_set(USART1_IRQn, IRQ_PRI_UART1);
}

void uart1_send_bytes(uint8_t *buf, uint16_t len)
{
	uint16_t i;
	
	for(i=0; i<len; i++)
	{
		while((USART1->ISR&USART_FLAG_TXE) == RESET);
		USART1->TDR = buf[i];
	}
}

uint8_t uart1_fifo_fetch(uint8_t *dat)
{
	return fifo_fetch(&uart1_fifo, dat);
}

void USART1_IRQHandler(void)
{	
	uint8_t dat;
	
	if((USART1->ISR&USART_ISR_RXNE) != RESET)
	{
		dat = USART1->RDR;
		
		fifo_append(&uart1_fifo, dat);
	}
}

