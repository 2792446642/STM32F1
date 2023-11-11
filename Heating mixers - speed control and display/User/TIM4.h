#ifndef __TIM4_H__
#define __TIM4_H__

/*头文件*/
#include "stm32f1xx.h"

/*用户自定义变量*/
#define TIM4_CLK_ENABLE __HAL_RCC_TIM4_CLK_ENABLE()
extern TIM_HandleTypeDef TIM4_HandleInit;
/*用户自定义函数*/
void TIM4_Init(void);

#endif
