#include "BoardW25Q256.h"

//DMA句柄
static MDMA_HandleTypeDef mdmaHandle;
//SPI句柄
QSPI_HandleTypeDef qspiW25q256Handle;
//指令发送完成标志
static __IO uint8_t CmdCplt;
//数据接收完成标志
static __IO uint8_t RxCplt;
//数据发送完成标志
static __IO uint8_t TxCplt;
//状态更新标志,在本驱动中标识芯片进入空闲状态
static __IO uint8_t StatusMatch;
//存储器互斥信号量
static OS_MUTEX mutexBoardW25q256;

//初始化QSPI接口
static D_ERR BoardW25Q256_Port_Init(void)
{
    /* 复位QSPI */
	    qspiW25q256Handle.Instance = QUADSPI;
    //复位
	    if (HAL_QSPI_DeInit(&qspiW25q256Handle) != HAL_OK)
        {
            return D_ERR_BOARD_MAIN_COMM_HAL_LIB;
        }
	/* 设置时钟速度，QSPI clock = 240MHz / (ClockPrescaler+1) = 120MHz */
	    qspiW25q256Handle.Init.ClockPrescaler  = 1;  
	/* 设置FIFO阀值，范围1 - 32 */
	    qspiW25q256Handle.Init.FifoThreshold = 32; 
	//QUADSPI在FLASH驱动信号后过半个CLK周期才对FLASH驱动的数据采样。在外部信号延迟时，这有利于推迟数据采样。
	    qspiW25q256Handle.Init.SampleShifting = QSPI_SAMPLE_SHIFTING_HALFCYCLE; 
	/*Flash大小是2^(FlashSize + 1) = 2^25 = 32MB */
	    qspiW25q256Handle.Init.FlashSize = W25Q256JV_FLASH_SIZE - 1; 
	/* 命令之间的CS片选至少保持1个时钟周期的高电平 */
	    qspiW25q256Handle.Init.ChipSelectHighTime = QSPI_CS_HIGH_TIME_1_CYCLE;
	//MODE0: 表示片选信号空闲期间，CLK时钟信号是低电平
	//MODE3: 表示片选信号空闲期间，CLK时钟信号是高电平
	    qspiW25q256Handle.Init.ClockMode = QSPI_CLOCK_MODE_0;
	/* QSPI有两个BANK，这里使用的BANK1 */
	    qspiW25q256Handle.Init.FlashID   = QSPI_FLASH_ID_1;
	/* 禁止双BANK */
	    qspiW25q256Handle.Init.DualFlash = QSPI_DUALFLASH_DISABLE;
	/* 初始化配置QSPI */
	    if (HAL_QSPI_Init(&qspiW25q256Handle) != HAL_OK)
        {
            return D_ERR_BOARD_MAIN_COMM_HAL_LIB;
        }
	//返回结果
        return D_ERR_NONE;
}

//QSPI复位时候自动调用的函数
void HAL_QSPI_MspDeInit(QSPI_HandleTypeDef *hqspi)
{
    /* 复位QSPI引脚 */
        //CS PG6
        MCU_PortDeInit(MCU_PIN_G_6);
        //CLK PF10
        MCU_PortDeInit(MCU_PIN_F_10);
        //BK_D0 PF8
        MCU_PortDeInit(MCU_PIN_F_8);
        //BK_D1 PF9
        MCU_PortDeInit(MCU_PIN_F_9);
        //BK_D2 PF7
        MCU_PortDeInit(MCU_PIN_F_7);
        //BK_D3 PF6
        MCU_PortDeInit(MCU_PIN_F_6);
	/* 复位QSPI */
        __HAL_RCC_QSPI_FORCE_RESET();
        __HAL_RCC_QSPI_RELEASE_RESET();
	/* 关闭QSPI时钟 */
	    __HAL_RCC_QSPI_CLK_DISABLE();
}

