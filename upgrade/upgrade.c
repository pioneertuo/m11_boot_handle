#include "upgrade.h"
#include "includes.h"

#define FW_BLOCK_SIZE				128

#define FLASH_APP_PAGE_START		8
#define FLASH_APP_PAGE_STOP			61

void upgrade_start(void)
{
//	uint8_t page_index;
//	uint32_t page_start_addr;
	
	FLASH_Unlock();
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPERR);
	
//	for(page_index=FLASH_APP_PAGE_START; page_index<=FLASH_APP_PAGE_STOP; page_index++)
//	{
//		page_start_addr = FLASH_BASE+page_index*FLASH_PAGE_SIZE;
//		FLASH_ErasePage(page_start_addr);
//	}
	
	uart3_send_boot_start_ack();
}

void upgrade_write_fw_block(uint32_t addr_offset, uint8_t *fw_block)
{
	uint16_t i;
	uint32_t program_addr;
	uint16_t program_u16_dat;
	
	if(addr_offset%FLASH_PAGE_SIZE == 0)
	{
		FLASH_ErasePage(FLASH_BASE+addr_offset);
	}
	
	for(i=0; i<FW_BLOCK_SIZE/2; i++)
	{
		program_addr = FLASH_BASE+addr_offset+i*2;
		program_u16_dat = (uint16_t)(fw_block[2*i+1]<<8|fw_block[2*i]);
		
		FLASH_ProgramHalfWord(program_addr, program_u16_dat);
	}
}

void upgrade_end(void)
{
	FLASH_Lock();
	
	fw_version_modify();
	
	uart3_send_boot_end_ack();
}


