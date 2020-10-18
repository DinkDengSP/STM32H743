/*******************************************************************
 *Description: Copyright(c) 2018-2090 DengXiaojun,All rights reserved.
 *Author: DengXiaoJun
 *Date: 2020-10-18 20:05:11
 *LastEditors: DengXiaoJun
 *LastEditTime: 2020-10-18 20:16:55
 *FilePath: \ProjectFilesd:\DinkGitHub\STM32H743\BoardArmfly\uCOSIII_App\Code\Driver\DriverBoard\BoardSDRAM.h
 *ModifyRecord1:    
******************************************************************/
#ifndef __BOARD_SDRAM_H_
#define __BOARD_SDRAM_H_
#include "MCU_Inc.h"

//SDRAM基础地址
#define BOARD_SDRAM_BASE_ADDR    ((uint32_t)0xC0000000)
//32M容量
#define BOARD_SDRAM_CAPACITY     (32 * 1024 * 1024)

//sdram初始化
void BoardSDRAM_Init(void);

//读取指定区域指定长度内存
D_ERR BoardSDRAM_ReadBuffer(uint32_t baseAddr,uint8_t* bufferPtr,uint32_t length);

//写入指定区域指定长度数据
D_ERR BoardSDRAM_WriteBuffer(uint32_t baseAddr,uint8_t* bufferPtr,uint32_t length);

//检查SDRAM数据完整性
D_ERR BoardSDRAM_SelfCheck(void);


#endif

