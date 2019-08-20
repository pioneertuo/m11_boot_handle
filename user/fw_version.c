#include "fw_version.h"
#include "includes.h"

static void fw_version_reset(void);

static uint8_t param_tab[FACTORY_PARAM_TAB_SIZE];

fw_version_type fw_version;

void fw_version_init(void)
{
	uint8_t ret;
	uint8_t *arg;
	uint8_t arg_len;
	
	//在最后2K处读128字节
	flash_read_bytes(FACTORY_PARAM_BASE_ADDR, param_tab, FACTORY_PARAM_TAB_SIZE);
	
	//查找版本号位置
	ret = param_tab_find(param_tab, CMD_18_FW_VERSION, &arg, &arg_len);
	
	if(ret==1 && arg_len==3)
	{
		fw_version.first = arg[0];
		fw_version.second = arg[1];
		fw_version.third = arg[2];
	}
	else
	{
		//未找到版本号，说明是第一次启动，此时把版本号设为0.0.0并写到Flash
		fw_version.first = 0;
		fw_version.second = 0;
		fw_version.third = 0;
		
		fw_version_reset();
	}
}

static void fw_version_reset(void)
{
	uint8_t i;
	
	param_tab[0] = FRAME_HEAD1;
	param_tab[1] = FRAME_HEAD2;
	param_tab[2] = 0x05;
	param_tab[3] = CMD_18_FW_VERSION;
	param_tab[4] = 0x03;
	param_tab[5] = 0x00;
	param_tab[6] = 0x00;
	param_tab[7] = 0x00;
	param_tab[8] = calc_sum(param_tab, 8);
	
	for(i=9; i<FACTORY_PARAM_TAB_SIZE; i++){
		param_tab[i] = 0xFF;
	}
	
	flash_write_bytes(FACTORY_PARAM_BASE_ADDR, param_tab, FACTORY_PARAM_TAB_SIZE);
}

uint8_t fw_version_modify(void)
{
	uint8_t ret;
	uint8_t *arg;
	uint8_t arg_len;
	uint8_t param_len;
	
	//在最后2K处读128字节
	flash_read_bytes(FACTORY_PARAM_BASE_ADDR, param_tab, FACTORY_PARAM_TAB_SIZE);
	
	//查找版本号位置
	ret = param_tab_find(param_tab, CMD_18_FW_VERSION, &arg, &arg_len);
	
	if(ret==1 && arg_len==3)
	{
		//修改版本号
		arg[0] = fw_version.first;
		arg[1] = fw_version.second;
		arg[2] = fw_version.third;
		
		//修改和校验
		param_len = param_tab[2]+4;
		param_tab[param_len-1] = calc_sum(param_tab, param_len-1);
		
		//写回Flash
		flash_write_bytes(FACTORY_PARAM_BASE_ADDR, param_tab, FACTORY_PARAM_TAB_SIZE);
		
		return 1;
	}
	
	return 0;
}