//QSPI初始化自动调用的函数
void HAL_QSPI_MspInit(QSPI_HandleTypeDef *hqspi)
{
     /* 打开QSPI时钟 */
	    __HAL_RCC_QSPI_CLK_ENABLE();
    /* 复位QSPI */
        __HAL_RCC_QSPI_FORCE_RESET();
        __HAL_RCC_QSPI_RELEASE_RESET();
    //初始化SPI引脚
	    //CS PG6
        MCU_PortInit(MCU_PIN_G_6,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF10_QUADSPI);
        //CLK PF10
        MCU_PortInit(MCU_PIN_F_10,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF9_QUADSPI);
        //BK_D0 PF8
        MCU_PortInit(MCU_PIN_F_8,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF10_QUADSPI);
        //BK_D1 PF9
        MCU_PortInit(MCU_PIN_F_9,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF10_QUADSPI);
        //BK_D2 PF7
        MCU_PortInit(MCU_PIN_F_7,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF9_QUADSPI);
        //BK_D3 PF6
        MCU_PortInit(MCU_PIN_F_6,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_PULLUP,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF9_QUADSPI);
	/* 使能QSPI中断 */
        HAL_NVIC_SetPriority(QUADSPI_IRQn, QSPI_PREEMPT_PRIORITY, QSPI_SUB_PRIORITY);
        HAL_NVIC_EnableIRQ(QUADSPI_IRQn);
	/* 配置MDMA时钟 */
	    __HAL_RCC_MDMA_CLK_ENABLE();
    //配置MDMA初始化配置
        mdmaHandle.Instance = MDMA_Channel1;                         /* 使用MDMA的通道1 */
        mdmaHandle.Init.Request = MDMA_REQUEST_QUADSPI_FIFO_TH;      /* QSPI的FIFO阀值触发中断 */
        mdmaHandle.Init.TransferTriggerMode = MDMA_BUFFER_TRANSFER;  /* 使用MDMA的buffer传输 */
        mdmaHandle.Init.Priority = MDMA_PRIORITY_HIGH;               /* 优先级高 */
        mdmaHandle.Init.Endianness = MDMA_LITTLE_ENDIANNESS_PRESERVE;/* 小端格式 */
        mdmaHandle.Init.SourceInc = MDMA_SRC_INC_BYTE;               /* 源地址字节递增 */
        mdmaHandle.Init.DestinationInc = MDMA_DEST_INC_DISABLE;      /* 目的地址无效自增 */
        mdmaHandle.Init.SourceDataSize = MDMA_SRC_DATASIZE_BYTE;     /* 源地址数据宽度字节 */
        mdmaHandle.Init.DestDataSize = MDMA_DEST_DATASIZE_BYTE;      /* 目的地址数据宽度字节 */
        mdmaHandle.Init.DataAlignment = MDMA_DATAALIGN_PACKENABLE;   /* 小端，右对齐 */
        mdmaHandle.Init.BufferTransferLength = 128;                  /* 每次传输128个字节 */
        mdmaHandle.Init.SourceBurst = MDMA_SOURCE_BURST_SINGLE;      /* 源数据单次传输 */
        mdmaHandle.Init.DestBurst = MDMA_DEST_BURST_SINGLE;          /* 目的数据单次传输 */
        mdmaHandle.Init.SourceBlockAddressOffset = 0;                /* 用于block传输，buffer传输用不到 */
        mdmaHandle.Init.DestBlockAddressOffset = 0;                  /* 用于block传输，buffer传输用不到 */
	/* 关联MDMA句柄到QSPI句柄里面  */
	    __HAL_LINKDMA(hqspi, hmdma, mdmaHandle);
	/* 先复位，然后配置MDMA */
	    HAL_MDMA_DeInit(&mdmaHandle);  
	    HAL_MDMA_Init(&mdmaHandle);
	/* 使能MDMA中断，并配置优先级 */
        HAL_NVIC_SetPriority(MDMA_IRQn, MDMA_PREEMPT_PRIORITY, MDMA_SUB_PRIORITY);
        HAL_NVIC_EnableIRQ(MDMA_IRQn);
}

//QSPI写入使能
D_ERR BoardW25Q256_WriteEnable(QSPI_HandleTypeDef *hqspi)
{
    HAL_StatusTypeDef halState;
    QSPI_CommandTypeDef     sCommand = {0};
	/* 基本配置 */
        sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;    /* 1线方式发送指令 */
        sCommand.AddressSize       = QSPI_ADDRESS_32_BITS;       /* 32位地址 */
        sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;  /* 无交替字节 */
        sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;      /* W25Q256JV不支持DDR */
        sCommand.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;  /* DDR模式，数据输出延迟 */
        sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;	 /* 每次传输都发指令 */
	/* 写使能 */
        sCommand.Instruction       = W25Q256_CMD_WRITE_ENABLE;  /* 写使能指令 */
        sCommand.AddressMode       = QSPI_ADDRESS_NONE; /* 无需地址 */
        sCommand.DataMode          = QSPI_DATA_NONE;    /* 无需数据 */
        sCommand.DummyCycles       = 0;                 /* 空周期  */
    //发送指令
	    halState = HAL_QSPI_Command(&qspiW25q256Handle, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);
    //转换结果
        return ErrorConvertHAL(halState);
}

