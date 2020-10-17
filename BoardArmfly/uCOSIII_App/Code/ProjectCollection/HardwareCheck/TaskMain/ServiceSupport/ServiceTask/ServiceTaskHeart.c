/*******************************************************************
**Description: Copyright(c) 2018-2090 DengXiaojun,All rights reserved.
**Author: DengXiaoJun
**Date: 2020-10-13 22:43:17
**LastEditors: DengXiaoJun
**LastEditTime: 2020-10-17 23:28:25
**FilePath: \ProjectFilesd:\DinkGitHub\STM32H743\BoardArmfly\uCOSIII_App\Code\ProjectCollection\HardwareCheck\TaskMain\ServiceSupport\ServiceTask\ServiceTaskHeart.c
**ModifyRecord1:    
******************************************************************/
#include "ServiceTaskConfig.h"


//任务控制块,8字节对齐
#pragma pack(8)
//任务堆栈
CPU_STK stackBufferServiceTaskHeart[STK_SIZE_SERVICE_TASK_HEART]@".dtcm_ram";
#pragma pack()

//任务控制块
OS_TCB tcbServiceTaskHeart@".dtcm_ram";

//任务函数
void ServiceTaskFuncHeart(void *p_arg)
{
    p_arg = p_arg;
    while(1)
    {
        BoardLedToogle(BOARD_LED3_W25Q128);
        CoreDelayMs(250);
    }
}
