/*
 * @Author: your name
 * @Date: 2022-04-14 20:00:08
 * @LastEditTime: 2022-04-15 00:20:49
 * @LastEditors: your name
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \21_使用自有协议实现LoRa组网\网关\DRIVER\UART\uart.h
 */

#ifndef __UART_H
#define __UART_H
#include "stm32f10x.h"

void initUART(void);
void sendByte(USART_TypeDef* USARTx,u16 byte);
void sendString(USART_TypeDef* USARTx,char* str);

void USART1_IRQHandler(void);
void USART2_IRQHandler(void);
void USART3_IRQHandler(void);

#endif
