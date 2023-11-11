/*头文件*/
#include "SPI2.h"

/*用户自定义变量*/
SPI_HandleTypeDef SPI2_HandleInit = {0};

/*SPI2初始化函数*/
void SPI2_Init(void)
{
    SPI2_CLK_ENABLE;
    SPI2_Port_CLK_ENABLE;

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;		//设置端口模式为复用推挽输出
    GPIO_InitStruct.Pin = SPI2_SCK;		//选择SPI2_SCK引脚
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(SPI2_Port,&GPIO_InitStruct);		//初始化GPIOB
    
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;		//设置端口模式为复用推挽输出
    GPIO_InitStruct.Pin = SPI2_MOSI;		//选择SPI2_MOSI引脚
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;		//端口输出速率为最高
    HAL_GPIO_Init(SPI2_Port,&GPIO_InitStruct);		//初始化GPIOB
    
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pin = SPI2_MISO;		//选择SPI2_MISO引脚
    GPIO_InitStruct.Pull = GPIO_NOPULL;		//设置引脚为上拉模式
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;		//端口输出速率为最高
    HAL_GPIO_Init(SPI2_Port,&GPIO_InitStruct);		//初始化GPIOB

    SPI2_HandleInit.Instance = SPI2;		//选择SPI2外设
	SPI2_HandleInit.Init.Mode = SPI_MODE_MASTER;		//配置SPI外设为主机模式
	SPI2_HandleInit.Init.Direction = SPI_DIRECTION_2LINES;		//配置SPI设备为同步全双工模式
	SPI2_HandleInit.Init.DataSize = SPI_DATASIZE_8BIT;		//配置SPI传送数据类型为8位
	SPI2_HandleInit.Init.CLKPolarity = SPI_POLARITY_LOW;		//配置SPI的极性为低电平(SCK在空闲状态时为低电平)
	SPI2_HandleInit.Init.CLKPhase = SPI_PHASE_1EDGE;		//配置SPI为第一个边沿采样
	SPI2_HandleInit.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;		//配置SPI波特率为2分频(最大只能2分频)
	SPI2_HandleInit.Init.FirstBit = SPI_FIRSTBIT_MSB;		//配置SPI设备从高位开始传输数据
	SPI2_HandleInit.Init.NSS = SPI_NSS_SOFT;		//配置SPI外设的片选引脚由软件控制
	SPI2_HandleInit.Init.TIMode = SPI_TIMODE_DISABLE;		//失能TI模式(即采用摩托罗拉模式)
	SPI2_HandleInit.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;		//失能CRC校验
	SPI2_HandleInit.Init.CRCPolynomial = 10;		//CRC校验常规为10
	HAL_SPI_Init(&SPI2_HandleInit);
    __HAL_SPI_ENABLE(&SPI2_HandleInit);
}

/*SPI2读写一字节函数*/
uint8_t SPI2_ReadWriteByte(uint8_t TX_Data)
{
	static uint8_t RX_Data = 0;		//读数据存放变量
	HAL_SPI_TransmitReceive(&SPI2_HandleInit,&TX_Data,&RX_Data,1,1000);		//HAL库中的SPI读写函数
	return RX_Data;		//返回接收到的数据
}
