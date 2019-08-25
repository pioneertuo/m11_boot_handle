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
        if(uart3_fifo_fetch(&dat) == 0)    //串口3接收数据fifo为空则跳出此函数
        {
            break;
        }
        
        if(parse_process(&uart3_parse, dat) == 1)
        {
            cmd = uart3_parse.frame[3];
            arg = &uart3_parse.frame[5];
            
            switch(cmd)
            {
                case CMD_01_CONNECT:			//PC端发送连接命令
                    uart3_send_connect_ack();	//向PC端返回产品型号和固件版本
                    break;
                
                case BOOT_CMD_START:			
                    uart1_send_bytes(uart3_parse.frame, uart3_parse.frame_len);
                    break;
                
                case BOOT_CMD_INFO:				//PC端下发的boot信息命令
                    uart3_rx_boot_info(arg);    //可由PC端手动下发指令来设置固件版本号
                    break;
                
                case BOOT_CMD_FW_HANDLE:		 //handle板固件命令
                    uart3_rx_boot_fw_handle(arg);//接收handle板固件并写入到指定的FLASH地址中
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
	
//	if(product == PRODUCT_M11_SELECT)
	if(product == PRODUCT_M11)
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




