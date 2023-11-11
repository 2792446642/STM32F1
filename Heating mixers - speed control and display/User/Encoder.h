#ifndef __ENCODER_H__
#define __ENCODER_H__

/*头文件*/
#include "stm32f1xx.h"
#include "tim4.h"
#include "Delay.h"
#include "OLED.h"

/*用户自定义变量*/
#define ENCODER_CLK_ENABLE __HAL_RCC_TIM3_CLK_ENABLE()
#define ENCODER_Port_CLK_ENABLE __HAL_RCC_GPIOA_CLK_ENABLE()
#define ENCODER_Port GPIOA
#define ENCODER_Phase_A GPIO_PIN_6
#define ENCODER_Phase_B GPIO_PIN_7

extern float Speed;

/*用户自定义函数*/
void Encoder_Init(void);
float Encoder_Speed_Test(void);
void Encoder_Speed_Display(void);
#endif
