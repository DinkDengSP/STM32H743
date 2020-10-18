/*******************************************************************
 *Description: Copyright(c) 2018-2090 DengXiaojun,All rights reserved.
 *Author: DengXiaoJun
 *Date: 2020-10-17 00:27:31
 *LastEditors: DengXiaoJun
 *LastEditTime: 2020-10-18 19:37:49
 *FilePath: \ProjectFilesd:\DinkGitHub\STM32H743\BoardArmfly\uCOSIII_App\Code\Driver\DriverMCU\MCU_SPI.h
 *ModifyRecord1:    
******************************************************************/
#ifndef __MCU_SPI_H_
#define __MCU_SPI_H_
#include "MCU_Common.h"

//SPI速度设定,基于200M外设基准频率,如果使用480M,则基于240基准另外计算
typedef enum MCU_SPI_CLK
{
    SPI_BAUDRATEPRESCALER_120M      = SPI_BAUDRATEPRESCALER_2,/* 120M */
    SPI_BAUDRATEPRESCALER_60M       = SPI_BAUDRATEPRESCALER_4,/* 60M */
    SPI_BAUDRATEPRESCALER_15M       = SPI_BAUDRATEPRESCALER_8,/* 12.5M */
    SPI_BAUDRATEPRESCALER_7_5M      = SPI_BAUDRATEPRESCALER_16,/* 7.5M */
    SPI_BAUDRATEPRESCALER_3_75M     = SPI_BAUDRATEPRESCALER_32,/* 3.75M */
    SPI_BAUDRATEPRESCALER_1_875M    = SPI_BAUDRATEPRESCALER_64,/* 1.875M */
    SPI_BAUDRATEPRESCALER_937_5K    = SPI_BAUDRATEPRESCALER_128,/* 937.5K */
    SPI_BAUDRATEPRESCALER_468_75K   = SPI_BAUDRATEPRESCALER_256,/* 468.75K */
}MCU_SPI_CLK;

//SPI信号极性
typedef enum MCU_SPI_CPOL
{
    MCU_SPI_CPOL_HIGH = SPI_POLARITY_HIGH,
    MCU_SPI_CPOL_LOW = SPI_POLARITY_LOW,
}MCU_SPI_CPOL;

//SPI采样点设置
typedef enum MCU_SPI_CPHA
{
    MCU_SPI_CPHA_1EDGE = SPI_PHASE_1EDGE,
    MCU_SPI_CPHA_2EDGE = SPI_PHASE_2EDGE,
}MCU_SPI_CPHA;

/**************************************SPI1************************************/
//SPI1互斥信号量
extern OS_MUTEX mutexMCU_Spi1;
//SPI1初始化
void MCU_SPI1_Init(MCU_SPI_CLK speed,MCU_SPI_CPOL cpol,MCU_SPI_CPHA cpha);
//SPI1设定传输速度
void MCU_SPI1_SetSpeed(MCU_SPI_CLK speed);
//SPI1读写数据
uint8_t MCU_SPI1_ReadWriteByte(uint8_t dat);


/**************************************SPI2************************************/
//SPI2互斥信号量
extern OS_MUTEX mutexMCU_Spi2;
//SPI2初始化
void MCU_SPI2_Init(MCU_SPI_CLK speed,MCU_SPI_CPOL cpol,MCU_SPI_CPHA cpha);
//SPI2设定传输速度
void MCU_SPI2_SetSpeed(MCU_SPI_CLK speed);
//SPI2读写数据
uint8_t MCU_SPI2_ReadWriteByte(uint8_t dat);


#endif
