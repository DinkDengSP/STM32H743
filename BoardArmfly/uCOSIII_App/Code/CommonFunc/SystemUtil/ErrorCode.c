/*******************************************************************
**Description: Copyright(c) 2018-2090 DengXiaojun,All rights reserved.
**Author: DengXiaoJun
**Date: 2020-10-12 23:15:53
**LastEditors: DengXiaoJun
**LastEditTime: 2020-10-18 17:09:18
**FilePath: \ProjectFilesd:\DinkGitHub\STM32H743\BoardArmfly\uCOSIII_App\Code\CommonFunc\SystemUtil\ErrorCode.c
**ModifyRecord1:    
******************************************************************/
#include "ErrorCode.h"

//转换HAL库错误
D_ERR ErrorConvertHAL(HAL_StatusTypeDef halError)
{
    D_ERR errorCode = D_ERR_NONE;
    switch(halError)
    {
        case HAL_OK:
            errorCode = D_ERR_NONE;
            break;
        case HAL_ERROR:
            errorCode = D_ERR_BOARD_MAIN_COMM_HAL_LIB;
            break;
        case HAL_BUSY:
            errorCode = D_ERR_BOARD_MAIN_COMM_HAL_BUSY;
            break;
        case HAL_TIMEOUT:
            errorCode = D_ERR_BOARD_MAIN_COMM_HAL_TIMEOUT;
            break;
        default:
            errorCode = D_ERR_NONE;
            break;
    }
    return errorCode;
}
