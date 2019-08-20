#ifndef __PARAM_H__
#define __PARAM_H__

#include <stdint.h>

uint8_t param_tab_check(uint8_t *param_tab);
uint8_t param_tab_find(uint8_t *param_tab, uint8_t cmd, uint8_t **arg, uint8_t *arg_len);


#endif
