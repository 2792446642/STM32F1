#ifndef __USART1_H__
#define __USART1_H__

/*ͷ�ļ�*/
#include "stm32f1xx.h"
#include <stdio.h>
#include <string.h>

/*�û��Զ������*/
#define USART1_Port GPIOA
#define USART1_TX GPIO_PIN_9
#define USART1_RX GPIO_PIN_10
#define USART1_Port_CLK_ENABLE __HAL_RCC_GPIOA_CLK_ENABLE()
#define USART1_CLK_ENABLE __HAL_RCC_USART1_CLK_ENABLE()

#pragma  diag_suppress 870

/*�û��Զ��庯��*/
void UART1_Init(uint32_t BaudRate);
void UART1_Transmit(uint8_t * TX_Data);
int fputc(int ch, FILE *f);

#endif

