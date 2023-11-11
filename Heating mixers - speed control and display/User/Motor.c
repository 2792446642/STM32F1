/*头文件*/
#include "Motor.h"
/*用户自定义变量*/
TIM_HandleTypeDef TIM1_HandleInit = {0};
uint32_t Motor_Speed = 0;       //电机设定转速百分值
uint32_t Motor_Past_Speed = 0;
uint8_t Motor_Flag = 0;

/*定时器1初始化函数*/
void Motor_Init(void)
{
    Motor_Port_CLK_ENABLE;      //开启电机控制端口时钟
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = Motor_Control_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(Motor_PWM_Port, &GPIO_InitStruct);

    Motor_CLK_ENABLE;       //开启PWM输出定时器时钟
    TIM_MasterConfigTypeDef TIM1_MasterConfig = {0};
    TIM_OC_InitTypeDef TIM1_OC_Init = {0};
    TIM_BreakDeadTimeConfigTypeDef TIM1_BreakDeadTimeConfig = {0};

    TIM1_HandleInit.Instance = TIM1;
    TIM1_HandleInit.Init.Prescaler = 7199;
    TIM1_HandleInit.Init.CounterMode = TIM_COUNTERMODE_UP;
    TIM1_HandleInit.Init.Period = 99;
    TIM1_HandleInit.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    TIM1_HandleInit.Init.RepetitionCounter = 0;
    TIM1_HandleInit.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    HAL_TIM_PWM_Init(&TIM1_HandleInit);
    HAL_TIM_Base_Init(&TIM1_HandleInit);
    
    TIM1_MasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    TIM1_MasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    HAL_TIMEx_MasterConfigSynchronization(&TIM1_HandleInit, &TIM1_MasterConfig);

    TIM1_OC_Init.OCMode = TIM_OCMODE_PWM1;
    TIM1_OC_Init.Pulse = 0;
    TIM1_OC_Init.OCPolarity = TIM_OCPOLARITY_HIGH;
    TIM1_OC_Init.OCNPolarity = TIM_OCNPOLARITY_HIGH;
    TIM1_OC_Init.OCFastMode = TIM_OCFAST_DISABLE;
    TIM1_OC_Init.OCIdleState = TIM_OCIDLESTATE_RESET;
    TIM1_OC_Init.OCNIdleState = TIM_OCNIDLESTATE_RESET;
    HAL_TIM_PWM_ConfigChannel(&TIM1_HandleInit, &TIM1_OC_Init, Motor_Control_Channel);
    
    TIM1_BreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
    TIM1_BreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
    TIM1_BreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
    TIM1_BreakDeadTimeConfig.DeadTime = 0;
    TIM1_BreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
    TIM1_BreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
    TIM1_BreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
    HAL_TIMEx_ConfigBreakDeadTime(&TIM1_HandleInit, &TIM1_BreakDeadTimeConfig);

    HAL_TIM_Base_Start(&TIM1_HandleInit);
    HAL_TIM_PWM_Start(&TIM1_HandleInit,Motor_Control_Channel);
}

/*转速自动调节函数函数*/
void Motor_Speed_Auto_Control(void)
{
    Motor_Speed = EC11_Count();     //获取设定转速值  
    if(Motor_Past_Speed == Motor_Speed && Motor_Past_Speed != 0)
    {
        if(Motor_Flag == 0)
        {
            __HAL_TIM_SET_COMPARE(&TIM1_HandleInit,Motor_Control_Channel,Motor_Speed);
            Motor_Flag = 1;
        }       
    }
    else
    {
        Motor_Flag = 0;
    }
    Motor_Past_Speed = Motor_Speed;  
    if(Motor_Speed == 0)
    {
        Motor_Speed = 0;
        __HAL_TIM_SET_COMPARE(&TIM1_HandleInit,Motor_Control_Channel,Motor_Speed);
    } 
}
