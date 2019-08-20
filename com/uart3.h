#ifndef __UART3_H__
#define __UART3_H__

#include <stdint.h>

void uart3_init(void);
void uart3_send_byte(uint8_t dat);
void uart3_send_bytes(uint8_t *buf, uint16_t len);
uint8_t uart3_fifo_fetch(uint8_t *dat);

#endif
