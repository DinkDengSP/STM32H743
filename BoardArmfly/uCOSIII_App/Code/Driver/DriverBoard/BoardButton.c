/*******************************************************************
**Description: Copyright(c) 2018-2090 DengXiaojun,All rights reserved.
**Author: DengXiaoJun
**Date: 2020-10-19 00:02:48
**LastEditors: DengXiaoJun
**LastEditTime: 2020-10-19 00:08:15
**FilePath: \ProjectFilesd:\DinkGitHub\STM32H743\BoardArmfly\uCOSIII_App\Code\Driver\DriverBoard\BoardButton.c
**ModifyRecord1:    
******************************************************************/
#include "BoardButton.h"


//按键配置
typedef struct BOARD_BUTTON_CONFIG
{
    MCU_PIN pinValue;//按键引脚序号
    MCU_PORT_MODE portMode;//按键配置模式
    MCU_EXTI_MODE extiMode;//按键中断模式
    MCU_PORT_PULL pullMode;//按键上下拉设置
    MCU_PORT_SPEED speed;//按键速度
    BitAction validLevelPrsee;//按键有效电平
}BOARD_BUTTON_CONFIG;

//按键配置信息数组
static const BOARD_BUTTON_CONFIG boardButtonConfigArray[] = {
    {MCU_PIN_I_8 ,MCU_PORT_MODE_INPUT,MCU_EXTI_MODE_IT_FALLING,MCU_PORT_PULL_NOPULL,MCU_PORT_SPEED_FREQ_MEDIUM,Bit_RESET},//BOARD_BUTTON_K1   
    {MCU_PIN_C_13,MCU_PORT_MODE_INPUT,MCU_EXTI_MODE_IT_FALLING,MCU_PORT_PULL_NOPULL,MCU_PORT_SPEED_FREQ_MEDIUM,Bit_RESET},//BOARD_BUTTON_K2   
    {MCU_PIN_H_4 ,MCU_PORT_MODE_INPUT,MCU_EXTI_MODE_IT_FALLING,MCU_PORT_PULL_NOPULL,MCU_PORT_SPEED_FREQ_MEDIUM,Bit_RESET},//BOARD_BUTTON_K3   
};

//独立按键初始化
void BoardButtonScanInit(BUTTON_NAME buttonName)
{
    //调用MCU引脚初始化
    MCU_PortInit(boardButtonConfigArray[buttonName].pinValue,
                    boardButtonConfigArray[buttonName].portMode,
                    boardButtonConfigArray[buttonName].pullMode,
                    boardButtonConfigArray[buttonName].speed,
                    0);
}

//独立按键中断初始化
void BoardButtonIntInit(BUTTON_NAME buttonName,NVIC_INT_PRE_PRI preePri,NVIC_INT_SUB_PRI subPri,MCU_Exti_CallBackFuncPtr callBackFuncPtr)
{
     MCU_PortExtiInit(boardButtonConfigArray[buttonName].pinValue,boardButtonConfigArray[buttonName].extiMode,boardButtonConfigArray[buttonName].pullMode,
                    boardButtonConfigArray[buttonName].speed,preePri,subPri,callBackFuncPtr);
}

//获取独立按键当前状态
SENSOR_STATE BoardButtonRead(BUTTON_NAME buttonName)
{
    //读取MCU引脚状态
    BitAction keyValue = MCU_PortReadSingle(boardButtonConfigArray[buttonName].pinValue);
    return (keyValue ==  boardButtonConfigArray[buttonName].validLevelPrsee)?SENSOR_STATE_VALID:SENSOR_STATE_INVALID;
}
