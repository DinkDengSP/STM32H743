/*******************************************************************
**Description: Copyright(c) 2018-2090 DengXiaojun,All rights reserved.
**Author: DengXiaoJun
**Date: 2020-10-12 23:19:07
**LastEditors: DengXiaoJun
**LastEditTime: 2020-10-15 23:41:36
**FilePath: \ProjectFilesd:\DinkGitHub\STM32H743\BoardArmfly\uCOSIII_App\Code\ProjectCollection\HardwareCheck\DriverConfig\CoreConfig\MPU_Config.c
**ModifyRecord1:    
******************************************************************/
#include "MPU_Config.h"

//系统配置MPU区域0
const MPU_REGION_CONFIG mpuRegionConfigNBR0 = {
    MPU_REGION_FUNC_STATE_DISABLE,                 //MPU_REGION_FUNC_STATE MPU区域功能设置
    0x00000000,                                    //uint32_t baseAddr;//MPU管理的地址起点
    MPU_REGION_LENGTH_4GB,                         //MPU_REGION_LENGTH MPU管理的地址长度
    MPU_REGION_ACCESS_PERMISSIONS_FULL_ACCESS,     //MPU_REGION_ACCESS_PERMISSIONS MPU访问权限
    MPU_EXEC_STATE_ENABLE,                         //MPU_EXEC_STATE 该区域是否可以运行代码
    MPU_TEX_SET_LEVEL0,                            //MPU_TEX_SET 该区域的Cache策略
    MPU_BUFFER_STATE_ENABLE,                       //MPU_BUFFER_STATE CACHE模式下是否使用缓冲
    MPU_CACHE_STATE_ENABLE,                        //MPU_CACHE_STATE 是否开启cache功能
    MPU_SHARE_STATE_DISABLE,                        //MPU_SHARE_STATE Cache模式下是否多核共享内存区域
    0x00,                                          //subRegionEnableConfig子区域控制,一共八个,一般设置为0X00
};

//系统配置MPU区域1
const MPU_REGION_CONFIG mpuRegionConfigNBR1 = {
    MPU_REGION_FUNC_STATE_DISABLE,                 //MPU_REGION_FUNC_STATE MPU区域功能设置
    0x00000000,                                    //uint32_t baseAddr;//MPU管理的地址起点
    MPU_REGION_LENGTH_4GB,                         //MPU_REGION_LENGTH MPU管理的地址长度
    MPU_REGION_ACCESS_PERMISSIONS_FULL_ACCESS,     //MPU_REGION_ACCESS_PERMISSIONS MPU访问权限
    MPU_EXEC_STATE_ENABLE,                         //MPU_EXEC_STATE 该区域是否可以运行代码
    MPU_TEX_SET_LEVEL0,                            //MPU_TEX_SET 该区域的Cache策略
    MPU_BUFFER_STATE_ENABLE,                       //MPU_BUFFER_STATE CACHE模式下是否使用缓冲
    MPU_CACHE_STATE_ENABLE,                        //MPU_CACHE_STATE 是否开启cache功能
    MPU_SHARE_STATE_DISABLE,                        //MPU_SHARE_STATE Cache模式下是否多核共享内存区域
    0x00,                                          //subRegionEnableConfig子区域控制,一共八个,一般设置为0X00
};

//系统配置MPU区域2
const MPU_REGION_CONFIG mpuRegionConfigNBR2 = {
    MPU_REGION_FUNC_STATE_DISABLE,                 //MPU_REGION_FUNC_STATE MPU区域功能设置
    0x00000000,                                    //uint32_t baseAddr;//MPU管理的地址起点
    MPU_REGION_LENGTH_4GB,                         //MPU_REGION_LENGTH MPU管理的地址长度
    MPU_REGION_ACCESS_PERMISSIONS_FULL_ACCESS,     //MPU_REGION_ACCESS_PERMISSIONS MPU访问权限
    MPU_EXEC_STATE_ENABLE,                         //MPU_EXEC_STATE 该区域是否可以运行代码
    MPU_TEX_SET_LEVEL0,                            //MPU_TEX_SET 该区域的Cache策略
    MPU_BUFFER_STATE_ENABLE,                       //MPU_BUFFER_STATE CACHE模式下是否使用缓冲
    MPU_CACHE_STATE_ENABLE,                        //MPU_CACHE_STATE 是否开启cache功能
    MPU_SHARE_STATE_DISABLE,                        //MPU_SHARE_STATE Cache模式下是否多核共享内存区域
    0x00,                                          //subRegionEnableConfig子区域控制,一共八个,一般设置为0X00
};

