/*ͷ�ļ�*/
#include "usart1.h"

/*�û��Զ������*/
UART_HandleTypeDef UART_HandleInit = {0};

/*����1��ʼ������*/
void UART1_Init(uint32_t BaudRate)
{
	UART_HandleInit.Instance = USART1;
	UART_HandleInit.Init.BaudRate = BaudRate;		//���ô���1������
	UART_HandleInit.Init.Parity = UART_PARITY_NONE;		//����żУ��
	UART_HandleInit.Init.StopBits = UART_STOPBITS_1;		//һλֹͣλ
	UART_HandleInit.Init.WordLength = UART_WORDLENGTH_8B;		//����1�ֳ�Ϊ8λ
	UART_HandleInit.Init.Mode = UART_MODE_TX_RX;		//����1����Ϊ�շ�ģʽ
	UART_HandleInit.Init.HwFlowCtl = UART_HWCONTROL_NONE;		//��Ӳ��������
	UART_HandleInit.Init.OverSampling = UART_OVERSAMPLING_16;		//16�ι��������ݴ��Ը���
	HAL_UART_Init(&UART_HandleInit);		//��ʼ������1
	
}

/*����1�ص�����*/
void HAL_UART_MspInit(UART_HandleTypeDef * huart)
{
	USART1_Port_CLK_ENABLE;
	USART1_CLK_ENABLE;

	if(huart->Instance == USART1)
	{
		GPIO_InitTypeDef GPIO_InitStruct = {0};		
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pin = USART1_TX;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(USART1_Port,&GPIO_InitStruct);
		
		GPIO_InitStruct.Mode = GPIO_MODE_AF_INPUT;
		GPIO_InitStruct.Pin = USART1_RX;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		HAL_GPIO_Init(USART1_Port,&GPIO_InitStruct);

	}
}

/*����1printf�ض�����*/
int fputc(int ch, FILE *f)
{ 
	HAL_UART_Transmit(&UART_HandleInit,(uint8_t *)&ch,1,1000);   //��Ҫ���͵��ַ�д�뵽DR�Ĵ���	
	while(__HAL_UART_GET_FLAG(&UART_HandleInit, UART_FLAG_TC) == RESET);
	return ch;
}

/*����1����ʽ�������ݺ���*/
void UART1_Transmit(uint8_t *TX_Data)
{
	uint32_t i = 0;
	__HAL_UART_CLEAR_FLAG(&UART_HandleInit, UART_FLAG_TC);		//������ڷ�����ɱ�־λ
	while(TX_Data[i] != '\0')
	{
		HAL_UART_Transmit(&UART_HandleInit,(uint8_t *)&TX_Data[i],1,0xffff);		//�����û�ָ���ַ���
		while(__HAL_USART_GET_FLAG(&UART_HandleInit,UART_FLAG_TC) == RESET);		//�ȴ�����1��һ�����ݷ������
		__HAL_UART_CLEAR_FLAG(&UART_HandleInit, UART_FLAG_TC);		//�ٴ����
		i++;
	}
}








