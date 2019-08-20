#ifndef __UTIL_H__
#define __UTIL_H__

#include <stdint.h>

#define STM32F3_UDID_ADDR				((uint32_t)0x1FFFF7AC)

#define ERR								0
#define OK								1

#define ROL								0
#define PIT								1
#define YAW								2

#define R2D(x)  						((x)*57.2957795130823f)
#define D2R(x)  						((x)*0.01745329251994f)

#define BYTE3(val)  					(*((uint8_t *)(&val)+3))
#define BYTE2(val)  					(*((uint8_t *)(&val)+2))
#define BYTE1(val)  					(*((uint8_t *)(&val)+1))
#define BYTE0(val)  					(*(uint8_t *)(&val))

#define mymax(a, b)						(((a)>(b))?(a):(b))
#define mymin(a, b)						(((a)<(b))?(a):(b))
#define myabs(a)						(((a)>=0)?(a):-(a))

#define inrange(x, min, max)			(((x)<(min))?0:(((x)>(max))?0:1))
#define constrain(v, lo, hi)	    	(((v)<(lo))?(lo):(((v)>(hi))?(hi):(v)))

void nvic_set(uint8_t ch, uint8_t pre, uint8_t sub);
void nvic_disable(uint8_t ch);
float sgn(float val);
uint8_t calc_sum(uint8_t *buf, uint16_t len);


#endif
