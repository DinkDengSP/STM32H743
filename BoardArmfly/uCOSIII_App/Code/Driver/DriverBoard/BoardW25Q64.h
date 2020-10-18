/*******************************************************************
 *Description: Copyright(c) 2018-2090 DengXiaojun,All rights reserved.
 *Author: DengXiaoJun
 *Date: 2020-10-17 00:28:50
 *LastEditors: DengXiaoJun
 *LastEditTime: 2020-10-18 19:50:16
 *FilePath: \ProjectFilesd:\DinkGitHub\STM32H743\BoardArmfly\uCOSIII_App\Code\Driver\DriverBoard\BoardW25Q64.h
 *ModifyRecord1:    
******************************************************************/
#ifndef __BOARD_W25Q64_H_
#define __BOARD_W25Q64_H_
#include "MCU_Inc.h"

//设备的ID识别号
#define W25Q64_ID                  0X00EF4017
#define W25Q64_FLASH_SIZE          (8*1024*1024)

//选中引脚
#define BOARD_W25Q64_CS_SELECT()          MCU_PortWriteSingle(MCU_PIN_D_13,Bit_RESET)
//释放选中引脚
#define BOARD_W25Q64_CS_RELEASE()         MCU_PortWriteSingle(MCU_PIN_D_13,Bit_SET)

//指令表
#define W25QXX_CMD_WRITE_ENABLE			0x06 
#define W25QXX_CMD_WRITE_DISABLE		0x04 
#define W25QXX_CMD_READ_STATUS_REG1		0x05 
#define W25QXX_CMD_READ_STATUS_REG2		0x35 
#define W25QXX_CMD_READ_STATUS_REG3		0x15 
#define W25QXX_CMD_WRITE_STATUS_REG1    0x01 
#define W25QXX_CMD_WRITE_STATUS_REG2    0x31 
#define W25QXX_CMD_WRITE_STATUS_REG3    0x11 
#define W25QXX_CMD_READ_DATA			0x03 
#define W25QXX_CMD_FAST_READ_DATA		0x0B 
#define W25QXX_CMD_FAST_READ_DUAL		0x3B 
#define W25QXX_CMD_PAGE_PROGRAM			0x02 
#define W25QXX_CMD_BLOCK_ERASE			0xD8 
#define W25QXX_CMD_SECTOR_ERASE			0x20 
#define W25QXX_CMD_CHIP_ERASE			0xC7 
#define W25QXX_CMD_POWER_DOWN			0xB9 
#define W25QXX_CMD_RELEASE_POWER_DOWN	0xAB 
#define W25QXX_CMD_DEVICE_ID			0xAB 
#define W25QXX_CMD_MANUFACT_DEVICE_ID	0x90 
#define W25QXX_CMD_JEDEC_DEVICE_ID		0x9F 
#define W25QXX_CMD_SET_READ_PARAM		0xC0 
#define W25QXX_CMD_DUMMY_BYTE           0xFF
#define W25QXX_STATE_WIP_FLAG           0x01  /* Write In Progress (WIP) flag */
#define W25QXX_PAGE_SIZE                256

//板上Flash初始化
void BoardW25Q64_Init(void);

//板上Flash自检
D_ERR BoardW25Q64_Check(void);

//擦除指定扇区
void BoardW25Q64_EraseSector(uint32_t sectorNo);

//整片擦除
void BoardW25Q64_EraseChip(void);

//写入指定地址数据
void BoardW25Q64_WriteBuffer(uint8_t* pBuffer, uint32_t addr, uint16_t dataLength);

//读取指定地址数据
void BoardW25Q64_ReadBuffer(uint8_t* pBuffer, uint32_t addr, uint32_t dataLength);

//读取板上设备ID
D_ERR BoardW25Q64_ReadID(uint32_t* deviceIdPtr);

#endif
