#ifndef __TIM1_H__
#define __TIM1_H__

/*ͷ�ļ�*/
#include "stm32f1xx.h"

/*�û��Զ������*/
#define TIM1_CLK_ENABLE __HAL_RCC_TIM1_CLK_ENABLE()
extern TIM_HandleTypeDef TIM1_HandleInit;

/*�û��Զ��庯��*/
void TIM1_Init(void);

#endif
