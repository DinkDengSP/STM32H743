/*******************************************************************
**Description: ,: Copyright(c) 2018-2090 DengXiaojun,All rights reserved.
**Author: ,: DengXiaoJun
**Date: ,: 2020-10-17 00:35:29
**LastEditors: ,: DengXiaoJun
**LastEditTime: ,: 2020-10-20 21:20:38
**FilePath: ,: \ProjectFilesd:\DinkGitHub\STM32H743\BoardArmfly\uCOSIII_App\Code\Driver\DriverBoard\BoardBMP180.c
**ModifyRecord1: ,:    
******************************************************************/
/*
	应用说明:访问BMP085前，请先调用一次 bsp_InitI2C()函数配置好I2C相关的GPIO.

	BMP085 是BOSCH公司生产的的一款高精度、超低能耗的压力传感器。绝对精度最低可以达到0.03hPa。
	BMP085 通过I2C总线直接与各种微处理器相连。
	压力范围：300 ... 1100hPa（海拔9000米...-500米）
			30kPa ... 110kPa

	压强单位：
		inHg 英寸汞柱
		mmHg 毫米汞柱
		mbar 毫巴(=百帕)
		hPa 百帕
		kPa 千帕, 1kPa = 1000Pa
		MPa 兆帕, 1MPa = 1000kPa = 1000000Pa

	1百帕=1毫巴=3/4毫米水银柱
	在海平面的平均气压 约为1013.25百帕斯卡（760毫米水银柱），这个值也被称为标准大气压

	度量衡换算：
		1标准大气压=101 325帕斯卡
		1帕斯卡=9.8692326671601*10-6标准大气压

	Doc文件夹下有《全国各地主要城市海拔高度及大气压参考数据.pdf》

	城市   海拔高度(m)  气压强度(kPa)
	北京     31.2         99.86
	天津     3.3          100.48
	石家庄   80.5         99.56
	太原     777.9        91.92
	呼和浩特 1063         88.94
	沈阳     41.6         100.07
	大连     92.8         99.47
	长春     236.8        97.79
	哈尔滨   171.7        98.51
	上海     4.5          100.53
	南京     8.9          100.4
	杭州     41.7         100.05
	合肥     29.8         100.09
	福州     84           99.64
	厦门     63.2         99.91
	南昌     46.7         99.91
	济南     51.6         99.85
	武汉     23.3         100.17
	郑州     110.4        99.17
	长沙     44.9         99.94
	广州     6.6          100.45
	南宁     72.2         99.6
	重庆     259.1        97.32
	贵阳     1071.2       88.79
	昆明     1891.4       80.8
	拉萨     3658.        65.23
	西安     396.9        95.92
	兰州     1517.2       84.31
	成都     505.9        94.77
	西宁     2261.2       77.35
	银川     1111.5       88.35
	乌鲁木齐 917.9        90.67

	香港     32           100.56
	台北     9            100.53

	汕头     1.2          100.55   【最低海拔】广东省
	那曲     4507         58.9     【最高海拔】西藏自治区

	珠峰高度为海拔 8848米    相当于0.3个大气压 ,即30.39KPa  【该数据存在争议】

	【根据气压，温度计算海拔高度，只是大致关系，仅供参考】
	H = (RT/gM)*ln(p0/p)
		R为常数8.51
		T为热力学温度（常温下）（摄氏度要转化成热力学温度）
		g为重力加速度10
		M为气体的分子量29
		P0为标准大气压
		P为要求的高度的气压
		这个公式的推导过程较复杂就不推导了，自己应该会转换的。


	可以总结出近似的计算公式；
		P=100KPa   H*10kPa/km   H在0,3km之间
		P=70kPa    H*8kPa/km    H在3km,5km之间
		P=54kPa    H*6.5kPa/km   H在5km,7km之间
		P=41kPa    H*5kPa/km   H在7km,10km之间
		P=25kPa    H*3.5kPa/km   H在10km,12km之间

*/
#include "BoardBMP180.h"