//QSPI写入禁止
D_ERR BoardW25Q256_WriteDisable(QSPI_HandleTypeDef *hqspi)
{
    HAL_StatusTypeDef halState;
    QSPI_CommandTypeDef     sCommand = {0};
	/* 基本配置 */
        sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;    /* 1线方式发送指令 */
        sCommand.AddressSize       = QSPI_ADDRESS_32_BITS;       /* 32位地址 */
        sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;  /* 无交替字节 */
        sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;      /* W25Q256JV不支持DDR */
        sCommand.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;  /* DDR模式，数据输出延迟 */
        sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;	 /* 每次传输都发指令 */
	/* 写使能 */
        sCommand.Instruction       = W25Q256_CMD_WRITE_DISABLE;  /* 写禁止指令 */
        sCommand.AddressMode       = QSPI_ADDRESS_NONE; /* 无需地址 */
        sCommand.DataMode          = QSPI_DATA_NONE;    /* 无需数据 */
        sCommand.DummyCycles       = 0;                 /* 空周期  */
    //发送指令
	    halState = HAL_QSPI_Command(&qspiW25q256Handle, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);
    //转换结果
        return ErrorConvertHAL(halState);
}

//QSPI循环检查设备状态
static void BoardW25Q256_AutoPollingDeviceIdleState(void)
{
    //自动查询结构
        QSPI_CommandTypeDef     sCommand = {0};
        QSPI_AutoPollingTypeDef sConfig = {0};
	/* 基本配置 */
        sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;    /* 1线方式发送指令 */
        sCommand.AddressSize       = QSPI_ADDRESS_32_BITS;       /* 32位地址 */
        sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;  /* 无交替字节 */
        sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;      /* W25Q256JV不支持DDR */
        sCommand.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;  /* DDR模式，数据输出延迟 */
        sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;	 /* 每次传输都发指令 */
	/* 读取状态*/
        sCommand.Instruction       = W25Q256_CMD_READ_STATUSREG1; /* 读取状态命令 */
        sCommand.AddressMode       = QSPI_ADDRESS_NONE;   /* 无需地址 */
        sCommand.DataMode          = QSPI_DATA_1_LINE;    /* 1线数据 */
        sCommand.DummyCycles       = 0;                   /* 无需空周期 */
	/* 屏蔽位设置的bit0，匹配位等待bit0为0，即不断查询状态寄存器bit0，等待其为0 */
        sConfig.Mask            = 0x01;
        sConfig.Match           = 0x00;
        sConfig.MatchMode       = QSPI_MATCH_MODE_AND;
        sConfig.StatusBytesSize = 1;
        sConfig.Interval        = 0x10;
        sConfig.AutomaticStop   = QSPI_AUTOMATIC_STOP_ENABLE;
    //等待执行完成,打开状态改变中断检测
	    HAL_QSPI_AutoPolling_IT(&qspiW25q256Handle, &sCommand, &sConfig);
}

//等待Flash就绪
static void BoardW25Q256_WaitDeviceIdle(void)
{
    //状态设置为0
	    StatusMatch = 0;
    //开始循环查询状态变化
	    BoardW25Q256_AutoPollingDeviceIdleState();	
    //等待状态完成
	    while(StatusMatch == 0);
    //状态清空
	    StatusMatch = 0;	
}

