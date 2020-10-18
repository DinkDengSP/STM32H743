/*******************************************************************
 *Description: Copyright(c) 2018-2090 DengXiaojun,All rights reserved.
 *Author: DengXiaoJun
 *Date: 2020-10-18 23:38:54
 *LastEditors: DengXiaoJun
 *LastEditTime: 2020-10-18 23:56:28
 *FilePath: \ProjectFilesd:\DinkGitHub\STM32H743\BoardArmfly\uCOSIII_App\Code\Driver\DriverBoard\BoardJoysTick.h
 *ModifyRecord1:    
******************************************************************/
#ifndef __BOARD_JOYS_TICK_H_
#define __BOARD_JOYS_TICK_H_
#include "MCU_Inc.h"

//多向按键序号
typedef enum JOYS_TICK_NAME
{
    JOYS_TICK_ENTER = 0,
    JOYS_TICK_LEFT  = 1,
    JOYS_TICK_RIGHT = 2,
    JOYS_TICK_UP    = 3,
    JOYS_TICK_DOWN  = 4,
}JOYS_TICK_NAME;


//多向按键初始化
void BoardJoysTickScanInit(JOYS_TICK_NAME tickName);

//多向按键中断初始化
void BoardJoysTickIntInit(JOYS_TICK_NAME tickName,NVIC_INT_PRE_PRI preePri,NVIC_INT_SUB_PRI subPri,MCU_Exti_CallBackFuncPtr callBackFuncPtr);

//获取多向按键当前状态
SENSOR_STATE BoardJoysTickRead(JOYS_TICK_NAME tickName);


#endif
