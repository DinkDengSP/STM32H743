/*******************************************************************
 *Description: Copyright(c) 2018-2090 DengXiaojun,All rights reserved.
 *Author: DengXiaoJun
 *Date: 2020-10-17 00:30:13
 *LastEditors: DengXiaoJun
 *LastEditTime: 2020-10-19 01:10:24
 *FilePath: \ProjectFilesd:\DinkGitHub\STM32H743\BoardArmfly\uCOSIII_App\Code\Driver\DriverBoard\BoardAT24CXX.h
 *ModifyRecord1:    
******************************************************************/
#ifndef __BOARD_AT24CXX_H_
#define __BOARD_AT24CXX_H_
#include "MCU_Inc.h"

//不同的AT芯片的Flash容量
#define BOARD_AT24C01_SIZE		    127
#define BOARD_AT24C02_SIZE		    255
#define BOARD_AT24C04_SIZE		    511
#define BOARD_AT24C08_SIZE		    1023
#define BOARD_AT24C16_SIZE		    2047
#define BOARD_AT24C32_SIZE		    4095
#define BOARD_AT24C64_SIZE	        8191
#define BOARD_AT24C128_SIZE	        16383
#define BOARD_AT24C256_SIZE	        32767

//板上AT芯片的信号
#define BOARD_AT24CXX_SIZE          BOARD_AT24C128_SIZE
//板上芯片的读写地址
#define BOARD_AT24CXX_WRITE_ADDR    0XA0
#define BOARD_AT24CXX_READ_ADDR     0XA1

//板上芯片初始化
D_ERR BoardAT24CXX_Init(void);

//IIC芯片自检
D_ERR BoardAT24CXX_Check(void);

//写入数据
D_ERR BoardAT24CXX_Write(uint16_t addrWrite,uint8_t* writeBuffer,uint16_t numWrite);

//读取数据
D_ERR BoardAT24CXX_Read(uint16_t addrRead,uint8_t* recvBufferPtr,uint16_t numRead);

#endif
