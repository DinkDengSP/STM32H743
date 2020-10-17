/*******************************************************************
**Description: Copyright(c) 2018-2090 DengXiaojun,All rights reserved.
**Author: DengXiaoJun
**Date: 2020-10-17 00:25:29
**LastEditors: DengXiaoJun
**LastEditTime: 2020-10-17 23:01:29
**FilePath: \ProjectFilesd:\DinkGitHub\STM32H743\BoardArmfly\uCOSIII_App\Code\Driver\DriverMCU\MCU_Random.c
**ModifyRecord1:    
******************************************************************/
#include "MCU_Random.h"
//RNG句柄
RNG_HandleTypeDef RNG_Handler;  

//随机数初始化
void MCU_RandomInit(void)
{
    RCC_PeriphCLKInitTypeDef RNGClkInitStruct;
	//设置RNG时钟源，选择PLL，时钟为400MHz
	RNGClkInitStruct.PeriphClockSelection=RCC_PERIPHCLK_RNG;  
    //RNG时钟源选择PLL	
	RNGClkInitStruct.RngClockSelection=RCC_RNGCLKSOURCE_PLL;	
    //配置时钟
	HAL_RCCEx_PeriphCLKConfig(&RNGClkInitStruct);
	//使能时钟
	__HAL_RCC_RNG_CLK_ENABLE();
    //设定
    RNG_Handler.Instance=RNG;  
    //复位 
    HAL_RNG_DeInit(&RNG_Handler);
    //初始化RNG
    HAL_RNG_Init(&RNG_Handler);
    //等待RNG准备就绪
    while(__HAL_RNG_GET_FLAG(&RNG_Handler,RNG_FLAG_DRDY)==RESET)
    {
        asm("nop");
    }
}

//得到随机数
uint32_t MCU_RandomGetNext(void)
{
    OS_ERR  p_err;
    uint32_t randomnum;
    //锁定
    OSSchedLock(&p_err);
    //生成随机数
    HAL_RNG_GenerateRandomNumber(&RNG_Handler,&randomnum);
    //解锁
    OSSchedUnlock(&p_err);
    //返回数据
	return randomnum;
}

//生成指定范围的随机数
int MCU_RandomGetNextRange(int min, int max)
{
    //此处其实并不是真的随机数发生器,运算不正确
    return MCU_RandomGetNext() % (max - min + 1) + min;
}

//正确计算随机数的方法
int MCU_RandomGetNextRangeReal(int min, int max)
{
    if (max <= min)
        return 0;
    else
    {
        //基础值
        uint32_t baseResult = MCU_RandomGetNext();
        //将取得的值在32位数据中计算到的位置计算出来,阈值在1
        //然后根据本次阈值扩张,然后取整
        uint32_t rangeBase = (uint32_t)((max - min) * (((double)baseResult) / ((double)UINT32_MAX)));
        //最后确定符号位
        return (int)(min + rangeBase);
    }
}




