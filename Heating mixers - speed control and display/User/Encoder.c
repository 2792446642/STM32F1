/*头文件*/
#include "Encoder.h"

/*用户自定义变量*/
TIM_HandleTypeDef TIM3_HandleInit = {0};
uint16_t Count = 0;     //计数变量
uint8_t Dir = 0;    //方向变量
float Speed = 0;   //速度变量
uint32_t OLED_Speed_Display = 0;
uint8_t Encoder_Bit[7];
uint32_t intermediate_Value = 1;    //中间变量

/*编码器初始化函数*/
void Encoder_Init(void)
{
    ENCODER_Port_CLK_ENABLE;    //开启编码器端口时钟
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = ENCODER_Phase_A;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(ENCODER_Port, &GPIO_InitStruct);      //编码器端口配置初始化

    GPIO_InitStruct.Pin = ENCODER_Phase_B;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(ENCODER_Port, &GPIO_InitStruct);      //编码器端口配置初始化

    ENCODER_CLK_ENABLE;    //开启定时器3时钟
    TIM_Encoder_InitTypeDef TIM3_Encoder_Init = {0};
    TIM_MasterConfigTypeDef TIM3_MasterConfig = {0};

    TIM3_HandleInit.Instance = TIM3;    //使用定时器3
    TIM3_HandleInit.Init.Prescaler = 0;     //定时器3不分频
    TIM3_HandleInit.Init.CounterMode = TIM_COUNTERMODE_UP;      //编码器向上计数模式
    TIM3_HandleInit.Init.Period = 65535;    //计数值为65535
    TIM3_HandleInit.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    TIM3_HandleInit.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    TIM3_Encoder_Init.EncoderMode = TIM_ENCODERMODE_TI1;
    TIM3_Encoder_Init.IC1Polarity = TIM_ICPOLARITY_RISING;
    TIM3_Encoder_Init.IC1Selection = TIM_ICSELECTION_DIRECTTI;
    TIM3_Encoder_Init.IC1Prescaler = TIM_ICPSC_DIV1;
    TIM3_Encoder_Init.IC1Filter = 6;
    TIM3_Encoder_Init.IC2Polarity = TIM_ICPOLARITY_RISING;
    TIM3_Encoder_Init.IC2Selection = TIM_ICSELECTION_DIRECTTI;
    TIM3_Encoder_Init.IC2Prescaler = TIM_ICPSC_DIV1;
    TIM3_Encoder_Init.IC2Filter = 6;
    HAL_TIM_Encoder_Init(&TIM3_HandleInit, &TIM3_Encoder_Init);     //定时器3编码器模式配置初始化
    TIM3_MasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    TIM3_MasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    HAL_TIMEx_MasterConfigSynchronization(&TIM3_HandleInit, &TIM3_MasterConfig);
    HAL_TIM_Encoder_Start(&TIM3_HandleInit,TIM_CHANNEL_ALL);    //开启定时器3编码器模式，全通道（通道1和通道2）
}

/*编码器测速函数*/
float Encoder_Speed_Test(void)
{
    if(__HAL_TIM_GET_FLAG(&TIM4_HandleInit,TIM_FLAG_UPDATE) == SET)
    {
        HAL_TIM_Base_Stop(&TIM4_HandleInit);    //关闭定时器4计时
        HAL_TIM_Encoder_Stop(&TIM3_HandleInit,TIM_CHANNEL_ALL);    //关闭定时器3编码器模式，全通道（通道1和通道2）
        __HAL_TIM_CLEAR_FLAG(&TIM4_HandleInit,TIM_FLAG_UPDATE);     //清除定时器4更新标志
        Count = __HAL_TIM_GET_COUNTER(&TIM3_HandleInit);     //获取编码器计数值
        Dir = __HAL_TIM_IS_TIM_COUNTING_DOWN(&TIM3_HandleInit);     //获取转向信息
        if(Dir == 1)    //电机反转
        {
            Count = 65535 - Count;      //计算编码器反向计数值
            if(Count == 65535)
            {
                Count = 0;
            }
        }
        Speed = (float)(Count/11.0f/2.0f)*60.0f;       //计算电机实时转速
        __HAL_TIM_SET_COUNTER(&TIM3_HandleInit,0);      //计数值清0
        HAL_TIM_Base_Start(&TIM4_HandleInit);    //开启定时器4计时
		HAL_TIM_Encoder_Start(&TIM3_HandleInit,TIM_CHANNEL_ALL);    //开启定时器3编码器模式，全通道（通道1和通道2）
    }
    return Speed;
}

/*编码器转速显示函数*/
void Encoder_Speed_Display(void)
{
    OLED_Speed_Display = Encoder_Speed_Test()*100;      //获得编码器当前测速值
    if(OLED_Speed_Display != intermediate_Value)
    {
        Encoder_Bit[0] = OLED_Speed_Display / 100000 + '0';        //获取千位值
        Encoder_Bit[1] = OLED_Speed_Display / 10000 % 10 + '0';     //获取百位值
        Encoder_Bit[2] = OLED_Speed_Display / 1000 % 10 + '0';      //获取十位值
        Encoder_Bit[3] = OLED_Speed_Display / 100 % 10 + '0';       //获取个位值
        Encoder_Bit[4] = '.';
        Encoder_Bit[5] = OLED_Speed_Display / 10 % 10 + '0';        //获取十分位值
        Encoder_Bit[6] = OLED_Speed_Display % 100 % 10 + '0';        //获取百分位值
        OLED_ShowChinese(32,32,16,"当前转速",1);
        OLED_ShowEString(12,48,Encoder_Bit,16,1);
        OLED_ShowEString(72,48,"r/min",16,1);
    }
    intermediate_Value = OLED_Speed_Display;  
}
