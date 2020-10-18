/*******************************************************************
 *Description: Copyright(c) 2018-2090 DengXiaojun,All rights reserved.
 *Author: DengXiaoJun
 *Date: 2020-10-12 23:16:00
 *LastEditors: DengXiaoJun
 *LastEditTime: 2020-10-18 22:01:31
 *FilePath: \ProjectFilesd:\DinkGitHub\STM32H743\BoardArmfly\uCOSIII_App\Code\CommonFunc\SystemUtil\ErrorCode.h
 *ModifyRecord1:    
******************************************************************/
#ifndef __ERROR_CODE_H_
#define __ERROR_CODE_H_
#include "stm32h7xx_hal.h"

//系统错误代码
typedef enum  D_ERR
{
    D_ERR_NONE                                                 = 0X00000000,//无错误
    /************************主控通用的错误代码**********************************************************************************************/
    D_ERR_BOARD_MAIN_COMM_BASE                                 = 0XD0000000,
    /****************************************************主控板上硬件错误********************************************************/
    D_ERR_BOARD_MAIN_COMM_MCU_FLASH_ADDR                       = 0XD0000001,//芯片Flash驱动
    D_ERR_BOARD_MAIN_COMM_MCU_FLASH_ERASE                      = 0XD0000002,//芯片Flash擦除失败
    D_ERR_BOARD_MAIN_COMM_MCU_FLASH_WRITE                      = 0XD0000003,//芯片Flash写入失败
    D_ERR_BOARD_MAIN_COMM_SD_INIT                              = 0XD0000004,//SDCARD初始化失败
    D_ERR_BOARD_MAIN_COMM_SD_READ                              = 0XD0000005,//SD卡读卡失败
    D_ERR_BOARD_MAIN_COMM_SD_WRITE                             = 0XD0000006,//SD卡写卡失败
    D_ERR_BOARD_MAIN_COMM_SD_CHECK                             = 0XD0000007,//SD卡检查失败
    D_ERR_BOARD_MAIN_COMM_SDRAM_CHECK                          = 0XD0000008,//SRAM IS62WV51216
    D_ERR_BOARD_MAIN_COMM_SDRAM_ADDR                           = 0XD0000009,//SRAM地址错误
    D_ERR_BOARD_MAIN_COMM_FRAM_CHECK                           = 0XD000000A,//MB85RS2MT存储器检查失败
    D_ERR_BOARD_MAIN_COMM_FRAM_ID_READ                         = 0XD000000B,//存储器ID读取失败
    D_ERR_BOARD_MAIN_COMM_FRAM_ID_MATCH                        = 0XD000000C,//存储器ID匹配失败
    D_ERR_BOARD_MAIN_COMM_W5500_MAC                            = 0XD000000D,//W5500 MAC初始化错误
    D_ERR_BOARD_MAIN_COMM_HAL_LIB                              = 0XD000000E,//HAL库报错
    D_ERR_BOARD_MAIN_COMM_HAL_BUSY                             = 0XD000000F,//HAL库忙错误
    D_ERR_BOARD_MAIN_COMM_HAL_TIMEOUT                          = 0XD0000010,//HAL库超时错误
    D_ERR_BOARD_MAIN_COMM_IIC_ACK_TIMEOUT                      = 0XD0000011,//IIC ACK超时
    D_ERR_BOARD_MAIN_COMM_IIC_ADDR_LIMIT                       = 0XD0000012,//IIC ADDR超过限制
}D_ERR;

//转换HAL库错误
D_ERR ErrorConvertHAL(HAL_StatusTypeDef halError);



#endif



