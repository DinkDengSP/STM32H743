/*******************************************************************
 *Description: Copyright(c) 2018-2090 DengXiaojun,All rights reserved.
 *Author: DengXiaoJun
 *Date: 2020-10-13 22:30:21
 *LastEditors: DengXiaoJun
 *LastEditTime: 2020-10-16 00:03:41
 *FilePath: \ProjectFilesd:\DinkGitHub\STM32H743\BoardArmfly\uCOSIII_App\Code\Driver\DriverBoard\BoardLed.h
 *ModifyRecord1:    
******************************************************************/
#ifndef __BOARD_LED_H_
#define __BOARD_LED_H_
#include "MCU_Inc.h"

//LED状态
typedef enum BOARD_LED_STATE
{
    BOARD_LED_ON  = 0,
    BOARD_LED_OFF = 1,
}BOARD_LED_STATE;

//定义四个LED序号
#define BOARD_LED1  BOARD_EXT_PORT_PIN_LED1
#define BOARD_LED2  BOARD_EXT_PORT_PIN_LED2
#define BOARD_LED3  BOARD_EXT_PORT_PIN_LED3
#define BOARD_LED4  BOARD_EXT_PORT_PIN_LED4

//初始化LED状态
void BoardLedInit(uint32_t ledPin,BOARD_LED_STATE initState);

//设置指定LED状态
void BoardLedSet(uint32_t ledPin,BOARD_LED_STATE setState);

//翻转LED状态
void BoardLedToogle(uint32_t ledPin);


#endif