//擦除指定扇区,扇区地址，以4KB为单位的地址
void BoardW25Q256_EraseSector(uint32_t sectorNo)
{
    OS_ERR err;
    QSPI_CommandTypeDef sCommand={0};
    //申请互斥信号量
	    if (OSRunning)OSMutexPend(&mutexBoardW25q256, 0, OS_OPT_PEND_BLOCKING, 0, &err); 
	/* 用于命令发送完成标志 */	
	    CmdCplt = 0;
	/* 写使能 */
	    BoardW25Q256_WriteEnable(&qspiW25q256Handle);	
	/* 基本配置 */
        sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;  /* 1线方式发送指令 */
        sCommand.AddressSize       = QSPI_ADDRESS_32_BITS;     /* 32位地址 */
        sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;/* 无交替字节 */
        sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;    /* W25Q256JV不支持DDR */
        sCommand.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;/* DDR模式，数据输出延迟 */
        sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD; /* 每次传输都发指令 */	
	/* 擦除配置 */
        sCommand.Instruction = W25Q256_CMD_SECTOR_ERASE_4_LINES;/* 32bit地址方式的扇区擦除命令，扇区大小4KB*/       
        sCommand.AddressMode = QSPI_ADDRESS_1_LINE;            /* 地址发送是1线方式 */       
        sCommand.Address     = sectorNo*4096; /* 扇区首地址，保证是4KB整数倍 */    
        sCommand.DataMode    = QSPI_DATA_NONE; /* 无需发送数据 */  
        sCommand.DummyCycles = 0;              /* 无需空周期 */  
    //发出指令
        HAL_QSPI_Command_IT(&qspiW25q256Handle, &sCommand);
	/* 等待命令发送完毕 */
        while(CmdCplt == 0);
        CmdCplt = 0;
	/* 等待编程结束,Flash Ready */
	    BoardW25Q256_WaitDeviceIdle();
    //释放互斥信号量
	    if (OSRunning)OSMutexPost(&mutexBoardW25q256, OS_OPT_POST_FIFO, &err);
}

//擦除全芯片,等待时间500S
void BoardW25Q256_EraseChip(void)
{
    OS_ERR err;
    QSPI_CommandTypeDef sCommand={0};
    //申请互斥信号量
	    if (OSRunning)OSMutexPend(&mutexBoardW25q256, 0, OS_OPT_PEND_BLOCKING, 0, &err); 
	/* 用于命令发送完成标志 */	
	    CmdCplt = 0;
	/* 写使能 */
	    BoardW25Q256_WriteEnable(&qspiW25q256Handle);
    /* 基本配置 */
        sCommand.InstructionMode   = QSPI_INSTRUCTION_4_LINES; /* 1线方式发送指令 */
        sCommand.AddressSize       = QSPI_ADDRESS_8_BITS;      /* 32位地址 */
        sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;/* 无交替字节 */
        sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;    /* W25Q256JV不支持DDR */
        sCommand.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;/* DDR模式，数据输出延迟 */
        sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD; /* 每次传输都发指令 */	
	/* 擦除配置 */
        sCommand.Instruction = W25Q256_CMD_CHIP_ERASE;/* 32bit地址方式的扇区擦除命令，扇区大小4KB*/       
        sCommand.AddressMode = QSPI_ADDRESS_NONE;    /* 无地址 */       
        sCommand.Address     = 0;              /* 扇区首地址，保证是4KB整数倍 */    
        sCommand.DataMode    = QSPI_DATA_NONE; /* 无需发送数据 */  
        sCommand.DummyCycles = 0;              /* 无需空周期 */  
    //发出指令
        HAL_QSPI_Command_IT(&qspiW25q256Handle, &sCommand);
    /* 等待命令发送完毕 */
        while(CmdCplt == 0);
        CmdCplt = 0;
	/* 等待编程结束,Flash Ready */
	    BoardW25Q256_WaitDeviceIdle();
    //释放互斥信号量
	    if (OSRunning)OSMutexPost(&mutexBoardW25q256, OS_OPT_POST_FIFO, &err);
}

