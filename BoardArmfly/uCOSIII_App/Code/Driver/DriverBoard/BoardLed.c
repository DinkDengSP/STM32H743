/*******************************************************************
**Description: Copyright(c) 2018-2090 DengXiaojun,All rights reserved.
**Author: DengXiaoJun
**Date: 2020-10-13 22:30:15
**LastEditors: DengXiaoJun
**LastEditTime: 2020-10-17 00:13:54
**FilePath: \ProjectFilesd:\DinkGitHub\STM32H743\BoardArmfly\uCOSIII_App\Code\Driver\DriverBoard\BoardLed.c
**ModifyRecord1:    
******************************************************************/
#include "BoardLed.h"
#include "BoardExtPort.h"

//LED名称转换为独立端口号
static BOARD_EXT_PORT_INDEX BoardLedGetPortIndex(BOARD_LED_NAME ledPin)
{
    BOARD_EXT_PORT_INDEX extPortIndex = BOARD_EXT_PORT_PIN_LED1;
    switch(ledPin)
    {
        case BOARD_LED1_REMOTE:
            extPortIndex = BOARD_EXT_PORT_PIN_LED1;
            break;
        case BOARD_LED2_NRF24L01:
            extPortIndex = BOARD_EXT_PORT_PIN_LED2;
            break;
        case BOARD_LED3_W25Q128:
            extPortIndex = BOARD_EXT_PORT_PIN_LED3;
            break;
        case BOARD_LED4_DHT11:
            extPortIndex = BOARD_EXT_PORT_PIN_LED4;
            break;
        default:
            break;
    }
    return extPortIndex;
}

//板上LED初始化
void BoardLedInit(BOARD_LED_NAME ledPin,BOARD_LED_STATE initState)
{
    BOARD_EXT_PORT_INDEX extPortIndex = BoardLedGetPortIndex(ledPin);
    BoardExtPort_SetPin(extPortIndex,(BitAction)initState);
}

//设置指定LED状态
void BoardLedSet(BOARD_LED_NAME ledPin,BOARD_LED_STATE setState)
{
    BOARD_EXT_PORT_INDEX extPortIndex = BoardLedGetPortIndex(ledPin);
    BoardExtPort_SetPin(extPortIndex,(BitAction)setState);
}

//翻转LED状态
void BoardLedToogle(BOARD_LED_NAME ledPin)
{
    BOARD_EXT_PORT_INDEX extPortIndex = BoardLedGetPortIndex(ledPin);
    BoardExtPort_TooglePin(extPortIndex);
}

