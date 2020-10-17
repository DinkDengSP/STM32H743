/*******************************************************************
**Description: Copyright(c) 2018-2090 DengXiaojun,All rights reserved.
**Author: DengXiaoJun
**Date: 2020-10-17 00:28:10
**LastEditors: DengXiaoJun
**LastEditTime: 2020-10-17 23:49:16
**FilePath: \ProjectFilesd:\DinkGitHub\STM32H743\BoardArmfly\uCOSIII_App\Code\Driver\DriverMCU\MCU_WDG.c
**ModifyRecord1:    
******************************************************************/
#include "MCU_WDG.h"

//独立看门狗句柄
static IWDG_HandleTypeDef IWDG_Handle;

/*
 * 设置 IWDG 的超时时间
 * Tout = prv/40 * rlv (s)
 *      prv可以是[4,8,16,32,64,128,256]
 * prv:预分频器值，取值如下：
 *     @arg IWDG_PRESCALER_4: IWDG prescaler set to 4
 *     @arg IWDG_PRESCALER_8: IWDG prescaler set to 8
 *     @arg IWDG_PRESCALER_16: IWDG prescaler set to 16
 *     @arg IWDG_PRESCALER_32: IWDG prescaler set to 32
 *     @arg IWDG_PRESCALER_64: IWDG prescaler set to 64
 *     @arg IWDG_PRESCALER_128: IWDG prescaler set to 128
 *     @arg IWDG_PRESCALER_256: IWDG prescaler set to 256
 *
 *		独立看门狗使用LSI作为时钟。
 *		LSI 的频率一般在 30~60KHZ 之间，根据温度和工作场合会有一定的漂移，我
 *		们一般取 40KHZ，所以独立看门狗的定时时间并一定非常精确，只适用于对时间精度
 *		要求比较低的场合。
 *
 * rlv:预分频器值，取值范围为：0-0XFFF
 * 函数调用举例：
 * MCU_IWDG_Init(IWDG_PRESCALER_64 ,625);  // IWDG 1s 超时溢出 （64/40）*625 = 1s					
 */
void MCU_IWDG_Init(uint8_t prv, uint16_t rlv)
{
    IWDG_Handle.Instance = IWDG1;
	// 设置预分频器值
	IWDG_Handle.Init.Prescaler = prv;
	// 设置重装载寄存器值
	IWDG_Handle.Init.Reload = rlv;
	// 设置要与向下计数器进行比较的窗口值
	IWDG_Handle.Init.Window = IWDG_WINDOW_DISABLE;
	// 初始化IWDG
	HAL_IWDG_Init(&IWDG_Handle);	
	// 启动 IWDG
	__HAL_IWDG_START(&IWDG_Handle);
}

//独立看门狗喂狗,打开之后必须定时喂狗
void MCU_IWDG_Feed(void)
{
    // 把重装载寄存器的值放到计数器中，喂狗，防止IWDG复位
	// 当计数器的值减到0的时候会产生系统复位
	HAL_IWDG_Refresh(&IWDG_Handle);
}




//窗口看门狗句柄
static WWDG_HandleTypeDef WWDG_Handle;
//窗口看门狗提前中断回调函数
static MCU_WWDG_CallBackFunc wwdgCallBack = NULL;


/* WWDG 配置函数
 * tr ：递减计时器的值， 取值范围为：0x7f~0x40，超出范围会直接复位
 * wr ：窗口值，取值范围为：0x7f~0x40
 * prv：预分频器值，取值可以是
 * @arg WWDG_PRESCALER_1: WWDG counter clock = (PCLK1(54MHz)/4096)/1   
	 约13184 76us
 * @arg WWDG_PRESCALER_2: WWDG counter clock = (PCLK1(54MHz)/4096)/2	 
	 约6592Hz 152us
 * @arg WWDG_PRESCALER_4: WWDG counter clock = (PCLK1(54MHz)/4096)/4	 
	 约3296Hz 304us
 * @arg WWDG_PRESCALER_8: WWDG counter clock = (PCLK1(54MHz)/4096)/8   
   约1648Hz	608us
 *      
 * 例：tr = 127(0x7f，tr的最大值)  
 *     wr = 80（0x50, 0x40为最小wr最小值）  
 *	  prv = WWDG_PRESCALER_8
 * 窗口时间为608 * (127-80) = 28.6ms < 刷新窗口 < ~608 * 64 = 38.9ms
 * 也就是说调用WWDG_Config进行这样的配置，若在之后的28.6ms前喂狗，
 * 系统会复位，在38.9ms后没有喂狗，系统也会复位。
 * 需要在刷新窗口的时间内喂狗，系统才不会复位。	
*/
void MCU_WWDG_Init(uint8_t tr, uint8_t wr, uint32_t fprer,MCU_WWDG_CallBackFunc callBack)
{
    //开启 WWDG 时钟
	__HAL_RCC_WWDG1_CLK_ENABLE();
	// 配置WWDG中断优先级
	HAL_NVIC_SetPriority(WWDG_IRQn,MCU_WDG_WINDOW_PREE_PRI,MCU_WDG_WINDOW_SUB_PRI);
	HAL_NVIC_EnableIRQ(WWDG_IRQn);
	// 配置WWDG句柄即寄存器基地址
	WWDG_Handle.Instance = WWDG1;
	// 设置预分频器值
	WWDG_Handle.Init.Prescaler = fprer;
	// 设置上窗口值
	WWDG_Handle.Init.Window = wr;	
	// 设置计数器的值
	WWDG_Handle.Init.Counter = tr;
	// 使能提前唤醒中断
	WWDG_Handle.Init.EWIMode = WWDG_EWI_ENABLE;
	// 初始化WWDG
	HAL_WWDG_Init(&WWDG_Handle);
    //提前中断回调函数
    wwdgCallBack = callBack;
}

//窗口看门狗喂狗,在中断中喂狗,所以注意中断关闭的时间
void MCU_WWDG_Feed(void)
{
	uint8_t wwdg_tr;
	wwdg_tr = WWDG1->CR & 0X7F;
	if(wwdg_tr <= WWDG_Handle.Init.Window)
	{
		// 喂狗，刷新递减计数器的值，设置成最大WDG_CNT=0X7F
		HAL_WWDG_Refresh(&WWDG_Handle);
	}
}

//窗口看门狗中断服务程序
void WWDG_IRQHandler(void)
{
	HAL_WWDG_IRQHandler(&WWDG_Handle);
	HAL_WWDG_Refresh(&WWDG_Handle);
}

//回调函数
void HAL_WWDG_EarlyWakeupCallback(WWDG_HandleTypeDef *hwwdg)
{
	if(wwdgCallBack != NULL)
	{
		wwdgCallBack();
	}
}