//系统配置MPU区域3
const MPU_REGION_CONFIG mpuRegionConfigNBR3 = {
    MPU_REGION_FUNC_STATE_DISABLE,                 //MPU_REGION_FUNC_STATE MPU区域功能设置
    0x00000000,                                    //uint32_t baseAddr;//MPU管理的地址起点
    MPU_REGION_LENGTH_4GB,                         //MPU_REGION_LENGTH MPU管理的地址长度
    MPU_REGION_ACCESS_PERMISSIONS_FULL_ACCESS,     //MPU_REGION_ACCESS_PERMISSIONS MPU访问权限
    MPU_EXEC_STATE_ENABLE,                         //MPU_EXEC_STATE 该区域是否可以运行代码
    MPU_TEX_SET_LEVEL0,                            //MPU_TEX_SET 该区域的Cache策略
    MPU_BUFFER_STATE_ENABLE,                       //MPU_BUFFER_STATE CACHE模式下是否使用缓冲
    MPU_CACHE_STATE_ENABLE,                        //MPU_CACHE_STATE 是否开启cache功能
    MPU_SHARE_STATE_DISABLE,                        //MPU_SHARE_STATE Cache模式下是否多核共享内存区域
    0x00,                                          //subRegionEnableConfig子区域控制,一共八个,一般设置为0X00
};

//系统配置MPU区域4
const MPU_REGION_CONFIG mpuRegionConfigNBR4 = {
    MPU_REGION_FUNC_STATE_DISABLE,                 //MPU_REGION_FUNC_STATE MPU区域功能设置
    0x00000000,                                    //uint32_t baseAddr;//MPU管理的地址起点
    MPU_REGION_LENGTH_4GB,                         //MPU_REGION_LENGTH MPU管理的地址长度
    MPU_REGION_ACCESS_PERMISSIONS_FULL_ACCESS,     //MPU_REGION_ACCESS_PERMISSIONS MPU访问权限
    MPU_EXEC_STATE_ENABLE,                         //MPU_EXEC_STATE 该区域是否可以运行代码
    MPU_TEX_SET_LEVEL0,                            //MPU_TEX_SET 该区域的Cache策略
    MPU_BUFFER_STATE_ENABLE,                       //MPU_BUFFER_STATE CACHE模式下是否使用缓冲
    MPU_CACHE_STATE_ENABLE,                        //MPU_CACHE_STATE 是否开启cache功能
    MPU_SHARE_STATE_DISABLE,                        //MPU_SHARE_STATE Cache模式下是否多核共享内存区域
    0x00,                                          //subRegionEnableConfig子区域控制,一共八个,一般设置为0X00
};

//系统配置MPU区域5
const MPU_REGION_CONFIG mpuRegionConfigNBR5 = {
    MPU_REGION_FUNC_STATE_DISABLE,                 //MPU_REGION_FUNC_STATE MPU区域功能设置
    0x00000000,                                    //uint32_t baseAddr;//MPU管理的地址起点
    MPU_REGION_LENGTH_4GB,                         //MPU_REGION_LENGTH MPU管理的地址长度
    MPU_REGION_ACCESS_PERMISSIONS_FULL_ACCESS,     //MPU_REGION_ACCESS_PERMISSIONS MPU访问权限
    MPU_EXEC_STATE_ENABLE,                         //MPU_EXEC_STATE 该区域是否可以运行代码
    MPU_TEX_SET_LEVEL0,                            //MPU_TEX_SET 该区域的Cache策略
    MPU_BUFFER_STATE_ENABLE,                       //MPU_BUFFER_STATE CACHE模式下是否使用缓冲
    MPU_CACHE_STATE_ENABLE,                        //MPU_CACHE_STATE 是否开启cache功能
    MPU_SHARE_STATE_DISABLE,                        //MPU_SHARE_STATE Cache模式下是否多核共享内存区域
    0x00,                                          //subRegionEnableConfig子区域控制,一共八个,一般设置为0X00
};

