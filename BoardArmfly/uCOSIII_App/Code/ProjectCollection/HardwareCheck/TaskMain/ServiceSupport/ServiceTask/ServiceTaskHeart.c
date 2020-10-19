/*******************************************************************
**Description: Copyright(c) 2018-2090 DengXiaojun,All rights reserved.
**Author: DengXiaoJun
**Date: 2020-10-13 22:43:17
**LastEditors: ,: DengXiaoJun
**LastEditTime: ,: 2020-10-19 23:50:26
**FilePath: ,: \ProjectFilesd:\DinkGitHub\STM32H743\BoardArmfly\uCOSIII_App\Code\ProjectCollection\HardwareCheck\TaskMain\ServiceSupport\ServiceTask\ServiceTaskHeart.c
**ModifyRecord1:    
******************************************************************/
#include "ServiceTaskConfig.h"


//任务控制块,8字节对齐
#pragma pack(8)
//任务堆栈
CPU_STK stackBufferServiceTaskHeart[STK_SIZE_SERVICE_TASK_HEART]@".dtcm_ram";
#pragma pack()

//任务控制块
OS_TCB tcbServiceTaskHeart@".dtcm_ram";

//显示MPU66050原始数据
void ServiceHeartUtilShowMPU6050SrcDat(void)
{
    D_ERR errorCode = D_ERR_NONE;
    DAT_MPU6050_SRC dataSrc;
    errorCode = BoardMPU6050_ReadCurrentAllDat(&dataSrc);
    if(errorCode != D_ERR_NONE)
    {
        return;
    }
    //打印状态
    SystemPrintf("dataSrc.tempValue = %f\r\n",dataSrc.tempValue);
    SystemPrintf("dataSrc.gyroscopeAxisX = %d\r\n",dataSrc.gyroscopeAxisX);
    SystemPrintf("dataSrc.gyroscopeAxisY = %d\r\n",dataSrc.gyroscopeAxisY);
    SystemPrintf("dataSrc.gyroscopeAxisZ = %d\r\n",dataSrc.gyroscopeAxisZ);
    SystemPrintf("dataSrc.accelerometerAxisX = %d\r\n",dataSrc.accelerometerAxisX);
    SystemPrintf("dataSrc.accelerometerAxisY = %d\r\n",dataSrc.accelerometerAxisY);
    SystemPrintf("dataSrc.accelerometerAxisZ = %d\r\n",dataSrc.accelerometerAxisZ);
}

//显示MPU66050姿态解算数据
void ServiceHeartUtilShowMPU6050Dmp(void)
{
    uint8_t dmpResult = 0;
    float pitch,roll,yaw;
    //循环读取
    do
    {
        dmpResult = mpu_dmp_get_data(&pitch,&roll,&yaw);
    }while(dmpResult != 0);
    //打印结果
    if(dmpResult != 0)
    {
        //打印相关讯息
        SystemPrintf("mpu_dmp_get_data Failed,ErrorCode = 0X%08X\r\n",dmpResult);
        return;
    }
    SystemPrintf("pitch: %f, roll: %f, yaw: %f\r\n",pitch,roll,yaw);
}

//任务函数
void ServiceTaskFuncHeart(void *p_arg)
{
    p_arg = p_arg;
    while(1)
    {
        BoardLedToogle(BOARD_LED3_W25Q128);
        CoreDelayMs(250);
        ServiceHeartUtilShowMPU6050Dmp();
    }
}
