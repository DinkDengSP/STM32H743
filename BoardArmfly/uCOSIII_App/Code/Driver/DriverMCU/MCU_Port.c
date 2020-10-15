/*******************************************************************
**Description: Copyright(c) 2018-2090 DengXiaojun,All rights reserved.
**Author: DengXiaoJun
**Date: 2020-10-12 23:20:26
**LastEditors: DengXiaoJun
**LastEditTime: 2020-10-15 23:47:21
**FilePath: \ProjectFilesd:\DinkGitHub\STM32H743\BoardArmfly\uCOSIII_App\Code\Driver\DriverMCU\MCU_Port.c
**ModifyRecord1:    
******************************************************************/
#include "MCU_Port.h"

//使能指定IO口时钟
static void MCU_PortClkEnable(MCU_PIN pin)
{
    if(pin <= MCU_PIN_A_15) __HAL_RCC_GPIOA_CLK_ENABLE();
    else if(pin <= MCU_PIN_B_15)__HAL_RCC_GPIOB_CLK_ENABLE();
    else if(pin <= MCU_PIN_C_15)__HAL_RCC_GPIOC_CLK_ENABLE();
    else if(pin <= MCU_PIN_D_15)__HAL_RCC_GPIOD_CLK_ENABLE();
    else if(pin <= MCU_PIN_E_15)__HAL_RCC_GPIOE_CLK_ENABLE();
    else if(pin <= MCU_PIN_F_15)__HAL_RCC_GPIOF_CLK_ENABLE();
    else if(pin <= MCU_PIN_G_15)__HAL_RCC_GPIOG_CLK_ENABLE();
    else if(pin <= MCU_PIN_H_15)__HAL_RCC_GPIOH_CLK_ENABLE();
    else if(pin <= MCU_PIN_I_15)__HAL_RCC_GPIOI_CLK_ENABLE();
    else if(pin <= MCU_PIN_J_15)__HAL_RCC_GPIOJ_CLK_ENABLE();
    else if(pin <= MCU_PIN_K_15)__HAL_RCC_GPIOK_CLK_ENABLE();
}

//计算MCU_PIN对应的pin宏定义
static uint16_t MCU_PortCalcPinIndex(MCU_PIN pin)
{
    uint16_t pinIndex = 0x0001;
    uint8_t pinShift = 0;
    if(pin <= MCU_PIN_A_15)pinShift = pin - MCU_PIN_A_0;
    else if(pin <= MCU_PIN_B_15)pinShift = pin - MCU_PIN_B_0;
    else if(pin <= MCU_PIN_C_15)pinShift = pin - MCU_PIN_C_0;
    else if(pin <= MCU_PIN_D_15)pinShift = pin - MCU_PIN_D_0;
    else if(pin <= MCU_PIN_E_15)pinShift = pin - MCU_PIN_E_0;
    else if(pin <= MCU_PIN_F_15)pinShift = pin - MCU_PIN_F_0;
    else if(pin <= MCU_PIN_G_15)pinShift = pin - MCU_PIN_G_0;
    else if(pin <= MCU_PIN_H_15)pinShift = pin - MCU_PIN_H_0;
    else if(pin <= MCU_PIN_I_15)pinShift = pin - MCU_PIN_I_0;
    else if(pin <= MCU_PIN_J_15)pinShift = pin - MCU_PIN_J_0;
    else if(pin <= MCU_PIN_K_15)pinShift = pin - MCU_PIN_K_0;
    //移位计算
    pinIndex <<= pinShift;
    return pinIndex;
}

//调用特定初始化
static void MCU_PortInitEnd(MCU_PIN pin,GPIO_InitTypeDef *GPIO_Init)
{
    if(pin <= MCU_PIN_A_15) HAL_GPIO_Init(GPIOA,GPIO_Init);
    else if(pin <= MCU_PIN_B_15)HAL_GPIO_Init(GPIOB,GPIO_Init);
    else if(pin <= MCU_PIN_C_15)HAL_GPIO_Init(GPIOC,GPIO_Init);
    else if(pin <= MCU_PIN_D_15)HAL_GPIO_Init(GPIOD,GPIO_Init);
    else if(pin <= MCU_PIN_E_15)HAL_GPIO_Init(GPIOE,GPIO_Init);
    else if(pin <= MCU_PIN_F_15)HAL_GPIO_Init(GPIOF,GPIO_Init);
    else if(pin <= MCU_PIN_G_15)HAL_GPIO_Init(GPIOG,GPIO_Init);
    else if(pin <= MCU_PIN_H_15)HAL_GPIO_Init(GPIOH,GPIO_Init);
    else if(pin <= MCU_PIN_I_15)HAL_GPIO_Init(GPIOI,GPIO_Init);
    else if(pin <= MCU_PIN_J_15)HAL_GPIO_Init(GPIOJ,GPIO_Init);
    else if(pin <= MCU_PIN_K_15)HAL_GPIO_Init(GPIOK,GPIO_Init);
}