//系统配置MPU区域6
const MPU_REGION_CONFIG mpuRegionConfigNBR6 = {
    MPU_REGION_FUNC_STATE_DISABLE,                 //MPU_REGION_FUNC_STATE MPU区域功能设置
    0x00000000,                                    //uint32_t baseAddr;//MPU管理的地址起点
    MPU_REGION_LENGTH_4GB,                         //MPU_REGION_LENGTH MPU管理的地址长度
    MPU_REGION_ACCESS_PERMISSIONS_FULL_ACCESS,     //MPU_REGION_ACCESS_PERMISSIONS MPU访问权限
    MPU_EXEC_STATE_ENABLE,                         //MPU_EXEC_STATE 该区域是否可以运行代码
    MPU_TEX_SET_LEVEL0,                            //MPU_TEX_SET 该区域的Cache策略
    MPU_BUFFER_STATE_ENABLE,                       //MPU_BUFFER_STATE CACHE模式下是否使用缓冲
    MPU_CACHE_STATE_ENABLE,                        //MPU_CACHE_STATE 是否开启cache功能
    MPU_SHARE_STATE_DISABLE,                        //MPU_SHARE_STATE Cache模式下是否多核共享内存区域
    0x00,                                          //subRegionEnableConfig子区域控制,一共八个,一般设置为0X00
};

//系统配置MPU区域7
const MPU_REGION_CONFIG mpuRegionConfigNBR7 = {
    MPU_REGION_FUNC_STATE_DISABLE,                 //MPU_REGION_FUNC_STATE MPU区域功能设置
    0x00000000,                                    //uint32_t baseAddr;//MPU管理的地址起点
    MPU_REGION_LENGTH_4GB,                         //MPU_REGION_LENGTH MPU管理的地址长度
    MPU_REGION_ACCESS_PERMISSIONS_FULL_ACCESS,     //MPU_REGION_ACCESS_PERMISSIONS MPU访问权限
    MPU_EXEC_STATE_ENABLE,                         //MPU_EXEC_STATE 该区域是否可以运行代码
    MPU_TEX_SET_LEVEL0,                            //MPU_TEX_SET 该区域的Cache策略
    MPU_BUFFER_STATE_ENABLE,                       //MPU_BUFFER_STATE CACHE模式下是否使用缓冲
    MPU_CACHE_STATE_ENABLE,                        //MPU_CACHE_STATE 是否开启cache功能
    MPU_SHARE_STATE_DISABLE,                        //MPU_SHARE_STATE Cache模式下是否多核共享内存区域
    0x00,                                          //subRegionEnableConfig子区域控制,一共八个,一般设置为0X00
};

