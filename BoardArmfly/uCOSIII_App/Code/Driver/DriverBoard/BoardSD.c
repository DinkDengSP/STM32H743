#include "BoardSD.h"

//SD卡句柄
static SD_HandleTypeDef uSdHandle;
//SD卡相关讯息
static HAL_SD_CardInfoTypeDef currentSDCardInfo;
//存储器互斥信号量
static OS_MUTEX mutexBoardSD;
//数据传输完成标志
static volatile  uint8_t  writeTransOverFlag = 0, readTransOverFlag = 0;

//硬件初始化
void HAL_SD_MspInit(SD_HandleTypeDef *hsd)
{
    //时钟使能
        __HAL_RCC_SDMMC1_CLK_ENABLE();
    //时钟复位
        __HAL_RCC_SDMMC1_FORCE_RESET();
        __HAL_RCC_SDMMC1_RELEASE_RESET();
    //PC8 SDIO_S0
        MCU_PortInit(MCU_PIN_C_8,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_NOPULL,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_SDIO1);
    //PC9 SDIO_D1
        MCU_PortInit(MCU_PIN_C_9,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_NOPULL,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_SDIO1);
    //PC10 SDIO_D2
        MCU_PortInit(MCU_PIN_C_10,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_NOPULL,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_SDIO1);
    //PC11 SDIO_D3
        MCU_PortInit(MCU_PIN_C_11,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_NOPULL,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_SDIO1);
    //PC12 SDIO_CK
        MCU_PortInit(MCU_PIN_C_12,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_NOPULL,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_SDIO1);
    //PD2 SDIO_CMD
        MCU_PortInit(MCU_PIN_D_2,MCU_PORT_MODE_AF_PP,MCU_PORT_PULL_NOPULL,MCU_PORT_SPEED_FREQ_VERY_HIGH,GPIO_AF12_SDIO1);
    //中断初初始化
        HAL_NVIC_SetPriority(SDMMC1_IRQn, SDIO_PREEMPT_PRIORITY, SDIO_SUB_PRIORITY);
        HAL_NVIC_EnableIRQ(SDMMC1_IRQn);
}

//硬件重新初始化
void HAL_SD_MspDeInit(SD_HandleTypeDef *hsd)
{
    //中断关闭
        HAL_NVIC_DisableIRQ(SDMMC1_IRQn);
    //IO口初始化
        MCU_PortDeInit(MCU_PIN_C_8);
        MCU_PortDeInit(MCU_PIN_C_9);
        MCU_PortDeInit(MCU_PIN_C_10);
        MCU_PortDeInit(MCU_PIN_C_11);
        MCU_PortDeInit(MCU_PIN_C_12);
        MCU_PortDeInit(MCU_PIN_D_2);
    /* 复位SDMMC */
        __HAL_RCC_SDMMC1_FORCE_RESET();
        __HAL_RCC_SDMMC1_RELEASE_RESET();
    //关闭时钟
        __HAL_RCC_SDMMC1_CLK_DISABLE();
}

//SD卡状态初始化
D_ERR BoardSD_Init(void)
{
    D_ERR errorCode = D_ERR_NONE;
    OS_ERR err;
    HAL_StatusTypeDef halState;
    //初始化互斥信号量
        OSMutexCreate((OS_MUTEX*	)&mutexBoardSD,
                        (CPU_CHAR*	)"mutexBoardSD",
                        (OS_ERR*		)&err);
    //状态复位
        writeTransOverFlag = 0, 
        readTransOverFlag = 0;
    //SD卡接口选择
        uSdHandle.Instance = SDMMC1;
    //SD接口初始化
        HAL_SD_DeInit(&uSdHandle);
    //配置SD卡类型
        //高速卡可以用1，低速卡用2（用1不稳定）
        uSdHandle.Init.ClockDiv            = 2;		
        uSdHandle.Init.ClockPowerSave      = SDMMC_CLOCK_POWER_SAVE_DISABLE;
        uSdHandle.Init.ClockEdge           = SDMMC_CLOCK_EDGE_RISING;
        uSdHandle.Init.HardwareFlowControl = SDMMC_HARDWARE_FLOW_CONTROL_DISABLE;
        uSdHandle.Init.BusWide             = SDMMC_BUS_WIDE_4B;
    //初始化
        halState = HAL_SD_Init(&uSdHandle);
        if(halState != HAL_OK)
        {
            return ErrorConvertHAL(halState);
        }
    //SD卡初始化
        halState = HAL_SD_InitCard(&uSdHandle);
        if(halState != HAL_OK)
        {
            return ErrorConvertHAL(halState);
        }
    //更新卡模式
        halState = HAL_SD_ConfigWideBusOperation(&uSdHandle,uSdHandle.Init.BusWide);
        if(halState != HAL_OK)
        {
            return ErrorConvertHAL(halState);
        }
    //更新SD卡相关讯息
        errorCode = BoardSD_GetCardInfo(&currentSDCardInfo);
    //完成
        return errorCode;
}