//初始化指定引脚
//alternateSelect使用GPIO_Alternate_function_selection选择
void MCU_PortInit(MCU_PIN pin,MCU_PORT_MODE mode, MCU_PORT_PULL pullType,MCU_PORT_SPEED speed, uint8_t alternateSelect)
{
     GPIO_InitTypeDef GPIO_Initure;
    //开启时钟
    MCU_PortClkEnable(pin);
	
    //引脚序号
    GPIO_Initure.Pin = MCU_PortCalcPinIndex(pin);		
    //引脚模式
    GPIO_Initure.Mode = mode;  	
    //上下拉状态	
    GPIO_Initure.Pull = pullType;   
    //速度设置      			
    GPIO_Initure.Speed = speed;
    //复用模式
    GPIO_Initure.Alternate = alternateSelect;  
    //初始化
    MCU_PortInitEnd(pin,&GPIO_Initure);	
}

//复位指定引脚
void MCU_PortDeInit(MCU_PIN pin)
{
    if(pin <= MCU_PIN_A_15) HAL_GPIO_DeInit(GPIOA,MCU_PortCalcPinIndex(pin));
    else if(pin <= MCU_PIN_B_15)HAL_GPIO_DeInit(GPIOB,MCU_PortCalcPinIndex(pin));
    else if(pin <= MCU_PIN_C_15)HAL_GPIO_DeInit(GPIOC,MCU_PortCalcPinIndex(pin));
    else if(pin <= MCU_PIN_D_15)HAL_GPIO_DeInit(GPIOD,MCU_PortCalcPinIndex(pin));
    else if(pin <= MCU_PIN_E_15)HAL_GPIO_DeInit(GPIOE,MCU_PortCalcPinIndex(pin));
    else if(pin <= MCU_PIN_F_15)HAL_GPIO_DeInit(GPIOF,MCU_PortCalcPinIndex(pin));
    else if(pin <= MCU_PIN_G_15)HAL_GPIO_DeInit(GPIOG,MCU_PortCalcPinIndex(pin));
    else if(pin <= MCU_PIN_H_15)HAL_GPIO_DeInit(GPIOH,MCU_PortCalcPinIndex(pin));
    else if(pin <= MCU_PIN_I_15)HAL_GPIO_DeInit(GPIOI,MCU_PortCalcPinIndex(pin));
    else if(pin <= MCU_PIN_J_15)HAL_GPIO_DeInit(GPIOJ,MCU_PortCalcPinIndex(pin));
    else if(pin <= MCU_PIN_K_15)HAL_GPIO_DeInit(GPIOK,MCU_PortCalcPinIndex(pin));
}

//设置指定引脚的值
void MCU_PortWriteSingle(MCU_PIN pin,BitAction value)
{
    if(pin <= MCU_PIN_A_15) HAL_GPIO_WritePin(GPIOA,MCU_PortCalcPinIndex(pin),(GPIO_PinState)value);
    else if(pin <= MCU_PIN_B_15)HAL_GPIO_WritePin(GPIOB,MCU_PortCalcPinIndex(pin),(GPIO_PinState)value);
    else if(pin <= MCU_PIN_C_15)HAL_GPIO_WritePin(GPIOC,MCU_PortCalcPinIndex(pin),(GPIO_PinState)value);
    else if(pin <= MCU_PIN_D_15)HAL_GPIO_WritePin(GPIOD,MCU_PortCalcPinIndex(pin),(GPIO_PinState)value);
    else if(pin <= MCU_PIN_E_15)HAL_GPIO_WritePin(GPIOE,MCU_PortCalcPinIndex(pin),(GPIO_PinState)value);
    else if(pin <= MCU_PIN_F_15)HAL_GPIO_WritePin(GPIOF,MCU_PortCalcPinIndex(pin),(GPIO_PinState)value);
    else if(pin <= MCU_PIN_G_15)HAL_GPIO_WritePin(GPIOG,MCU_PortCalcPinIndex(pin),(GPIO_PinState)value);
    else if(pin <= MCU_PIN_H_15)HAL_GPIO_WritePin(GPIOH,MCU_PortCalcPinIndex(pin),(GPIO_PinState)value);
    else if(pin <= MCU_PIN_I_15)HAL_GPIO_WritePin(GPIOI,MCU_PortCalcPinIndex(pin),(GPIO_PinState)value);
    else if(pin <= MCU_PIN_J_15)HAL_GPIO_WritePin(GPIOJ,MCU_PortCalcPinIndex(pin),(GPIO_PinState)value);
    else if(pin <= MCU_PIN_K_15)HAL_GPIO_WritePin(GPIOK,MCU_PortCalcPinIndex(pin),(GPIO_PinState)value);
}

