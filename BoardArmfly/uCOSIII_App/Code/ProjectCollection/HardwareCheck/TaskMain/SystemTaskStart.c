/*******************************************************************
**Description: Copyright(c) 2018-2090 DengXiaojun,All rights reserved.
**Author: DengXiaoJun
**Date: 2020-10-11 22:36:02
**LastEditors: DengXiaoJun
**LastEditTime: 2020-10-18 23:59:09
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


void JoysTickEnterCallBack(void)
{
    SystemPrintf("JoysTickEnterCallBack\r\n");
}
void JoysTickLeftCallBack(void)
{
    SystemPrintf("JoysTickLeftCallBack\r\n");
}
void JoysTickRightCallBack(void)
{
    SystemPrintf("JoysTickRightCallBack\r\n");
}
void JoysTickUpCallBack(void)
{
    SystemPrintf("JoysTickUpCallBack\r\n");
}
void JoysTickDownCallBack(void)
{
    SystemPrintf("JoysTickDownCallBack\r\n");
}

//板上外设初始化
void BoardDeviceInit(void)
{
    D_ERR errorCode = D_ERR_NONE;
    //初始化外部IO口
        BoardExtPort_Init();
    //随机数初始化
        MCU_RandomInit();
    //初始化LED系统
        BoardLedInit(BOARD_LED1_REMOTE,BOARD_LED_ON);
        BoardLedInit(BOARD_LED2_NRF24L01,BOARD_LED_ON);
        BoardLedInit(BOARD_LED3_W25Q128,BOARD_LED_ON);
        BoardLedInit(BOARD_LED4_DHT11,BOARD_LED_ON);
    //初始化Beep
        BoardBeepInit(BEEP_OFF);
    //系统串口初始化
        MCU_Uart1Init(115200,MCU_UART_LENGTH_8B,MCU_UART_STOPBIT1,MCU_UART_CHECK_MODE_NONE,MCU_UART_HARD_CONTROL_NONE,NULL);
    //芯片电子签名初始化
        MCU_UNIQUE_ID localUniqueID = {0};
        MCU_UniqueID_Read(&localUniqueID);
        SystemPrintf(" idSn0 = 0X%08X\r\n idSn1 = 0X%08X\r\n idSn2 = 0X%08X\r\n flashSizeID = 0X%08X\r\n",
                            localUniqueID.idSn0,localUniqueID.idSn1,localUniqueID.idSn2,localUniqueID.flashSizeID);
    //W25Q256初始化
        do
        {
            errorCode = BoardW25Q256_Init();
            if(errorCode != D_ERR_NONE)
            {
                SystemPrintf("BoardW25Q256_Init Failed,ErrorCode : 0X%08X\r\n",errorCode);
                CoreDelayMs(500);
                BoardLedToogle(BOARD_LED1_REMOTE);
            }
        } while (errorCode != D_ERR_NONE);
    //W25Q256自检
        do
        {
            errorCode = BoardW25Q256_Check();
            if(errorCode != D_ERR_NONE)
            {
                SystemPrintf("BoardW25Q256_Check Failed,ErrorCode : 0X%08X\r\n",errorCode);
                CoreDelayMs(500);
                BoardLedToogle(BOARD_LED1_REMOTE);
            }
        } while (errorCode != D_ERR_NONE);
    //W25Q64初始化
        BoardW25Q64_Init();
    //W25Q64自检
        do
        {
            errorCode = BoardW25Q64_Check();
            if(errorCode != D_ERR_NONE)
            {
                SystemPrintf("BoardW25Q64_Check Failed,ErrorCode : 0X%08X\r\n",errorCode);
                CoreDelayMs(500);
                BoardLedToogle(BOARD_LED1_REMOTE);
            }
        } while (errorCode != D_ERR_NONE);
    //SDRAM初始化
        BoardSDRAM_Init();
    //SDRAM自检
        do
        {
            errorCode = BoardSDRAM_SelfCheck();
            if(errorCode != D_ERR_NONE)
            {
                SystemPrintf("BoardSDRAM_SelfCheck Failed,ErrorCode : 0X%08X\r\n",errorCode);
                CoreDelayMs(500);
                BoardLedToogle(BOARD_LED1_REMOTE);
            }
        } while (errorCode != D_ERR_NONE);
    //内存管理初始化
        UserMemInit(MEM_DTCM);
        UserMemInit(MEM_AXI_SRAM);
        UserMemInit(MEM_D2_SRAM1);
        UserMemInit(MEM_D2_SRAM2);
        UserMemInit(MEM_D3_SRAM4);
        UserMemInit(MEM_SDRAM);
    //SD卡初始化
        do
        {
            errorCode = BoardSD_Init();
            if(errorCode != D_ERR_NONE)
            {
                SystemPrintf("BoardSD_Init Failed,ErrorCode : 0X%08X\r\n",errorCode);
                CoreDelayMs(500);
                BoardLedToogle(BOARD_LED1_REMOTE);
            }
        } while (errorCode != D_ERR_NONE);
    //显示SD卡信息
        BoardSD_PrintfCardMsg();
    //SD卡读写自检
        do
        {
            errorCode = BoardSD_Check();
            if(errorCode != D_ERR_NONE)
            {
                SystemPrintf("BoardSD_Check Failed,ErrorCode : 0X%08X\r\n",errorCode);
                CoreDelayMs(500);
                BoardLedToogle(BOARD_LED1_REMOTE);
            }
        } while (errorCode != D_ERR_NONE);
    //JoysTick初始化
        BoardJoysTickIntInit(JOYS_TICK_ENTER,BOARD_KEY_PREE_PRI,BOARD_KEY_SUB_PRI,JoysTickEnterCallBack);
        BoardJoysTickIntInit(JOYS_TICK_LEFT,BOARD_KEY_PREE_PRI,BOARD_KEY_SUB_PRI,JoysTickLeftCallBack);
        BoardJoysTickIntInit(JOYS_TICK_RIGHT,BOARD_KEY_PREE_PRI,BOARD_KEY_SUB_PRI,JoysTickRightCallBack);
        BoardJoysTickIntInit(JOYS_TICK_UP,BOARD_KEY_PREE_PRI,BOARD_KEY_SUB_PRI,JoysTickUpCallBack);
        BoardJoysTickIntInit(JOYS_TICK_DOWN,BOARD_KEY_PREE_PRI,BOARD_KEY_SUB_PRI,JoysTickDownCallBack);

    
    //蜂鸣器提示一下
        BoardBeepSetState(BEEP_ON);
    //等待开机指示,留一个时间让出现可以观察到的重复初始化现象
        CoreDelayMs(200);
    //蜂鸣器关闭
        BoardBeepSetState(BEEP_OFF);
    //关闭全部LED灯
        BoardLedSet(BOARD_LED1_REMOTE,BOARD_LED_OFF);
        BoardLedSet(BOARD_LED2_NRF24L01,BOARD_LED_OFF);
        BoardLedSet(BOARD_LED3_W25Q128,BOARD_LED_OFF);
        BoardLedSet(BOARD_LED4_DHT11,BOARD_LED_OFF);
    //芯片启动正式任务
        SystemPrintf("System App Start\r\n");  
}
