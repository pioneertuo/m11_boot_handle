#include "uart3.h"
#include "includes.h"

//static fifo_type uart3_fifo = {
fifo_type uart3_fifo = {
	0,
	0,
	{0},
};

void uart3_init(void)
{	
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	
	//PB10 - USART3_TX
	//PB11 - USART3_RX
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_7);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_7);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;
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
	USART_Init(USART3, &USART_InitStructure);
	
	USART_OverrunDetectionConfig(USART3, USART_OVRDetection_Disable);
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	
	USART_Cmd(USART3, ENABLE);
	
	//清除RXNE标志位
	USART3->RQR |= USART_Request_RXFRQ;
	nvic_set(USART3_IRQn, IRQ_PRI_UART3);
}

void uart3_send_byte(uint8_t dat)
{
    while((USART3->ISR&USART_FLAG_TXE) == RESET);
	USART3->TDR = dat;
}

void uart3_send_bytes(uint8_t *buf, uint16_t len)
{
	uint16_t i;
	
	for(i=0; i<len; i++)
	{
		while((USART3->ISR&USART_FLAG_TXE) == RESET);
		USART3->TDR = buf[i];
	}
}

uint8_t uart3_fifo_fetch(uint8_t *dat)
{
	return fifo_fetch(&uart3_fifo, dat);
}

void USART3_IRQHandler(void)
{	
	uint8_t dat;
	
	if((USART3->ISR&USART_ISR_RXNE) != RESET)
	{
		dat = USART3->RDR;
		
		fifo_append(&uart3_fifo, dat);
	}
}

