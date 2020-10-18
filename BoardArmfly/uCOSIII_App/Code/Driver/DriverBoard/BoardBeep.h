/*******************************************************************
 *Description: Copyright(c) 2018-2090 DengXiaojun,All rights reserved.
 *Author: DengXiaoJun
 *Date: 2020-10-18 16:21:22
 *LastEditors: DengXiaoJun
 *LastEditTime: 2020-10-18 16:23:40
 *FilePath: \ProjectFilesd:\DinkGitHub\STM32H743\BoardArmfly\uCOSIII_App\Code\Driver\DriverBoard\BoardBeep.h
 *ModifyRecord1:    
******************************************************************/
#ifndef __BOARD_BEEP_H_
#define __BOARD_BEEP_H_
#include "MCU_Inc.h"

//BEEP状态
typedef enum BEEP_STATE
{
    BEEP_OFF,
    BEEP_ON,
}BEEP_STATE;

//蜂鸣器初始化
void BoardBeepInit(BEEP_STATE initState);

//设置蜂鸣器状态
void BoardBeepSetState(BEEP_STATE state);

#endif
