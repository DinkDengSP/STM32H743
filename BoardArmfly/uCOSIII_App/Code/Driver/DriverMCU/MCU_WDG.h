/*******************************************************************
 *Description: Copyright(c) 2018-2090 DengXiaojun,All rights reserved.
 *Author: DengXiaoJun
 *Date: 2020-10-17 00:28:18
 *LastEditors: DengXiaoJun
 *LastEditTime: 2020-10-17 23:46:08
 *FilePath: \ProjectFilesd:\DinkGitHub\STM32H743\BoardArmfly\uCOSIII_App\Code\Driver\DriverMCU\MCU_WDG.h
 *ModifyRecord1:    
******************************************************************/
#ifndef __MCU_WDG_H_
#define __MCU_WDG_H_
#include "MCU_Common.h"

//独立看门狗初始化
//MCU_IWDG_Init(IWDG_PRESCALER_64 ,625)
//IWDG 1s 超时溢出 （64/40）*625 = 1s	
void MCU_IWDG_Init(uint8_t prv, uint16_t rlv);

//独立看门狗喂狗,打开之后必须定时喂狗
void MCU_IWDG_Feed(void);



//保存WWDG计数器的设置值,默认为最大.
#define WWDG_CNT_MAX         0X7F

//窗口看门狗中断回调函数,该函数不得调用系统API
typedef void (*MCU_WWDG_CallBackFunc)(void);

//窗口看门狗打开
//MCU_WDG_WindowInit(127,80,WWDG_PRESCALER_8,NULL); 
//窗口时间为608 * (127-80) = 28.6ms < 刷新窗口 < ~608 * 64 = 38.9ms
//也就是说调用WWDG_Config进行这样的配置，若在之后的28.6ms前喂狗，
//系统会复位，在38.9ms后没有喂狗，系统也会复位。
//需要在刷新窗口的时间内喂狗，系统才不会复位。
void MCU_WWDG_Init(uint8_t tr, uint8_t wr, uint32_t fprer,MCU_WWDG_CallBackFunc callBack);

//窗口看门狗喂狗,在中断中喂狗,所以注意中断关闭的时间
void MCU_WWDG_Feed(void);


#endif




