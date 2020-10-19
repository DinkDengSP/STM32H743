#include "BoardW25Q64.h"

static void BoardW25Q64_IO_Init(void)
{
    //复位
        MCU_PortDeInit(MCU_PIN_D_13);
    //初始化
        MCU_PortInit(MCU_PIN_D_13,MCU_PORT_MODE_OUTPUT_PP,MCU_PORT_PULL_NOPULL,MCU_PORT_SPEED_FREQ_HIGH,0);
    //释放
        BOARD_W25Q64_CS_RELEASE();
    //SPI接口初始化
        MCU_SPI1_Init(SPI_BAUDRATEPRESCALER_60M,MCU_SPI_CPOL_LOW,MCU_SPI_CPHA_1EDGE);
}

//写使能
void BoardW25Q64_WriteEnable(void)
{
    /* 选择串行FLASH: CS低电平 */
    BOARD_W25Q64_CS_SELECT();
    /* 发送命令：写使能 */
    MCU_SPI1_ReadWriteByte(W25QXX_CMD_WRITE_ENABLE);
    /* 禁用串行Flash：CS高电平 */
    BOARD_W25Q64_CS_RELEASE();
}

//写禁止
void BoardW25Q64_WriteDisable(void)
{
    /* 选择串行FLASH: CS低电平 */
    BOARD_W25Q64_CS_SELECT();
    /* 发送命令：写使能 */
    MCU_SPI1_ReadWriteByte(W25QXX_CMD_WRITE_DISABLE);
    /* 禁用串行Flash：CS高电平 */
    BOARD_W25Q64_CS_RELEASE();
}

//等待执行完成,等待设备空闲
static void BoardW25Q64_WaitIdle()
{
    uint8_t FLASH_Status = 0;
    /* 选择串行FLASH: CS低电平 */
    BOARD_W25Q64_CS_SELECT();
    /* 发送命令：写读状态寄存器 */
    MCU_SPI1_ReadWriteByte(W25QXX_CMD_READ_STATUS_REG1);
    do
    {
        FLASH_Status = MCU_SPI1_ReadWriteByte(W25QXX_CMD_DUMMY_BYTE);	 
    }
    while ((FLASH_Status & W25QXX_STATE_WIP_FLAG) == SET); 
    /* 禁用串行Flash：CS高电平 */
    BOARD_W25Q64_CS_RELEASE();
}

//板上Flash初始化
void BoardW25Q64_Init(void)
{
    //CS IO初始化
    BoardW25Q64_IO_Init();
}

//板上Flash自检
D_ERR BoardW25Q64_Check(void)
{
    D_ERR errorCode = D_ERR_NONE;
    uint32_t deviceID = 0;
    //读取ID
    errorCode = BoardW25Q64_ReadID(&deviceID);
    if(errorCode != D_ERR_NONE)
    {
        return D_ERR_BOARD_MAIN_COMM_FRAM_ID_READ;
    }
    if(deviceID != W25Q64_ID)
    {
        return D_ERR_BOARD_MAIN_COMM_FRAM_ID_MATCH;
    }
    //生成一个随机地址
    uint32_t addrCheck = MCU_RandomGetNextRangeReal(0,W25Q64_FLASH_SIZE);
    //读写源数据
    uint8_t readSrcByte;
    uint8_t readByteUtil1 = 0,readByteUtil2 = 0;
    //首先读取源数据
    BoardW25Q64_ReadBuffer(&readSrcByte,addrCheck,1);
    //源数据进行计算后写入
    readByteUtil1 = (~readSrcByte);
    BoardW25Q64_WriteBuffer(&readByteUtil1,addrCheck,1);
    //将写入的数据读出
    BoardW25Q64_ReadBuffer(&readByteUtil2,addrCheck,1);
    //检查读写是否相等
    if(readByteUtil2 != readByteUtil1)
    {
        return D_ERR_BOARD_MAIN_COMM_FRAM_CHECK;
    }
    //将原始数据写入
    BoardW25Q64_WriteBuffer(&readSrcByte,addrCheck,1);
    //将原始数据读出
    BoardW25Q64_ReadBuffer(&readByteUtil2,addrCheck,1);
    //检查读写是否相等
    if(readByteUtil2 != readSrcByte)
    {
        return D_ERR_BOARD_MAIN_COMM_FRAM_CHECK;
    }
    return D_ERR_NONE;
}

