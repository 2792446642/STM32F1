/*头文件*/
#include "usart1.h"

/*用户自定义变量*/
UART_HandleTypeDef UART_HandleInit = {0};

/*串口1初始化函数*/
void UART1_Init(uint32_t BaudRate)
{
	UART_HandleInit.Instance = USART1;
	UART_HandleInit.Init.BaudRate = BaudRate;		//设置串口1波特率
	UART_HandleInit.Init.Parity = UART_PARITY_NONE;		//无奇偶校验
	UART_HandleInit.Init.StopBits = UART_STOPBITS_1;		//一位停止位
	UART_HandleInit.Init.WordLength = UART_WORDLENGTH_8B;		//串口1字长为8位
	UART_HandleInit.Init.Mode = UART_MODE_TX_RX;		//串口1设置为收发模式
	UART_HandleInit.Init.HwFlowCtl = UART_HWCONTROL_NONE;		//无硬件流控制
	UART_HandleInit.Init.OverSampling = UART_OVERSAMPLING_16;		//16次过采样，容错性更好
	HAL_UART_Init(&UART_HandleInit);		//初始化串口1
	
}

/*串口1回调函数*/
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

/*串口1printf重定向函数*/
int fputc(int ch, FILE *f)
{ 
	HAL_UART_Transmit(&UART_HandleInit,(uint8_t *)&ch,1,1000);   //将要发送的字符写入到DR寄存器	
	while(__HAL_UART_GET_FLAG(&UART_HandleInit, UART_FLAG_TC) == RESET);
	return ch;
}

/*串口1阻塞式发送数据函数*/
void UART1_Transmit(uint8_t *TX_Data)
{
	uint32_t i = 0;
	__HAL_UART_CLEAR_FLAG(&UART_HandleInit, UART_FLAG_TC);		//清除串口发送完成标志位
	while(TX_Data[i] != '\0')
	{
		HAL_UART_Transmit(&UART_HandleInit,(uint8_t *)&TX_Data[i],1,0xffff);		//发送用户指定字符串
		while(__HAL_USART_GET_FLAG(&UART_HandleInit,UART_FLAG_TC) == RESET);		//等待串口1上一次数据发送完成
		__HAL_UART_CLEAR_FLAG(&UART_HandleInit, UART_FLAG_TC);		//再次清除
		i++;
	}
}








