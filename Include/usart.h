#ifndef __USART_H__
#define __USART_H__
#include "main.h"

extern UART_HandleTypeDef huart1;

extern UART_HandleTypeDef huart2;

extern UART_HandleTypeDef huart3;

int printf_hook(const char* restrict, ...);
/*****************************************************************************
 ** 声明全局函数
 ****************************************************************************/
// USART1
void USART1_Init(uint32_t baudrate);
void USART1_SendData(uint8_t* buf, uint16_t cnt);
void USART1_SendString(char* stringTemp);
void USART2_Init(uint32_t baudrate);
void USART2_SendData(uint8_t* buf, uint16_t cnt);
void USART2_SendString(char* stringTemp);
void USART3_Init(uint32_t baudrate);
void USART3_SendData(uint8_t* buf, uint16_t cnt);
void USART3_SendString(char* stringTemp);
// USART4
// void    UART4_Init(uint32_t baudrate);                //
// 初始化串口的GPIO、通信参数配置、中断优先级;
// (波特率可设、8位数据、无校验、1个停止位) void    UART4_SendData(uint8_t *buf,
// uint16_t cnt);   // 通过中断发送数据，适合各种数据 void UART4_SendString(char
// *stringTemp);           //
// 通过中断发送字符串，适合字符串，长度在256个长度内的
// // USART5
// void    UART5_Init(uint32_t baudrate);                //
// 初始化串口的GPIO、通信参数配置、中断优先级;
// (波特率可设、8位数据、无校验、1个停止位) void    UART5_SendData(uint8_t *buf,
// uint16_t cnt);   // 通过中断发送数据，适合各种数据 void UART5_SendString(char
// *stringTemp);           //
// 通过中断发送字符串，适合字符串，长度在256个长度内的
// // USART6
// void    USART6_Init(uint32_t baudrate);               //
// 初始化串口的GPIO、通信参数配置、中断优先级;
// (波特率可设、8位数据、无校验、1个停止位) void    USART6_SendData(uint8_t
// *buf, uint16_t cnt);  // 通过中断发送数据，适合各种数据 void
// USART6_SendString(char *stringTemp);          //
// 通过中断发送字符串，适合字符串，长度在256个长度内的

#endif   // !__USART_H__
