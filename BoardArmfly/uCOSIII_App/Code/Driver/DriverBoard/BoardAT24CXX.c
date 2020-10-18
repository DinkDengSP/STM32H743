#include "BoardAT24Cxx.h"

//IIC互斥信号量
static OS_MUTEX mutexBoardAT24CXX;

//板上芯片初始化
D_ERR BoardAT24CXX_Init(void)
{
    OS_ERR err;
    //接口初始化
    MCU_IIC_Init();
    //检查芯片ACK响应
    if(1 == MCU_IIC_CheckDeviceAddr(BOARD_AT24CXX_WRITE_ADDR))
    {
        return D_ERR_BOARD_MAIN_COMM_IIC_ACK_TIMEOUT;
    }
    //初始化互斥信号量
	OSMutexCreate((OS_MUTEX*	)&mutexBoardAT24CXX,
				  (CPU_CHAR*	)"mutexBoardAT24CXX",
                  (OS_ERR*		)&err);
    //完成
    return D_ERR_NONE;
}

//在AT24CXX指定地址读出一个数据
static D_ERR BoardAT24CXX_ReadOneByte(uint16_t readAddr,uint8_t* readValue)
{				  
	uint8_t temp=0;
    OS_ERR err;
    //申请AT24CXX总线信号量与IIC总线信号量
    //请求互斥信号量,申请不到,任务挂起等待OS_OPT_PEND_BLOCKING
    if (OSRunning)OSMutexPend(&mutexBoardAT24CXX, 0, OS_OPT_PEND_BLOCKING, 0, &err);
    if (OSRunning)OSMutexPend(&mutexMCU_IIC, 0, OS_OPT_PEND_BLOCKING, 0, &err);
    //发送启动信号
    MCU_IIC_SendStart();  
	if(BOARD_AT24CXX_SIZE > BOARD_AT24C16_SIZE)
	{
        //发送写命令
		MCU_IIC_SendByte(BOARD_AT24CXX_WRITE_ADDR);	   
		if(1 == MCU_IIC_WaitAck(MCU_IIC_ACK_TIMEOUT_COUNT))
        {
            //产生一个停止条件
            MCU_IIC_SendStop();
            //释放信号量
            if (OSRunning)OSMutexPost(&mutexBoardAT24CXX, OS_OPT_POST_FIFO, &err);
            if (OSRunning)OSMutexPost(&mutexMCU_IIC, OS_OPT_POST_FIFO, &err);
            //超时未收到ACK
            return D_ERR_BOARD_MAIN_COMM_IIC_ACK_TIMEOUT;
        }
        //发送高地址	
		MCU_IIC_SendByte(readAddr>>8);    
	}
    else 
    {
        //发送器件地址0XA0,写数据
        MCU_IIC_SendByte(BOARD_AT24CXX_WRITE_ADDR+((readAddr/256)<<1));   
    } 	   
    //等待ACK
	if(1 == MCU_IIC_WaitAck(MCU_IIC_ACK_TIMEOUT_COUNT))
    {
        //产生一个停止条件
        MCU_IIC_SendStop();
        //释放信号量
        if (OSRunning)OSMutexPost(&mutexBoardAT24CXX, OS_OPT_POST_FIFO, &err);
        if (OSRunning)OSMutexPost(&mutexMCU_IIC, OS_OPT_POST_FIFO, &err);
        //超时未收到ACK
        return D_ERR_BOARD_MAIN_COMM_IIC_ACK_TIMEOUT;
    } 
    //发送低地址
    MCU_IIC_SendByte(readAddr%256);   
	//等待ACK
	if(1 == MCU_IIC_WaitAck(MCU_IIC_ACK_TIMEOUT_COUNT))
    {
        //产生一个停止条件
        MCU_IIC_SendStop();
        //释放信号量
        if (OSRunning)OSMutexPost(&mutexBoardAT24CXX, OS_OPT_POST_FIFO, &err);
        if (OSRunning)OSMutexPost(&mutexMCU_IIC, OS_OPT_POST_FIFO, &err);
        //超时未收到ACK
        return D_ERR_BOARD_MAIN_COMM_IIC_ACK_TIMEOUT;
    }  
    //Dummy Start   
	MCU_IIC_SendStart();  	 	   
    //进入接收模式	
	MCU_IIC_SendByte(BOARD_AT24CXX_READ_ADDR); 
    //等待ACK
	if(1 == MCU_IIC_WaitAck(MCU_IIC_ACK_TIMEOUT_COUNT))
    {
        //产生一个停止条件
        MCU_IIC_SendStop();
        //释放信号量
        if (OSRunning)OSMutexPost(&mutexBoardAT24CXX, OS_OPT_POST_FIFO, &err);
        if (OSRunning)OSMutexPost(&mutexMCU_IIC, OS_OPT_POST_FIFO, &err);
        //超时未收到ACK
        return D_ERR_BOARD_MAIN_COMM_IIC_ACK_TIMEOUT;
    } 	 
    //读取数据
    temp=MCU_IIC_ReadByte();		  
    //发送NACK
    MCU_IIC_SendNAck();
    //产生一个停止条件
    MCU_IIC_SendStop();	   
    //释放信号量
    if (OSRunning)OSMutexPost(&mutexBoardAT24CXX, OS_OPT_POST_FIFO, &err);
    if (OSRunning)OSMutexPost(&mutexMCU_IIC, OS_OPT_POST_FIFO, &err); 
    //结果返回
	*readValue =  temp;
    return D_ERR_NONE;
}