//写入指定地址数据,页编程，页大小256字节，任意页都可以写入
//数据个数，不能超过页面大小，范围1 - 256
static void BoardW25Q256_WritePage(uint8_t* pBuffer, uint32_t addr, uint16_t dataLength)
{
    QSPI_CommandTypeDef sCommand={0};
	/* 用于等待发送完成标志 */
	    TxCplt = 0;
	/* 写使能 */
	    BoardW25Q256_WriteEnable(&qspiW25q256Handle);	
	/* 基本配置 */
        sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;    /* 1线方式发送指令 */
        sCommand.AddressSize       = QSPI_ADDRESS_32_BITS;       /* 32位地址 */
        sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;  /* 无交替字节 */
        sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;      /* W25Q256JV不支持DDR */
        sCommand.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;  /* DDR模式，数据输出延迟 */
        sCommand.SIOOMode          = QSPI_SIOO_INST_ONLY_FIRST_CMD;	 /* 仅发送一次命令 */	
	/* 写序列配置 */
        sCommand.Instruction = W25Q256_CMD_FAST_PROG_4_LINES; /* 32bit地址的4线快速写入命令 */
        sCommand.DummyCycles = 0;                    /* 不需要空周期 */
        sCommand.AddressMode = QSPI_ADDRESS_1_LINE; /* 4线地址方式 */
        sCommand.DataMode    = QSPI_DATA_4_LINES;    /* 4线数据方式 */
        sCommand.NbData      = dataLength;         /* 写数据大小 */   
        sCommand.Address     = addr;         /* 写入地址 */
    //发出指令
        HAL_QSPI_Command(&qspiW25q256Handle, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);
	/* 启动MDMA传输 */
	    HAL_QSPI_Transmit_DMA(&qspiW25q256Handle, pBuffer);
	/* 等待数据发送完毕 */
        while(TxCplt == 0);
        TxCplt = 0;
	/* 等待编程结束,Flash Ready */
	    BoardW25Q256_WaitDeviceIdle();	
}

//无检验写SPI FLASH 
//必须确保所写的地址范围内的数据全部为0XFF,否则在非0XFF处写入的数据将失败!
//具有自动换页功能 
//在指定地址开始写入指定长度的数据,但是要确保地址不越界!
static void BoardW25Q256_WriteNoCheck(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite)  
{
    uint16_t pageremain;	   
    //单页剩余的字节数
	pageremain=256-WriteAddr%256; 
    //不大于256个字节		 	    
	if(NumByteToWrite<=pageremain)
    {
        pageremain=NumByteToWrite;
    }
	while(1)
	{	   
        //页写入
		BoardW25Q256_WritePage(pBuffer,WriteAddr,pageremain);
		if(NumByteToWrite==pageremain)
        {
            break;//写入结束了
        }
	 	else
		{
            //写入地址增加
			pBuffer += pageremain;
			WriteAddr+=pageremain;	
            //减去已经写入了的字节数
			NumByteToWrite-=pageremain;			  
			if(NumByteToWrite>256)
            {
                //一次可以写入256个字节
                pageremain=256; 
            } 
			else 
            {
                //不够256个字节了
                pageremain=NumByteToWrite; 
            } 	  
		}
	}   
}

//读取指定地址数据
void BoardW25Q256_ReadBuffer(uint8_t* pBuffer, uint32_t addr, uint32_t dataLength)
{
    OS_ERR err;
    QSPI_CommandTypeDef sCommand = {0};
    //申请互斥信号量
	    if (OSRunning)OSMutexPend(&mutexBoardW25q256, 0, OS_OPT_PEND_BLOCKING, 0, &err); 
	/* 用于等待接收完成标志 */
	    RxCplt = 0;
	/* 基本配置 */
        sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;    	/* 1线方式发送指令 */
        sCommand.AddressSize       = QSPI_ADDRESS_32_BITS;      	/* 32位地址 */
        sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;  	/* 无交替字节 */
        sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;      	/* W25Q256JV不支持DDR */
        sCommand.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;  	/* DDR模式，数据输出延迟 */
        sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;		/* 每次传输要发指令 */	
	/* 读取数据 */
        sCommand.Instruction = W25Q256_CMD_FAST_READ_4_LINES; /* 32bit地址的4线快速读取命令 */
        sCommand.DummyCycles = 6;                    /* 空周期 */
        sCommand.AddressMode = QSPI_ADDRESS_4_LINES; /* 4线地址 */
        sCommand.DataMode    = QSPI_DATA_4_LINES;    /* 4线数据 */ 
        sCommand.NbData      = dataLength;           /* 读取的数据大小 */ 
        sCommand.Address     = addr;          /* 读取数据的起始地址 */ 
    //发出指令
	    HAL_QSPI_Command(&qspiW25q256Handle, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);
	/* MDMA方式读取 */
	    HAL_QSPI_Receive_DMA(&qspiW25q256Handle, pBuffer);	
	/* 等接受完毕 */
        while(RxCplt == 0);
        RxCplt = 0;
    //释放互斥信号量
	    if (OSRunning)OSMutexPost(&mutexBoardW25q256, OS_OPT_POST_FIFO, &err);
}