//读取指定引脚的值
BitAction MCU_PortReadSingle(MCU_PIN pin)
{
    GPIO_PinState pinState;
    if(pin <= MCU_PIN_A_15)pinState = HAL_GPIO_ReadPin(GPIOA,MCU_PortCalcPinIndex(pin));
    else if(pin <= MCU_PIN_B_15)pinState = HAL_GPIO_ReadPin(GPIOB,MCU_PortCalcPinIndex(pin));
    else if(pin <= MCU_PIN_C_15)pinState = HAL_GPIO_ReadPin(GPIOC,MCU_PortCalcPinIndex(pin));
    else if(pin <= MCU_PIN_D_15)pinState = HAL_GPIO_ReadPin(GPIOD,MCU_PortCalcPinIndex(pin));
    else if(pin <= MCU_PIN_E_15)pinState = HAL_GPIO_ReadPin(GPIOE,MCU_PortCalcPinIndex(pin));
    else if(pin <= MCU_PIN_F_15)pinState = HAL_GPIO_ReadPin(GPIOF,MCU_PortCalcPinIndex(pin));
    else if(pin <= MCU_PIN_G_15)pinState = HAL_GPIO_ReadPin(GPIOG,MCU_PortCalcPinIndex(pin));
    else if(pin <= MCU_PIN_H_15)pinState = HAL_GPIO_ReadPin(GPIOH,MCU_PortCalcPinIndex(pin));
    else if(pin <= MCU_PIN_I_15)pinState = HAL_GPIO_ReadPin(GPIOI,MCU_PortCalcPinIndex(pin));
    else if(pin <= MCU_PIN_J_15)pinState = HAL_GPIO_ReadPin(GPIOJ,MCU_PortCalcPinIndex(pin));
    else if(pin <= MCU_PIN_K_15)pinState = HAL_GPIO_ReadPin(GPIOK,MCU_PortCalcPinIndex(pin));
    //转换为基础信号
    return (pinState == GPIO_PIN_RESET)?Bit_RESET:Bit_SET;
}

//翻转指定引脚的值
void MCU_PortToogleSingle(MCU_PIN pin)
{
    if(pin <= MCU_PIN_A_15) HAL_GPIO_TogglePin(GPIOA,MCU_PortCalcPinIndex(pin));
    else if(pin <= MCU_PIN_B_15)HAL_GPIO_TogglePin(GPIOB,MCU_PortCalcPinIndex(pin));
    else if(pin <= MCU_PIN_C_15)HAL_GPIO_TogglePin(GPIOC,MCU_PortCalcPinIndex(pin));
    else if(pin <= MCU_PIN_D_15)HAL_GPIO_TogglePin(GPIOD,MCU_PortCalcPinIndex(pin));
    else if(pin <= MCU_PIN_E_15)HAL_GPIO_TogglePin(GPIOE,MCU_PortCalcPinIndex(pin));
    else if(pin <= MCU_PIN_F_15)HAL_GPIO_TogglePin(GPIOF,MCU_PortCalcPinIndex(pin));
    else if(pin <= MCU_PIN_G_15)HAL_GPIO_TogglePin(GPIOG,MCU_PortCalcPinIndex(pin));
    else if(pin <= MCU_PIN_H_15)HAL_GPIO_TogglePin(GPIOH,MCU_PortCalcPinIndex(pin));
    else if(pin <= MCU_PIN_I_15)HAL_GPIO_TogglePin(GPIOI,MCU_PortCalcPinIndex(pin));
    else if(pin <= MCU_PIN_J_15)HAL_GPIO_TogglePin(GPIOJ,MCU_PortCalcPinIndex(pin));
    else if(pin <= MCU_PIN_K_15)HAL_GPIO_TogglePin(GPIOK,MCU_PortCalcPinIndex(pin));
}

//中断回调函数指针数组
static MCU_Exti_CallBackFuncPtr extiCallBackArray[16] = {NULL};
//通过计算出来的终端序号寻找中断通道
static const IRQn_Type extiIrqChannelArray[16] = {EXTI0_IRQn,EXTI1_IRQn,EXTI2_IRQn,EXTI3_IRQn,EXTI4_IRQn,EXTI9_5_IRQn,EXTI9_5_IRQn,EXTI9_5_IRQn,
                                                    EXTI9_5_IRQn,EXTI9_5_IRQn,EXTI15_10_IRQn,EXTI15_10_IRQn,EXTI15_10_IRQn,EXTI15_10_IRQn,EXTI15_10_IRQn,EXTI15_10_IRQn};

//计算端口的中断序号
static uint8_t MCU_PortExtiCalcIndex(MCU_PIN pin)
{
    uint8_t modValue = (pin%16);
    return modValue;
}