//在AT24CXX指定地址写入一个数据
//WriteAddr  :写入数据的目的地址    
//DataToWrite:要写入的数据
D_ERR BoardAT24CXX_WriteOneByte(uint16_t WriteAddr,uint8_t DataToWrite)
{				   	  	  
    OS_ERR err;
    //申请AT24CXX总线信号量与IIC总线信号量
    //请求互斥信号量,申请不到,任务挂起等待OS_OPT_PEND_BLOCKING
    if (OSRunning)OSMutexPend(&mutexBoardAT24CXX, 0, OS_OPT_PEND_BLOCKING, 0, &err);
    if (OSRunning)OSMutexPend(&mutexMCU_IIC, 0, OS_OPT_PEND_BLOCKING, 0, &err);  																 
    MCU_IIC_SendStart();  
	if(BOARD_AT24CXX_SIZE > BOARD_AT24C16_SIZE)
	{
        //发送写命令
		MCU_IIC_SendByte(BOARD_AT24CXX_WRITE_ADDR);	   
        //等待ACK
        if(1 == MCU_IIC_WaitAck(MCU_IIC_ACK_TIMEOUT_COUNT))
        {
            //产生一个停止条件
            MCU_IIC_SendStop();
            //释放信号量
            if (OSRunning)OSMutexPost(&mutexBoardAT24CXX, OS_OPT_POST_FIFO, &err);
            if (OSRunning)OSMutexPost(&mutexMCU_IIC, OS_OPT_POST_FIFO, &err);
            //超时未收到ACK
            return D_ERR_BOARD_MAIN_COMM_IIC_ACK_TIMEOUT;
        } 
        //发送高地址	 
		MCU_IIC_SendByte(WriteAddr>>8); 
	}
    else
    {
        //发送器件地址0XA0,写数据 
        MCU_IIC_SendByte(BOARD_AT24CXX_WRITE_ADDR+((WriteAddr/256)<<1));   
    } 	 
    //等待ACK
	if(1 == MCU_IIC_WaitAck(MCU_IIC_ACK_TIMEOUT_COUNT))
    {
        //产生一个停止条件
        MCU_IIC_SendStop();
        //释放信号量
        if (OSRunning)OSMutexPost(&mutexBoardAT24CXX, OS_OPT_POST_FIFO, &err);
        if (OSRunning)OSMutexPost(&mutexMCU_IIC, OS_OPT_POST_FIFO, &err);
        //超时未收到ACK
        return D_ERR_BOARD_MAIN_COMM_IIC_ACK_TIMEOUT;
    }  
    //发送低地址	   
    MCU_IIC_SendByte(WriteAddr%256);   
    //等待ACK
	if(1 == MCU_IIC_WaitAck(MCU_IIC_ACK_TIMEOUT_COUNT))
    {
        //产生一个停止条件
        MCU_IIC_SendStop();
        //释放信号量
        if (OSRunning)OSMutexPost(&mutexBoardAT24CXX, OS_OPT_POST_FIFO, &err);
        if (OSRunning)OSMutexPost(&mutexMCU_IIC, OS_OPT_POST_FIFO, &err);
        //超时未收到ACK
        return D_ERR_BOARD_MAIN_COMM_IIC_ACK_TIMEOUT;
    }  
    //发送字节		 										  		   
	MCU_IIC_SendByte(DataToWrite);     
    //等待ACK
	if(1 == MCU_IIC_WaitAck(MCU_IIC_ACK_TIMEOUT_COUNT))
    {
        //产生一个停止条件
        MCU_IIC_SendStop();
        //释放信号量
        if (OSRunning)OSMutexPost(&mutexBoardAT24CXX, OS_OPT_POST_FIFO, &err);
        if (OSRunning)OSMutexPost(&mutexMCU_IIC, OS_OPT_POST_FIFO, &err);
        //超时未收到ACK
        return D_ERR_BOARD_MAIN_COMM_IIC_ACK_TIMEOUT;
    }   	
    //产生一个停止条件 	    	   
    MCU_IIC_SendStop();
    //释放IIC总线
    if (OSRunning)OSMutexPost(&mutexMCU_IIC, OS_OPT_POST_FIFO, &err);
    //等待写入完成
	CoreDelayMs(10);
    //释放设备
    if (OSRunning)OSMutexPost(&mutexBoardAT24CXX, OS_OPT_POST_FIFO, &err);
    return D_ERR_NONE;

}


