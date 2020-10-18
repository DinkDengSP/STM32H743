/*******************************************************************
**Description: Copyright(c) 2018-2090 DengXiaojun,All rights reserved.
**Author: DengXiaoJun
**Date: 2020-10-18 16:53:29
**LastEditors: DengXiaoJun
**LastEditTime: 2020-10-18 17:05:26
**FilePath: \ProjectFilesd:\DinkGitHub\STM32H743\BoardArmfly\uCOSIII_App\Code\Driver\DriverBoard\BoardIntMasterDMA.c
**ModifyRecord1:    
******************************************************************/
#include "BoardW25Q256.h"

//MDMA中断处理函数
void MDMA_IRQHandler(void)
{
    //W25Q256中断处理
    if(qspiW25q256Handle.hmdma != NULL)
    {
        HAL_MDMA_IRQHandler(qspiW25q256Handle.hmdma);
    }
	
}

