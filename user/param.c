#include "param.h"
#include "includes.h"

uint8_t param_tab_check(uint8_t *param_tab)
{
	uint8_t arg_len;
	uint8_t sum;
	
	if(param_tab[0]!=FRAME_HEAD1)
	{
		return 0;
	}
	if(param_tab[1]!=FRAME_HEAD2)
	{
		return 0;
	}
	
	arg_len = param_tab[2];
	sum = param_tab[arg_len+3];
	
	if(calc_sum(param_tab, arg_len+3) != sum)
	{
		return 0;
	}
	
	return 1;
}

uint8_t param_tab_find(uint8_t *param_tab, uint8_t cmd, uint8_t **arg, uint8_t *arg_len)
{
	uint8_t i = 0;
	uint8_t *content;
	uint8_t content_len;
	
	if(param_tab_check(param_tab) == 0){
		return 0;
	}
	
	content_len = param_tab[2];
	content = &param_tab[3];
	
	while(i < content_len)
	{
		if(content[i] == cmd)
		{
			*arg_len = content[i+1];
			*arg = &content[i+2];
			
			return 1;
		}
		
		i += (content[i+1]+2);
	}
	
	return 0;
}