//初始化指定引脚为中断引脚
void MCU_PortExtiInit(MCU_PIN pin,MCU_EXTI_MODE extiMode,MCU_PORT_PULL pullType,MCU_PORT_SPEED speed,NVIC_INT_PRE_PRI preePri,NVIC_INT_SUB_PRI subPri,MCU_Exti_CallBackFuncPtr callBackFuncPtr)
{
    //初始化端口为中断端口
        MCU_PortInit(pin,(MCU_PORT_MODE)extiMode,pullType,speed,0);
    //H7的PA0和PA0_C共用EXTI0外部中断源，且是两个独立的焊盘，通过一个模拟开关连接到片上外设，为了避免干扰，使用时需要切换
        if(pin == MCU_PIN_A_0)
        {
            HAL_SYSCFG_AnalogSwitchConfig(SYSCFG_SWITCH_PA0, SYSCFG_SWITCH_PA0_CLOSE);
        }
    //计算中断序号
        uint8_t index = MCU_PortExtiCalcIndex(pin);
    //设置中断优先级
        HAL_NVIC_SetPriority(extiIrqChannelArray[index], preePri, subPri);
	/* 使能中断 */
	    HAL_NVIC_EnableIRQ(extiIrqChannelArray[index]);
    //设置中断回调函数
        extiCallBackArray[index] = callBackFuncPtr;
}

//HAL库事件回调
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    uint16_t pinIndex = 0;
    //计算序号
    do
    {
        GPIO_Pin >>= 1;
        if(GPIO_Pin != 0)pinIndex += 1;
        else break;
    }while(1);
    //调用回调函数
    if(extiCallBackArray[pinIndex] != NULL)
    {
        extiCallBackArray[pinIndex]();
    }
}


//中断函数
void EXTI0_IRQHandler(void)
{
    //中断内核感知,需要
    CPU_SR_ALLOC();
    CPU_CRITICAL_ENTER();
    //此时要禁止操作系统调度打断中断
    OSIntEnter();
    //关闭了就要打开
    CPU_CRITICAL_EXIT();
    //调用HAL库中断
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
    //退出中断,启用调度
    OSIntExit();
}
//中断函数
void EXTI1_IRQHandler(void)
{
    //中断内核感知,需要
    CPU_SR_ALLOC();
    CPU_CRITICAL_ENTER();
    //此时要禁止操作系统调度打断中断
    OSIntEnter();
    //关闭了就要打开
    CPU_CRITICAL_EXIT();
    //调用HAL库中断
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
    //退出中断,启用调度
    OSIntExit();
}
//中断函数
void EXTI2_IRQHandler(void)
{
    //中断内核感知,需要
    CPU_SR_ALLOC();
    CPU_CRITICAL_ENTER();
    //此时要禁止操作系统调度打断中断
    OSIntEnter();
    //关闭了就要打开
    CPU_CRITICAL_EXIT();
    //调用HAL库中断
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);
    //退出中断,启用调度
    OSIntExit();
}
//中断函数
void EXTI3_IRQHandler(void)
{
    //中断内核感知,需要
    CPU_SR_ALLOC();
    CPU_CRITICAL_ENTER();
    //此时要禁止操作系统调度打断中断
    OSIntEnter();
    //关闭了就要打开
    CPU_CRITICAL_EXIT();
    //调用HAL库中断
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3);
    //退出中断,启用调度
    OSIntExit();
}
//中断函数
void EXTI4_IRQHandler(void)
{
    //中断内核感知,需要
    CPU_SR_ALLOC();
    CPU_CRITICAL_ENTER();
    //此时要禁止操作系统调度打断中断
    OSIntEnter();
    //关闭了就要打开
    CPU_CRITICAL_EXIT();
    //调用HAL库中断
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);
    //退出中断,启用调度
    OSIntExit();
}
//中断函数
void EXTI9_5_IRQHandler(void)
{
    //中断内核感知,需要
    CPU_SR_ALLOC();
    CPU_CRITICAL_ENTER();
    //此时要禁止操作系统调度打断中断
    OSIntEnter();
    //关闭了就要打开
    CPU_CRITICAL_EXIT();
    //调用HAL库中断
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_5);
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_6);
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_7);
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_8);
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_9);
    //退出中断,启用调度
    OSIntExit();
}
//中断函数
void EXTI15_10_IRQHandler(void)
{
    //中断内核感知,需要
    CPU_SR_ALLOC();
    CPU_CRITICAL_ENTER();
    //此时要禁止操作系统调度打断中断
    OSIntEnter();
    //关闭了就要打开
    CPU_CRITICAL_EXIT();
    //调用HAL库中断
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_10);
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_11);
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_12);
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_14);
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_15);
    //退出中断,启用调度
    OSIntExit();
}
