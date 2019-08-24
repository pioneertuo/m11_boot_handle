#include "includes.h"

static void launch_for_app(void);
static void launch_for_boot(void);

int main(void)
{
    port_init();
	delay_init();
	btn_init();
	
	//如果中键未按下则跳转到应用程序
	if(btn_center_active() == 0)
	{
		launch_for_app();
	}
	//按住中键并且按下电源键，则执行boot程序				
	launch_for_boot();  
	
	while(1)
	{
		led_process();			  //LED闪烁方式处理
		
		bat_shut_down_process();  //boot模式下开关机处理
		
		uart1_parse_process();	  //串口1解析处理(内部通信)
		
		uart3_parse_process();    //串口3解析处理(外部通信)
	}
}

static void launch_for_app(void)
{	
	//延时100ms，让pit先跳转
	delay_ms(100);
	
	sys_periph_deinit();  						  //将bootloderz中用到的外设恢复为缺省值
	sys_jump_to_app(M11_HANDLE_APP_ADDR_OFFSET);  //跳转到APP程序段
}

static void launch_for_boot(void)
{
	sys_init();
	led_init();
	bat_init();
	timebase_init();
	uart1_init();
	uart3_init();
	uart1_parse_init();
	uart3_parse_init();
	fw_version_init();
	
	LED1_ON;
	LED2_ON;
	LED3_ON;
	
	delay_ms(10);
	
	uart1_send_boot_wait(); 
	
	POWER_EN_ON;
	
	//等待power键释放
	while(btn_power_active() == 1);
}


