/*******************************************************************
**Description: Copyright(c) 2018-2090 DengXiaojun,All rights reserved.e
**Author: DengXiaoJun
**Date: 2020-10-18 23:38:42
**LastEditors: DengXiaoJun
**LastEditTime: 2020-10-18 23:52:42
**FilePath: \ProjectFilesd:\DinkGitHub\STM32H743\BoardArmfly\uCOSIII_App\Code\Driver\DriverBoard\BoardJoysTick.c
**ModifyRecord1:    
******************************************************************/
#include "BoardJoysTick.h"

//按键配置
typedef struct JOYS_TICK_CONFIG
{
    MCU_PIN pinValue;//按键引脚序号
    MCU_PORT_MODE portMode;//按键配置模式
    MCU_EXTI_MODE extiMode;//按键中断模式
    MCU_PORT_PULL pullMode;//按键上下拉设置
    MCU_PORT_SPEED speed;//按键速度
    BitAction validLevelPrsee;//按键有效电平
}JOYS_TICK_CONFIG;

//按键配置信息数组
static const JOYS_TICK_CONFIG joysTickConfigArray[] = {
    {MCU_PIN_I_11,MCU_PORT_MODE_INPUT,MCU_EXTI_MODE_IT_FALLING,MCU_PORT_PULL_NOPULL,MCU_PORT_SPEED_FREQ_MEDIUM,Bit_RESET},//BOARD_KEY_PRESS
    {MCU_PIN_G_3 ,MCU_PORT_MODE_INPUT,MCU_EXTI_MODE_IT_FALLING,MCU_PORT_PULL_NOPULL,MCU_PORT_SPEED_FREQ_MEDIUM,Bit_RESET},//BOARD_KEY_LEFT 
    {MCU_PIN_G_7 ,MCU_PORT_MODE_INPUT,MCU_EXTI_MODE_IT_FALLING,MCU_PORT_PULL_NOPULL,MCU_PORT_SPEED_FREQ_MEDIUM,Bit_RESET},//BOARD_KEY_RIGHT
    {MCU_PIN_G_2 ,MCU_PORT_MODE_INPUT,MCU_EXTI_MODE_IT_FALLING,MCU_PORT_PULL_NOPULL,MCU_PORT_SPEED_FREQ_MEDIUM,Bit_RESET},//BOARD_KEY_UP   
    {MCU_PIN_B_0 ,MCU_PORT_MODE_INPUT,MCU_EXTI_MODE_IT_FALLING,MCU_PORT_PULL_NOPULL,MCU_PORT_SPEED_FREQ_MEDIUM,Bit_RESET},//BOARD_KEY_DOWN 
};


//多向按键初始化
void BoardJoysTickScanInit(JOYS_TICK_NAME tickName)
{
    //调用MCU引脚初始化
    MCU_PortInit(joysTickConfigArray[tickName].pinValue,
                    joysTickConfigArray[tickName].portMode,
                    joysTickConfigArray[tickName].pullMode,
                    joysTickConfigArray[tickName].speed,
                    0);
}

//多向按键中断初始化
void BoardJoysTickIntInit(JOYS_TICK_NAME tickName,NVIC_INT_PRE_PRI preePri,NVIC_INT_SUB_PRI subPri,MCU_Exti_CallBackFuncPtr callBackFuncPtr)
{
    MCU_PortExtiInit(joysTickConfigArray[tickName].pinValue,joysTickConfigArray[tickName].extiMode,joysTickConfigArray[tickName].pullMode,
                    joysTickConfigArray[tickName].speed,preePri,subPri,callBackFuncPtr);
}

//获取多向按键当前状态
SENSOR_STATE BoardJoysTickRead(JOYS_TICK_NAME tickName)
{
    //读取MCU引脚状态
    BitAction keyValue = MCU_PortReadSingle(joysTickConfigArray[tickName].pinValue);
    return (keyValue ==  joysTickConfigArray[tickName].validLevelPrsee)?SENSOR_STATE_VALID:SENSOR_STATE_INVALID;
}

