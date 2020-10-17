/*******************************************************************
 *Description: Copyright(c) 2018-2090 DengXiaojun,All rights reserved.
 *Author: DengXiaoJun
 *Date: 2020-10-16 23:06:32
 *LastEditors: DengXiaoJun
 *LastEditTime: 2020-10-17 00:02:26
 *FilePath: \ProjectFilesd:\DinkGitHub\STM32H743\BoardArmfly\uCOSIII_App\Code\Driver\DriverBoard\BoardExtPortConfig.h
 *ModifyRecord1:    
******************************************************************/
#ifndef __BOARD_EXT_PORT_CONFIG_H_
#define __BOARD_EXT_PORT_CONFIG_H_
#include "stm32h7xx_hal.h"

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

//外部扩展IO信号名称
typedef enum BOARD_EXT_PORT_INDEX
{
    BOARD_EXT_PORT_PIN_GPRS_TERM_ON = BOARD_EXT_PORT_PIN_0,
    BOARD_EXT_PORT_PIN_GPRS_RESET   = BOARD_EXT_PORT_PIN_1,
    BOARD_EXT_PORT_PIN_NRF24L01_CE  = BOARD_EXT_PORT_PIN_2,
    BOARD_EXT_PORT_PIN_NRF905_TX_EN = BOARD_EXT_PORT_PIN_3,
    BOARD_EXT_PORT_PIN_VS1053_XRESET= BOARD_EXT_PORT_PIN_3,
    BOARD_EXT_PORT_PIN_NRF905_TRX_CE= BOARD_EXT_PORT_PIN_4,
    BOARD_EXT_PORT_PIN_VS1053_XDCS  = BOARD_EXT_PORT_PIN_4,/* NRF905_TRX_CE， VS1053_XDCS 复用 */
    BOARD_EXT_PORT_PIN_NRF905_PWR_UP= BOARD_EXT_PORT_PIN_5,
    BOARD_EXT_PORT_PIN_ESP8266_G0   = BOARD_EXT_PORT_PIN_6,
    BOARD_EXT_PORT_PIN_ESP8266_G2   = BOARD_EXT_PORT_PIN_7,
    BOARD_EXT_PORT_PIN_LED1         = BOARD_EXT_PORT_PIN_8,
    BOARD_EXT_PORT_PIN_LED2         = BOARD_EXT_PORT_PIN_9,
    BOARD_EXT_PORT_PIN_LED3         = BOARD_EXT_PORT_PIN_10,
    BOARD_EXT_PORT_PIN_LED4         = BOARD_EXT_PORT_PIN_11,
    BOARD_EXT_PORT_PIN_TP_NRST      = BOARD_EXT_PORT_PIN_12,
    BOARD_EXT_PORT_PIN_AD7606_OS0   = BOARD_EXT_PORT_PIN_13,
    BOARD_EXT_PORT_PIN_AD7606_OS1   = BOARD_EXT_PORT_PIN_14,
    BOARD_EXT_PORT_PIN_AD7606_OS2   = BOARD_EXT_PORT_PIN_15,
    BOARD_EXT_PORT_PIN_Y50_0        = BOARD_EXT_PORT_PIN_16,
    BOARD_EXT_PORT_PIN_Y50_1        = BOARD_EXT_PORT_PIN_17,
    BOARD_EXT_PORT_PIN_Y50_2        = BOARD_EXT_PORT_PIN_18,
    BOARD_EXT_PORT_PIN_Y50_3        = BOARD_EXT_PORT_PIN_19,
    BOARD_EXT_PORT_PIN_Y50_4        = BOARD_EXT_PORT_PIN_20,
    BOARD_EXT_PORT_PIN_Y50_5        = BOARD_EXT_PORT_PIN_21,
    BOARD_EXT_PORT_PIN_Y50_6        = BOARD_EXT_PORT_PIN_22,
    BOARD_EXT_PORT_PIN_Y50_7        = BOARD_EXT_PORT_PIN_23,
    BOARD_EXT_PORT_PIN_AD7606_RESET = BOARD_EXT_PORT_PIN_24,
    BOARD_EXT_PORT_PIN_AD7606_RANGE = BOARD_EXT_PORT_PIN_25,
    BOARD_EXT_PORT_PIN_Y33_2        = BOARD_EXT_PORT_PIN_26,
    BOARD_EXT_PORT_PIN_Y33_3        = BOARD_EXT_PORT_PIN_27,
    BOARD_EXT_PORT_PIN_Y33_4        = BOARD_EXT_PORT_PIN_28,
    BOARD_EXT_PORT_PIN_Y33_5        = BOARD_EXT_PORT_PIN_29,
    BOARD_EXT_PORT_PIN_Y33_6        = BOARD_EXT_PORT_PIN_30,
    BOARD_EXT_PORT_PIN_Y33_7        = BOARD_EXT_PORT_PIN_31,
}BOARD_EXT_PORT_INDEX;


#endif




