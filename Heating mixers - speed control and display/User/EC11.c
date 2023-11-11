/*头文件*/
#include "EC11.h"

/*用户自定义变量*/
uint32_t EC11_Current_Count = 0;
// uint32_t EC11_Past_Count = 0;
uint8_t EC11_Bit[3] = {0,0,0};
uint32_t Current_value = 0;
uint32_t Stored_value = 1;
uint32_t Counter = 0;

TIM_HandleTypeDef TIM2_HandleInit = {0};

/*EC11初始化函数*/
void EC11_Init(void)
{
    EC11_Port_CLK_ENABLE;    //开启编码器端口时钟
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = EC11_Phase_A;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(EC11_Port, &GPIO_InitStruct);      //编码器端口配置初始化

    GPIO_InitStruct.Pin = EC11_Phase_B;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(EC11_Port, &GPIO_InitStruct);      //编码器端口配置初始化

    EC11_CLK_ENABLE;    //开启定时器2时钟
    TIM_Encoder_InitTypeDef TIM2_Encoder_Init = {0};
    TIM_MasterConfigTypeDef TIM2_MasterConfig = {0};

    TIM2_HandleInit.Instance = TIM2;    //使用定时器2
    TIM2_HandleInit.Init.Prescaler = 0;     //定时器2不分频
    TIM2_HandleInit.Init.CounterMode = TIM_COUNTERMODE_UP;      //编码器向上计数模式
    TIM2_HandleInit.Init.Period = 65535;    //计数值为65535
    TIM2_HandleInit.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    TIM2_HandleInit.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    TIM2_Encoder_Init.EncoderMode = TIM_ENCODERMODE_TI1;
    TIM2_Encoder_Init.IC1Polarity = TIM_ICPOLARITY_RISING;
    TIM2_Encoder_Init.IC1Selection = TIM_ICSELECTION_DIRECTTI;
    TIM2_Encoder_Init.IC1Prescaler = TIM_ICPSC_DIV1;
    TIM2_Encoder_Init.IC1Filter = 10;
    TIM2_Encoder_Init.IC2Polarity = TIM_ICPOLARITY_RISING;
    TIM2_Encoder_Init.IC2Selection = TIM_ICSELECTION_DIRECTTI;
    TIM2_Encoder_Init.IC2Prescaler = TIM_ICPSC_DIV1;
    TIM2_Encoder_Init.IC2Filter = 10;
    HAL_TIM_Encoder_Init(&TIM2_HandleInit, &TIM2_Encoder_Init);     //定时器2编码器模式配置初始化

    TIM2_MasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    TIM2_MasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    HAL_TIMEx_MasterConfigSynchronization(&TIM2_HandleInit, &TIM2_MasterConfig);

    HAL_TIM_Encoder_Start(&TIM2_HandleInit,TIM_CHANNEL_ALL);    //开启定时器2编码器模式，全通道（通道1和通道2）
	__HAL_TIM_SET_COUNTER(&TIM2_HandleInit,0);
}

/*EC11计数函数*/
uint32_t EC11_Count(void)
{ 
    Counter = __HAL_TIM_GET_COUNTER(&TIM2_HandleInit);
    HAL_TIM_Encoder_Stop(&TIM2_HandleInit,TIM_CHANNEL_ALL);    //开启定时器2编码器模式，全通道（通道1和通道2）    
    if(__HAL_TIM_IS_TIM_COUNTING_DOWN(&TIM2_HandleInit) == 1)
    { 
        if(Counter <= 0 || Counter > 20)
        {
            __HAL_TIM_SET_COUNTER(&TIM2_HandleInit,0);
            Counter = __HAL_TIM_GET_COUNTER(&TIM2_HandleInit);
            EC11_Current_Count = Counter*5;
        }
        else
        {
            EC11_Current_Count = Counter*5-5; 
        }        
    }
    else
    {
        Counter = __HAL_TIM_GET_COUNTER(&TIM2_HandleInit);
        if(Counter > 20)
        {
            __HAL_TIM_SET_COUNTER(&TIM2_HandleInit,20);
            Counter = __HAL_TIM_GET_COUNTER(&TIM2_HandleInit);
            EC11_Current_Count = Counter*5;
        }
        else
        {
            EC11_Current_Count = Counter*5;
        }                
    } 
    HAL_TIM_Encoder_Start(&TIM2_HandleInit,TIM_CHANNEL_ALL);    //开启定时器2编码器模式，全通道（通道1和通道2）      
	return EC11_Current_Count;   
}

/*EC11计数显示函数*/
void EC11_Speed_Display(void)
{
    Current_value = EC11_Count();
    if(Current_value != Stored_value)
    {
        HAL_TIM_Encoder_Stop(&TIM2_HandleInit,TIM_CHANNEL_ALL);    //关闭定时器2编码器模式，全通道（通道1和通道2）
        EC11_Bit[0] = Current_value /100 + '0';      //获取十位值
        EC11_Bit[1] = Current_value % 100 / 10 + '0';      //获取十位值
        EC11_Bit[2] = Current_value % 100 % 10 + '0';       //获取个位值
        OLED_ShowChinese(24,0,16,"速度百分值",1);
        OLED_ShowEString(48,16,EC11_Bit,16,1);
        OLED_ShowEString(72,16,"%",16,1);
        HAL_TIM_Encoder_Start(&TIM2_HandleInit,TIM_CHANNEL_ALL);    //开启定时器2编码器模式，全通道（通道1和通道2）       
    }
	Stored_value = Current_value;	
}
