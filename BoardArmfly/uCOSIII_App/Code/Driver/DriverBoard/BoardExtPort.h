/*******************************************************************
 *Description: Copyright(c) 2018-2090 DengXiaojun,All rights reserved.
 *Author: DengXiaoJun
 *Date: 2020-10-13 22:29:55
 *LastEditors: DengXiaoJun
 *LastEditTime: 2020-10-15 23:50:31
 *FilePath: \ProjectFilesd:\DinkGitHub\STM32H743\BoardArmfly\uCOSIII_App\Code\Driver\DriverBoard\BoardExtPort.h
 *ModifyRecord1:    
******************************************************************/
#ifndef __BOARD_EXT_PORT_H_
#define __BOARD_EXT_PORT_H_
#include "MCU_Inc.h"

//外部扩展IO序号定义
#define BOARD_EXT_PORT_PIN_0               ((uint32_t)0x00000001)
#define BOARD_EXT_PORT_PIN_1               ((uint32_t)0x00000002)
#define BOARD_EXT_PORT_PIN_2               ((uint32_t)0x00000004)
#define BOARD_EXT_PORT_PIN_3               ((uint32_t)0x00000008)
#define BOARD_EXT_PORT_PIN_4               ((uint32_t)0x00000010)
#define BOARD_EXT_PORT_PIN_5               ((uint32_t)0x00000020)
#define BOARD_EXT_PORT_PIN_6               ((uint32_t)0x00000040)
#define BOARD_EXT_PORT_PIN_7               ((uint32_t)0x00000080)
#define BOARD_EXT_PORT_PIN_8               ((uint32_t)0x00000100)
#define BOARD_EXT_PORT_PIN_9               ((uint32_t)0x00000200)
#define BOARD_EXT_PORT_PIN_10              ((uint32_t)0x00000400)
#define BOARD_EXT_PORT_PIN_11              ((uint32_t)0x00000800)
#define BOARD_EXT_PORT_PIN_12              ((uint32_t)0x00001000)
#define BOARD_EXT_PORT_PIN_13              ((uint32_t)0x00002000)
#define BOARD_EXT_PORT_PIN_14              ((uint32_t)0x00004000)
#define BOARD_EXT_PORT_PIN_15              ((uint32_t)0x00008000)
#define BOARD_EXT_PORT_PIN_16              ((uint32_t)0x00010000)
#define BOARD_EXT_PORT_PIN_17              ((uint32_t)0x00020000)
#define BOARD_EXT_PORT_PIN_18              ((uint32_t)0x00040000)
#define BOARD_EXT_PORT_PIN_19              ((uint32_t)0x00080000)
#define BOARD_EXT_PORT_PIN_20              ((uint32_t)0x00100000)
#define BOARD_EXT_PORT_PIN_21              ((uint32_t)0x00200000)
#define BOARD_EXT_PORT_PIN_22              ((uint32_t)0x00400000)
#define BOARD_EXT_PORT_PIN_23              ((uint32_t)0x00800000)
#define BOARD_EXT_PORT_PIN_24              ((uint32_t)0x01000000)
#define BOARD_EXT_PORT_PIN_25              ((uint32_t)0x02000000)
#define BOARD_EXT_PORT_PIN_26              ((uint32_t)0x04000000)
#define BOARD_EXT_PORT_PIN_27              ((uint32_t)0x08000000)
#define BOARD_EXT_PORT_PIN_28              ((uint32_t)0x10000000)
#define BOARD_EXT_PORT_PIN_29              ((uint32_t)0x20000000)
#define BOARD_EXT_PORT_PIN_30              ((uint32_t)0x40000000)
#define BOARD_EXT_PORT_PIN_31              ((uint32_t)0x80000000)

