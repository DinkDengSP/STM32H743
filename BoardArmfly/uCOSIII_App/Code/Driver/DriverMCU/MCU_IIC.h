/*******************************************************************
 *Description: Copyright(c) 2018-2090 DengXiaojun,All rights reserved.
 *Author: DengXiaoJun
 *Date: 2020-10-17 00:27:00
 *LastEditors: DengXiaoJun
 *LastEditTime: 2020-10-19 00:54:04
 *FilePath: \ProjectFilesd:\DinkGitHub\STM32H743\BoardArmfly\uCOSIII_App\Code\Driver\DriverMCU\MCU_IIC.h
 *ModifyRecord1:    
******************************************************************/
#ifndef __MCU_IIC_H_
#define __MCU_IIC_H_
#include "MCU_Common.h"

//IIC总线访问需要获取的信号量
extern OS_MUTEX mutexMCU_IIC;

//IIC等待ACK超时的计数事件
#define MCU_IIC_ACK_TIMEOUT_COUNT       5000

//IIC初始化IO口
void MCU_IIC_Init(void);

//IIC发送Start讯号
void MCU_IIC_SendStart(void);

//IIC发送停止讯号
void MCU_IIC_SendStop(void);

//IIC发出数据
void MCU_IIC_SendByte(uint8_t byteValue);

//IIC读取数据
uint8_t MCU_IIC_ReadByte(void);

//IIC等待ACK,等到返回0,没等到返回1,0代表不存在问题
uint8_t MCU_IIC_WaitAck(uint32_t timeOutCount);

//IIC发送ACK
void MCU_IIC_SendAck(void);

//IIC发送NACK
void MCU_IIC_SendNAck(void);

//IIC检查指定地址的设备是否存在
uint8_t MCU_IIC_CheckDeviceAddr(uint8_t deviceAddrWrite);


#endif
