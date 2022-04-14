/*
 * @Author: your name
 * @Date: 2022-04-14 20:00:08
 * @LastEditTime: 2022-04-14 20:09:28
 * @LastEditors: your name
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \21_使用自有协议实现LoRa组网\网关\DRIVER\SPIx\SPIx.h
 */
/******************************************************************
 * 文件：SPIx.h
 * 功能：声明SPI功能函数
 * 日期：2018-03-17
 * 作者：zx
 * 版本：Ver.1.0 | 最初版本
 *
 * Copyright (C) 2018 zx. All rights reserved.
 *******************************************************************/
#ifndef __SPI_H
#define __SPI_H
#include "stm32f10x.h"

void initSPIx();
void setNSS(u8 status);
void sendSPIxByte(u16 byte);
u16 readSPIxByte();

#endif