typedef struct BMP180_DATA
{
	/* 用于保存芯片内部EEPROM的校准参数 */
	int16_t AC1;
	int16_t AC2;
	int16_t AC3;
	uint16_t AC4;
	uint16_t AC5;
	uint16_t AC6;
	int16_t B1;
	int16_t B2;
	int16_t MB;
	int16_t MC;
	int16_t MD;
	/* 过采样值，可有用户自己设定 */
	uint8_t OSS;	
}BMP180_DATA;

//存储BMP180相关数据
static BMP180_DATA bmp180Data;

//等待芯片结果转换
/* 4.5ms  7.5ms  13.5ms   25.5ms */
//对应四个过采样级别
static void BoardBmp180WaitConvert(void)
{   
    if (bmp180Data.OSS == 0)CoreDelayMs(6);	
	else if (bmp180Data.OSS == 1)CoreDelayMs(9);	
	else if (bmp180Data.OSS == 2)CoreDelayMs(15);
	else if (bmp180Data.OSS == 3)CoreDelayMs(27);	
    else CoreDelayMs(27);	
}

static D_ERR BoardBmp180WriteRegByte(uint8_t regAddr,uint8_t regValue)
{
    OS_ERR err;
    //请求互斥信号量,申请不到,任务挂起等待OS_OPT_PEND_BLOCKING
    if (OSRunning)OSMutexPend(&mutexMCU_IIC, 0, OS_OPT_PEND_BLOCKING, 0, &err);
    MCU_IIC_SendStart();
    //发送写命令
	MCU_IIC_SendByte(BOARD_BMP180_ADDR_WRITE);	 
    //等待ACK
    if(1 == MCU_IIC_WaitAck(MCU_IIC_ACK_TIMEOUT_COUNT))
    {
        //产生一个停止条件
        MCU_IIC_SendStop();
        //释放信号量
        if (OSRunning)OSMutexPost(&mutexMCU_IIC, OS_OPT_POST_FIFO, &err);
        //超时未收到ACK
        return D_ERR_BOARD_MAIN_COMM_IIC_ACK_TIMEOUT;
    } 
    //发送寄存器地址
    MCU_IIC_SendByte(regAddr);
    //等待ACK
    if(1 == MCU_IIC_WaitAck(MCU_IIC_ACK_TIMEOUT_COUNT))
    {
        //产生一个停止条件
        MCU_IIC_SendStop();
        //释放信号量
        if (OSRunning)OSMutexPost(&mutexMCU_IIC, OS_OPT_POST_FIFO, &err);
        //超时未收到ACK
        return D_ERR_BOARD_MAIN_COMM_IIC_ACK_TIMEOUT;
    } 
    //写入寄存器值
    MCU_IIC_SendByte(regValue);
    //等待ACK
    if(1 == MCU_IIC_WaitAck(MCU_IIC_ACK_TIMEOUT_COUNT))
    {
        //产生一个停止条件
        MCU_IIC_SendStop();
        //释放信号量
        if (OSRunning)OSMutexPost(&mutexMCU_IIC, OS_OPT_POST_FIFO, &err);
        //超时未收到ACK
        return D_ERR_BOARD_MAIN_COMM_IIC_ACK_TIMEOUT;
    } 
    //产生一个停止条件 	    	   
    MCU_IIC_SendStop();
    //释放IIC总线
    if (OSRunning)OSMutexPost(&mutexMCU_IIC, OS_OPT_POST_FIFO, &err);
    return D_ERR_NONE;
}