//写入指定地址数据
//写SPI FLASH  
//在指定地址开始写入指定长度的数据
//该函数带擦除操作! 
uint8_t W25QXX_BUFFER[4096];	
void BoardW25Q256_WriteBuffer(uint8_t* pBuffer, uint32_t addr, uint16_t dataLength)
{
    OS_ERR err;
    uint32_t secpos;
	uint16_t secoff;
	uint16_t secremain;	   
 	uint16_t i;    
	uint8_t * W25QXX_BUF;
    //操作需要的数据
        //缓存区	  
        W25QXX_BUF=W25QXX_BUFFER;	   
        //扇区地址   
        secpos=addr/4096; 
        //在扇区内的偏移
        secoff=addr%4096;
        //扇区剩余空间大小 
        secremain=4096-secoff; 
    //申请互斥信号量
	    if (OSRunning)OSMutexPend(&mutexBoardW25q256, 0, OS_OPT_PEND_BLOCKING, 0, &err); 
 	if(dataLength<=secremain)
    {
        //不大于4096个字节
        secremain=dataLength;
    }
	while(1) 
	{	
        //读出整个扇区的内容
		BoardW25Q256_ReadBuffer(W25QXX_BUF,secpos*4096,4096);
		for(i=0;i<secremain;i++)//校验数据
		{
			if(W25QXX_BUF[secoff+i]!=0XFF)
                break;//需要擦除  	  
		}
		if(i<secremain)//需要擦除
		{
            //擦除这个扇区
			BoardW25Q256_EraseSector(secpos);
			for(i=0;i<secremain;i++)	   //复制
			{
				W25QXX_BUF[i+secoff]=pBuffer[i];	  
			}
            //写入整个扇区
			BoardW25Q256_WriteNoCheck(W25QXX_BUF,secpos*4096,4096);  

		}
        else 
        {
            //写已经擦除了的,直接写入扇区剩余区间. 
            BoardW25Q256_WriteNoCheck(pBuffer,addr,secremain);	
        }			   
		if(dataLength==secremain)break;//写入结束了
		else//写入未结束
		{
			secpos++;//扇区地址增1
			secoff=0;//偏移位置为0 	 
		   	pBuffer+=secremain;  //指针偏移
			addr+=secremain;//写地址偏移	   
		   	dataLength-=secremain;//字节数递减
			if(dataLength>4096)
                secremain=4096;	//下一个扇区还是写不完
			else 
                secremain=dataLength;			//下一个扇区可以写完了
		}	 
	};
    //释放互斥信号量
	    if (OSRunning)OSMutexPost(&mutexBoardW25q256, OS_OPT_POST_FIFO, &err);
}

//读取板上设备ID
D_ERR BoardW25Q256_ReadID(uint32_t* deviceIdPtr)
{
    HAL_StatusTypeDef halState;
    OS_ERR err;
    uint32_t deviceID;
	QSPI_CommandTypeDef s_command = {0};
	uint8_t buf[3];
    //申请互斥信号量
	    if (OSRunning)OSMutexPend(&mutexBoardW25q256, 0, OS_OPT_PEND_BLOCKING, 0, &err);
    /* 基本配置 */
        s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;    /* 1线方式发送指令 */
        s_command.AddressSize       = QSPI_ADDRESS_32_BITS;       /* 32位地址 */
        s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;  /* 无交替字节 */
        s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;      /* W25Q256JV不支持DDR */
        s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;  /* DDR模式，数据输出延迟 */
        s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;	  /* 每次传输都发指令 */
        /* 读取JEDEC ID */
        s_command.Instruction = W25Q256_CMD_JEDEC_DEVICE_ID;/* 读取ID命令 */
        s_command.AddressMode = QSPI_ADDRESS_NONE;/* 1线地址 */
        s_command.DataMode = QSPI_DATA_1_LINE;    /* 1线地址 */
        s_command.DummyCycles = 0;                /* 无空周期 */
        s_command.NbData = 3;                     /* 读取三个数据 */
    //发出指令
	    halState = HAL_QSPI_Command(&qspiW25q256Handle, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);
        if(halState != HAL_OK)
        {
            *deviceIdPtr = 0XFFFFFFFF;
            //释放互斥信号量
	        if (OSRunning)OSMutexPost(&mutexBoardW25q256, OS_OPT_POST_FIFO, &err);
            //转换结果
            return ErrorConvertHAL(halState);
        }
    //接收数据
	    halState = HAL_QSPI_Receive(&qspiW25q256Handle, buf, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);
        if(halState != HAL_OK)
        {
            *deviceIdPtr = 0XFFFFFFFF;
            //释放互斥信号量
	        if (OSRunning)OSMutexPost(&mutexBoardW25q256, OS_OPT_POST_FIFO, &err);
            //转换结果
            return ErrorConvertHAL(halState);
        } 
    //组成ID
	    deviceID = (buf[0] << 16) | (buf[1] << 8 ) | buf[2];
        *deviceIdPtr = deviceID;
    //释放互斥信号量
	    if (OSRunning)OSMutexPost(&mutexBoardW25q256, OS_OPT_POST_FIFO, &err);
    //返回数据
	    return D_ERR_NONE;
}

