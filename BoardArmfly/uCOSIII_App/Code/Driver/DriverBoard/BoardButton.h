/*******************************************************************
 *Description: Copyright(c) 2018-2090 DengXiaojun,All rights reserved.
 *Author: DengXiaoJun
 *Date: 2020-10-19 00:03:45
 *LastEditors: DengXiaoJun
 *LastEditTime: 2020-10-19 00:05:20
 *FilePath: \ProjectFilesd:\DinkGitHub\STM32H743\BoardArmfly\uCOSIII_App\Code\Driver\DriverBoard\BoardButton.h
 *ModifyRecord1:    
******************************************************************/
#ifndef __BOARD_BUTTON_H_
#define __BOARD_BUTTON_H_
#include "MCU_Inc.h"

//独立按键序号
typedef enum BUTTON_NAME
{
    BUTTON_K1 = 0,
    BUTTON_K2 = 1,
    BUTTON_K3 = 2,
}BUTTON_NAME;


//独立按键初始化
void BoardButtonScanInit(BUTTON_NAME buttonName);

//独立按键中断初始化
void BoardButtonIntInit(BUTTON_NAME buttonName,NVIC_INT_PRE_PRI preePri,NVIC_INT_SUB_PRI subPri,MCU_Exti_CallBackFuncPtr callBackFuncPtr);

//获取独立按键当前状态
SENSOR_STATE BoardButtonRead(BUTTON_NAME buttonName);


#endif
