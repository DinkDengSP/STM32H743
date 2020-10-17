/*******************************************************************
 *Description: Copyright(c) 2018-2090 DengXiaojun,All rights reserved.
 *Author: DengXiaoJun
 *Date: 2020-10-17 00:25:20
 *LastEditors: DengXiaoJun
 *LastEditTime: 2020-10-17 22:24:49
 *FilePath: \ProjectFilesd:\DinkGitHub\STM32H743\BoardArmfly\uCOSIII_App\Code\Driver\DriverMCU\MCU_UniqueID.h
 *ModifyRecord1:    
******************************************************************/
#ifndef __MCU_UNIQUE_ID_H_
#define __MCU_UNIQUE_ID_H_
#include "MCU_Common.h"

//芯片电子签名
typedef struct MCU_UNIQUE_ID
{
    uint32_t idSn0;
    uint32_t idSn1;
    uint32_t idSn2;
    uint32_t flashSizeID;
}MCU_UNIQUE_ID;

//读取芯片的电子签名和Flash尺寸信息
void MCU_UniqueID_Read(MCU_UNIQUE_ID* idPtr);

#endif