//板上Flash初始化
D_ERR BoardW25Q256_Init(void)
{
    D_ERR errorCode = D_ERR_NONE;
    OS_ERR err;
    //初始化互斥信号量
	OSMutexCreate((OS_MUTEX*	)&mutexBoardW25q256,
				  (CPU_CHAR*	)"mutexBoardW25q256",
                  (OS_ERR*		)&err);
    //端口初始化
    errorCode = BoardW25Q256_Port_Init();
    if(errorCode != D_ERR_NONE)
    {
        return errorCode;
    }
    return D_ERR_NONE;
}

//板上Flash检测
D_ERR BoardW25Q256_Check(void)
{
    D_ERR errorCode = D_ERR_NONE;
    //生成一个随机地址
    uint32_t addrCheck = MCU_RandomGetNextRangeReal(0,W25Q256JV_FLASH_SIZES);
    //读写源数据
    uint8_t readSrcByte;
    uint8_t readByteUtil1 = 0,readByteUtil2 = 0;
    //读取ID
    uint32_t deviceID = 0;
    errorCode = BoardW25Q256_ReadID(&deviceID);
    if(errorCode != D_ERR_NONE)
    {
        return D_ERR_BOARD_MAIN_COMM_FRAM_ID_READ;
    }
    //检查ID
    if(deviceID != W25Q256_ID)
    {
        return D_ERR_BOARD_MAIN_COMM_FRAM_ID_MATCH;
    }
    //首先读取源数据
    BoardW25Q256_ReadBuffer(&readSrcByte,addrCheck,1);
    //源数据进行计算后写入
    readByteUtil1 = (~readSrcByte);
    BoardW25Q256_WriteBuffer(&readByteUtil1,addrCheck,1);
    //将写入的数据读出
    BoardW25Q256_ReadBuffer(&readByteUtil2,addrCheck,1);
    //检查读写是否相等
    if(readByteUtil2 != readByteUtil1)
    {
        return D_ERR_BOARD_MAIN_COMM_FRAM_CHECK;
    }
    //将原始数据写入
    BoardW25Q256_WriteBuffer(&readSrcByte,addrCheck,1);
    //将原始数据读出
    BoardW25Q256_ReadBuffer(&readByteUtil2,addrCheck,1);
    //检查读写是否相等
    if(readByteUtil2 != readSrcByte)
    {
        return D_ERR_BOARD_MAIN_COMM_FRAM_CHECK;
    }
    return D_ERR_NONE;
}



/*************************************相关中断处理函数********************************************/
//QSPI中断的回调函数,指令发送完成，Flash擦除函数QSPI_EraseSector要使用
void HAL_QSPI_CmdCpltCallback(QSPI_HandleTypeDef *hqspi)
{
	CmdCplt++;
}

//QSPI中断的回调函数，数据接收完成,Flash读函数QSPI_ReadBuffer要使用
void HAL_QSPI_RxCpltCallback(QSPI_HandleTypeDef *hqspi)
{
	RxCplt++;
}
//QSPI中断的回调函数，数据写入完成,Flash写函数QSPI_ReadBuffer要使用
 void HAL_QSPI_TxCpltCallback(QSPI_HandleTypeDef *hqspi)
{
	TxCplt++; 
}

//QSPI中断的回调函数，Flash状态查询函数QSPI_AutoPollingMemReady使用,状态切换完成
void HAL_QSPI_StatusMatchCallback(QSPI_HandleTypeDef *hqspi)
{
	StatusMatch++;
}

//QSPI中断处理函数
void QUADSPI_IRQHandler(void)
{
	HAL_QSPI_IRQHandler(&qspiW25q256Handle);
}

