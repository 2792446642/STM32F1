#ifndef __TIM4_H__
#define __TIM4_H__

/*ͷ�ļ�*/
#include "stm32f1xx.h"

/*�û��Զ������*/
#define TIM4_CLK_ENABLE __HAL_RCC_TIM4_CLK_ENABLE()
extern TIM_HandleTypeDef TIM4_HandleInit;
/*�û��Զ��庯��*/
void TIM4_Init(void);

#endif
