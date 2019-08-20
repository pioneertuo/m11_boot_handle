#ifndef __FW_VERSION_H__
#define __FW_VERSION_H__

#include <stdint.h>

typedef struct{
	uint8_t first;
	uint8_t second;
	uint8_t third;
}fw_version_type;
extern fw_version_type fw_version;

void fw_version_init(void);
uint8_t fw_version_modify(void);

#endif
