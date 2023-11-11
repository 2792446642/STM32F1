#ifndef __SPI2_H__
#define __SPI2_H__

/*ͷ�ļ�*/
#include "stm32f1xx.h"

/*�û��Զ������*/
#define SPI2_CLK_ENABLE __HAL_RCC_SPI2_CLK_ENABLE()
#define SPI2_Port_CLK_ENABLE __HAL_RCC_GPIOB_CLK_ENABLE()
#define SPI2_Port GPIOB
#define SPI2_MOSI GPIO_PIN_15      //D1
#define SPI2_MISO GPIO_PIN_14
#define SPI2_SCK GPIO_PIN_13        //D0

extern SPI_HandleTypeDef SPI2_HandleInit;

/*�û��Զ��庯��*/
void SPI2_Init(void);
uint8_t SPI2_ReadWriteByte(uint8_t TX_Data);

#endif
