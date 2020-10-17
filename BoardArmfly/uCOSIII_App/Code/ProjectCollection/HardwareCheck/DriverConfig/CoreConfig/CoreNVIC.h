/*******************************************************************
 *Description: Copyright(c) 2018-2090 DengXiaojun,All rights reserved.
 *Author: DengXiaoJun
 *Date: 2020-10-12 23:19:20
 *LastEditors: DengXiaoJun
 *LastEditTime: 2020-10-17 23:36:36
 *FilePath: \ProjectFilesd:\DinkGitHub\STM32H743\BoardArmfly\uCOSIII_App\Code\ProjectCollection\HardwareCheck\DriverConfig\CoreConfig\CoreNVIC.h
 *ModifyRecord1:    
******************************************************************/
#ifndef __CORE_NVIC_H_
#define __CORE_NVIC_H_
#include "CoreUtil.h"

//中断优先级配置,优先级数值越低,优先级越高
//操作系统关注的中断是抢占优先级2以及2以上的中断,不需要操作系统关注的中断是抢占优先级1以及1一下的中断


/*******************************不调用操作系统内核函数的中断**************************************/
//窗口看门狗 最高优先级
#define MCU_WDG_WINDOW_PREE_PRI             NVIC_INT_PRE_PRI_0
#define MCU_WDG_WINDOW_SUB_PRI              NVIC_INT_SUB_PRI_0



#endif



