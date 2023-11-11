/*ͷ�ļ�*/
#include "EC11.h"

/*�û��Զ������*/
uint32_t EC11_Current_Count = 0;
// uint32_t EC11_Past_Count = 0;
uint8_t EC11_Bit[3] = {0,0,0};
uint32_t Current_value = 0;
uint32_t Stored_value = 1;
uint32_t Counter = 0;

TIM_HandleTypeDef TIM2_HandleInit = {0};

/*EC11��ʼ������*/
void EC11_Init(void)
{
    EC11_Port_CLK_ENABLE;    //�����������˿�ʱ��
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = EC11_Phase_A;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(EC11_Port, &GPIO_InitStruct);      //�������˿����ó�ʼ��

    GPIO_InitStruct.Pin = EC11_Phase_B;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(EC11_Port, &GPIO_InitStruct);      //�������˿����ó�ʼ��

    EC11_CLK_ENABLE;    //������ʱ��2ʱ��
    TIM_Encoder_InitTypeDef TIM2_Encoder_Init = {0};
    TIM_MasterConfigTypeDef TIM2_MasterConfig = {0};

    TIM2_HandleInit.Instance = TIM2;    //ʹ�ö�ʱ��2
    TIM2_HandleInit.Init.Prescaler = 0;     //��ʱ��2����Ƶ
    TIM2_HandleInit.Init.CounterMode = TIM_COUNTERMODE_UP;      //���������ϼ���ģʽ
    TIM2_HandleInit.Init.Period = 65535;    //����ֵΪ65535
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
    HAL_TIM_Encoder_Init(&TIM2_HandleInit, &TIM2_Encoder_Init);     //��ʱ��2������ģʽ���ó�ʼ��

    TIM2_MasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    TIM2_MasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    HAL_TIMEx_MasterConfigSynchronization(&TIM2_HandleInit, &TIM2_MasterConfig);

    HAL_TIM_Encoder_Start(&TIM2_HandleInit,TIM_CHANNEL_ALL);    //������ʱ��2������ģʽ��ȫͨ����ͨ��1��ͨ��2��
	__HAL_TIM_SET_COUNTER(&TIM2_HandleInit,0);
}

/*EC11��������*/
uint32_t EC11_Count(void)
{ 
    Counter = __HAL_TIM_GET_COUNTER(&TIM2_HandleInit);
    HAL_TIM_Encoder_Stop(&TIM2_HandleInit,TIM_CHANNEL_ALL);    //������ʱ��2������ģʽ��ȫͨ����ͨ��1��ͨ��2��    
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
    HAL_TIM_Encoder_Start(&TIM2_HandleInit,TIM_CHANNEL_ALL);    //������ʱ��2������ģʽ��ȫͨ����ͨ��1��ͨ��2��      
	return EC11_Current_Count;   
}

/*EC11������ʾ����*/
void EC11_Speed_Display(void)
{
    Current_value = EC11_Count();
    if(Current_value != Stored_value)
    {
        HAL_TIM_Encoder_Stop(&TIM2_HandleInit,TIM_CHANNEL_ALL);    //�رն�ʱ��2������ģʽ��ȫͨ����ͨ��1��ͨ��2��
        EC11_Bit[0] = Current_value /100 + '0';      //��ȡʮλֵ
        EC11_Bit[1] = Current_value % 100 / 10 + '0';      //��ȡʮλֵ
        EC11_Bit[2] = Current_value % 100 % 10 + '0';       //��ȡ��λֵ
        OLED_ShowChinese(24,0,16,"�ٶȰٷ�ֵ",1);
        OLED_ShowEString(48,16,EC11_Bit,16,1);
        OLED_ShowEString(72,16,"%",16,1);
        HAL_TIM_Encoder_Start(&TIM2_HandleInit,TIM_CHANNEL_ALL);    //������ʱ��2������ģʽ��ȫͨ����ͨ��1��ͨ��2��       
    }
	Stored_value = Current_value;	
}