static D_ERR BoardBmp180ReadRegTwoByte(uint8_t regAddr,uint16_t* readValue)
{
    uint8_t ucData1 = 0;
	uint8_t ucData2 = 0;
    OS_ERR err;
    *readValue = 0;
    //请求互斥信号量,申请不到,任务挂起等待OS_OPT_PEND_BLOCKING
    if (OSRunning)OSMutexPend(&mutexMCU_IIC, 0, OS_OPT_PEND_BLOCKING, 0, &err);
    //发送启动信号
    MCU_IIC_SendStart();
    //发送写命令
	MCU_IIC_SendByte(BOARD_BMP180_ADDR_WRITE);	 
    //等待ACK
    if(1 == MCU_IIC_WaitAck(MCU_IIC_ACK_TIMEOUT_COUNT))
    {
        //产生一个停止条件
        MCU_IIC_SendStop();
        //释放信号量
        if (OSRunning)OSMutexPost(&mutexMCU_IIC, OS_OPT_POST_FIFO, &err);
        //超时未收到ACK
        return D_ERR_BOARD_MAIN_COMM_IIC_ACK_TIMEOUT;
    } 
    //发送寄存器地址
    MCU_IIC_SendByte(regAddr);
    //等待ACK
    if(1 == MCU_IIC_WaitAck(MCU_IIC_ACK_TIMEOUT_COUNT))
    {
        //产生一个停止条件
        MCU_IIC_SendStop();
        //释放信号量
        if (OSRunning)OSMutexPost(&mutexMCU_IIC, OS_OPT_POST_FIFO, &err);
        //超时未收到ACK
        return D_ERR_BOARD_MAIN_COMM_IIC_ACK_TIMEOUT;
    } 
    //发送启动信号
    MCU_IIC_SendStart();
    //发送读取命令
	MCU_IIC_SendByte(BOARD_BMP180_ADDR_READ);	 
    //等待ACK
    if(1 == MCU_IIC_WaitAck(MCU_IIC_ACK_TIMEOUT_COUNT))
    {
        //产生一个停止条件
        MCU_IIC_SendStop();
        //释放信号量
        if (OSRunning)OSMutexPost(&mutexMCU_IIC, OS_OPT_POST_FIFO, &err);
        //超时未收到ACK
        return D_ERR_BOARD_MAIN_COMM_IIC_ACK_TIMEOUT;
    } 
    //读取数据
    ucData1=MCU_IIC_ReadByte();		  
    //发送NACK
    MCU_IIC_SendAck();
    //读取数据
    ucData2=MCU_IIC_ReadByte();		  
    //发送NACK
    MCU_IIC_SendNAck();
    //产生一个停止条件
    MCU_IIC_SendStop();	 
    //释放IIC总线
    if (OSRunning)OSMutexPost(&mutexMCU_IIC, OS_OPT_POST_FIFO, &err);
    //数据组合
    *readValue = (ucData1 << 8) + ucData2;
    return D_ERR_NONE;
}

