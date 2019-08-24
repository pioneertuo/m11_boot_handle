#include "uart1_parse.h"
#include "includes.h"

static parse_type uart1_parse;

void uart1_parse_init(void)
{
	parse_init(&uart1_parse);
}

void uart1_parse_process(void)
{
	uint8_t dat;
	uint8_t cmd;
	
    while(1)
    {
        if(uart1_fifo_fetch(&dat) == 0) {   //串口1没有接收到数据
            break;
        }
        
        if(parse_process(&uart1_parse, dat) == 1)  //串口1接收到了数据
        {
            cmd = uart1_parse.frame[3];
            
            switch(cmd)
            {	
                case BOOT_CMD_WAIT:
                    
                    break;
                
                case BOOT_CMD_START:
                    upgrade_start();
                    break;
                
                case BOOT_CMD_FW_PIT:
                    uart3_send_bytes(uart1_parse.frame, uart1_parse.frame_len);
                    break;
                
                case BOOT_CMD_END:
                    upgrade_end();
                    break;
            }
        }
    }
}

