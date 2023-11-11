#ifndef __MOTOR_H__
#define __MOTOR_H__

/*ͷ�ļ�*/
#include "stm32f1xx.h"
#include "EC11.h"
#include "Encoder.h"
#include "Delay.h"

/*�û��Զ������*/
#define Motor_CLK_ENABLE __HAL_RCC_TIM1_CLK_ENABLE()
#define Motor_Port_CLK_ENABLE __HAL_RCC_GPIOA_CLK_ENABLE()
#define Motor_PWM_Port GPIOA
#define Motor_Control_Pin GPIO_PIN_11
#define Motor_Control_Channel TIM_CHANNEL_4
extern TIM_HandleTypeDef TIM1_HandleInit;

/*�û��Զ��庯��*/
void Motor_Init(void);
void Motor_Speed_Auto_Control(void);
#endif
