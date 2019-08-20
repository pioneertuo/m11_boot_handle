#ifndef __TIMEBASE_H__
#define __TIMEBASE_H__

#include <stdint.h>

typedef struct{
	uint32_t cnt;
}timebase_type;
extern timebase_type timebase;

void timebase_init(void);
void systick_deinit(void);

#endif
