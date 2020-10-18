/*******************************************************************
**Description: Copyright(c) 2018-2090 DengXiaojun,All rights reserved.
**Author: DengXiaoJun
**Date: 2020-10-17 00:26:54
**LastEditors: DengXiaoJun
**LastEditTime: 2020-10-19 00:55:52
**FilePath: \ProjectFilesd:\DinkGitHub\STM32H743\BoardArmfly\uCOSIII_App\Code\Driver\DriverMCU\MCU_IIC.c
**ModifyRecord1:    
******************************************************************/
#include "MCU_IIC.h"
#include "MCU_Port.h"

//PB6
#define MCU_IIC_SCL_SET(x)  ((x == 0)?MCU_PortWriteSingle(MCU_PIN_B_6,Bit_RESET):MCU_PortWriteSingle(MCU_PIN_B_6,Bit_SET))
//PB9
#define MCU_IIC_SDA_SET(x)  ((x ==  0)?MCU_PortWriteSingle(MCU_PIN_B_9,Bit_RESET):MCU_PortWriteSingle(MCU_PIN_B_9,Bit_SET))
#define MCU_IIC_SDA_READ()  ((Bit_RESET == MCU_PortReadSingle(MCU_PIN_B_9))?0:1)
#define MCU_IIC_SDA_IN()    {GPIOB->MODER &= ~(3<<(9*2)); GPIOB->MODER |= 0<<9*2;}	//SDA输入模式
#define MCU_IIC_SDA_OUT()   {GPIOB->MODER &= ~(3<<(9*2)); GPIOB->MODER |= 1<<9*2;}  //SDA输出模式

//IIC总线访问需要获取的信号量
OS_MUTEX mutexMCU_IIC;
//IIC已经初始化过了的标志
static uint8_t MCU_IIC_InitFlag = 0;

//操作延时
static void MCU_IIC_Delay()
{
    //上拉电阻选择2.2K欧时，SCL上升沿时间约0.5us，如果选4.7K欧，则上升沿约1us
	//实际应用选择400KHz左右的速率即可
    CoreDelayUs(2);
}

//IIC初始化IO口
void MCU_IIC_Init(void)
{
    OS_ERR err;
    if(MCU_IIC_InitFlag == 0)
    {   
        //SCL初始化
        MCU_PortInit(MCU_PIN_B_6,MCU_PORT_MODE_OUTPUT_OD,MCU_PORT_PULL_NOPULL,MCU_PORT_SPEED_FREQ_LOW, 0);
        //SDA初始化
        MCU_PortInit(MCU_PIN_B_9,MCU_PORT_MODE_OUTPUT_OD,MCU_PORT_PULL_NOPULL,MCU_PORT_SPEED_FREQ_LOW, 0);
        //给一个停止信号,复位总线上所有设备到待机模式
        MCU_IIC_SendStop();
        //IIC信号量初始化
        OSMutexCreate((OS_MUTEX*	)&mutexMCU_IIC,
                    (CPU_CHAR*	)"mutexMCU_IIC",
                    (OS_ERR*		)&err);
    }
    //设置初始化标志,防止反复初始化
    MCU_IIC_InitFlag = 1;
}

//IIC发送Start讯号
void MCU_IIC_SendStart(void)
{
    //SDA输出
    MCU_IIC_SDA_OUT();
    //当SCL高电平时，SDA出现一个下跳沿表示I2C总线启动信号
    MCU_IIC_SDA_SET(1);
    MCU_IIC_SCL_SET(1);
    //操作延时
    MCU_IIC_Delay();
    MCU_IIC_SDA_SET(0);
    //操作延时
    MCU_IIC_Delay();
    MCU_IIC_SCL_SET(0);
    MCU_IIC_Delay();
}

//IIC发送停止讯号
void MCU_IIC_SendStop()
{
    //SDA输出
    MCU_IIC_SDA_OUT();
    /* 当SCL高电平时，SDA出现一个上跳沿表示I2C总线停止信号 */
    MCU_IIC_SDA_SET(0);
    MCU_IIC_Delay();
    MCU_IIC_SCL_SET(1);
    //操作延时
    MCU_IIC_Delay();
    MCU_IIC_SDA_SET(1);
    MCU_IIC_Delay();
}