//系统配置MPU区域8
//SDRAM的MPU配置
//MPU属性为Write back, Read allocate，Write allocate
const MPU_REGION_CONFIG mpuRegionConfigNBR8 = {
    MPU_REGION_FUNC_STATE_ENABLE,                  //MPU_REGION_FUNC_STATE MPU区域功能设置
    0xC0000000,                                    //uint32_t baseAddr;//MPU管理的地址起点
    MPU_REGION_LENGTH_32MB,                         //MPU_REGION_LENGTH MPU管理的地址长度
    MPU_REGION_ACCESS_PERMISSIONS_FULL_ACCESS,     //MPU_REGION_ACCESS_PERMISSIONS MPU访问权限
    MPU_EXEC_STATE_ENABLE,                         //MPU_EXEC_STATE 该区域是否可以运行代码
    MPU_TEX_SET_LEVEL1,                            //MPU_TEX_SET 该区域的Cache策略
    MPU_BUFFER_STATE_ENABLE,                       //MPU_BUFFER_STATE CACHE模式下是否使用缓冲
    MPU_CACHE_STATE_ENABLE,                        //MPU_CACHE_STATE 是否开启cache功能
    MPU_SHARE_STATE_DISABLE,                       //MPU_SHARE_STATE Cache模式下是否多核共享内存区域
    0x00,                                          //subRegionEnableConfig子区域控制,一共八个,一般设置为0X00
};


//系统配置MPU区域9
//EXT_IO的MPU配置地址和长度
//属性为Device或者Strongly Ordered ----Buffer为1,Cache为0,Tex为0,Device配置
const MPU_REGION_CONFIG mpuRegionConfigNBR9 = {
    MPU_REGION_FUNC_STATE_ENABLE,                  //MPU_REGION_FUNC_STATE MPU区域功能设置
    0x60000000,                                    //uint32_t baseAddr;//MPU管理的地址起点
    MPU_REGION_LENGTH_64KB,                        //MPU_REGION_LENGTH MPU管理的地址长度
    MPU_REGION_ACCESS_PERMISSIONS_FULL_ACCESS,     //MPU_REGION_ACCESS_PERMISSIONS MPU访问权限
    MPU_EXEC_STATE_DISABLE,                        //MPU_EXEC_STATE 该区域是否可以运行代码
    MPU_TEX_SET_LEVEL0,                            //MPU_TEX_SET 该区域的Cache策略
    MPU_BUFFER_STATE_ENABLE,                       //MPU_BUFFER_STATE CACHE模式下是否使用缓冲
    MPU_CACHE_STATE_DISABLE,                       //MPU_CACHE_STATE 是否开启cache功能
    MPU_SHARE_STATE_DISABLE,                       //MPU_SHARE_STATE Cache模式下是否多核共享内存区域
    0x00,                                          //subRegionEnableConfig子区域控制,一共八个,一般设置为0X00
};


//系统配置MPU区域10
/*配置D3_BACKUP_SRAM的MPU属性为Write back, Read allocate，Write allocate -----Buffer为1 Cache为1,Tex为1 Normal配置*/
/*写入时,同时写入Cache和SRAM,读取时候,若Cache中已经存在,则读取Cache不读取SRAM,否则,读取SRAM*/
const MPU_REGION_CONFIG mpuRegionConfigNBR10 = {
    MPU_REGION_FUNC_STATE_ENABLE,                  //MPU_REGION_FUNC_STATE MPU区域功能设置
    0x38800000,                                    //uint32_t baseAddr;//MPU管理的地址起点
    MPU_REGION_LENGTH_4KB,                         //MPU_REGION_LENGTH MPU管理的地址长度
    MPU_REGION_ACCESS_PERMISSIONS_FULL_ACCESS,     //MPU_REGION_ACCESS_PERMISSIONS MPU访问权限
    MPU_EXEC_STATE_ENABLE,                         //MPU_EXEC_STATE 该区域是否可以运行代码
    MPU_TEX_SET_LEVEL1,                            //MPU_TEX_SET 该区域的Cache策略
    MPU_BUFFER_STATE_ENABLE,                       //MPU_BUFFER_STATE CACHE模式下是否使用缓冲
    MPU_CACHE_STATE_ENABLE,                        //MPU_CACHE_STATE 是否开启cache功能
    MPU_SHARE_STATE_DISABLE,                       //MPU_SHARE_STATE Cache模式下是否多核共享内存区域
    0x00,                                          //subRegionEnableConfig子区域控制,一共八个,一般设置为0X00
};