//SD卡测试是否正常读写
D_ERR BoardSD_Check(void)
{
    D_ERR errorCode = D_ERR_NONE;
    //申请内存,作为读取的参数
        uint8_t* readSourceMem = UserMemMalloc(MEM_AXI_SRAM,currentSDCardInfo.LogBlockSize);
        if(readSourceMem == NULL)
        {
            return D_ERR_BOARD_MAIN_COMM_SD_CHECK;
        }
        uint8_t* writeSourceMem = UserMemMalloc(MEM_AXI_SRAM,currentSDCardInfo.LogBlockSize);
        if(readSourceMem == NULL)
        {
            return D_ERR_BOARD_MAIN_COMM_SD_CHECK;
        }
        uint8_t* utilSourceMem = UserMemMalloc(MEM_AXI_SRAM,currentSDCardInfo.LogBlockSize);
        if(utilSourceMem == NULL)
        {
            return D_ERR_BOARD_MAIN_COMM_SD_CHECK;
        }
    //获取扇区编号
        uint32_t checkBlockAddr = MCU_RandomGetNextRangeReal(0,currentSDCardInfo.LogBlockNbr);
    //等待执行完成
    //读取源数据
        errorCode = BoardSD_ReadBlocks(readSourceMem,checkBlockAddr,1);
        if(errorCode != D_ERR_NONE)
        {
            UserMemFree(MEM_AXI_SRAM,utilSourceMem);
            UserMemFree(MEM_AXI_SRAM,readSourceMem);
            UserMemFree(MEM_AXI_SRAM,writeSourceMem);
            return errorCode;
        }
    //目标数据转换
        uint16_t indexUtil = 0;
        for(indexUtil = 0; indexUtil < currentSDCardInfo.LogBlockSize;indexUtil++)
        {
            writeSourceMem[indexUtil] = ~(readSourceMem[indexUtil]);
        }
    //写入目标数据
        errorCode = BoardSD_WriteBlocks(writeSourceMem,checkBlockAddr,1);
        if(errorCode != D_ERR_NONE)
        {
            UserMemFree(MEM_AXI_SRAM,utilSourceMem);
            UserMemFree(MEM_AXI_SRAM,readSourceMem);
            UserMemFree(MEM_AXI_SRAM,writeSourceMem);
            return errorCode;
        }
    //第三方读取
        errorCode = BoardSD_ReadBlocks(utilSourceMem,checkBlockAddr,1);
        if(errorCode != D_ERR_NONE)
        {
            UserMemFree(MEM_AXI_SRAM,utilSourceMem);
            UserMemFree(MEM_AXI_SRAM,readSourceMem);
            UserMemFree(MEM_AXI_SRAM,writeSourceMem);
            return errorCode;
        }
    //检查第三方数据和写入数据是否一致
        for(indexUtil = 0; indexUtil < currentSDCardInfo.LogBlockSize;indexUtil++)
        {
            if(writeSourceMem[indexUtil] != utilSourceMem[indexUtil])
            {
                UserMemFree(MEM_AXI_SRAM,utilSourceMem);
                UserMemFree(MEM_AXI_SRAM,readSourceMem);
                UserMemFree(MEM_AXI_SRAM,writeSourceMem);
                return D_ERR_BOARD_MAIN_COMM_SD_CHECK;
            }
        }
    //写入原始数据
        errorCode = BoardSD_WriteBlocks(readSourceMem,checkBlockAddr,1);
        if(errorCode != D_ERR_NONE)
        {
            UserMemFree(MEM_AXI_SRAM,utilSourceMem);
            UserMemFree(MEM_AXI_SRAM,readSourceMem);
            UserMemFree(MEM_AXI_SRAM,writeSourceMem);
            return errorCode;
        }
    //读取写入的数据
        errorCode = BoardSD_ReadBlocks(utilSourceMem,checkBlockAddr,1);
        if(errorCode != D_ERR_NONE)
        {
            UserMemFree(MEM_AXI_SRAM,utilSourceMem);
            UserMemFree(MEM_AXI_SRAM,readSourceMem);
            UserMemFree(MEM_AXI_SRAM,writeSourceMem);
            return errorCode;
        }
    //检查原始数据是否一致
        for(indexUtil = 0; indexUtil < currentSDCardInfo.LogBlockSize;indexUtil++)
        {
            if(readSourceMem[indexUtil] != utilSourceMem[indexUtil])
            {
                UserMemFree(MEM_AXI_SRAM,utilSourceMem);
                UserMemFree(MEM_AXI_SRAM,readSourceMem);
                UserMemFree(MEM_AXI_SRAM,writeSourceMem);
                return D_ERR_BOARD_MAIN_COMM_SD_CHECK;
            }
        }
    //释放内存
        UserMemFree(MEM_AXI_SRAM,utilSourceMem);
        UserMemFree(MEM_AXI_SRAM,readSourceMem);
        UserMemFree(MEM_AXI_SRAM,writeSourceMem);
    //回传结果
    return errorCode;
}