//擦除指定扇区
void BoardW25Q64_EraseSector(uint32_t sectorNo)
{
    OS_ERR err;
    //申请互斥信号量
	    if (OSRunning)OSMutexPend(&mutexMCU_Spi1, 0, OS_OPT_PEND_BLOCKING, 0, &err);
        sectorNo *= 4096;
    /* 发送FLASH写使能命令 */
        BoardW25Q64_WriteEnable();
    //等待设备空闲
        BoardW25Q64_WaitIdle();
    /* 擦除扇区 */
    /* 选择串行FLASH: CS低电平 */
        BOARD_W25Q64_CS_SELECT();
    /* 发送扇区擦除指令*/
        MCU_SPI1_ReadWriteByte(W25QXX_CMD_SECTOR_ERASE);
    /*发送擦除扇区地址的高位*/
        MCU_SPI1_ReadWriteByte((sectorNo & 0xFF0000) >> 16);
    /* 发送擦除扇区地址的中位 */
        MCU_SPI1_ReadWriteByte((sectorNo & 0xFF00) >> 8);
    /* 发送擦除扇区地址的低位 */
        MCU_SPI1_ReadWriteByte(sectorNo & 0xFF);
    /* 禁用串行FLASH: CS 高电平 */
        BOARD_W25Q64_CS_RELEASE();
    /* 等待擦除完毕*/
        BoardW25Q64_WaitIdle();
    //释放互斥信号量
	    if (OSRunning)OSMutexPost(&mutexMCU_Spi1, OS_OPT_POST_FIFO, &err);
}

//整片擦除
void BoardW25Q64_EraseChip(void)
{
    OS_ERR err;
    //申请互斥信号量
	    if (OSRunning)OSMutexPend(&mutexMCU_Spi1, 0, OS_OPT_PEND_BLOCKING, 0, &err);
    /* 发送FLASH写使能命令 */
        BoardW25Q64_WriteEnable();
    /* 整片擦除 Erase */
    /* 选择串行FLASH: CS低电平 */
        BOARD_W25Q64_CS_SELECT();
    /* 发送整片擦除指令*/
        MCU_SPI1_ReadWriteByte(W25QXX_CMD_CHIP_ERASE);
    /* 禁用串行FLASH: CS高电平 */
        BOARD_W25Q64_CS_RELEASE();
    /* 等待擦除完毕*/
        BoardW25Q64_WaitIdle();
    //释放互斥信号量
	    if (OSRunning)OSMutexPost(&mutexMCU_Spi1, OS_OPT_POST_FIFO, &err);
}

//往串行FLASH按页写入数据，调用本函数写入数据前需要先擦除扇区
static void BoardW25Q64_WritePage(uint8_t* pBuffer, uint32_t addr, uint16_t dataLength)
{
    /* 发送FLASH写使能命令 */
    BoardW25Q64_WriteEnable();
    /* 寻找串行FLASH: CS低电平 */
    BOARD_W25Q64_CS_SELECT();
    /* 写送写指令*/
    MCU_SPI1_ReadWriteByte(W25QXX_CMD_PAGE_PROGRAM);
    /*发送写地址的高位*/
    MCU_SPI1_ReadWriteByte((addr & 0xFF0000) >> 16);
    /*发送写地址的中位*/
    MCU_SPI1_ReadWriteByte((addr & 0xFF00) >> 8);
    /*发送写地址的低位*/
    MCU_SPI1_ReadWriteByte(addr & 0xFF);
    if(dataLength > W25QXX_PAGE_SIZE)
    {
        dataLength = W25QXX_PAGE_SIZE;
    }
    /* 写入数据*/
    while (dataLength--)
    {
        /* 发送当前要写入的字节数据 */
        MCU_SPI1_ReadWriteByte(*pBuffer);
        /* 指向下一字节数据 */
        pBuffer++;
    }
    /* 禁用串行FLASH: CS 高电平 */
    BOARD_W25Q64_CS_RELEASE();
    /* 等待写入完毕*/
    BoardW25Q64_WaitIdle();
}

//写入指定地址数据
static void BoardW25Q64_WriteBufferNoCheck(uint8_t* pBuffer, uint32_t addr, uint16_t dataLength)
{
    uint16_t pageremain;	   
	pageremain=256-addr%256; //单页剩余的字节数		 	    
	if(dataLength<=pageremain)
        pageremain=dataLength;//不大于256个字节
	while(1)
	{	   
		BoardW25Q64_WritePage(pBuffer,addr,pageremain);
		if(dataLength==pageremain)
            break;//写入结束了
	 	else //dataLength>pageremain
		{
			pBuffer+=pageremain;
			addr+=pageremain;	
            //减去已经写入了的字节数
			dataLength -= pageremain;			  
			if(dataLength > 256)
                pageremain = 256; //一次可以写入256个字节
			else 
                pageremain=dataLength; 	  //不够256个字节了
		}
	}   
}

