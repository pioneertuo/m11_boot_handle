#include "uart3_tx.h"
#include "includes.h"

#define UART3_TX_TAB_SIZE			MAX_TRANSFER_SIZE
static uint8_t uart3_tx_tab[UART3_TX_TAB_SIZE];

void uart3_send_connect_ack(void)
{	
	uart3_tx_tab[0]  = FRAME_HEAD1;
	uart3_tx_tab[1]  = FRAME_HEAD2;
	uart3_tx_tab[2]  = 0x0D;//13
	
	uart3_tx_tab[3]  = CMD_01_CONNECT;
	uart3_tx_tab[4]  = 0x06;
	uart3_tx_tab[5]  = CONN_02_PRODUCT;
	uart3_tx_tab[6]  = 0x01;
//	uart3_tx_tab[7]  = PRODUCT_M11_SELECT;
	uart3_tx_tab[7]  = PRODUCT_M11;
	uart3_tx_tab[8]  = CONN_03_STATE;
	uart3_tx_tab[9]  = 0x01;
	uart3_tx_tab[10] = STATE_BOOT;
	
	uart3_tx_tab[11] = CMD_18_FW_VERSION;
	uart3_tx_tab[12] = 0x03;
	uart3_tx_tab[13] = fw_version.first;
	uart3_tx_tab[14] = fw_version.second;
	uart3_tx_tab[15] = fw_version.third;
	
	uart3_tx_tab[16] = calc_sum(uart3_tx_tab, 16);
	
	uart3_send_bytes(uart3_tx_tab, 17);
}

void uart3_send_boot_start_ack(void)
{
	uart3_tx_tab[0] = FRAME_HEAD1;
	uart3_tx_tab[1] = FRAME_HEAD2;
	uart3_tx_tab[2] = 0x03;
	
	uart3_tx_tab[3] = BOOT_CMD_START;
	uart3_tx_tab[4] = 0x01;
	uart3_tx_tab[5] = 0x00;
	
	uart3_tx_tab[6] = calc_sum(uart3_tx_tab, 6);
	
	uart3_send_bytes(uart3_tx_tab, 7);
}

void uart3_send_boot_info_ack(void)
{
	uart3_tx_tab[0] = FRAME_HEAD1;
	uart3_tx_tab[1] = FRAME_HEAD2;
	uart3_tx_tab[2] = 0x02;
	
	uart3_tx_tab[3] = BOOT_CMD_INFO;
	uart3_tx_tab[4] = 0x00;
	
	uart3_tx_tab[5] = calc_sum(uart3_tx_tab, 5);
	
	uart3_send_bytes(uart3_tx_tab, 6);
}

void uart3_send_boot_fw_handle_ack(uint32_t addr)
{
	uart3_tx_tab[0]  = FRAME_HEAD1;
	uart3_tx_tab[1]  = FRAME_HEAD2;
	uart3_tx_tab[2]  = 0x08;
	
	uart3_tx_tab[3]  = BOOT_CMD_FW_HANDLE;
	uart3_tx_tab[4]  = 0x06;
	uart3_tx_tab[5]  = BOOT_ACK_HANDLE_ADDR;
	uart3_tx_tab[6]  = 0x04;
	uart3_tx_tab[7]  = BYTE0(addr);
	uart3_tx_tab[8]  = BYTE1(addr);
	uart3_tx_tab[9]  = BYTE2(addr);
	uart3_tx_tab[10] = BYTE3(addr);
	
	uart3_tx_tab[11] = calc_sum(uart3_tx_tab, 11);
	
	uart3_send_bytes(uart3_tx_tab, 12);
}

void uart3_send_boot_end_ack(void)
{
	uart3_tx_tab[0] = FRAME_HEAD1;
	uart3_tx_tab[1] = FRAME_HEAD2;
	uart3_tx_tab[2] = 0x03;
	
	uart3_tx_tab[3] = BOOT_CMD_END;
	uart3_tx_tab[4] = 0x01;
	uart3_tx_tab[5] = 0x00;
	
	uart3_tx_tab[6] = calc_sum(uart3_tx_tab, 6);
	
	uart3_send_bytes(uart3_tx_tab, 7);
}
