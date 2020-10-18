/*******************************************************************
 *Description: Copyright(c) 2018-2090 DengXiaojun,All rights reserved.
 *Author: DengXiaoJun
 *Date: 2020-10-12 23:18:14
 *LastEditors: DengXiaoJun
 *LastEditTime: 2020-10-18 21:21:05
 *FilePath: \ProjectFilesd:\DinkGitHub\STM32H743\BoardArmfly\uCOSIII_App\Code\ProjectCollection\HardwareCheck\DriverConfig\UserConfig\UserMemManageConfig.h
 *ModifyRecord1:    
******************************************************************/
#ifndef __MEM_MANAGE_CONFIG_H_
#define __MEM_MANAGE_CONFIG_H_
#include "stm32h7xx_hal.h"

//DTCM 最大容量128KB
#define BLOCK_SIZE_DTCM			        32//内存块大小默认为32字节
#define MAX_SIZE_DTCM			        60*1024//最大管理内存
#define ALLOC_TABLE_SIZE_DTCM	        (MAX_SIZE_DTCM/BLOCK_SIZE_DTCM) //内存表大小

//D1_AXI_SRAM 最大容量512KB
#define BLOCK_SIZE_AXI_SRAM			    32//内存块大小默认为32字节
#define MAX_SIZE_AXI_SRAM			    480*1024//最大管理内存
#define ALLOC_TABLE_SIZE_AXI_SRAM	    (MAX_SIZE_AXI_SRAM/BLOCK_SIZE_AXI_SRAM) //内存表大小

//D2_SRAM1 最大容量128KB
#define BLOCK_SIZE_D2_SRAM1			    32//内存块大小默认为32字节
#define MAX_SIZE_D2_SRAM1			    110*1024//最大管理内存
#define ALLOC_TABLE_SIZE_D2_SRAM1	    (MAX_SIZE_D2_SRAM1/BLOCK_SIZE_D2_SRAM1) //内存表大小

//D2_SRAM2 最大容量128KB
#define BLOCK_SIZE_D2_SRAM2			    32//内存块大小默认为32字节
#define MAX_SIZE_D2_SRAM2			    110*1024//最大管理内存
#define ALLOC_TABLE_SIZE_D2_SRAM2	    (MAX_SIZE_D2_SRAM2/BLOCK_SIZE_D2_SRAM2) //内存表大小

//D3_SRAM4 最大容量64KB
#define BLOCK_SIZE_D3_SRAM4			    32//内存块大小默认为32字节
#define MAX_SIZE_D3_SRAM4			    55*1024//最大管理内存
#define ALLOC_TABLE_SIZE_D3_SRAM4	    (MAX_SIZE_D3_SRAM4/BLOCK_SIZE_D3_SRAM4) //内存表大小

//MEN_SDRAM IS42S32800G 32MB
//使用Bget管理
#define MAX_SIZE_SDRAM			        32*1024*1024//最大管理内存



#endif
