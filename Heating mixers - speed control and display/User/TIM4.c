/*头文件*/
#include "tim4.h"

/*用户自定义变量*/
TIM_HandleTypeDef TIM4_HandleInit = {0};

/*定时器4初始化函数*/
void TIM4_Init(void)
{
    TIM4_CLK_ENABLE;    //开启定时器4时钟

    TIM_ClockConfigTypeDef TIM4_ClockConfig = {0};
    TIM_MasterConfigTypeDef TIM4_MasterConfig = {0};

    TIM4_HandleInit.Instance = TIM4;    //定时器4
    TIM4_HandleInit.Init.Prescaler = 7199;      //定时器4预分频系数设置为7200
    TIM4_HandleInit.Init.CounterMode = TIM_COUNTERMODE_UP;      //定时器4向上计数模式
    TIM4_HandleInit.Init.Period = 9999;   //定时器计数值设置为100
    TIM4_HandleInit.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;    //定时器4时钟不分频
    TIM4_HandleInit.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    HAL_TIM_Base_Init(&TIM4_HandleInit);    //初始化定时器4配置

    TIM4_ClockConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;      //使用内部时钟源
    HAL_TIM_ConfigClockSource(&TIM4_HandleInit, &TIM4_ClockConfig);
    TIM4_MasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    TIM4_MasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    HAL_TIMEx_MasterConfigSynchronization(&TIM4_HandleInit, &TIM4_MasterConfig);

    HAL_TIM_Base_Start(&TIM4_HandleInit);   //开启定时器4    
}
