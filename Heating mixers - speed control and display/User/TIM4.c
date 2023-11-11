/*ͷ�ļ�*/
#include "tim4.h"

/*�û��Զ������*/
TIM_HandleTypeDef TIM4_HandleInit = {0};

/*��ʱ��4��ʼ������*/
void TIM4_Init(void)
{
    TIM4_CLK_ENABLE;    //������ʱ��4ʱ��

    TIM_ClockConfigTypeDef TIM4_ClockConfig = {0};
    TIM_MasterConfigTypeDef TIM4_MasterConfig = {0};

    TIM4_HandleInit.Instance = TIM4;    //��ʱ��4
    TIM4_HandleInit.Init.Prescaler = 7199;      //��ʱ��4Ԥ��Ƶϵ������Ϊ7200
    TIM4_HandleInit.Init.CounterMode = TIM_COUNTERMODE_UP;      //��ʱ��4���ϼ���ģʽ
    TIM4_HandleInit.Init.Period = 9999;   //��ʱ������ֵ����Ϊ100
    TIM4_HandleInit.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;    //��ʱ��4ʱ�Ӳ���Ƶ
    TIM4_HandleInit.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    HAL_TIM_Base_Init(&TIM4_HandleInit);    //��ʼ����ʱ��4����

    TIM4_ClockConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;      //ʹ���ڲ�ʱ��Դ
    HAL_TIM_ConfigClockSource(&TIM4_HandleInit, &TIM4_ClockConfig);
    TIM4_MasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    TIM4_MasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    HAL_TIMEx_MasterConfigSynchronization(&TIM4_HandleInit, &TIM4_MasterConfig);

    HAL_TIM_Base_Start(&TIM4_HandleInit);   //������ʱ��4    
}
