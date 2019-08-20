#ifndef __UPGRADE_H__
#define __UPGRADE_H__

#include <stdint.h>

void upgrade_start(void);
void upgrade_write_fw_block(uint32_t addr_offset, uint8_t *fw_block);
void upgrade_end(void);

#endif
