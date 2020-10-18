/*******************************************************************
**Description: Copyright(c) 2018-2090 DengXiaojun,All rights reserved.
**Author: DengXiaoJun
**Date: 2020-10-18 15:22:37
**LastEditors: DengXiaoJun
**LastEditTime: 2020-10-18 15:26:05
**FilePath: \ProjectFilesd:\DinkGitHub\STM32H743\BoardArmfly\uCOSIII_App\Code\CommonFunc\ADT\ADT_CircleByteQueue.c
**ModifyRecord1:    
******************************************************************/
#include "ADT_CircleByteQueue.h"


//循环队列初始化
void ADT_CircleByteQueueInit(ADT_CIRCLE_BYTE_QUEUE* circleByteQueuePtr,uint8_t* bufferStartPtr,uint16_t bufferSize)
{
    //首先检测各个参数是否为空
    if(circleByteQueuePtr == NULL)return;
    if(bufferStartPtr == NULL)return;
    if(bufferSize == 0)return;
    ThreadLockInt();
    circleByteQueuePtr->queueArrayBuffer = bufferStartPtr;
    circleByteQueuePtr->frontPos = 0;
    circleByteQueuePtr->rearPos = 0;
    circleByteQueuePtr->maxSize = bufferSize;
    circleByteQueuePtr->currentSize = 0;
    ThreadUnlockInt();
}

//获取循环队列最大容量
uint16_t ADT_CircleByteQueueGetMaxCapacity(ADT_CIRCLE_BYTE_QUEUE* circleByteQueuePtr)
{
    if(circleByteQueuePtr == 0)
    {
        return 0;
    }
    return circleByteQueuePtr->maxSize;
}

//获取当前循环队列已经存储的数据
uint16_t ADT_CircleByteQueueGetCurrentSize(ADT_CIRCLE_BYTE_QUEUE* circleByteQueuePtr)
{
    if(circleByteQueuePtr == 0)
    {
        return 0;
    }
    return circleByteQueuePtr->currentSize;
}

//获取当前循环队列中空数据的量
uint16_t ADT_CircleByteQueueGetCurrentEmptySize(ADT_CIRCLE_BYTE_QUEUE* circleByteQueuePtr)
{
    if(circleByteQueuePtr == 0)
    {
        return 0;
    }
    uint16_t emptySize = 0;
    ThreadLockInt();
    emptySize = circleByteQueuePtr->maxSize - circleByteQueuePtr->currentSize;
    ThreadUnlockInt();
    return emptySize;
}

//往循环队列中写入指定数量数据,当空间不足的时候,会将缓冲区数据填满,并返回真实的写入量
void ADT_CircleByteQueueWriteBuffer(ADT_CIRCLE_BYTE_QUEUE* circleByteQueuePtr,uint8_t* bufferWritePtr,uint16_t length,uint16_t* realWriteByteCount)
{
    uint16_t writeCount = 0;
    if(circleByteQueuePtr == NULL)
    {
        *realWriteByteCount = 0;
        return;
    }
    if(bufferWritePtr == NULL)
    {
        *realWriteByteCount = 0;
        return;
    }
    ThreadLockInt();
    if(circleByteQueuePtr->maxSize == circleByteQueuePtr->currentSize)
    {
        //当前数据已满
        *realWriteByteCount = 0;
        ThreadUnlockInt();
        return;
    }
    else
    {
        while(circleByteQueuePtr->currentSize < circleByteQueuePtr->maxSize)
        {
            circleByteQueuePtr->queueArrayBuffer[circleByteQueuePtr->rearPos++] = bufferWritePtr[writeCount++];
            circleByteQueuePtr->rearPos %= circleByteQueuePtr->maxSize;
            circleByteQueuePtr->currentSize++;
            if(writeCount == length)
            {
                break;
            }
        }
        *realWriteByteCount = writeCount;
        ThreadUnlockInt();
        return;
    }
    
}

//从循环队列中读取指定数量数据,当数据不足时,已有的数据写到缓冲区,并返回真实读取到的数据
void ADT_CircleByteQueueReadBuffer(ADT_CIRCLE_BYTE_QUEUE* circleByteQueuePtr,uint8_t* bufferReadPtr,uint16_t length,uint16_t* realReadByteCount)
{
    uint16_t readCount = 0;
    if(circleByteQueuePtr == NULL)
    {
        *realReadByteCount = 0;
        return;
    }
    if(bufferReadPtr == NULL)
    {
        *realReadByteCount = 0;
        return;
    }
    ThreadLockInt();
    if(0 == circleByteQueuePtr->currentSize)
    {
        *realReadByteCount = 0;
        ThreadUnlockInt();
        return;
    }
    else
    {
        while(circleByteQueuePtr->currentSize > 0)
        {
            bufferReadPtr[readCount++] = circleByteQueuePtr->queueArrayBuffer[circleByteQueuePtr->frontPos++];
            circleByteQueuePtr->frontPos %= circleByteQueuePtr->maxSize;
            circleByteQueuePtr->currentSize--;
            if(readCount == length)
            {
                break;
            }
        }
        *realReadByteCount = readCount;
        ThreadUnlockInt();
        return;
    }
}
