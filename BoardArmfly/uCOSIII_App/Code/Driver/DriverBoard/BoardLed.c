/*******************************************************************
**Description: Copyright(c) 2018-2090 DengXiaojun,All rights reserved.
**Author: DengXiaoJun
**Date: 2020-10-13 22:30:15
**LastEditors: DengXiaoJun
**LastEditTime: 2020-10-15 23:59:11
**FilePath: \ProjectFilesd:\DinkGitHub\STM32H743\BoardArmfly\uCOSIII_App\Code\Driver\DriverBoard\BoardLed.c
**ModifyRecord1:    
******************************************************************/
#include "BoardLed.h"
#include "BoardExtPort.h"

//板上LED初始化
void BoardLedInit(uint32_t ledPin,BOARD_LED_STATE initState)
{
    BoardExtPort_SetPin(ledPin,(uint8_t)initState);
}

//设置指定LED状态
void BoardLedSet(uint32_t ledPin,BOARD_LED_STATE setState)
{
    BoardExtPort_SetPin(ledPin,(uint8_t)setState);
}

//翻转LED状态
void BoardLedToogle(uint32_t ledPin)
{
    BoardExtPort_TooglePin(ledPin);
}

