#ifndef __TIM1_H__
#define __TIM1_H__

/*头文件*/
#include "stm32f1xx.h"

/*用户自定义变量*/
#define TIM1_CLK_ENABLE __HAL_RCC_TIM1_CLK_ENABLE()
extern TIM_HandleTypeDef TIM1_HandleInit;

/*用户自定义函数*/
void TIM1_Init(void);

#endif
