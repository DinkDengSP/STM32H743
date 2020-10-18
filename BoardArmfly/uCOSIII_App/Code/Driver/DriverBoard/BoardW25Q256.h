/*******************************************************************
 *Description: Copyright(c) 2018-2090 DengXiaojun,All rights reserved.
 *Author: DengXiaoJun
 *Date: 2020-10-17 00:29:15
 *LastEditors: DengXiaoJun
 *LastEditTime: 2020-10-18 18:01:10
 *FilePath: \ProjectFilesd:\DinkGitHub\STM32H743\BoardArmfly\uCOSIII_App\Code\Driver\DriverBoard\BoardW25Q256.h
 *ModifyRecord1:    
******************************************************************/
#ifndef __BOARD_W25Q256_H_
#define __BOARD_W25Q256_H_
#include "MCU_Inc.h"

//设备的ID识别号
#define W25Q256_ID                                  0X00EF4019
/* W25Q256JV基本信息 */
#define W25Q256JV_FLASH_SIZE                        25                      /* Flash大小，2^25 = 32MB*/
#define W25Q256JV_SECTOR_SIZE                       (4 * 1024)              /* 扇区大小，4KB */
#define W25Q256JV_PAGE_SIZE                         256        				/* 页大小，256字节 */
#define W25Q256JV_END_ADDR    	                    (1 << QSPI_FLASH_SIZE)  /* 末尾地址 */
#define W25Q256JV_FLASH_SIZES                       32*1024*1024            /* Flash大小，2^25 = 32MB*/
#define W25Q256JV_CMD_TIME_OUT                      1000                    /*指令超时时间*/

//指令表 W25Q256
#define W25Q256_CMD_WRITE_STATUSREG1                0x01 
#define W25Q256_CMD_PAGE_PROGRAM		            0x02 
#define W25Q256_CMD_READ_DATA			            0x03 
#define W25Q256_CMD_WRITE_DISABLE		            0x04 
#define W25Q256_CMD_READ_STATUSREG1		            0x05/* 读取状态命令 */ 
#define W25Q256_CMD_WRITE_ENABLE		            0x06/* 写使能指令 */  
#define W25Q256_CMD_FAST_READ_DATA		            0x0B 
#define W25Q256_CMD_WRITE_STATUSREG3                0x11 
#define W25Q256_CMD_READ_STATUSREG3		            0x15
#define W25Q256_CMD_SECTOR_ERASE		            0x20
#define W25Q256_CMD_WRITE_STATUSREG2                0x31  
#define W25Q256_CMD_READ_STATUSREG2		            0x35 
#define W25Q256_CMD_ENTER_QSPI_MODE                 0x38
#define W25Q256_CMD_FAST_READ_DUAL		            0x3B
#define W25Q256_CMD_MANUFACT_DEVICE_ID	            0x90 
#define W25Q256_CMD_JEDEC_DEVICE_ID		            0x9F/* 读取ID命令 */
#define W25Q256_CMD_RELEASE_POWER_DOWN	            0xAB 
#define W25Q256_CMD_DEVICE_ID			            0xAB 
#define W25Q256_CMD_ENABLE_4BYTE_ADDR               0xB7
#define W25Q256_CMD_POWER_DOWN			            0xB9
#define W25Q256_CMD_SET_READ_PARAM		            0xC0 
#define W25Q256_CMD_CHIP_ERASE			            0xC7
#define W25Q256_CMD_BLOCK_ERASE			            0xD8 
#define W25Q256_CMD_EXIT_4BYTE_ADDR                 0xE9
#define W25Q256_CMD_EXIT_QSPI_MODE                  0xFF
#define W25Q256_CMD_SECTOR_ERASE_4_LINES            0x21    /* 32bit地址扇区擦除指令, 4KB */
#define W25Q256_CMD_FAST_PROG_4_LINES               0x34    /* 32bit地址的4线快速写入命令 */
#define W25Q256_CMD_FAST_READ_4_LINES               0xEC    /* 32bit地址的4线快速读取命令 */

//QSPI句柄
extern QSPI_HandleTypeDef qspiW25q256Handle;

//板上Flash初始化
D_ERR BoardW25Q256_Init(void);

//板上Flash检测
D_ERR BoardW25Q256_Check(void);

//擦除指定扇区
void BoardW25Q256_EraseSector(uint32_t sectorNo);

//擦除全芯片,等待时间500S
void BoardW25Q256_EraseChip(void);

//写入指定地址数据
void BoardW25Q256_WriteBuffer(uint8_t* pBuffer, uint32_t addr, uint16_t dataLength);

//读取指定地址数据
void BoardW25Q256_ReadBuffer(uint8_t* pBuffer, uint32_t addr, uint32_t dataLength);

//读取板上设备ID
D_ERR BoardW25Q256_ReadID(uint32_t* deviceIdPtr);

#endif
