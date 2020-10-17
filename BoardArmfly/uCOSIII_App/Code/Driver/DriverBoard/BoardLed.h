/*******************************************************************
 *Description: Copyright(c) 2018-2090 DengXiaojun,All rights reserved.
 *Author: DengXiaoJun
 *Date: 2020-10-13 22:30:21
 *LastEditors: DengXiaoJun
 *LastEditTime: 2020-10-17 00:16:09
 *FilePath: \ProjectFilesd:\DinkGitHub\STM32H743\BoardArmfly\uCOSIII_App\Code\Driver\DriverBoard\BoardLed.h
 *ModifyRecord1:    
******************************************************************/
#ifndef __BOARD_LED_H_
#define __BOARD_LED_H_
#include "MCU_Inc.h"

//LED状态
typedef enum BOARD_LED_STATE
{
    BOARD_LED_ON  = Bit_RESET,
    BOARD_LED_OFF = Bit_SET,
}BOARD_LED_STATE;

//定义四个LED序号
typedef enum BOARD_LED_NAME
{
    BOARD_LED1_REMOTE   = 0,//红外传感器附近
    BOARD_LED2_NRF24L01 = 1,//NRF24L01附近
    BOARD_LED3_W25Q128  = 2,//底板W25Q128附近
    BOARD_LED4_DHT11    = 3,//DHT11插头附近
}BOARD_LED_NAME;

//初始化LED状态
void BoardLedInit(BOARD_LED_NAME ledPin,BOARD_LED_STATE initState);

//设置指定LED状态
void BoardLedSet(BOARD_LED_NAME ledPin,BOARD_LED_STATE setState);

//翻转LED状态
void BoardLedToogle(BOARD_LED_NAME ledPin);


#endif




