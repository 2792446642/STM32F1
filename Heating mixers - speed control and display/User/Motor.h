#ifndef __MOTOR_H__
#define __MOTOR_H__

/*头文件*/
#include "stm32f1xx.h"
#include "EC11.h"
#include "Encoder.h"
#include "Delay.h"

/*用户自定义变量*/
#define Motor_CLK_ENABLE __HAL_RCC_TIM1_CLK_ENABLE()
#define Motor_Port_CLK_ENABLE __HAL_RCC_GPIOA_CLK_ENABLE()
#define Motor_PWM_Port GPIOA
#define Motor_Control_Pin GPIO_PIN_11
#define Motor_Control_Channel TIM_CHANNEL_4
extern TIM_HandleTypeDef TIM1_HandleInit;

/*用户自定义函数*/
void Motor_Init(void);
void Motor_Speed_Auto_Control(void);
#endif
