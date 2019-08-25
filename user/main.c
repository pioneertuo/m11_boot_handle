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
	
	launch_for_boot();   	//按住中键,再按下电源键，系统进入boot模式
	
	while(1)				//若执行的是bootloder，下面则一直在执行
	{
		led_process();
		
		bat_shut_down_process();   //关机处理过程
		
		uart1_parse_process();	   //串口1解析过程
		
		uart3_parse_process();	   //串口3解析过程
	}
}

static void launch_for_app(void)
{	
	//延时100ms，让pit先跳转
	delay_ms(100);
	
	sys_periph_deinit();							//将bootloder中用到的外设恢复至缺省值
	sys_jump_to_app(M11_HANDLE_APP_ADDR_OFFSET);	//从boot程序块跳转至APP代码块执行
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


