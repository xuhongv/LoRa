/*
 * @Author: your name
 * @Date: 2022-04-14 20:00:08
 * @LastEditTime: 2022-04-14 20:03:38
 * @LastEditors: your name
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \21_使用自有协议实现LoRa组网\网关\DRIVER\LED\LED.c
 */
/******************************************************************
 * 文件：LED.c
 * 功能：实现LED驱动功能函数
 * 日期：2018-02-16
 * 作者：zx
 * 版本：Ver.1.0 | 最初版本
 *
 * Copyright (C) 2018 zx. All rights reserved.
 *******************************************************************/
#include "LED/LED.h"
#include "DELAY/Delay.h"

#define GPIO_OUTP GPIO_Pin_12
/**
 * 功能：初始化LED
 * 参数：None
 * 返回值：None
 */
void initLED(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; //定义GPIO初始化结构体

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //使能GPIO和复用外设时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_OUTP;		  //设置对应引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //设置推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //工作速度50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);			  //设置生效
	GPIO_ResetBits(GPIOB, GPIO_OUTP);				  //默认低电平，LED不亮
}

/**
 * 功能：点亮LED
 * 参数：None
 * 返回值：None
 */
void openLED(void)
{
	GPIO_SetBits(GPIOB, GPIO_OUTP); //设置引脚为高电平
}

/**
 * 功能：熄灭LED
 * 参数：None
 * 返回值：None
 */
void closeLED(void)
{
	GPIO_ResetBits(GPIOB, GPIO_OUTP); //设置引脚为低电平
}

/**
 * 功能：LED闪烁
 * 参数：times：闪烁次数 open_ms:高电平持续时间 close_ms：低电平持续时间
 * 返回值：None
 */
void blinkLED(u8 times, u32 open_ms, u32 close_ms)
{
	u8 t;							  //用于翻转计数
	GPIO_ResetBits(GPIOB, GPIO_OUTP); //设置引脚为低电平
	for (t = 0; t < times; ++t)
	{
		toggleLED(); //翻转为高电平
		Delay_ms(open_ms);
		toggleLED(); //翻转为低电平
		Delay_ms(close_ms);
	}
}

/**
 * 功能：翻转LED
 * 参数：None
 * 返回值：None
 */
void toggleLED(void)
{
	GPIOB->ODR ^= GPIO_OUTP;
}