static D_ERR BoardBmp180ReadRegThreeByte(uint8_t regAddr,uint32_t* regValue)
{
    uint8_t ucData1 = 0;
	uint8_t ucData2 = 0;
	uint8_t ucData3 = 0;
    OS_ERR err;
    *regValue = 0;
    //请求互斥信号量,申请不到,任务挂起等待OS_OPT_PEND_BLOCKING
    if (OSRunning)OSMutexPend(&mutexMCU_IIC, 0, OS_OPT_PEND_BLOCKING, 0, &err);
    //发送启动信号
    MCU_IIC_SendStart();
    //发送写命令
	MCU_IIC_SendByte(BOARD_BMP180_ADDR_WRITE);	 
    //等待ACK
    if(1 == MCU_IIC_WaitAck(MCU_IIC_ACK_TIMEOUT_COUNT))
    {
        //产生一个停止条件
        MCU_IIC_SendStop();
        //释放信号量
        if (OSRunning)OSMutexPost(&mutexMCU_IIC, OS_OPT_POST_FIFO, &err);
        //超时未收到ACK
        return D_ERR_BOARD_MAIN_COMM_IIC_ACK_TIMEOUT;
    } 
    //发送寄存器地址
    MCU_IIC_SendByte(regAddr);
    //等待ACK
    if(1 == MCU_IIC_WaitAck(MCU_IIC_ACK_TIMEOUT_COUNT))
    {
        //产生一个停止条件
        MCU_IIC_SendStop();
        //释放信号量
        if (OSRunning)OSMutexPost(&mutexMCU_IIC, OS_OPT_POST_FIFO, &err);
        //超时未收到ACK
        return D_ERR_BOARD_MAIN_COMM_IIC_ACK_TIMEOUT;
    } 
    //发送启动信号
    MCU_IIC_SendStart();
    //发送读取命令
	MCU_IIC_SendByte(BOARD_BMP180_ADDR_READ);	 
    //等待ACK
    if(1 == MCU_IIC_WaitAck(MCU_IIC_ACK_TIMEOUT_COUNT))
    {
        //产生一个停止条件
        MCU_IIC_SendStop();
        //释放信号量
        if (OSRunning)OSMutexPost(&mutexMCU_IIC, OS_OPT_POST_FIFO, &err);
        //超时未收到ACK
        return D_ERR_BOARD_MAIN_COMM_IIC_ACK_TIMEOUT;
    } 
    //读取数据
    ucData1=MCU_IIC_ReadByte();		  
    //发送NACK
    MCU_IIC_SendAck();
    //读取数据
    ucData2=MCU_IIC_ReadByte();		  
    //发送ACK
    MCU_IIC_SendAck();
    //读取数据
    ucData3=MCU_IIC_ReadByte();		  
    //发送NACK
    MCU_IIC_SendNAck();
    //产生一个停止条件
    MCU_IIC_SendStop();	 
    //释放IIC总线
    if (OSRunning)OSMutexPost(&mutexMCU_IIC, OS_OPT_POST_FIFO, &err);
    //数据组合
    *regValue = (ucData1 << 16) + (ucData2 << 8) + ucData3;
    return D_ERR_NONE;
}

//传感器初始化
D_ERR BoardBmp180Init(uint8_t ossSet)
{
    D_ERR errorCode = D_ERR_NONE;
    uint16_t datUtil = 0;
    //接口初始化
    MCU_IIC_Init();
    /* 读出芯片内部的校准参数（每个芯片不同，这是BOSCH出厂前校准好的数据） */
	errorCode = BoardBmp180ReadRegTwoByte(0xAA,&datUtil);
    if(errorCode != D_ERR_NONE)return errorCode;
    bmp180Data.AC1 = (int16_t)datUtil;
	errorCode = BoardBmp180ReadRegTwoByte(0xAC,&datUtil);
    if(errorCode != D_ERR_NONE)return errorCode;
    bmp180Data.AC2 = (int16_t)datUtil;
	errorCode = BoardBmp180ReadRegTwoByte(0xAE,&datUtil);
    if(errorCode != D_ERR_NONE)return errorCode;
    bmp180Data.AC3 = (int16_t)datUtil;
	errorCode = BoardBmp180ReadRegTwoByte(0xB0,&datUtil);
    if(errorCode != D_ERR_NONE)return errorCode;
    bmp180Data.AC4 = (uint16_t)datUtil;
	errorCode = BoardBmp180ReadRegTwoByte(0xB2,&datUtil);
    if(errorCode != D_ERR_NONE)return errorCode;
    bmp180Data.AC5 = (uint16_t)datUtil;
	errorCode = BoardBmp180ReadRegTwoByte(0xB4,&datUtil);
    if(errorCode != D_ERR_NONE)return errorCode;
    bmp180Data.AC6 = (uint16_t)datUtil;
	errorCode = BoardBmp180ReadRegTwoByte(0xB6,&datUtil);
    if(errorCode != D_ERR_NONE)return errorCode;
    bmp180Data.B1 = (int16_t)datUtil;
	errorCode = BoardBmp180ReadRegTwoByte(0xB8,&datUtil);
    if(errorCode != D_ERR_NONE)return errorCode;
    bmp180Data.B2 = (int16_t)datUtil;
	errorCode = BoardBmp180ReadRegTwoByte(0xBA,&datUtil);
    if(errorCode != D_ERR_NONE)return errorCode;
    bmp180Data.MB = (int16_t)datUtil;
	errorCode = BoardBmp180ReadRegTwoByte(0xBC,&datUtil);
    if(errorCode != D_ERR_NONE)return errorCode;
    bmp180Data.MC = (int16_t)datUtil;
	errorCode = BoardBmp180ReadRegTwoByte(0xBE,&datUtil);
    if(errorCode != D_ERR_NONE)return errorCode;
    bmp180Data.MD = (int16_t)datUtil; 
    /* 过采样参数，0-3 */
	bmp180Data.OSS = ossSet;	
    return D_ERR_NONE;
}


