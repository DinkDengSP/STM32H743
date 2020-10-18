/*******************************************************************
**Description: Copyright(c) 2018-2090 DengXiaojun,All rights reserved.
**Author: DengXiaoJun
**Date: 2020-10-18 15:12:09
**LastEditors: DengXiaoJun
**LastEditTime: 2020-10-18 15:14:39
**FilePath: \ProjectFilesd:\DinkGitHub\STM32H743\BoardArmfly\uCOSIII_App\Code\Driver\DriverMCU\MCU_UartInt.c
**ModifyRecord1:    
******************************************************************/
#include "MCU_Uart.h"

//串口回调函数,接收完成中断
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
{
    if(UartHandle->Instance == USART1)
    {
        //串口1接收中断
        MCU_UART1_RxCpltCallback(UartHandle);
    }
}

//串口发送完成事件处理
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandle)
{
    if(UartHandle->Instance == USART1)
    {
        //串口1接收中断
        MCU_UART1_TxCpltCallback(UartHandle);
    }
}




