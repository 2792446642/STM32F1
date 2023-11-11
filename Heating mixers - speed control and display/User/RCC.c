/*ͷ�ļ�*/
#include "rcc.h"
/*�û��Զ������*/

/*�û��Զ��庯��*/
void SysClk_Init(void)
{
//	HAL_Init(void);
	HAL_StatusTypeDef RCC_OSC_Status;
	RCC_OscInitTypeDef RCC_OSCInitStruct = {0};		//��ʼ���ṹ���ԱֵΪ0(��������ֵ���ԱֵΪ�����)
	RCC_OSCInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;		//HSEԤ��Ƶֵ
	RCC_OSCInitStruct.HSEState = RCC_HSE_ON;		//HSE״̬
	RCC_OSCInitStruct.HSIState = RCC_HSI_ON;						//HSI״̬
	RCC_OSCInitStruct.LSEState = RCC_LSE_ON;					//LSE״̬
	RCC_OSCInitStruct.LSIState = RCC_LSI_ON;						//LSI״̬
	RCC_OSCInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;			//ѡ����Ҫ���õ�����
	RCC_OSCInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;		//���໷9��Ƶ
	RCC_OSCInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;		//���໷ʱ��Դ
	RCC_OSCInitStruct.PLL.PLLState = RCC_PLL_ON;		//ʹ�����໷
	RCC_OSC_Status = HAL_RCC_OscConfig(&RCC_OSCInitStruct);		//��ʼ��ʱ��Դ�����໷����

	if(RCC_OSC_Status != HAL_OK)
	{
		while(1);		//ʱ��Դ�����໷��ʼ��ʧ�ܣ�
	}
	RCC_ClkInitTypeDef RCC_ClkInitStruct;
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;		//ʱ������
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;		//����ϵͳʱ����Դ
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;		//AHB����Ԥ��Ƶϵ��
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;		//APB1����Ԥ��Ƶϵ��
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;		//APB2����Ԥ��Ƶϵ��
	HAL_RCC_ClockConfig(&RCC_ClkInitStruct,FLASH_LATENCY_2);
}