//IIC发出数据
void MCU_IIC_SendByte(uint8_t byteValue)
{
    //SDA输出
    MCU_IIC_SDA_OUT();
    uint8_t i;
	/* 先发送字节的高位bit7 */
	for (i = 0; i < 8; i++)
	{
		if (byteValue & 0x80)
		{
			MCU_IIC_SDA_SET(1);
		}
		else
		{
			MCU_IIC_SDA_SET(0);
		}
		MCU_IIC_Delay();
		MCU_IIC_SCL_SET(1);
		MCU_IIC_Delay();
		MCU_IIC_SCL_SET(0);
        /* 2019-03-14 针对GT811电容触摸，添加一行，相当于延迟几十ns */
		MCU_IIC_SCL_SET(0);	
		if (i == 7)
		{
            // 释放总线
			 MCU_IIC_SDA_SET(1); 
		}
        /* 左移一个bit */	
		byteValue <<= 1;
	}
}

//IIC读取数据
uint8_t MCU_IIC_ReadByte(void)
{
    //SDA输入
    MCU_IIC_SDA_IN();
    uint8_t i;
	uint8_t value;
	/* 读到第1个bit为数据的bit7 */
	value = 0;
	for (i = 0; i < 8; i++)
	{
		value <<= 1;
		MCU_IIC_SCL_SET(1);
		MCU_IIC_Delay();
		if (MCU_IIC_SDA_READ())
		{
			value++;
		}
		MCU_IIC_SCL_SET(0);
		MCU_IIC_Delay();
	}
	return value;
}

//IIC等待ACK,等到返回0,没等到返回1,0代表不存在问题
uint8_t MCU_IIC_WaitAck(uint32_t timeOutCount)
{
    uint8_t re;
    //SDA输出
    MCU_IIC_SDA_OUT();
    //CPU释放SDA总线
	MCU_IIC_SDA_SET(1);	
	MCU_IIC_Delay();
    //SDA输入
    MCU_IIC_SDA_IN();
    //CPU驱动SCL = 1, 此时器件会返回ACK应答
	MCU_IIC_SCL_SET(1);	
	MCU_IIC_Delay();
    /* CPU读取SDA口线状态 */
    do
    {
        if(0 == MCU_IIC_SDA_READ())
        {
            break;
        }
        timeOutCount--;
        MCU_IIC_Delay();
    }while(timeOutCount > 0);
    //检查结果
	if (timeOutCount == 0)re = 1;
	else re = 0;
	MCU_IIC_SCL_SET(0);
	MCU_IIC_Delay();
	return re;
}

//IIC发送ACK
void MCU_IIC_SendAck(void)
{
    //SDA输出
    MCU_IIC_SDA_OUT();
    /* CPU驱动SDA = 0 */
    MCU_IIC_SDA_SET(0);	
	MCU_IIC_Delay();
    /* CPU产生1个时钟 */
	MCU_IIC_SCL_SET(1);	
	MCU_IIC_Delay();
	MCU_IIC_SCL_SET(0);
	MCU_IIC_Delay();
    /* CPU释放SDA总线 */
	MCU_IIC_SDA_SET(1);	
	MCU_IIC_Delay();
}

//IIC发送NACK
void MCU_IIC_SendNAck(void)
{
    //SDA输出
    MCU_IIC_SDA_OUT();
    /* CPU驱动SDA = 1 */
    MCU_IIC_SDA_SET(1);	
	MCU_IIC_Delay();
    /* CPU产生1个时钟 */
	MCU_IIC_SCL_SET(1);	
	MCU_IIC_Delay();
	MCU_IIC_SCL_SET(0);
	MCU_IIC_Delay();
}

//IIC检查指定地址的设备是否存在
uint8_t MCU_IIC_CheckDeviceAddr(uint8_t deviceAddrWrite)
{
    uint8_t ucAck;
    //发送起始
    MCU_IIC_SendStart();
    //发送设备写地址
    MCU_IIC_SendByte(deviceAddrWrite);
    /* 检测设备的ACK应答 */
    ucAck = MCU_IIC_WaitAck(MCU_IIC_ACK_TIMEOUT_COUNT);
    //发送停止讯号	
    MCU_IIC_SendStop();
    //返回ACK结果
    return ucAck;
}