//读取并计算温度和压力传感器值
D_ERR BoardBmp180_ReadTempPress(float* temp,uint32_t* press)
{
    long UT, X1, X2, B5, T;
	long UP, X3, B3, B6, B7, p;
	unsigned long B4;
    D_ERR errorCode = D_ERR_NONE;
    uint16_t srcDat16 = 0;
    uint32_t srcDat32 = 0;

	/* 读温度原始值 */
	errorCode = BoardBmp180WriteRegByte(0xF4, 0x2E);
    if(errorCode != D_ERR_NONE)return errorCode;
    /* 等待转换结束 */
	BoardBmp180WaitConvert();	
	errorCode = BoardBmp180ReadRegTwoByte(0xF6,&srcDat16);
    if(errorCode != D_ERR_NONE)return errorCode;
    UT = srcDat16;

	/* 读压力原始值 */
	errorCode = BoardBmp180WriteRegByte(0xF4, 0x34 + (bmp180Data.OSS << 6));
    if(errorCode != D_ERR_NONE)return errorCode;
    /* 等待转换结束 */
	BoardBmp180WaitConvert();	
	errorCode = BoardBmp180ReadRegThreeByte(0xF6,&srcDat32);
    UP = (srcDat32 >> (8 - bmp180Data.OSS));

	/* 计算真实温度（单位 0.1摄氏度） */
	X1 = ((long)(UT - bmp180Data.AC6) * bmp180Data.AC5) >> 15;
	X2 = ((long)bmp180Data.MC << 11) / (X1 + bmp180Data.MD);
	B5 = X1 + X2;	/* 该系数将用于压力的温度补偿计算 */
	T = (B5 + 8) >> 4;
    *temp = T;
    *temp /= 10.0;

	/* 计算真实压力值（单位 Pa） */
	B6 = B5 - 4000;
	X1 = (bmp180Data.B2 * (B6 * B6) >> 12) >> 11;
	X2 = (bmp180Data.AC2 * B6) >> 11;
	X3 = X1 + X2;
	B3 = (((((long)bmp180Data.AC1) * 4 + X3) << bmp180Data.OSS) + 2) >> 2;

	X1 = (bmp180Data.AC3 * B6) >> 13;
	X2 = (bmp180Data.B1 * ((B6 * B6) >> 12)) >> 16;
	X3 = ((X1 + X2) + 2) >> 2;
	B4 = (bmp180Data.AC4 * (unsigned long)(X3 + 32768)) >> 15;

	B7 = ((unsigned long)(UP - B3) * (50000 >> bmp180Data.OSS));
	if (B7 < 0x80000000)
	{
		p = (B7 << 1) / B4;
	}
	else
	{
		p = (B7 / B4) << 1;
	}

	X1 = (p >> 8) * (p >> 8);
	X1 = (X1 * 3038) >> 16;
	X2 = (-7357 * p) >> 16;
 	p =  p + ((X1 + X2 + 3791) >> 4);

	*press = p;		

    return D_ERR_NONE;
}



