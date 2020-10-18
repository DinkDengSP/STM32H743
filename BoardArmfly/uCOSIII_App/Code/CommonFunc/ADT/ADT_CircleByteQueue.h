/*******************************************************************
 *Description: Copyright(c) 2018-2090 DengXiaojun,All rights reserved.
 *Author: DengXiaoJun
 *Date: 2020-10-18 15:22:26
 *LastEditors: DengXiaoJun
 *LastEditTime: 2020-10-18 15:22:47
 *FilePath: \ProjectFilesd:\DinkGitHub\STM32H743\BoardArmfly\uCOSIII_App\Code\CommonFunc\ADT\ADT_CircleByteQueue.h
 *ModifyRecord1:    
******************************************************************/
#ifndef __ADT_CIRCLE_BYTE_QUEUE_H_
#define __ADT_CIRCLE_BYTE_QUEUE_H_
#include "ADT_Port.h"

//环形队列
//定义循环队列结构体
typedef struct ADT_CIRCLE_BYTE_QUEUE
{
    uint8_t *queueArrayBuffer; //循环队列缓冲区
    uint16_t frontPos;         //循环队列头,下一次取数据从该位置去取
    uint16_t rearPos;          //循环队列位,插入数据的时候看这个数据
    uint16_t maxSize;          //队列最大容量
    uint16_t currentSize;      //当前有效数据长度
}ADT_CIRCLE_BYTE_QUEUE;

//循环队列初始化
void ADT_CircleByteQueueInit(ADT_CIRCLE_BYTE_QUEUE* circleByteQueuePtr,uint8_t* bufferStartPtr,uint16_t bufferSize);

//获取循环队列最大容量
uint16_t ADT_CircleByteQueueGetMaxCapacity(ADT_CIRCLE_BYTE_QUEUE* circleByteQueuePtr);

//获取当前循环队列已经存储的数据
uint16_t ADT_CircleByteQueueGetCurrentSize(ADT_CIRCLE_BYTE_QUEUE* circleByteQueuePtr);

//获取当前循环队列中空数据的量
uint16_t ADT_CircleByteQueueGetCurrentEmptySize(ADT_CIRCLE_BYTE_QUEUE* circleByteQueuePtr);

//往循环队列中写入指定数量数据,当空间不足的时候,会将缓冲区数据填满,并返回真实的写入量
void ADT_CircleByteQueueWriteBuffer(ADT_CIRCLE_BYTE_QUEUE* circleByteQueuePtr,uint8_t* bufferWritePtr,uint16_t length,uint16_t* realWriteByteCount);

//从循环队列中读取指定数量数据,当数据不足时,已有的数据写到缓冲区,并返回真实读取到的数据
void ADT_CircleByteQueueReadBuffer(ADT_CIRCLE_BYTE_QUEUE* circleByteQueuePtr,uint8_t* bufferReadPtr,uint16_t length,uint16_t* realReadByteCount);



#endif

