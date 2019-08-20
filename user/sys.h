#ifndef __SYS_H__
#define __SYS_H__

#include <stdint.h>

/********************************************
* m11 product code select
********************************************/
#define PRODUCT_M11_SELECT              PRODUCT_M11_CD //PRODUCT_M11_CD


/********************************************
* debug option
********************************************/
#define DEBUG_EN						0


/********************************************
* irq priority (pre,sub)
********************************************/
#define IRQ_PRI_RESERVED1				0,0
#define IRQ_PRI_UART3					1,0
#define IRQ_PRI_UART1					2,0


#define MAX_TRANSFER_SIZE				200


/********************************************
* flash info
********************************************/
#define FACTORY_PARAM_BASE_ADDR			0x0801F800
#define FACTORY_PARAM_TAB_SIZE			128


/********************************************
* boot cmd
********************************************/
#define BOOT_CMD_WAIT       			0x02
#define BOOT_CMD_START      			0x03
#define BOOT_CMD_INFO       			0x04
#define BOOT_CMD_FW_HANDLE  			0x05
#define BOOT_CMD_FW_PIT     			0x06
#define BOOT_CMD_END        			0xFF

#define BOOT_INFO_PRODUCT   			0x01
#define BOOT_INFO_VERSION   			0x02

#define BOOT_FW_HANDLE_ADDR  			0x01
#define BOOT_FW_HANDLE_CONTENT  		0x02
#define BOOT_ACK_HANDLE_ADDR  			0x0F

#define BOOT_FW_PIT_ADDR     			0x01
#define BOOT_FW_PIT_CONTENT  			0x02
#define BOOT_ACK_PIT_ADDR    			0x0F


typedef struct{
	uint8_t pit_connect_ok;
}sys_type;
extern sys_type sys;

void sys_init(void);

void sys_periph_deinit(void);
void sys_jump_to_app(uint32_t app_addr);

#endif
