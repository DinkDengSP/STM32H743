/*******************************************************************
 *Description: Copyright(c) 2018-2090 DengXiaojun,All rights reserved.
 *Author: DengXiaoJun
 *Date: 2020-10-13 22:29:55
 *LastEditors: DengXiaoJun
 *LastEditTime: 2020-10-16 23:47:14
 *FilePath: \ProjectFilesd:\DinkGitHub\STM32H743\BoardArmfly\uCOSIII_App\Code\Driver\DriverBoard\BoardExtPort.h
 *ModifyRecord1:    
******************************************************************/
#ifndef __BOARD_EXT_PORT_H_
#define __BOARD_EXT_PORT_H_
#include "MCU_Inc.h"
#include "BoardExtPortConfig.h"

//扩展IO初始化
void BoardExtPort_Init(void);

//扩展IO设置指定IO口
void BoardExtPort_SetPin(BOARD_EXT_PORT_INDEX pin, BitAction value);

//扩展IO读取指定IO口状态
BitAction BoardExtPort_GetPin(BOARD_EXT_PORT_INDEX pin);

//扩展IO翻转IO口状态
void BoardExtPort_TooglePin(BOARD_EXT_PORT_INDEX pin);

#endif