//写入指定地址数据
uint8_t W25Q64_BUFFER[4096];	
void BoardW25Q64_WriteBuffer(uint8_t* pBuffer, uint32_t addr, uint16_t dataLength)
{
    OS_ERR err;
    uint32_t secpos;
	uint16_t secoff;
	uint16_t secremain;	   
 	uint16_t i;    
	uint8_t * W25QXX_BUF;	  
   	W25QXX_BUF=W25Q64_BUFFER;	     
 	secpos=addr/4096;//扇区地址  
	secoff=addr%4096;//在扇区内的偏移
	secremain=4096-secoff;//扇区剩余空间大小   
 	if(dataLength<=secremain)
        secremain=dataLength;//不大于4096个字节
    //申请互斥信号量
	    if (OSRunning)OSMutexPend(&mutexMCU_Spi1, 0, OS_OPT_PEND_BLOCKING, 0, &err);
	while(1) 
	{	
        //读出整个扇区的内容
		BoardW25Q64_ReadBuffer(W25QXX_BUF,secpos*4096,4096);
		for(i=0;i<secremain;i++)//校验数据
		{
			if(W25QXX_BUF[secoff+i]!=0XFF)
                break;//需要擦除  	  
		}
		if(i<secremain)//需要擦除
		{
            //擦除这个扇区
			BoardW25Q64_EraseSector(secpos);
			for(i=0;i<secremain;i++)	   //复制
			{
				W25QXX_BUF[i+secoff]=pBuffer[i];	  
			}
            //写入整个扇区
			BoardW25Q64_WriteBufferNoCheck(W25QXX_BUF,secpos*4096,4096);  
		}
        else//写已经擦除了的,直接写入扇区剩余区间.  
            BoardW25Q64_WriteBufferNoCheck(pBuffer,addr,secremain);				   
		if(dataLength==secremain)
            break;//写入结束了
		else//写入未结束
		{
			secpos++;//扇区地址增1
			secoff=0;//偏移位置为0 	 
		   	pBuffer+=secremain;  //指针偏移
			addr+=secremain;//写地址偏移	   
		   	dataLength-=secremain;//字节数递减
			if(dataLength>4096)//下一个扇区还是写不完
                secremain=4096;	
			else //下一个扇区可以写完了
                secremain=dataLength;			
		}	 
	};	 
    //释放互斥信号量
	    if (OSRunning)OSMutexPost(&mutexMCU_Spi1, OS_OPT_POST_FIFO, &err);
}

//读取指定地址数据
void BoardW25Q64_ReadBuffer(uint8_t* pBuffer, uint32_t addr, uint32_t dataLength)
{
    OS_ERR err;
    //申请互斥信号量
	    if (OSRunning)OSMutexPend(&mutexMCU_Spi1, 0, OS_OPT_PEND_BLOCKING, 0, &err);
    /* 选择串行FLASH: CS低电平 */
        BOARD_W25Q64_CS_SELECT();
    /* 发送 读 指令 */
        MCU_SPI1_ReadWriteByte(W25QXX_CMD_READ_DATA);
    /* 发送 读 地址高位 */
        MCU_SPI1_ReadWriteByte((addr & 0xFF0000) >> 16);
    /* 发送 读 地址中位 */
        MCU_SPI1_ReadWriteByte((addr& 0xFF00) >> 8);
    /* 发送 读 地址低位 */
        MCU_SPI1_ReadWriteByte(addr & 0xFF);
    /* 读取数据 */
        while (dataLength--) 
        {
            /* 读取一个字节*/
            *pBuffer = MCU_SPI1_ReadWriteByte(W25QXX_CMD_DUMMY_BYTE);
            /* 指向下一个字节缓冲区 */
            pBuffer++;
        }
    /* 禁用串行FLASH: CS 高电平 */
        BOARD_W25Q64_CS_RELEASE();
    //释放互斥信号量
	    if (OSRunning)OSMutexPost(&mutexMCU_Spi1, OS_OPT_POST_FIFO, &err);
}

//读取板上设备ID
D_ERR BoardW25Q64_ReadID(uint32_t* deviceIdPtr)
{
    OS_ERR err;
    uint32_t Temp = 0, Temp0 = 0, Temp1 = 0, Temp2 = 0;
    //申请互斥信号量
	    if (OSRunning)OSMutexPend(&mutexMCU_Spi1, 0, OS_OPT_PEND_BLOCKING, 0, &err);
    /* 选择串行FLASH: CS低电平 */
        BOARD_W25Q64_CS_SELECT();
    /* 发送命令：读取芯片型号ID */
        MCU_SPI1_ReadWriteByte(W25QXX_CMD_JEDEC_DEVICE_ID);
    /* 从串行Flash读取一个字节数据 */
        Temp0 = MCU_SPI1_ReadWriteByte(W25QXX_CMD_DUMMY_BYTE);
    /* 从串行Flash读取一个字节数据 */
        Temp1 = MCU_SPI1_ReadWriteByte(W25QXX_CMD_DUMMY_BYTE);
    /* 从串行Flash读取一个字节数据 */
        Temp2 = MCU_SPI1_ReadWriteByte(W25QXX_CMD_DUMMY_BYTE);
    /* 禁用串行Flash：CS高电平 */
        BOARD_W25Q64_CS_RELEASE();
        Temp = (Temp0 << 16) | (Temp1 << 8) | Temp2;
    //释放互斥信号量
	    if (OSRunning)OSMutexPost(&mutexMCU_Spi1, OS_OPT_POST_FIFO, &err);
    *deviceIdPtr = Temp;
    return D_ERR_NONE;
}