//外部扩展IO功能定义
/* 为了方便记忆，重命名上面的宏 */
#define	BOARD_EXT_PORT_PIN_GPRS_TERM_ON   BOARD_EXT_PORT_PIN_0
#define	BOARD_EXT_PORT_PIN_GPRS_RESET     BOARD_EXT_PORT_PIN_1
#define	BOARD_EXT_PORT_PIN_NRF24L01_CE    BOARD_EXT_PORT_PIN_2
#define	BOARD_EXT_PORT_PIN_NRF905_TX_EN   BOARD_EXT_PORT_PIN_3
#define	BOARD_EXT_PORT_PIN_VS1053_XRESET  BOARD_EXT_PORT_PIN_3
#define	BOARD_EXT_PORT_PIN_NRF905_TRX_CE  BOARD_EXT_PORT_PIN_4
#define BOARD_EXT_PORT_PIN_VS1053_XDCS    BOARD_EXT_PORT_PIN_4	/* NRF905_TRX_CE， VS1053_XDCS 复用 */
#define	BOARD_EXT_PORT_PIN_NRF905_PWR_UP  BOARD_EXT_PORT_PIN_5
#define	BOARD_EXT_PORT_PIN_ESP8266_G0     BOARD_EXT_PORT_PIN_6
#define	BOARD_EXT_PORT_PIN_ESP8266_G2     BOARD_EXT_PORT_PIN_7
#define	BOARD_EXT_PORT_PIN_LED1           BOARD_EXT_PORT_PIN_8
#define	BOARD_EXT_PORT_PIN_LED2           BOARD_EXT_PORT_PIN_9
#define	BOARD_EXT_PORT_PIN_LED3           BOARD_EXT_PORT_PIN_10
#define	BOARD_EXT_PORT_PIN_LED4           BOARD_EXT_PORT_PIN_11
#define	BOARD_EXT_PORT_PIN_TP_NRST        BOARD_EXT_PORT_PIN_12
#define	BOARD_EXT_PORT_PIN_AD7606_OS0     BOARD_EXT_PORT_PIN_13
#define	BOARD_EXT_PORT_PIN_AD7606_OS1     BOARD_EXT_PORT_PIN_14
#define	BOARD_EXT_PORT_PIN_AD7606_OS2     BOARD_EXT_PORT_PIN_15
#define	BOARD_EXT_PORT_PIN_Y50_0          BOARD_EXT_PORT_PIN_16
#define	BOARD_EXT_PORT_PIN_Y50_1          BOARD_EXT_PORT_PIN_17
#define	BOARD_EXT_PORT_PIN_Y50_2          BOARD_EXT_PORT_PIN_18
#define	BOARD_EXT_PORT_PIN_Y50_3          BOARD_EXT_PORT_PIN_19
#define	BOARD_EXT_PORT_PIN_Y50_4          BOARD_EXT_PORT_PIN_20
#define	BOARD_EXT_PORT_PIN_Y50_5          BOARD_EXT_PORT_PIN_21
#define	BOARD_EXT_PORT_PIN_Y50_6          BOARD_EXT_PORT_PIN_22
#define	BOARD_EXT_PORT_PIN_Y50_7          BOARD_EXT_PORT_PIN_23	
#define	BOARD_EXT_PORT_PIN_AD7606_RESET   BOARD_EXT_PORT_PIN_24
#define	BOARD_EXT_PORT_PIN_AD7606_RANGE   BOARD_EXT_PORT_PIN_25
#define	BOARD_EXT_PORT_PIN_Y33_2          BOARD_EXT_PORT_PIN_26
#define	BOARD_EXT_PORT_PIN_Y33_3          BOARD_EXT_PORT_PIN_27
#define	BOARD_EXT_PORT_PIN_Y33_4          BOARD_EXT_PORT_PIN_28
#define	BOARD_EXT_PORT_PIN_Y33_5          BOARD_EXT_PORT_PIN_29
#define	BOARD_EXT_PORT_PIN_Y33_6          BOARD_EXT_PORT_PIN_30
#define	BOARD_EXT_PORT_PIN_Y33_7          BOARD_EXT_PORT_PIN_31

//扩展IO初始化
void BoardExtPort_Init(void);

//扩展IO设置指定IO口
void BoardExtPort_SetPin(uint32_t pin, uint8_t value);

//扩展IO读取指定IO口状态
uint8_t BoardExtPort_GetPin(uint32_t pin);

//扩展IO翻转IO口状态
void BoardExtPort_TooglePin(uint32_t pin);

#endif