//IIC芯片自检
D_ERR BoardAT24CXX_Check(void)
{
    D_ERR errorCode = D_ERR_NONE;
    //生成一个随机地址
    uint16_t randomAddr = MCU_RandomGetNextRangeReal(0,BOARD_AT24CXX_SIZE);
    //读取到的源数据
    uint8_t srcDat = 0x00;
    //首先读取源数据
    errorCode = BoardAT24CXX_ReadOneByte(randomAddr,&srcDat);
    if(errorCode != D_ERR_NONE)return errorCode;
    //将源数据转换一下
    uint8_t convertDat = (~srcDat);
    //写入转换数据
    errorCode = BoardAT24CXX_WriteOneByte(randomAddr,convertDat);
    if(errorCode != D_ERR_NONE)return errorCode;
    //读取写入的数据
    uint8_t utilDat = 0x00;
    errorCode = BoardAT24CXX_ReadOneByte(randomAddr,&utilDat);
    if(errorCode != D_ERR_NONE)return errorCode;
    //看看是否写进入了
    if(utilDat != convertDat)
    {
        return D_ERR_BOARD_MAIN_COMM_AT24CXX_CHECK;
    }
    //将源数据写回
    errorCode = BoardAT24CXX_WriteOneByte(randomAddr,srcDat);
    if(errorCode != D_ERR_NONE)return errorCode;
    //读取写入的数据
    errorCode = BoardAT24CXX_ReadOneByte(randomAddr,&utilDat);
    if(errorCode != D_ERR_NONE)return errorCode;
    //看看是否写进入了
    if(utilDat != srcDat)
    {
        return D_ERR_BOARD_MAIN_COMM_AT24CXX_CHECK;
    }
    //完成
    return D_ERR_NONE;
}

//写入数据
D_ERR BoardAT24CXX_Write(uint16_t addrWrite,uint8_t* writeBuffer,uint16_t numWrite)
{
    D_ERR errorCode = D_ERR_NONE;
    if(addrWrite + numWrite >= BOARD_AT24CXX_SIZE)
    {
        return D_ERR_BOARD_MAIN_COMM_IIC_ADDR_LIMIT;
    }
    for(uint16_t index = 0; index < numWrite; index++)
    {
        errorCode = BoardAT24CXX_WriteOneByte(addrWrite+index,writeBuffer[index]);
        if(errorCode != D_ERR_NONE)
        {
            return errorCode;
        }
    }
    return errorCode;
}

//读取数据
D_ERR BoardAT24CXX_Read(uint16_t addrRead,uint8_t* recvBufferPtr,uint16_t numRead)
{
    D_ERR errorCode = D_ERR_NONE;
    if(addrRead + numRead >= BOARD_AT24CXX_SIZE)
    {
        return D_ERR_BOARD_MAIN_COMM_IIC_ADDR_LIMIT;
    }
    for(uint16_t index = 0; index < numRead; index++)
    {
        errorCode = BoardAT24CXX_ReadOneByte(addrRead+index,recvBufferPtr+index);
        if(errorCode != D_ERR_NONE)
        {
            return errorCode;
        }
    }
    return errorCode;
}
