#include "flash.h"
#include "includes.h"

void flash_read_bytes(uint32_t addr, uint8_t *u8_dat, uint32_t u8_len)
{
	uint32_t i;
	
	for(i=0; i<u8_len; i++)
	{
		u8_dat[i] = *(__IO uint8_t *)(addr+i);
	}
}

void flash_write_bytes(uint32_t addr, uint8_t *u8_dat, uint32_t u8_len)
{
	uint32_t i;
	uint32_t page_start_addr;
	uint32_t addr_temp;
	uint32_t u16_len;
	uint16_t u16_dat;
	
	u16_len = u8_len>>1;
	
	FLASH_Unlock();
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPERR);
	
	page_start_addr = addr&0xFFFFF800;
	FLASH_ErasePage(page_start_addr);
	
	for(i=0; i<u16_len; i++)
	{
		addr_temp = addr + i*2;
		u16_dat = (uint16_t)(u8_dat[2*i+1]<<8|u8_dat[2*i]);
		
		FLASH_ProgramHalfWord(addr_temp, u16_dat);
	}
	
	FLASH_Lock();
}

