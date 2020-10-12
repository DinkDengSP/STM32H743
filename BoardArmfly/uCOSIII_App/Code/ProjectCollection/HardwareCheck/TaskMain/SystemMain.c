#include "stm32h7xx_hal.h"

//板上时钟初始化申明
void BoardSystemClockInit(void);

int main(void)
{
    //STM32H7xx HAL 库初始化，此时系统用的还是H7自带的64MHz，HSI时钟:
    //1. 调用函数HAL_InitTick，初始化滴答时钟中断1ms。
    //2. 设置NVIV优先级分组4
	    HAL_Init();
    //重新设置系统中断优先级分组
        CoreNVIC_SetGroupDefault();
    //初始化系统时钟
        BoardSystemClockInit();
    //初始化延时系统
        CoreDelayInit();
    while(1)
    {
        asm("nop");
    }
}


/*
*********************************************************************************************************
*	函 数 名: BoardBaseSystemClockInit
*	功能说明: 初始化系统时钟
*            	System Clock source            = PLL (HSE)
*            	SYSCLK(Hz)                     = 400000000 (CPU Clock)
*           	HCLK(Hz)                       = 200000000 (AXI and AHBs Clock)
*            	AHB Prescaler                  = 2
*            	D1 APB3 Prescaler              = 2 (APB3 Clock  100MHz)
*            	D2 APB1 Prescaler              = 2 (APB1 Clock  100MHz)
*            	D2 APB2 Prescaler              = 2 (APB2 Clock  100MHz)
*            	D3 APB4 Prescaler              = 2 (APB4 Clock  100MHz)
*            	HSE Frequency(Hz)              = 25000000
*           	PLL_M                          = 5
*            	PLL_N                          = 160
*            	PLL_P                          = 2
*            	PLL_Q                          = 4
*            	PLL_R                          = 2
*            	VDD(V)                         = 3.3
*            	Flash Latency(WS)              = 4
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void BoardSystemClockInit(void)
{
    //初始化需要的结构体
        RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
        RCC_OscInitTypeDef RCC_OscInitStruct = {0};
        HAL_StatusTypeDef ret = HAL_OK;
	/* 锁住SCU(Supply configuration update) */
	    MODIFY_REG(PWR->CR3, PWR_CR3_SCUEN, 0);
	//1、芯片内部的LDO稳压器输出的电压范围，可选VOS1，VOS2和VOS3，不同范围对应不同的Flash读速度，详情看参考手册的Table 12的表格。
    //2、这里选择使用VOS1，电压范围1.15V - 1.26V。
	    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
    //等待系统电压稳定
	    while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}
	/* 使能HSE，并选择HSE作为PLL时钟源 */
        RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
        RCC_OscInitStruct.HSEState = RCC_HSE_ON;
        RCC_OscInitStruct.HSIState = RCC_HSI_OFF;
        RCC_OscInitStruct.CSIState = RCC_CSI_OFF;
        RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
        RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	//配置PLL锁相环的配置 
    //pllm:PLL1 预分频系数(进PLL 之前的分频),取值范围:2~63.  25/5=5M
        RCC_OscInitStruct.PLL.PLLM = 5;
    //plln:PLL1 倍频系数(PLL 倍频),取值范围:4~512.  5*160 = 800M
        RCC_OscInitStruct.PLL.PLLN = 160;
    //pllp:PLL1 的p分频系数(PLL 之后的分频),分频后作为系统时钟,取值范围:2~128 800/2 = 400M
        RCC_OscInitStruct.PLL.PLLP = 2;
    //pllr:PLL1 的r分频系数(PLL 之后的分频),分频后作为系统时钟,取值范围:2~128 800/2 = 400M
        RCC_OscInitStruct.PLL.PLLR = 2;
    //pllq:PLL1 的q 分频系数(PLL 之后的分频),取值范围:1~128. 800/4 = 200M
        RCC_OscInitStruct.PLL.PLLQ = 4;		
	//开始初始化PLL锁相环
    //设置调压器输出电压级别,级别数值越小工作频率越高，所以如果我们要配置 H7 的主频为 400MHz，那么我们必须
    //配置调压器输出电压级别VOS 为级别1
        RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
        RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_2;	
        ret = HAL_RCC_OscConfig(&RCC_OscInitStruct);
        if(ret != HAL_OK)
        {
            while(1);
        }
	//选择PLL的输出作为系统时钟
    //配置RCC_CLOCKTYPE_SYSCLK系统时钟
    //配置RCC_CLOCKTYPE_HCLK 时钟，对应AHB1，AHB2，AHB3和AHB4总线
    //配置RCC_CLOCKTYPE_PCLK1时钟，对应APB1总线
    //配置RCC_CLOCKTYPE_PCLK2时钟，对应APB2总线
    //配置RCC_CLOCKTYPE_D1PCLK1时钟，对应APB3总线
    //配置RCC_CLOCKTYPE_D3PCLK1时钟，对应APB4总线  
	    RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_D1PCLK1 | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2  | RCC_CLOCKTYPE_D3PCLK1);
    //系统时钟就是锁相环时钟 400MHZ
	    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	    RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
    //HCLK为系统时钟2分频 200MHZ
	    RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
    //APB1 2 3 4均从AHB二分瓶 100MHZ
    //定时器的时钟都是在D2域进行控制，而且当 D2PPRE1或 D2PPRE2 的分频系数不为1的时候，定时器的时钟频率为rcc_pclk1或rcc_pclk2的2倍,也就是200MHZ定时器
        RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;  
        RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2; 
        RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2; 
        RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2; 
	/* 此函数会更新SystemCoreClock，并重新配置HAL_InitTick,同时设置Flash访问周期为4 */
        ret = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4);
        if(ret != HAL_OK)
        {
            while(1);//配置失败,死循环
        }
    //使用IO的高速模式，要使能IO补偿，即调用下面三个函数 
    //使能CSI clock
    //使能SYSCFG clock
    //使能I/O补偿单元， 设置SYSCFG_CCCSR寄存器的bit0
	    __HAL_RCC_CSI_ENABLE() ;
    //系统配置时钟使能,该单元负责补偿
	    __HAL_RCC_SYSCFG_CLK_ENABLE();
    //使能IO补偿单元
	    HAL_EnableCompensationCell();
    /* AXI SRAM的时钟是上电自动使能的，而D2域的SRAM1，SRAM2和SRAM3要单独使能 */	
        __HAL_RCC_D2SRAM1_CLK_ENABLE();
        __HAL_RCC_D2SRAM2_CLK_ENABLE();
        __HAL_RCC_D2SRAM3_CLK_ENABLE();
}