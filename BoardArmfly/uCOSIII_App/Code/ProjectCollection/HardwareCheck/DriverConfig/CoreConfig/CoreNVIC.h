/*******************************************************************
 *Description: Copyright(c) 2018-2090 DengXiaojun,All rights reserved.
 *Author: DengXiaoJun
 *Date: 2020-10-12 23:19:20
 *LastEditors: DengXiaoJun
 *LastEditTime: 2020-10-18 17:35:47
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

//文件系统驱动 SDIO
#define SDIO_PREEMPT_PRIORITY               NVIC_INT_PRE_PRI_0
#define SDIO_SUB_PRIORITY                   NVIC_INT_SUB_PRI_1

//QSPI中断
#define QSPI_PREEMPT_PRIORITY               NVIC_INT_PRE_PRI_0
#define QSPI_SUB_PRIORITY                   NVIC_INT_SUB_PRI_2

//MDMA中断
#define MDMA_PREEMPT_PRIORITY               NVIC_INT_PRE_PRI_0
#define MDMA_SUB_PRIORITY                   NVIC_INT_SUB_PRI_3

/*******************************调用操作系统内核函数的中断**************************************/
//CAN2 中断优先级 INT0
#define CAN2_INT0_PREE_PRI                  NVIC_INT_PRE_PRI_2
#define CAN2_INT0_SUB_PRI                   NVIC_INT_SUB_PRI_0

//CAN2 中断优先级 INT1
#define CAN2_INT1_PREE_PRI                  NVIC_INT_PRE_PRI_2
#define CAN2_INT1_SUB_PRI                   NVIC_INT_SUB_PRI_1

//CAN1 中断优先级 INT0
#define CAN1_INT0_PREE_PRI                  NVIC_INT_PRE_PRI_2
#define CAN1_INT0_SUB_PRI                   NVIC_INT_SUB_PRI_2

//CAN1 中断优先级 INT1
#define CAN1_INT1_PREE_PRI                  NVIC_INT_PRE_PRI_2
#define CAN1_INT1_SUB_PRI                   NVIC_INT_SUB_PRI_3

//CAN时钟校准中断
#define CAN_CC_PREE_PRI                     NVIC_INT_PRE_PRI_3
#define CAN_CC_SUB_PRI                      NVIC_INT_SUB_PRI_3

//串口1中断
#define MCU_UART1_PREE_PRI                  NVIC_INT_PRE_PRI_3
#define MCU_UART1_SUB_PRI                   NVIC_INT_SUB_PRI_0

//串口2中断
#define MCU_UART2_PREE_PRI                  NVIC_INT_PRE_PRI_3
#define MCU_UART2_SUB_PRI                   NVIC_INT_SUB_PRI_1

//串口3中断
#define MCU_UART3_PREE_PRI                  NVIC_INT_PRE_PRI_3
#define MCU_UART3_SUB_PRI                   NVIC_INT_SUB_PRI_2

//串口6中断
#define MCU_UART6_PREE_PRI                  NVIC_INT_PRE_PRI_3
#define MCU_UART6_SUB_PRI                   NVIC_INT_SUB_PRI_3

//按键中断
#define BOARD_KEY_PREE_PRI                  NVIC_INT_PRE_PRI_3
#define BOARD_KEY_SUB_PRI                   NVIC_INT_SUB_PRI_3


#endif



