#ifndef __UART3_TX_H__
#define __UART3_TX_H__

#include <stdint.h>

void uart3_send_connect_ack(void);
void uart3_send_boot_start_ack(void);
void uart3_send_boot_info_ack(void);
void uart3_send_boot_fw_handle_ack(uint32_t addr);
void uart3_send_boot_end_ack(void);

#endif
