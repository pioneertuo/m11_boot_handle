# -*- coding: utf-8 -*-

import os

config = {
    'macro_location' : '../user/sys.h',
    'macro' : 'PRODUCT_M11_SELECT',
    'origin_bin_file' : 'm11_boot_handle.bin',
    'option_target_list' : [
            {
                'board' : 'PRODUCT_M11',
                'target_file' : 'm11_boot_handle.bin'
            },
            {
                'board' : 'PRODUCT_M11_CD',
                'target_file' : 'm11_cd_boot_handle.bin'
            }
        ]
    }

def get_board():
    board = ''
    f = open(config['macro_location'], 'r')
    while True:
        line = f.readline()
        if line == '':
            break
        line_con = line.split();
        if len(line_con) >= 3 and line_con[0] == '#define' and line_con[1] == config['macro']:
            board = line_con[2]
            break
    f.close()
    return board


def rename_bin():
    
    board = get_board()
    
    if board == '':
        print('未找到', config['macro'], '定义!')
        return
    
    dirs = os.listdir('.')

    if not config['origin_bin_file'] in dirs:
        print('未找到原始bin文件')
        return
    
    for option_tg in config['option_target_list']:
        if board == option_tg['board']:
            if option_tg['target_file'] in dirs:
                os.remove(option_tg['target_file'])
            os.rename(config['origin_bin_file'], option_tg['target_file'])
            print('成功生成', option_tg['target_file'])
            return

if __name__ == '__main__':
    rename_bin()
