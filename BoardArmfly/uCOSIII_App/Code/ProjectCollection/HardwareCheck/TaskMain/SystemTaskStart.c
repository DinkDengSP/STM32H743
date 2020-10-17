/*******************************************************************
**Description: Copyright(c) 2018-2090 DengXiaojun,All rights reserved.
**Author: DengXiaoJun
**Date: 2020-10-11 22:36:02
**LastEditors: DengXiaoJun
**LastEditTime: 2020-10-17 23:45:51
**FilePath: \ProjectFilesd:\DinkGitHub\STM32H743\BoardArmfly\uCOSIII_App\Code\ProjectCollection\HardwareCheck\TaskMain\SystemTaskStart.c
**ModifyRecord1:    
******************************************************************/
#include "SystemTaskConfig.h"

//任务控制块,8字节对齐
#pragma pack(8)
//任务堆栈
CPU_STK stackBufferTaskStart[STK_SIZE_TASK_START]@".dtcm_ram";
#pragma pack()

//启动任务的堆栈
OS_TCB tcbTaskStart@".dtcm_ram";

//板上外设初始化
void BoardDeviceInit(void);


//系统服务任务配置数组
static const OS_TASK_CREATE_CONFIG ServiceTaskArray[] = {
    //心跳任务
    {&tcbServiceTaskHeart, NAME_SERVICE_TASK_HEART, ServiceTaskFuncHeart,PRIO_SERVICE_TASK_HEART, &stackBufferServiceTaskHeart[0],STK_SIZE_SERVICE_TASK_HEART / 10, STK_SIZE_SERVICE_TASK_HEART,1},
};
//系统服务任务的数量,用于初始化
#define COUNT_SERVICE_TASK       (sizeof(ServiceTaskArray)/sizeof(ServiceTaskArray[0]))


void TaskFuncStart(void *p_arg)
{
    p_arg = p_arg;
    //辅助变量
        uint16_t indexUtil = 0;
    //临界段变量
        OS_ERR  os_err;
        CPU_SR_ALLOC();
    //默认为空的追踪函数
        OS_TRACE_INIT(); 
    //状态初始化
        #if OS_CFG_STAT_TASK_EN > 0u
            OSStatTaskCPUUsageInit(&os_err);                           
        #endif
    //中断时间测量初始化
        #ifdef CPU_CFG_INT_DIS_MEAS_EN
            CPU_IntDisMeasMaxCurReset();
        #endif
    //板上设备初始化
        BoardDeviceInit();
    //进入临界区
        CPU_CRITICAL_ENTER();
    //创建系统任务
        for (indexUtil = 0; indexUtil < COUNT_SERVICE_TASK; indexUtil++)
        {
            OSTaskCreate((OS_TCB *)ServiceTaskArray[indexUtil].tcbTaskPtr,          //任务控制块
                        (CPU_CHAR *)ServiceTaskArray[indexUtil].taskNamePtr,        //任务名字
                        (OS_TASK_PTR)ServiceTaskArray[indexUtil].taskFuncPtr,       //任务函数
                        (void *)0,                                                  //传递给任务函数的参数
                        (OS_PRIO)ServiceTaskArray[indexUtil].taskPrio,              //任务优先级
                        (CPU_STK *)ServiceTaskArray[indexUtil].taskStkBasePtr,      //任务堆栈基地址
                        (CPU_STK_SIZE)ServiceTaskArray[indexUtil].taskStkSizeLimit, //任务堆栈深度限位
                        (CPU_STK_SIZE)ServiceTaskArray[indexUtil].taskStkSize,      //任务堆栈大小
                        (OS_MSG_QTY)ServiceTaskArray[indexUtil].msgQueenSize,       //任务内部消息队列能够接收的最大消息数目,为0时禁止接收消息
                        (OS_TICK)0,                                                 //当使能时间片轮转时的时间片长度，为0时为默认长度，
                        (void *)0,                                                  //用户补充的存储区
                        (OS_OPT)OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR,          //任务选项
                        (OS_ERR *)&os_err);                                         //存放该函数错误时的返回值
        } 
    //服务层IPC数据结构初始化
    //服务层系统状态和系统参数初始化
    //创建应用层任务
    //应用层IPC数据结构初始化
    //应用层系统状态和系统参数初始化
    //退出临界区
        CPU_CRITICAL_EXIT();
    //删除start_task任务自身
        OSTaskDel((OS_TCB *)0, &os_err);
}


void MCU_WWDG_CallBack()
{
    BoardLedToogle(BOARD_LED1_REMOTE);
}

//板上外设初始化
void BoardDeviceInit(void)
{
    //初始化外部IO口
        BoardExtPort_Init();
    //随机数初始化
        MCU_RandomInit();
    //初始化LED系统
        BoardLedInit(BOARD_LED1_REMOTE,BOARD_LED_ON);
        BoardLedInit(BOARD_LED2_NRF24L01,BOARD_LED_ON);
        BoardLedInit(BOARD_LED3_W25Q128,BOARD_LED_ON);
        BoardLedInit(BOARD_LED4_DHT11,BOARD_LED_ON);
    //芯片电子签名初始化
        MCU_UNIQUE_ID localUniqueID = {0};
        MCU_UniqueID_Read(&localUniqueID);
        //打印信息
        SEGGER_RTT_printf(0," idSn0 = 0X%08X\r\n idSn1 = 0X%08X\r\n idSn2 = 0X%08X\r\n flashSizeID = 0X%08X\r\n",
                            localUniqueID.idSn0,localUniqueID.idSn1,localUniqueID.idSn2,localUniqueID.flashSizeID);

    
    //等待开机指示,留一个时间让出现可以观察到的重复初始化现象
        CoreDelayMs(200);
    //关闭全部LED灯
        BoardLedSet(BOARD_LED1_REMOTE,BOARD_LED_OFF);
        BoardLedSet(BOARD_LED2_NRF24L01,BOARD_LED_OFF);
        BoardLedSet(BOARD_LED3_W25Q128,BOARD_LED_OFF);
        BoardLedSet(BOARD_LED4_DHT11,BOARD_LED_OFF);
    //芯片启动正式任务
        SEGGER_RTT_printf(0,"System App Start\r\n");  
    //窗口看门狗
        MCU_WWDG_Init(127,80,WWDG_PRESCALER_8,MCU_WWDG_CallBack); 
}
