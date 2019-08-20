#ifndef __FLASH_H__
#define __FLASH_H__

#include <stdint.h>

//page 0~7  (8 pages / 16K bytes)   - bootloader code
//page 8~61 (54 pages / 108K bytes) - application code
//page 62   (1 page / 2K bytes)     - user parameter
//page 63   (1 page / 2K bytes)     - factory parameter

#define FLASH_PAGE_SIZE			2048
#define FLASH_PAGE_NUM			64

void flash_read_bytes(uint32_t addr, uint8_t *u8_dat, uint32_t u8_len);
void flash_write_bytes(uint32_t addr, uint8_t *u8_dat, uint32_t u8_len);

#endif
