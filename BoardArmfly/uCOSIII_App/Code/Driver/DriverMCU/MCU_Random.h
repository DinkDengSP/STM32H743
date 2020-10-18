/*******************************************************************
 *Description: Copyright(c) 2018-2090 DengXiaojun,All rights reserved.
 *Author: DengXiaoJun
 *Date: 2020-10-17 00:28:18
 *LastEditors: DengXiaoJun
 *LastEditTime: 2020-10-18 14:57:55
 *FilePath: \ProjectFilesd:\DinkGitHub\STM32H743\BoardArmfly\uCOSIII_App\Code\Driver\DriverMCU\MCU_Random.h
 *ModifyRecord1:    
******************************************************************/
#ifndef __MCU_RANDOM_H_
#define __MCU_RANDOM_H_
#include "MCU_Common.h"


//随机数初始化
void MCU_RandomInit(void);

//得到随机数
uint32_t MCU_RandomGetNext(void);

//生成指定范围的随机数
int MCU_RandomGetNextRange(int min, int max);

//正确计算随机数的方法
int MCU_RandomGetNextRangeReal(int min, int max);


#endif