//系统配置MPU区域11
/*配置D3_SRAM4的MPU属性为Write back, Read allocate，Write allocate -----Buffer为1 Cache为1,Tex为1 Normal配置*/
/*写入时,同时写入Cache和SRAM,读取时候,若Cache中已经存在,则读取Cache不读取SRAM,否则,读取SRAM*/
const MPU_REGION_CONFIG mpuRegionConfigNBR11 = {
    MPU_REGION_FUNC_STATE_ENABLE,                  //MPU_REGION_FUNC_STATE MPU区域功能设置
    0x38000000,                                    //uint32_t baseAddr;//MPU管理的地址起点
    MPU_REGION_LENGTH_64KB,                        //MPU_REGION_LENGTH MPU管理的地址长度
    MPU_REGION_ACCESS_PERMISSIONS_FULL_ACCESS,     //MPU_REGION_ACCESS_PERMISSIONS MPU访问权限
    MPU_EXEC_STATE_ENABLE,                         //MPU_EXEC_STATE 该区域是否可以运行代码
    MPU_TEX_SET_LEVEL1,                            //MPU_TEX_SET 该区域的Cache策略
    MPU_BUFFER_STATE_ENABLE,                       //MPU_BUFFER_STATE CACHE模式下是否使用缓冲
    MPU_CACHE_STATE_ENABLE,                        //MPU_CACHE_STATE 是否开启cache功能
    MPU_SHARE_STATE_DISABLE,                       //MPU_SHARE_STATE Cache模式下是否多核共享内存区域
    0x00,                                          //subRegionEnableConfig子区域控制,一共八个,一般设置为0X00
};


//系统配置MPU区域12
/*配置D2_SRAM3的MPU属性为Write back, Read allocate，Write allocate -----Buffer为1 Cache为1,Tex为1 Normal配置*/
/*写入时,同时写入Cache和SRAM,读取时候,若Cache中已经存在,则读取Cache不读取SRAM,否则,读取SRAM*/
const MPU_REGION_CONFIG mpuRegionConfigNBR12 = {
    MPU_REGION_FUNC_STATE_ENABLE,                  //MPU_REGION_FUNC_STATE MPU区域功能设置
    0x30040000,                                    //uint32_t baseAddr;//MPU管理的地址起点
    MPU_REGION_LENGTH_32KB,                        //MPU_REGION_LENGTH MPU管理的地址长度
    MPU_REGION_ACCESS_PERMISSIONS_FULL_ACCESS,     //MPU_REGION_ACCESS_PERMISSIONS MPU访问权限
    MPU_EXEC_STATE_ENABLE,                         //MPU_EXEC_STATE 该区域是否可以运行代码
    MPU_TEX_SET_LEVEL1,                            //MPU_TEX_SET 该区域的Cache策略
    MPU_BUFFER_STATE_ENABLE,                       //MPU_BUFFER_STATE CACHE模式下是否使用缓冲
    MPU_CACHE_STATE_ENABLE,                        //MPU_CACHE_STATE 是否开启cache功能
    MPU_SHARE_STATE_DISABLE,                       //MPU_SHARE_STATE Cache模式下是否多核共享内存区域
    0x00,                                          //subRegionEnableConfig子区域控制,一共八个,一般设置为0X00
};


        
//系统配置MPU区域13 D2_SRAM2
/*配置D2_SRAM2的MPU属性为Write back, Read allocate，Write allocate -----Buffer为1 Cache为1,Tex为1 Normal配置*/
/*写入时,同时写入Cache和SRAM,读取时候,若Cache中已经存在,则读取Cache不读取SRAM,否则,读取SRAM*/
const MPU_REGION_CONFIG mpuRegionConfigNBR13 = {
    MPU_REGION_FUNC_STATE_ENABLE,                  //MPU_REGION_FUNC_STATE MPU区域功能设置
    0x30020000,                                    //uint32_t baseAddr;//MPU管理的地址起点
    MPU_REGION_LENGTH_128KB,                       //MPU_REGION_LENGTH MPU管理的地址长度
    MPU_REGION_ACCESS_PERMISSIONS_FULL_ACCESS,     //MPU_REGION_ACCESS_PERMISSIONS MPU访问权限
    MPU_EXEC_STATE_ENABLE,                         //MPU_EXEC_STATE 该区域是否可以运行代码
    MPU_TEX_SET_LEVEL1,                            //MPU_TEX_SET 该区域的Cache策略
    MPU_BUFFER_STATE_ENABLE,                       //MPU_BUFFER_STATE CACHE模式下是否使用缓冲
    MPU_CACHE_STATE_ENABLE,                        //MPU_CACHE_STATE 是否开启cache功能
    MPU_SHARE_STATE_DISABLE,                       //MPU_SHARE_STATE Cache模式下是否多核共享内存区域
    0x00,                                          //subRegionEnableConfig子区域控制,一共八个,一般设置为0X00
};


