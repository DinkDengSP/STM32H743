/*******************************************************************
 *Description: ,: Copyright(c) 2018-2090 DengXiaojun,All rights reserved.
 *Author: ,: DengXiaoJun
 *Date: ,: 2020-10-17 00:35:37
 *LastEditors: ,: DengXiaoJun
 *LastEditTime: ,: 2020-10-20 21:23:15
 *FilePath: ,: \ProjectFilesd:\DinkGitHub\STM32H743\BoardArmfly\uCOSIII_App\Code\Driver\DriverBoard\BoardBMP180.h
 *ModifyRecord1: ,:    
******************************************************************/
#ifndef __BOARD_BMP180_H_
#define __BOARD_BMP180_H_
#include "MCU_Inc.h"

//IIC模块地址
#define BOARD_BMP180_ADDR_BASE                  0X77
#define BOARD_BMP180_ADDR_WRITE				    (BOARD_BMP180_ADDR_BASE<<1)
#define BOARD_BMP180_ADDR_READ                  (BOARD_BMP180_ADDR_WRITE+1)


D_ERR BoardBmp180Init(uint8_t ossSet);

//读取并计算温度和压力传感器值
D_ERR BoardBmp180_ReadTempPress(float* temp,uint32_t* press);

#endif






