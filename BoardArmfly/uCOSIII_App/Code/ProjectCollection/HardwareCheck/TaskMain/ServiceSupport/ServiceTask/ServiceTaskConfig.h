/*******************************************************************
 *Description: Copyright(c) 2018-2090 DengXiaojun,All rights reserved.
 *Author: DengXiaoJun
 *Date: 2020-10-13 22:34:41
 *LastEditors: DengXiaoJun
 *LastEditTime: 2020-10-13 22:43:55
 *FilePath: \ProjectFilesd:\DinkGitHub\STM32H743\BoardArmfly\uCOSIII_App\Code\ProjectCollection\HardwareCheck\TaskMain\ServiceSupport\ServiceTask\ServiceTaskConfig.h
 *ModifyRecord1:    
******************************************************************/
#ifndef __SERVICE_TASK_CONFIG_H_
#define __SERVICE_TASK_CONFIG_H_
#include "BoardInc.h"

/*******************************************************心跳任务********************************************************/
//任务定义
#define NAME_SERVICE_TASK_HEART                                  "Heart"
//任务优先级
#define PRIO_SERVICE_TASK_HEART                                  0
//任务堆栈大小
#define STK_SIZE_SERVICE_TASK_HEART                              8 * 32
//任务堆栈
extern CPU_STK stackBufferServiceTaskHeart[STK_SIZE_SERVICE_TASK_HEART];
//任务控制块
extern OS_TCB tcbServiceTaskHeart;
//任务函数
void ServiceTaskFuncHeart(void *p_arg);


#endif