//系统配置MPU区域14 D2_SRAM1
/*写入时,同时写入SRAM,读取时候,若Cache中已经存在,则读取Cache不读取SRAM,否则,读取SRAM*/
//这块内存用作共享内存
const MPU_REGION_CONFIG mpuRegionConfigNBR14 = {
    MPU_REGION_FUNC_STATE_ENABLE,                  //MPU_REGION_FUNC_STATE MPU区域功能设置
    0x30000000,                                    //uint32_t baseAddr;//MPU管理的地址起点
    MPU_REGION_LENGTH_128KB,                       //MPU_REGION_LENGTH MPU管理的地址长度
    MPU_REGION_ACCESS_PERMISSIONS_FULL_ACCESS,     //MPU_REGION_ACCESS_PERMISSIONS MPU访问权限
    MPU_EXEC_STATE_ENABLE,                         //MPU_EXEC_STATE 该区域是否可以运行代码
    MPU_TEX_SET_LEVEL0,                            //MPU_TEX_SET 该区域的Cache策略
    MPU_BUFFER_STATE_ENABLE,                       //MPU_BUFFER_STATE CACHE模式下是否使用缓冲
    MPU_CACHE_STATE_ENABLE,                        //MPU_CACHE_STATE 是否开启cache功能
    MPU_SHARE_STATE_DISABLE,                       //MPU_SHARE_STATE Cache模式下是否多核共享内存区域
    0x00,                                          //subRegionEnableConfig子区域控制,一共八个,一般设置为0X00
};


//系统配置MPU区域15 AXI SRAM
/*配置AXI SRAM的MPU属性为Write back, Read allocate，Write allocate -----Buffer为1 Cache为1,Tex为1 Normal配置*/
/*写入时,同时写入Cache和SRAM,读取时候,若Cache中已经存在,则读取Cache不读取SRAM,否则,读取SRAM*/
const MPU_REGION_CONFIG mpuRegionConfigNBR15 = {
    MPU_REGION_FUNC_STATE_ENABLE,                   //MPU_REGION_FUNC_STATE MPU区域功能设置
    0x24000000,                                     //baseAddrMPU管理的地址起点
    MPU_REGION_LENGTH_512B,                         //MPU_REGION_LENGTH MPU管理的地址长度
    MPU_REGION_ACCESS_PERMISSIONS_FULL_ACCESS,      //MPU_REGION_ACCESS_PERMISSIONS MPU访问权限
    MPU_EXEC_STATE_ENABLE,                          //MPU_EXEC_STATE 该区域是否可以运行代码
    MPU_TEX_SET_LEVEL1,                             //MPU_TEX_SET 该区域的Cache策略
    MPU_BUFFER_STATE_ENABLE,                        //MPU_BUFFER_STATE CACHE模式下是否使用缓冲
    MPU_CACHE_STATE_ENABLE,                         //MPU_CACHE_STATE 是否开启cache功能
    MPU_SHARE_STATE_DISABLE,                        //MPU_SHARE_STATE Cache模式下是否多核共享内存区域
    0x00,                                           //subRegionEnableConfig子区域控制,一共八个,一般设置为0X00
};


