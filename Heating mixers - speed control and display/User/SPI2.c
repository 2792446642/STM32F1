/*ͷ�ļ�*/
#include "SPI2.h"

/*�û��Զ������*/
SPI_HandleTypeDef SPI2_HandleInit = {0};

/*SPI2��ʼ������*/
void SPI2_Init(void)
{
    SPI2_CLK_ENABLE;
    SPI2_Port_CLK_ENABLE;

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;		//���ö˿�ģʽΪ�����������
    GPIO_InitStruct.Pin = SPI2_SCK;		//ѡ��SPI2_SCK����
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(SPI2_Port,&GPIO_InitStruct);		//��ʼ��GPIOB
    
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;		//���ö˿�ģʽΪ�����������
    GPIO_InitStruct.Pin = SPI2_MOSI;		//ѡ��SPI2_MOSI����
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;		//�˿��������Ϊ���
    HAL_GPIO_Init(SPI2_Port,&GPIO_InitStruct);		//��ʼ��GPIOB
    
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pin = SPI2_MISO;		//ѡ��SPI2_MISO����
    GPIO_InitStruct.Pull = GPIO_NOPULL;		//��������Ϊ����ģʽ
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;		//�˿��������Ϊ���
    HAL_GPIO_Init(SPI2_Port,&GPIO_InitStruct);		//��ʼ��GPIOB

    SPI2_HandleInit.Instance = SPI2;		//ѡ��SPI2����
	SPI2_HandleInit.Init.Mode = SPI_MODE_MASTER;		//����SPI����Ϊ����ģʽ
	SPI2_HandleInit.Init.Direction = SPI_DIRECTION_2LINES;		//����SPI�豸Ϊͬ��ȫ˫��ģʽ
	SPI2_HandleInit.Init.DataSize = SPI_DATASIZE_8BIT;		//����SPI������������Ϊ8λ
	SPI2_HandleInit.Init.CLKPolarity = SPI_POLARITY_LOW;		//����SPI�ļ���Ϊ�͵�ƽ(SCK�ڿ���״̬ʱΪ�͵�ƽ)
	SPI2_HandleInit.Init.CLKPhase = SPI_PHASE_1EDGE;		//����SPIΪ��һ�����ز���
	SPI2_HandleInit.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;		//����SPI������Ϊ2��Ƶ(���ֻ��2��Ƶ)
	SPI2_HandleInit.Init.FirstBit = SPI_FIRSTBIT_MSB;		//����SPI�豸�Ӹ�λ��ʼ��������
	SPI2_HandleInit.Init.NSS = SPI_NSS_SOFT;		//����SPI�����Ƭѡ�������������
	SPI2_HandleInit.Init.TIMode = SPI_TIMODE_DISABLE;		//ʧ��TIģʽ(������Ħ������ģʽ)
	SPI2_HandleInit.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;		//ʧ��CRCУ��
	SPI2_HandleInit.Init.CRCPolynomial = 10;		//CRCУ�鳣��Ϊ10
	HAL_SPI_Init(&SPI2_HandleInit);
    __HAL_SPI_ENABLE(&SPI2_HandleInit);
}

/*SPI2��дһ�ֽں���*/
uint8_t SPI2_ReadWriteByte(uint8_t TX_Data)
{
	static uint8_t RX_Data = 0;		//�����ݴ�ű���
	HAL_SPI_TransmitReceive(&SPI2_HandleInit,&TX_Data,&RX_Data,1,1000);		//HAL���е�SPI��д����
	return RX_Data;		//���ؽ��յ�������
}