//读取指定块
D_ERR BoardSD_ReadBlocks(uint8_t* pData, uint32_t ReadAddr, uint32_t NumOfBlocks)
{
    D_ERR errorCode = D_ERR_NONE;
    HAL_StatusTypeDef halState;
    uint32_t timeCount = 0;
    OS_ERR err;
    //申请互斥信号量
	    if (OSRunning)OSMutexPend(&mutexBoardSD, 0, OS_OPT_PEND_BLOCKING, 0, &err);
    //读取标志设为0
        readTransOverFlag = 0;
    //读取数据
        halState = HAL_SD_ReadBlocks_IT(&uSdHandle, (uint8_t *)pData, ReadAddr, NumOfBlocks);
        if(halState != HAL_OK)
        {
            //释放互斥信号量
	        if (OSRunning)OSMutexPost(&mutexBoardSD, OS_OPT_POST_FIFO, &err);
            return ErrorConvertHAL(halState);
        }
    //等待标志位切换
        do
        {
            if(readTransOverFlag == 1)break;
            CoreDelayMinTick();
            timeCount++;
        } while (timeCount < BOARD_SD_TIME_OUT);
    //计时时间超时
        if(timeCount >= BOARD_SD_TIME_OUT)
        {
            //释放互斥信号量
	        if (OSRunning)OSMutexPost(&mutexBoardSD, OS_OPT_POST_FIFO, &err);
            return D_ERR_BOARD_MAIN_COMM_HAL_TIMEOUT;
        }
    //等待SD卡状态正常
        errorCode = BoardSD_WaitStateNormal();
        if(errorCode != D_ERR_NONE)
        {
            //释放互斥信号量
	        if (OSRunning)OSMutexPost(&mutexBoardSD, OS_OPT_POST_FIFO, &err);
            return errorCode;
        }
    //释放互斥信号量
	    if (OSRunning)OSMutexPost(&mutexBoardSD, OS_OPT_POST_FIFO, &err);
    //完成
        return D_ERR_NONE;
}

//写入指定块
D_ERR BoardSD_WriteBlocks(uint8_t* pData, uint32_t WriteAddr, uint32_t NumOfBlocks)
{
    D_ERR errorCode = D_ERR_NONE;
    HAL_StatusTypeDef halState;
    OS_ERR err;
    uint32_t timeCount = 0;
    //申请互斥信号量
	    if (OSRunning)OSMutexPend(&mutexBoardSD, 0, OS_OPT_PEND_BLOCKING, 0, &err);
    //设置标志位为0
        writeTransOverFlag = 0;
    //写入数据
        halState = HAL_SD_WriteBlocks_IT(&uSdHandle, (uint8_t *)pData, WriteAddr, NumOfBlocks);
        if(halState != HAL_OK)
        {
            return ErrorConvertHAL(halState);
        }
    //等待标志位切换
        do
        {
            if(writeTransOverFlag == 1)break;
            CoreDelayMinTick();
            timeCount++;
        } while (timeCount < BOARD_SD_TIME_OUT);
    //计时时间超时
        if(timeCount >= BOARD_SD_TIME_OUT)
        {
            //释放互斥信号量
	        if (OSRunning)OSMutexPost(&mutexBoardSD, OS_OPT_POST_FIFO, &err);
            return D_ERR_BOARD_MAIN_COMM_HAL_TIMEOUT;
        }
    //等待SD卡状态正常
        errorCode = BoardSD_WaitStateNormal();
        if(errorCode != D_ERR_NONE)
        {
            //释放互斥信号量
	        if (OSRunning)OSMutexPost(&mutexBoardSD, OS_OPT_POST_FIFO, &err);
            return errorCode;
        }
    //释放互斥信号量
	    if (OSRunning)OSMutexPost(&mutexBoardSD, OS_OPT_POST_FIFO, &err);
    //完成
        return D_ERR_NONE;
}

