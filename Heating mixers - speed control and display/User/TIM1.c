/*头文件*/
#include "tim1.h"

/*用户自定义变量*/
TIM_HandleTypeDef TIM1_HandleInit = {0};

/*定时器1初始化函数*/
void TIM1_Init(void)
{
    TIM1_CLK_ENABLE;    //开启定时器1时钟

    TIM_ClockConfigTypeDef TIM1_ClockConfig = {0};
    TIM_MasterConfigTypeDef TIM1_MasterConfig = {0};

    TIM1_HandleInit.Instance = TIM1;    //定时器1
    TIM1_HandleInit.Init.Prescaler = 71;      //定时器1预分频系数设置为72,频率位1微秒
    TIM1_HandleInit.Init.CounterMode = TIM_COUNTERMODE_UP;      //定时器1向上计数模式
    TIM1_HandleInit.Init.Period = 9999;   //定时器计数值设置为10000，定时时长10ms
    TIM1_HandleInit.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;    //定时器1时钟不分频
    TIM1_HandleInit.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    HAL_TIM_Base_Init(&TIM1_HandleInit);    //初始化定时器1配置

    TIM1_ClockConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;      //使用内部时钟源
    HAL_TIM_ConfigClockSource(&TIM1_HandleInit, &TIM1_ClockConfig);
    TIM1_MasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    TIM1_MasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    HAL_TIMEx_MasterConfigSynchronization(&TIM1_HandleInit, &TIM1_MasterConfig);

    HAL_TIM_Base_Start(&TIM1_HandleInit);   //开启定时器1    
}
