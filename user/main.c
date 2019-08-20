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
	
	launch_for_boot();
	
	while(1)
	{
		led_process();
		
		bat_shut_down_process();
		
		uart1_parse_process();
		
		uart3_parse_process();
	}
}

static void launch_for_app(void)
{	
	//延时100ms，让pit先跳转
	delay_ms(100);
	
	sys_periph_deinit();
	sys_jump_to_app(M11_HANDLE_APP_ADDR_OFFSET);
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


