/*ͷ�ļ�*/
#include "tim1.h"

/*�û��Զ������*/
TIM_HandleTypeDef TIM1_HandleInit = {0};

/*��ʱ��1��ʼ������*/
void TIM1_Init(void)
{
    TIM1_CLK_ENABLE;    //������ʱ��1ʱ��

    TIM_ClockConfigTypeDef TIM1_ClockConfig = {0};
    TIM_MasterConfigTypeDef TIM1_MasterConfig = {0};

    TIM1_HandleInit.Instance = TIM1;    //��ʱ��1
    TIM1_HandleInit.Init.Prescaler = 71;      //��ʱ��1Ԥ��Ƶϵ������Ϊ72,Ƶ��λ1΢��
    TIM1_HandleInit.Init.CounterMode = TIM_COUNTERMODE_UP;      //��ʱ��1���ϼ���ģʽ
    TIM1_HandleInit.Init.Period = 9999;   //��ʱ������ֵ����Ϊ10000����ʱʱ��10ms
    TIM1_HandleInit.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;    //��ʱ��1ʱ�Ӳ���Ƶ
    TIM1_HandleInit.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    HAL_TIM_Base_Init(&TIM1_HandleInit);    //��ʼ����ʱ��1����

    TIM1_ClockConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;      //ʹ���ڲ�ʱ��Դ
    HAL_TIM_ConfigClockSource(&TIM1_HandleInit, &TIM1_ClockConfig);
    TIM1_MasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    TIM1_MasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    HAL_TIMEx_MasterConfigSynchronization(&TIM1_HandleInit, &TIM1_MasterConfig);

    HAL_TIM_Base_Start(&TIM1_HandleInit);   //������ʱ��1    
}
