#include "uart1_tx.h"
#include "includes.h"

#define UART1_TX_TAB_SIZE			MAX_TRANSFER_SIZE
static uint8_t uart1_tx_tab[UART1_TX_TAB_SIZE];

void uart1_send_boot_wait(void)
{
	uart1_tx_tab[0] = FRAME_HEAD1;
	uart1_tx_tab[1] = FRAME_HEAD2;
	uart1_tx_tab[2] = 0x02;
	
	uart1_tx_tab[3] = BOOT_CMD_WAIT;
	uart1_tx_tab[4] = 0x00;
	
	uart1_tx_tab[5] = calc_sum(uart1_tx_tab, 5);
	
	uart1_send_bytes(uart1_tx_tab, 6);
}



