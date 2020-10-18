/*******************************************************************
**Description: Copyright(c) 2018-2090 DengXiaojun,All rights reserved.
**Author: DengXiaoJun
**Date: 2020-10-13 22:29:49
**LastEditors: DengXiaoJun
**LastEditTime: 2020-10-18 20:50:43
**FilePath: \ProjectFilesd:\DinkGitHub\STM32H743\BoardArmfly\uCOSIII_App\Code\Driver\DriverBoard\BoardExtPort.c
**ModifyRecord1:    
******************************************************************/
#include "BoardExtPort.h"


//定义扩展IO的口
#define  EXT_PORT	 *(uint32_t *)0x60001000
//定义扩展IO的状态,保存扩展IO状态
static volatile uint32_t extPortState;	
//端口互斥信号量
static OS_MUTEX mutexBoardExtPort;

//配置FMC响应的管脚为复用功能
//安富莱STM32-H7开发板接线方法：4片74HC574挂在FMC 32位总线上。1个地址端口可以扩展出32个IO
static void BoardExtPort_GPIO_Config(void)
{
	/* 使能FMC时钟 */
	    __HAL_RCC_FMC_CLK_ENABLE();		
	//PD14 FMC_D0
		MCU_PortInit(MCU_PIN_D_14,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
	//PD15 FMC_D1
		MCU_PortInit(MCU_PIN_D_15,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
	//PD0 FMC_D2
		MCU_PortInit(MCU_PIN_D_0,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
	//PD1 FMC_D3
		MCU_PortInit(MCU_PIN_D_1,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
	//PE7 FMC_D4
		MCU_PortInit(MCU_PIN_E_7,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
	//PE8 FMC_D5
		MCU_PortInit(MCU_PIN_E_8,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
	//PE9 FMC_D6
		MCU_PortInit(MCU_PIN_E_9,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
	//PE10 FMC_D7
		MCU_PortInit(MCU_PIN_E_10,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
	//PE11 FMC_D8
		MCU_PortInit(MCU_PIN_E_11,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
	//PE12 FMC_D9
		MCU_PortInit(MCU_PIN_E_12,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
	//PE13 FMC_D10
		MCU_PortInit(MCU_PIN_E_13,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
	//PE14 FMC_D11
		MCU_PortInit(MCU_PIN_E_14,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
	//PE15 FMC_D12
		MCU_PortInit(MCU_PIN_E_15,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
	//PD8 FMC_D13
		MCU_PortInit(MCU_PIN_D_8,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
	//PD9 FMC_D14
		MCU_PortInit(MCU_PIN_D_9,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
	//PD10 FMC_D15
		MCU_PortInit(MCU_PIN_D_10,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
	//PH8 FMC_D16
		MCU_PortInit(MCU_PIN_H_8,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
	//PH9 FMC_D17
		MCU_PortInit(MCU_PIN_H_9,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
	//PH10 FMC_D18
		MCU_PortInit(MCU_PIN_H_10,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
	//PH11 FMC_D19
		MCU_PortInit(MCU_PIN_H_11,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
	//PH12 FMC_D20
		MCU_PortInit(MCU_PIN_H_12,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
	//PH13 FMC_D21
		MCU_PortInit(MCU_PIN_H_13,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
	//PH14 FMC_D22
		MCU_PortInit(MCU_PIN_H_14,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
	//PH15 FMC_D23
		MCU_PortInit(MCU_PIN_H_15,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
	//PI0 FMC_D24
		MCU_PortInit(MCU_PIN_I_0,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
	//PI1 FMC_D25
		MCU_PortInit(MCU_PIN_I_1,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
	//PI2 FMC_D26
		MCU_PortInit(MCU_PIN_I_2,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
	//PI3 FMC_D27
		MCU_PortInit(MCU_PIN_I_3,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
	//PI6 FMC_D28
		MCU_PortInit(MCU_PIN_I_6,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
	//PI7 FMC_D29
		MCU_PortInit(MCU_PIN_I_7,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
	//PI9 FMC_D30
		MCU_PortInit(MCU_PIN_I_9,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
	//PI10 FMC_D31
		MCU_PortInit(MCU_PIN_I_10,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
	//PD4 FMC_NOE --读控制信号，OE = Output Enable ， N 表示低有效
		MCU_PortInit(MCU_PIN_D_4,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
	//PD5 FMC_NWE --写控制信号，AD7606 只有读，无写信号
		MCU_PortInit(MCU_PIN_D_5,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
	//PD7 FMC_NE1 --主片选（OLED, 74HC574, DM9000, AD7606）
		MCU_PortInit(MCU_PIN_D_7,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
	//PG0 FMC_A10 --- 和主片选FMC_NE2一起译码
		MCU_PortInit(MCU_PIN_G_0,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
	//PG1 FMC_A11 --- 和主片选FMC_NE2一起译码
		MCU_PortInit(MCU_PIN_G_1,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
}

//扩展IO的FMC配置
static void BoardExtPort_FMC_Config(void)
{
    //初始化需要的数据结构
        SRAM_HandleTypeDef hsram = {0};
        FMC_NORSRAM_TimingTypeDef SRAM_Timing = {0};
	//设置类型
        hsram.Instance  = FMC_NORSRAM_DEVICE;
        hsram.Extended  = FMC_NORSRAM_EXTENDED_DEVICE;
    /* FMC使用的HCLK3，主频240MHz，1个FMC时钟周期就是5ns */
	/* SRAM 总线时序配置 4-1-2-1-2-2 不稳定，5-2-2-1-2-2 稳定 */  
    //时序配置
        SRAM_Timing.AddressSetupTime       = 5;  /* 5*5ns=25ns，地址建立时间，范围0 -15个FMC时钟周期个数 */
        SRAM_Timing.AddressHoldTime        = 2;  /* 地址保持时间，配置为模式A时，用不到此参数 范围1 -15个时钟周期个数 */
        SRAM_Timing.DataSetupTime          = 2;  /* 2*5ns=10ns，数据保持时间，范围1 -255个时钟周期个数 */
        SRAM_Timing.BusTurnAroundDuration  = 1;  /* 此配置用不到这个参数 */
        SRAM_Timing.CLKDivision            = 2;  /* 此配置用不到这个参数 */
        SRAM_Timing.DataLatency            = 2;  /* 此配置用不到这个参数 */
        SRAM_Timing.AccessMode             = FMC_ACCESS_MODE_A; /* 配置为模式A */
    //模式配置
        hsram.Init.NSBank             = FMC_NORSRAM_BANK1;              /* 使用的BANK1，即使用的片选FMC_NE1 */
        hsram.Init.DataAddressMux     = FMC_DATA_ADDRESS_MUX_DISABLE;   /* 禁止地址数据复用 */
        hsram.Init.MemoryType         = FMC_MEMORY_TYPE_SRAM;           /* 存储器类型SRAM */
        hsram.Init.MemoryDataWidth    = FMC_NORSRAM_MEM_BUS_WIDTH_32;	/* 32位总线宽度 */
        hsram.Init.BurstAccessMode    = FMC_BURST_ACCESS_MODE_DISABLE;  /* 关闭突发模式 */
        hsram.Init.WaitSignalPolarity = FMC_WAIT_SIGNAL_POLARITY_LOW;   /* 用于设置等待信号的极性，关闭突发模式，此参数无效 */
        hsram.Init.WaitSignalActive   = FMC_WAIT_TIMING_BEFORE_WS;      /* 关闭突发模式，此参数无效 */
        hsram.Init.WriteOperation     = FMC_WRITE_OPERATION_ENABLE;     /* 用于使能或者禁止写保护 */
        hsram.Init.WaitSignal         = FMC_WAIT_SIGNAL_DISABLE;        /* 关闭突发模式，此参数无效 */
        hsram.Init.ExtendedMode       = FMC_EXTENDED_MODE_DISABLE;      /* 禁止扩展模式 */
        hsram.Init.AsynchronousWait   = FMC_ASYNCHRONOUS_WAIT_DISABLE;  /* 用于异步传输期间，使能或者禁止等待信号，这里选择关闭 */
        hsram.Init.WriteBurst         = FMC_WRITE_BURST_DISABLE;        /* 禁止写突发 */
        hsram.Init.ContinuousClock    = FMC_CONTINUOUS_CLOCK_SYNC_ONLY; /* 仅同步模式才做时钟输出 */
        hsram.Init.WriteFifo          = FMC_WRITE_FIFO_ENABLE;          /* 使能写FIFO */
	/* 初始化SRAM控制器 */
        if (HAL_SRAM_Init(&hsram, &SRAM_Timing, &SRAM_Timing) != HAL_OK)
        {
            while(1);
        }
}




//外部扩展端口初始化
void BoardExtPort_Init(void)
{
	OS_ERR err;
    //先初始化IO口
    BoardExtPort_GPIO_Config();
    //后初始化FMC
    BoardExtPort_FMC_Config();
    /* 将开发板一些片选，LED口设置为高 */
	extPortState = (uint32_t)(BOARD_EXT_PORT_PIN_NRF24L01_CE | BOARD_EXT_PORT_PIN_VS1053_XDCS);
	/* 写硬件端口，更改IO状态 */
	EXT_PORT = extPortState;	
	//初始化互斥信号量
	OSMutexCreate((OS_MUTEX*	)&mutexBoardExtPort,
				  (CPU_CHAR*	)"mutexBoardExtPort",
                  (OS_ERR*		)&err);
}

//扩展IO设置指定IO口
void BoardExtPort_SetPin(BOARD_EXT_PORT_INDEX pin, BitAction value)
{
	OS_ERR err;
	//申请互斥信号量
	if (OSRunning)OSMutexPend(&mutexBoardExtPort, 0, OS_OPT_PEND_BLOCKING, 0, &err);
	//数据转换
    if (value == Bit_RESET)
	{
		extPortState &= (~((uint32_t)pin));
	}
	else
	{
		extPortState |= ((uint32_t)pin);
	}
	//写入端口
	EXT_PORT = extPortState;
	//释放互斥信号量
	if (OSRunning)OSMutexPost(&mutexBoardExtPort, OS_OPT_POST_FIFO, &err);
}

//扩展IO读取指定IO口状态
BitAction BoardExtPort_GetPin(BOARD_EXT_PORT_INDEX pin)
{
	BitAction result;
	OS_ERR err;
	//申请互斥信号量
	if (OSRunning)OSMutexPend(&mutexBoardExtPort, 0, OS_OPT_PEND_BLOCKING, 0, &err);
	//数据读取并转换
    if (extPortState & ((uint32_t)pin))
	{
		result = Bit_SET;
	}
	else
	{
		result = Bit_RESET;
	}
	//释放互斥信号量
	if (OSRunning)OSMutexPost(&mutexBoardExtPort, OS_OPT_POST_FIFO, &err);
	return result;
}

//扩展IO翻转IO口状态
void BoardExtPort_TooglePin(BOARD_EXT_PORT_INDEX pin)
{
	OS_ERR err;
	//申请互斥信号量
	if (OSRunning)OSMutexPend(&mutexBoardExtPort, 0, OS_OPT_PEND_BLOCKING, 0, &err);
	//数据设置
    if (extPortState & ((uint32_t)pin))
	{
		extPortState &= (~((uint32_t)pin));
	}
	else
	{
		extPortState |= ((uint32_t)pin);
	}
	//数据写入
	EXT_PORT = extPortState;
	//释放互斥信号量
	if (OSRunning)OSMutexPost(&mutexBoardExtPort, OS_OPT_POST_FIFO, &err);
}

