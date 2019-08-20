#ifndef __UART1_H__
#define __UART1_H__

#include <stdint.h>

void uart1_init(void);
void uart1_send_bytes(uint8_t *buf, uint16_t len);
uint8_t uart1_fifo_fetch(uint8_t *dat);

#endif
