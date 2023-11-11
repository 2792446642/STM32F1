#ifndef __EC11_H__
#define __EC11_H__

/*头文件*/
#include "stm32f1xx.h"
#include "USART1.h"
#include "OLED.h"

/*用户自定义变量*/
#define EC11_Port GPIOA
#define EC11_Port_CLK_ENABLE __HAL_RCC_GPIOA_CLK_ENABLE()
#define EC11_CLK_ENABLE __HAL_RCC_TIM2_CLK_ENABLE()
#define EC11_Phase_A GPIO_PIN_1
#define EC11_Phase_B GPIO_PIN_0

/*用户自定义函数*/
void EC11_Init(void);
uint32_t EC11_Count(void);
void EC11_Speed_Display(void);
#endif
