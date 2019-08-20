#ifndef __FIFO_H__
#define __FIFO_H__

#include "sys.h"

#define FIFO_SIZE		MAX_TRANSFER_SIZE

typedef struct{
	uint16_t w;
	uint16_t r;
	uint8_t buf[FIFO_SIZE];
}fifo_type;

void fifo_append(fifo_type *fifo, uint8_t dat);
uint8_t fifo_fetch(fifo_type *fifo, uint8_t *dat);

#endif
