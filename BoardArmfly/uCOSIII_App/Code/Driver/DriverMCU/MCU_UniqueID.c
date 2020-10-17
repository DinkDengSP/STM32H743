/*******************************************************************
**Description: Copyright(c) 2018-2090 DengXiaojun,All rights reserved.
**Author: DengXiaoJun
**Date: 2020-10-17 00:25:11
**LastEditors: DengXiaoJun
**LastEditTime: 2020-10-17 22:27:17
**FilePath: \ProjectFilesd:\DinkGitHub\STM32H743\BoardArmfly\uCOSIII_App\Code\Driver\DriverMCU\MCU_UniqueID.c
**ModifyRecord1:    
******************************************************************/
#include "MCU_UniqueID.h"

//读取芯片的电子签名和Flash尺寸信息
void MCU_UniqueID_Read(MCU_UNIQUE_ID* idPtr)
{
	//设备电子签名
    idPtr->idSn0 = *(__IO uint32_t*)(0x1FF1E800);
    idPtr->idSn1 = *(__IO uint32_t*)(0x1FF1E800 + 4);
    idPtr->idSn2 = *(__IO uint32_t*)(0x1FF1E800 + 8);
    //Flash大小
    idPtr->flashSizeID = *(__IO uint32_t*)(0x1FF1E880);
}
