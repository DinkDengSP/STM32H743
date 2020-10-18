#include "BoardSDRAM.h"

//时钟频率设置
#define SDRAM_CLOCK_PERIOD                  FMC_SDRAM_CLOCK_PERIOD_3
//指令超时时间
#define SDRAM_TIMEOUT                       ((uint32_t)0xFFFF)
/* SDRAM自刷新计数 */  
#define REFRESH_COUNT                       ((uint32_t)1230)    

/* SDRAM的参数配置 */
#define SDRAM_MODEREG_BURST_LENGTH_1             ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_LENGTH_2             ((uint16_t)0x0001)
#define SDRAM_MODEREG_BURST_LENGTH_4             ((uint16_t)0x0002)
#define SDRAM_MODEREG_BURST_LENGTH_8             ((uint16_t)0x0004)
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL      ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_TYPE_INTERLEAVED     ((uint16_t)0x0008)
#define SDRAM_MODEREG_CAS_LATENCY_2              ((uint16_t)0x0020)
#define SDRAM_MODEREG_CAS_LATENCY_3              ((uint16_t)0x0030)
#define SDRAM_MODEREG_OPERATING_MODE_STANDARD    ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE     ((uint16_t)0x0200)


//IS42S32800G接口初始化
static void BoardIS42IO_Init(void)
{
	/* 使能FMC时钟 */
	    __HAL_RCC_FMC_CLK_ENABLE();
    //控制信号
    //PG8 <-> FC_SDCLK 
        MCU_PortInit(MCU_PIN_G_8,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
    //PF11 <-> FMC_NRAS
        MCU_PortInit(MCU_PIN_F_11,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
    //PG15 <-> FMC_NCAS
        MCU_PortInit(MCU_PIN_G_15,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
    //PH2 <-> FMC_SDCKE0
        MCU_PortInit(MCU_PIN_H_2,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
    //PH3 <-> FMC_SDNE0 
        MCU_PortInit(MCU_PIN_H_3,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
    //PH5 <-> FMC_SDNW 
        MCU_PortInit(MCU_PIN_H_5,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
    //PE0 <-> FMC_NBL0  
        MCU_PortInit(MCU_PIN_E_0,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
    //PE1 <-> FMC_NBL1  
        MCU_PortInit(MCU_PIN_E_1,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
    //PI4 <-> FMC_NBL2  
        MCU_PortInit(MCU_PIN_I_4,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
    //PI5 <-> FMC_NBL3  
        MCU_PortInit(MCU_PIN_I_5,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
    //地址信号
    //PF0 <-> FMC_A0 
        MCU_PortInit(MCU_PIN_F_0,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
    //PF1 <-> FMC_A1 
        MCU_PortInit(MCU_PIN_F_1,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
    //PF2 <-> FMC_A2 
        MCU_PortInit(MCU_PIN_F_2,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
    //PF3 <-> FMC_A3
        MCU_PortInit(MCU_PIN_F_3,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
    //PF4 <-> FMC_A4 
        MCU_PortInit(MCU_PIN_F_4,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
    //PF5 <-> FMC_A5 
        MCU_PortInit(MCU_PIN_F_5,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
    //PF12 <-> FMC_A6 
        MCU_PortInit(MCU_PIN_F_12,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
    //PF13 <-> FMC_A7 
        MCU_PortInit(MCU_PIN_F_13,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
    //PF14 <-> FMC_A8 
        MCU_PortInit(MCU_PIN_F_14,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
    //PF15 <-> FMC_A9
        MCU_PortInit(MCU_PIN_F_15,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
    //PG0 <-> FMC_A10 
        MCU_PortInit(MCU_PIN_G_0,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
    //PG1 <-> FMC_A11   
        MCU_PortInit(MCU_PIN_G_1,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
    //PG4 <-> FMC_A14 
        MCU_PortInit(MCU_PIN_G_4,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
    //PG5 <-> FMC_A15
        MCU_PortInit(MCU_PIN_G_5,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
    //数据信号
    //PD14 <-> FMC_D0   
        MCU_PortInit(MCU_PIN_D_14,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
    //PD15 <-> FMC_D1
        MCU_PortInit(MCU_PIN_D_15,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
    //PD0 <-> FMC_D2 
        MCU_PortInit(MCU_PIN_D_0,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
    //PD1 <-> FMC_D3
        MCU_PortInit(MCU_PIN_D_1,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
    //PE7 <-> FMC_D4  
        MCU_PortInit(MCU_PIN_E_7,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
    //PE8 <-> FMC_D5 
        MCU_PortInit(MCU_PIN_E_8,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
    //PE9 <-> FMC_D6 
        MCU_PortInit(MCU_PIN_E_9,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
    //PE10 <-> FMC_D7 
        MCU_PortInit(MCU_PIN_E_10,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
    //PE11 <-> FMC_D8
        MCU_PortInit(MCU_PIN_E_11,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
    //PE12 <-> FMC_D9
        MCU_PortInit(MCU_PIN_E_12,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
    //PE13 <-> FMC_D10
        MCU_PortInit(MCU_PIN_E_13,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
    //PE14 <-> FMC_D11 
        MCU_PortInit(MCU_PIN_E_14,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
    //PE15 <-> FMC_D12  
        MCU_PortInit(MCU_PIN_E_15,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
    //PD8  <-> FMC_D13
        MCU_PortInit(MCU_PIN_D_8,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
    //PD9  <-> FMC_D14
        MCU_PortInit(MCU_PIN_D_9,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
    //PD10 <-> FMC_D15
        MCU_PortInit(MCU_PIN_D_10,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
    //PH8 <-> FMC_D16 
        MCU_PortInit(MCU_PIN_H_8,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
    //PH9 <-> FMC_D17 
        MCU_PortInit(MCU_PIN_H_9,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
    //PH10 <-> FMC_D18 
        MCU_PortInit(MCU_PIN_H_10,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
    //PH11 <-> FMC_D19    
        MCU_PortInit(MCU_PIN_H_11,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
    //PH12 <-> FMC_D20  
        MCU_PortInit(MCU_PIN_H_12,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
    //PH13 <-> FMC_D21 
        MCU_PortInit(MCU_PIN_H_13,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
    //PH14 <-> FMC_D22  
        MCU_PortInit(MCU_PIN_H_14,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
    //PH15 <-> FMC_D23 
        MCU_PortInit(MCU_PIN_H_15,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
    //PI0 <-> FMC_D24
        MCU_PortInit(MCU_PIN_I_0,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
    //PI1 <-> FMC_D25   
        MCU_PortInit(MCU_PIN_I_1,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
    //PI2 <-> FMC_D26  
        MCU_PortInit(MCU_PIN_I_2,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
    //PI3 <-> FMC_D27
        MCU_PortInit(MCU_PIN_I_3,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
    //PI6 <-> FMC_D28 
        MCU_PortInit(MCU_PIN_I_6,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
    //PI7 <-> FMC_D29  
        MCU_PortInit(MCU_PIN_I_7,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
    //PI9 <-> FMC_D30 
        MCU_PortInit(MCU_PIN_I_9,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
    //PI10 <-> FMC_D31 
        MCU_PortInit(MCU_PIN_I_10,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_FMC);
}

//IS42S32800G读写序列初始化
static void BoardIS42SequenceInit(SDRAM_HandleTypeDef *hsdram, FMC_SDRAM_CommandTypeDef *Command)
{
    __IO uint32_t tmpmrd =0;
    /*##-1- 时钟使能命令 ##################################################*/
        Command->CommandMode = FMC_SDRAM_CMD_CLK_ENABLE;
        Command->CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;;
        Command->AutoRefreshNumber = 1;
        Command->ModeRegisterDefinition = 0;
	    HAL_SDRAM_SendCommand(hsdram, Command, SDRAM_TIMEOUT);
    /*##-2- 插入延迟，至少100us ##################################################*/
	    HAL_Delay(1);
    /*##-3- 整个SDRAM预充电命令，PALL(precharge all) #############################*/
        Command->CommandMode = FMC_SDRAM_CMD_PALL;
        Command->CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
        Command->AutoRefreshNumber = 1;
        Command->ModeRegisterDefinition = 0;
	    HAL_SDRAM_SendCommand(hsdram, Command, SDRAM_TIMEOUT);
    /*##-4- 自动刷新命令 #######################################################*/
        Command->CommandMode = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
        Command->CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
        Command->AutoRefreshNumber = 8;
        Command->ModeRegisterDefinition = 0;
	    HAL_SDRAM_SendCommand(hsdram, Command, SDRAM_TIMEOUT);
    /*##-5- 配置SDRAM模式寄存器 ###############################################*/
        tmpmrd = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_1       |
                        SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL   |
                        SDRAM_MODEREG_CAS_LATENCY_3           |
                        SDRAM_MODEREG_OPERATING_MODE_STANDARD |
                        SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;
        Command->CommandMode = FMC_SDRAM_CMD_LOAD_MODE;
        Command->CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
        Command->AutoRefreshNumber = 1;
        Command->ModeRegisterDefinition = tmpmrd;
	    HAL_SDRAM_SendCommand(hsdram, Command, SDRAM_TIMEOUT);
    /*##-6- 设置自刷新率 ####################################################*/
    /*
        SDRAM refresh period / Number of rows）*SDRAM时钟速度 – 20
      = 64ms / 4096 *80MHz - 20
      = 1855 取值1855
    */
	    HAL_SDRAM_ProgramRefreshRate(hsdram, REFRESH_COUNT); 
}

//sdram初始化
void BoardSDRAM_Init(void)
{
    //需要使用的数据结构r
        SDRAM_HandleTypeDef      hsdram = {0};
        FMC_SDRAM_TimingTypeDef  SDRAM_Timing = {0};
        FMC_SDRAM_CommandTypeDef command = {0};
	/* FMC SDRAM所涉及到GPIO配置 */
	    BoardIS42IO_Init();
	/* SDRAM配置 */
	    hsdram.Instance = FMC_SDRAM_DEVICE;
	//FMC使用的HCLK3时钟，240MHz，用于SDRAM的话，至少3分频，也就是80MHz，即1个SDRAM时钟周期是12.5ns,下面参数单位均为12.5ns。
        SDRAM_Timing.LoadToActiveDelay    = 2; /* 12.5*2ns, TMRD定义加载模式寄存器的命令与激活命令或刷新命令之间的延迟 */
        SDRAM_Timing.ExitSelfRefreshDelay = 7; /* 12.5*7ns, TXSR定义从发出自刷新命令到发出激活命令之间的延迟 */
        SDRAM_Timing.SelfRefreshTime      = 4; /* 12.5*5ns, TRAS定义最短的自刷新周期 */
        SDRAM_Timing.RowCycleDelay        = 7; /* 12.5*7ns, TRC定义刷新命令和激活命令之间的延迟 */
        SDRAM_Timing.WriteRecoveryTime    = 2; /* 12.5*2ns, TWR定义在写命令和预充电命令之间的延迟 */
        SDRAM_Timing.RPDelay              = 2; /* 12.5*2ns, TRP定义预充电命令与其它命令之间的延迟 */
        SDRAM_Timing.RCDDelay             = 2; /* 12.5*2ns, TRCD定义激活命令与读/写命令之间的延迟 */
    //BANK1的设置
        hsdram.Init.SDBank             = FMC_SDRAM_BANK1;               /* 硬件设计上用的BANK1 */
        hsdram.Init.ColumnBitsNumber   = FMC_SDRAM_COLUMN_BITS_NUM_9;   /* 9列 */
        hsdram.Init.RowBitsNumber      = FMC_SDRAM_ROW_BITS_NUM_12;     /* 12行 */
        hsdram.Init.MemoryDataWidth    = FMC_SDRAM_MEM_BUS_WIDTH_32;	/* 32位带宽 */
        hsdram.Init.InternalBankNumber = FMC_SDRAM_INTERN_BANKS_NUM_4;  /* SDRAM有4个BANK */
        hsdram.Init.CASLatency         = FMC_SDRAM_CAS_LATENCY_3;       /* CAS Latency可以设置Latency1，2和3，实际测试Latency3稳定 */
        hsdram.Init.WriteProtection    = FMC_SDRAM_WRITE_PROTECTION_DISABLE; /* 禁止写保护 */
        hsdram.Init.SDClockPeriod      = SDRAM_CLOCK_PERIOD;            /* FMC时钟240MHz，3分频后给SDRAM，即80MHz */
        hsdram.Init.ReadBurst          = FMC_SDRAM_RBURST_ENABLE;       /* 使能读突发 */
        hsdram.Init.ReadPipeDelay      = FMC_SDRAM_RPIPE_DELAY_0;       /* 此位定CAS延时后延后多少个SDRAM时钟周期读取数据，实际测此位可以设置无需延迟 */
	/* 配置SDRAM控制器基本参数 */
	    HAL_SDRAM_Init(&hsdram, &SDRAM_Timing);
	/* 完成SDRAM序列初始化 */
	    BoardIS42SequenceInit(&hsdram, &command);
}

//读取指定区域指定长度内存
D_ERR BoardSDRAM_ReadBuffer(uint32_t baseAddr,uint8_t* bufferPtr,uint32_t length)
{
    if (baseAddr < BOARD_SDRAM_BASE_ADDR || baseAddr >(BOARD_SDRAM_BASE_ADDR + BOARD_SDRAM_CAPACITY))
        return D_ERR_BOARD_MAIN_COMM_SDRAM_ADDR;
    if ((baseAddr + length-1) > (BOARD_SDRAM_BASE_ADDR + BOARD_SDRAM_CAPACITY))
        return D_ERR_BOARD_MAIN_COMM_SDRAM_ADDR;
    for (; length != 0; length--)
    {
        *bufferPtr++ = *(volatile uint8_t*)(baseAddr);
        baseAddr++;
    }
    return D_ERR_NONE;
}

//写入指定区域指定长度数据
D_ERR BoardSDRAM_WriteBuffer(uint32_t baseAddr,uint8_t* bufferPtr,uint32_t length)
{
    if (baseAddr < BOARD_SDRAM_BASE_ADDR || baseAddr >(BOARD_SDRAM_BASE_ADDR + BOARD_SDRAM_CAPACITY))
        return D_ERR_BOARD_MAIN_COMM_SDRAM_ADDR;
    if ((baseAddr + length-1) > (BOARD_SDRAM_BASE_ADDR + BOARD_SDRAM_CAPACITY))
        return D_ERR_BOARD_MAIN_COMM_SDRAM_ADDR;
    for (; length != 0; length--)
    {
        *(volatile uint8_t*)(baseAddr) = *bufferPtr;
        baseAddr++;
        bufferPtr++;
    }
    return D_ERR_NONE;
}

//检查SDRAM数据完整性
//设备自检,先全部写成0xff,检查,后全部写成0x00,检查
//经过自检,SRAM的所有数据均为0
D_ERR BoardSDRAM_SelfCheck(void)
{
    uint32_t baseAddr = BOARD_SDRAM_BASE_ADDR;
    uint32_t length = 0;
    //首先全部写入
    for(length = 0; length < BOARD_SDRAM_CAPACITY;length++)
    {
        *(volatile uint8_t*)(baseAddr) = (length%0XFF);
        baseAddr++;
    }

    //检查是不是写入的值
    baseAddr = BOARD_SDRAM_BASE_ADDR;
    for(length = 0; length < BOARD_SDRAM_CAPACITY;length++)
    {
        if((length%0XFF) != (*(volatile uint8_t*)(baseAddr)))
        {
            return D_ERR_BOARD_MAIN_COMM_SDRAM_CHECK;
        }
        baseAddr++;
    }

    //然后全部写入0x00
    baseAddr = BOARD_SDRAM_BASE_ADDR;
    for(length = 0; length < BOARD_SDRAM_CAPACITY;length++)
    {
        *(volatile uint8_t*)(baseAddr) = 0x00;
        baseAddr++;
    }

    //检查是不是全部是0x00
    baseAddr = BOARD_SDRAM_BASE_ADDR;
    for(length = 0; length < BOARD_SDRAM_CAPACITY;length++)
    {
        if(0x00 != (*(volatile uint8_t*)(baseAddr)))
        {
            return D_ERR_BOARD_MAIN_COMM_SDRAM_CHECK;
        }
        baseAddr++;
    }
    return D_ERR_NONE;
}
