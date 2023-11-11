/*ͷ�ļ�*/
#include "Encoder.h"

/*�û��Զ������*/
TIM_HandleTypeDef TIM3_HandleInit = {0};
uint16_t Count = 0;     //��������
uint8_t Dir = 0;    //�������
float Speed = 0;   //�ٶȱ���
uint32_t OLED_Speed_Display = 0;
uint8_t Encoder_Bit[7];
uint32_t intermediate_Value = 1;    //�м����

/*��������ʼ������*/
void Encoder_Init(void)
{
    ENCODER_Port_CLK_ENABLE;    //�����������˿�ʱ��
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = ENCODER_Phase_A;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(ENCODER_Port, &GPIO_InitStruct);      //�������˿����ó�ʼ��

    GPIO_InitStruct.Pin = ENCODER_Phase_B;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(ENCODER_Port, &GPIO_InitStruct);      //�������˿����ó�ʼ��

    ENCODER_CLK_ENABLE;    //������ʱ��3ʱ��
    TIM_Encoder_InitTypeDef TIM3_Encoder_Init = {0};
    TIM_MasterConfigTypeDef TIM3_MasterConfig = {0};

    TIM3_HandleInit.Instance = TIM3;    //ʹ�ö�ʱ��3
    TIM3_HandleInit.Init.Prescaler = 0;     //��ʱ��3����Ƶ
    TIM3_HandleInit.Init.CounterMode = TIM_COUNTERMODE_UP;      //���������ϼ���ģʽ
    TIM3_HandleInit.Init.Period = 65535;    //����ֵΪ65535
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
    HAL_TIM_Encoder_Init(&TIM3_HandleInit, &TIM3_Encoder_Init);     //��ʱ��3������ģʽ���ó�ʼ��
    TIM3_MasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    TIM3_MasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    HAL_TIMEx_MasterConfigSynchronization(&TIM3_HandleInit, &TIM3_MasterConfig);
    HAL_TIM_Encoder_Start(&TIM3_HandleInit,TIM_CHANNEL_ALL);    //������ʱ��3������ģʽ��ȫͨ����ͨ��1��ͨ��2��
}

/*���������ٺ���*/
float Encoder_Speed_Test(void)
{
    if(__HAL_TIM_GET_FLAG(&TIM4_HandleInit,TIM_FLAG_UPDATE) == SET)
    {
        HAL_TIM_Base_Stop(&TIM4_HandleInit);    //�رն�ʱ��4��ʱ
        HAL_TIM_Encoder_Stop(&TIM3_HandleInit,TIM_CHANNEL_ALL);    //�رն�ʱ��3������ģʽ��ȫͨ����ͨ��1��ͨ��2��
        __HAL_TIM_CLEAR_FLAG(&TIM4_HandleInit,TIM_FLAG_UPDATE);     //�����ʱ��4���±�־
        Count = __HAL_TIM_GET_COUNTER(&TIM3_HandleInit);     //��ȡ����������ֵ
        Dir = __HAL_TIM_IS_TIM_COUNTING_DOWN(&TIM3_HandleInit);     //��ȡת����Ϣ
        if(Dir == 1)    //�����ת
        {
            Count = 65535 - Count;      //����������������ֵ
            if(Count == 65535)
            {
                Count = 0;
            }
        }
        Speed = (float)(Count/11.0f/2.0f)*60.0f;       //������ʵʱת��
        __HAL_TIM_SET_COUNTER(&TIM3_HandleInit,0);      //����ֵ��0
        HAL_TIM_Base_Start(&TIM4_HandleInit);    //������ʱ��4��ʱ
		HAL_TIM_Encoder_Start(&TIM3_HandleInit,TIM_CHANNEL_ALL);    //������ʱ��3������ģʽ��ȫͨ����ͨ��1��ͨ��2��
    }
    return Speed;
}

/*������ת����ʾ����*/
void Encoder_Speed_Display(void)
{
    OLED_Speed_Display = Encoder_Speed_Test()*100;      //��ñ�������ǰ����ֵ
    if(OLED_Speed_Display != intermediate_Value)
    {
        Encoder_Bit[0] = OLED_Speed_Display / 100000 + '0';        //��ȡǧλֵ
        Encoder_Bit[1] = OLED_Speed_Display / 10000 % 10 + '0';     //��ȡ��λֵ
        Encoder_Bit[2] = OLED_Speed_Display / 1000 % 10 + '0';      //��ȡʮλֵ
        Encoder_Bit[3] = OLED_Speed_Display / 100 % 10 + '0';       //��ȡ��λֵ
        Encoder_Bit[4] = '.';
        Encoder_Bit[5] = OLED_Speed_Display / 10 % 10 + '0';        //��ȡʮ��λֵ
        Encoder_Bit[6] = OLED_Speed_Display % 100 % 10 + '0';        //��ȡ�ٷ�λֵ
        OLED_ShowChinese(32,32,16,"��ǰת��",1);
        OLED_ShowEString(12,48,Encoder_Bit,16,1);
        OLED_ShowEString(72,48,"r/min",16,1);
    }
    intermediate_Value = OLED_Speed_Display;  
}
