#include "fifo.h"
#include "includes.h"

void fifo_append(fifo_type *fifo, uint8_t dat)
{
	fifo->buf[fifo->w] = dat;
	
	if(fifo->w+1 == FIFO_SIZE)
	{
		fifo->w = 0;
	}
	else
	{
		fifo->w += 1;
	}
}

uint8_t fifo_fetch(fifo_type *fifo, uint8_t *dat)
{
	if(fifo->w == fifo->r){
		return 0;
	}
	
	*dat = fifo->buf[fifo->r];
	
	if(fifo->r+1 == FIFO_SIZE)
	{
		fifo->r = 0;
	}
	else
	{
		fifo->r += 1;
	}
	
	return 1;
}

