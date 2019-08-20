#include "uart3_parse.h"
#include "includes.h"

static void uart3_rx_boot_info(uint8_t *arg);
static void uart3_rx_boot_fw_handle(uint8_t *arg);

//static parse_type uart3_parse;
parse_type uart3_parse;

void uart3_parse_init(void)
{
	parse_init(&uart3_parse);
}

void uart3_parse_process(void)
{
	uint8_t dat;
	uint8_t cmd;
	uint8_t *arg;
    
    while(1)
    {
        if(uart3_fifo_fetch(&dat) == 0)
        {
            break;
        }
        
        if(parse_process(&uart3_parse, dat) == 1)
        {
            cmd = uart3_parse.frame[3];
            arg = &uart3_parse.frame[5];
            
            switch(cmd)
            {
                case CMD_01_CONNECT:
                    uart3_send_connect_ack();
                    break;
                
                case BOOT_CMD_START:
                    uart1_send_bytes(uart3_parse.frame, uart3_parse.frame_len);
                    break;
                
                case BOOT_CMD_INFO:
                    uart3_rx_boot_info(arg);
                    break;
                
                case BOOT_CMD_FW_HANDLE:
                    uart3_rx_boot_fw_handle(arg);
                    break;
                
                case BOOT_CMD_FW_PIT:
                    uart1_send_bytes(uart3_parse.frame, uart3_parse.frame_len);
                    break;
                
                case BOOT_CMD_END:
                    uart1_send_bytes(uart3_parse.frame, uart3_parse.frame_len);
                    break;
            }
        }
    }
}

static void uart3_rx_boot_info(uint8_t *arg)
{
	// 0  1  2  3  4  5  6  7
	//01 01 XX 02 03 XX XX XX
	
	uint8_t product;
	
	product = arg[2];
	
	if(product == PRODUCT_M11_SELECT)
	{
		
	}
	
	fw_version.first  = arg[5];
	fw_version.second = arg[6];
	fw_version.third  = arg[7];
	
	uart3_send_boot_info_ack();
}

static void uart3_rx_boot_fw_handle(uint8_t *arg)
{
	// 0  1  2  3  4  5  6  7  8  ...  135
	//01 04 XX XX XX XX 02 80 XX  ...   XX
	
	uint32_t addr_offset;
	uint8_t *fw_block;
	
	addr_offset = arg[5]<<24|arg[4]<<16|arg[3]<<8|arg[2];
	fw_block = &arg[8];
	
	upgrade_write_fw_block(addr_offset, fw_block);
	
	uart3_send_boot_fw_handle_ack(addr_offset);
}