//擦除指定地址
D_ERR BoardSD_Erase(uint32_t StartAddr, uint32_t EndAddr)
{
    HAL_StatusTypeDef halState;
    OS_ERR err;
    //申请互斥信号量
	    if (OSRunning)OSMutexPend(&mutexBoardSD, 0, OS_OPT_PEND_BLOCKING, 0, &err);
    //擦除指定扇区
        halState = HAL_SD_Erase(&uSdHandle, StartAddr, EndAddr);
        if(halState != HAL_OK)
        {
            //释放互斥信号量
	        if (OSRunning)OSMutexPost(&mutexBoardSD, OS_OPT_POST_FIFO, &err);
            return ErrorConvertHAL(halState);
        }
    //释放互斥信号量
	    if (OSRunning)OSMutexPost(&mutexBoardSD, OS_OPT_POST_FIFO, &err);
    //完成
        return D_ERR_NONE;
}

//获取内存卡状态
SD_TRANS_STATE BoardSD_GetCardState(void)
{
    SD_TRANS_STATE transState;
    OS_ERR err;
    //申请互斥信号量
	    if (OSRunning)OSMutexPend(&mutexBoardSD, 0, OS_OPT_PEND_BLOCKING, 0, &err);
    //获取状态
        transState = ((HAL_SD_GetCardState(&uSdHandle) == HAL_SD_CARD_TRANSFER ) ? SD_TRANS_STATE_IDLE:SD_TRANS_STATE_BUSY);
    //释放互斥信号量
	    if (OSRunning)OSMutexPost(&mutexBoardSD, OS_OPT_POST_FIFO, &err);
    //完成
        return transState;
}

//等待内存卡模块状态正常
D_ERR BoardSD_WaitStateNormal(void)
{
    uint32_t timeOut = 0;
    do
    {
        if(SD_TRANS_STATE_IDLE == BoardSD_GetCardState())break;
        timeOut++;
        CoreDelayMinTick();
    }while(timeOut < BOARD_SD_TIME_OUT);
    if(timeOut >= BOARD_SD_TIME_OUT)
    {
        return D_ERR_BOARD_MAIN_COMM_HAL_TIMEOUT;
    }
    return D_ERR_NONE;
}

//获取内存卡讯息
D_ERR BoardSD_GetCardInfo(HAL_SD_CardInfoTypeDef *CardInfo)
{
    HAL_StatusTypeDef halState;
    OS_ERR err;
    //申请互斥信号量
	    if (OSRunning)OSMutexPend(&mutexBoardSD, 0, OS_OPT_PEND_BLOCKING, 0, &err);
    //获取卡讯息
        halState = HAL_SD_GetCardInfo(&uSdHandle, CardInfo);
        if(halState != HAL_OK)
        {
            //释放互斥信号量
	        if (OSRunning)OSMutexPost(&mutexBoardSD, OS_OPT_POST_FIFO, &err);
            return ErrorConvertHAL(halState);
        }
    //释放互斥信号量
	    if (OSRunning)OSMutexPost(&mutexBoardSD, OS_OPT_POST_FIFO, &err);
    //完成
        return D_ERR_NONE;
}

//打印SD卡讯息
void BoardSD_PrintfCardMsg(void)
{
    SDCardPrintf("currentSDCardInfo.CardType : %d \r\n",currentSDCardInfo.CardType);
    SDCardPrintf("currentSDCardInfo.CardVersion : %d \r\n",currentSDCardInfo.CardVersion);
    SDCardPrintf("currentSDCardInfo.Class : %d \r\n",currentSDCardInfo.Class);
    SDCardPrintf("currentSDCardInfo.RelCardAdd : %d \r\n",currentSDCardInfo.RelCardAdd);
    SDCardPrintf("currentSDCardInfo.BlockNbr : %d \r\n",currentSDCardInfo.BlockNbr);
    SDCardPrintf("currentSDCardInfo.BlockSize : %d \r\n",currentSDCardInfo.BlockSize);
    SDCardPrintf("currentSDCardInfo.LogBlockNbr : %d \r\n",currentSDCardInfo.LogBlockNbr);
    SDCardPrintf("currentSDCardInfo.LogBlockSize : %d \r\n",currentSDCardInfo.LogBlockSize);
}

//获取SD卡是否已经插入
SD_STATE BoardSD_IsDetected(void)
{
    return SD_INSERT;
}



//传输退出回调
void HAL_SD_AbortCallback(SD_HandleTypeDef *hsd)
{
    asm("nop");
}

//发送完成回调
void HAL_SD_TxCpltCallback(SD_HandleTypeDef *hsd)
{
    writeTransOverFlag = 1;
}

//接收完成回调
void HAL_SD_RxCpltCallback(SD_HandleTypeDef *hsd)
{
    readTransOverFlag = 1;
}

//错误回调
void HAL_SD_ErrorCallback(SD_HandleTypeDef *hsd)
{
    asm("nop");
}
  
//1.8V卡检测到回调
void HAL_SD_DriveTransciver_1_8V_Callback(FlagStatus status)
{
    asm("nop");
}

//SDIO中断
void SDMMC1_IRQHandler(void)
{
	HAL_SD_IRQHandler(&uSdHandle);
}
