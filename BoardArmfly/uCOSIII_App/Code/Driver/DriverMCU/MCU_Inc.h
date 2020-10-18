/*******************************************************************
 *Description: Copyright(c) 2018-2090 DengXiaojun,All rights reserved.
 *Author: DengXiaoJun
 *Date: 2020-10-12 23:21:25
 *LastEditors: DengXiaoJun
 *LastEditTime: 2020-10-18 23:59:46
 *FilePath: \ProjectFilesd:\DinkGitHub\STM32H743\BoardArmfly\uCOSIII_App\Code\Driver\DriverMCU\MCU_Inc.h
 *ModifyRecord1:    
******************************************************************/
#ifndef __MCU_INC_H_
#define __MCU_INC_H_

#include "MCU_Port.h"
#include "MCU_MPU.h"
#include "MCU_UniqueID.h"
#include "MCU_Random.h"
#include "MCU_WDG.h"
#include "MCU_Uart.h"
#include "MCU_SPI.h"


//变参宏定义,RS2,调试printf
#define SystemPrintf(format,args...)            MCU_Uart1Printf(format,##args)	

//#define SystemPrintf(format,args...)          SEGGER_RTT_printf(0,format,##args)

#endif



