#ifndef __USART1_H__
#define __USART1_H__
#include <stdio.h>
#include <stdarg.h>
#include "stm32f10x.h"                  // Device header

extern uint8_t G_RXData,G_RXFlag;
void USART1_Init();

// 发送部分
void USART1_SendByte(uint8_t Byte);
void USART1_SendArray(uint8_t *Array,uint16_t Length);
void USART1_SendString(char *String);
void USART1_SendNumber(uint32_t Number,uint8_t Length);
void USART1_Printf(char *fmt,...);
uint32_t Pow(uint32_t X,uint32_t Y);

uint8_t USART1_GetRxFlag(void);
uint8_t USART1_GetRxData(void);
#endif
