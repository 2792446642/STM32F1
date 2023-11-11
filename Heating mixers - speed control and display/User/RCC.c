/*头文件*/
#include "rcc.h"
/*用户自定义变量*/

/*用户自定义函数*/
void SysClk_Init(void)
{
//	HAL_Init(void);
	HAL_StatusTypeDef RCC_OSC_Status;
	RCC_OscInitTypeDef RCC_OSCInitStruct = {0};		//初始话结构体成员值为0(若不赋初值则成员值为随机数)
	RCC_OSCInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;		//HSE预分频值
	RCC_OSCInitStruct.HSEState = RCC_HSE_ON;		//HSE状态
	RCC_OSCInitStruct.HSIState = RCC_HSI_ON;						//HSI状态
	RCC_OSCInitStruct.LSEState = RCC_LSE_ON;					//LSE状态
	RCC_OSCInitStruct.LSIState = RCC_LSI_ON;						//LSI状态
	RCC_OSCInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;			//选择需要配置的振荡器
	RCC_OSCInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;		//锁相环9倍频
	RCC_OSCInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;		//锁相环时钟源
	RCC_OSCInitStruct.PLL.PLLState = RCC_PLL_ON;		//使能锁相环
	RCC_OSC_Status = HAL_RCC_OscConfig(&RCC_OSCInitStruct);		//初始化时钟源、锁相环配置

	if(RCC_OSC_Status != HAL_OK)
	{
		while(1);		//时钟源、锁相环初始化失败！
	}
	RCC_ClkInitTypeDef RCC_ClkInitStruct;
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;		//时钟类型
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;		//设置系统时钟来源
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;		//AHB总线预分频系数
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;		//APB1总线预分频系数
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;		//APB2总线预分频系数
	HAL_RCC_ClockConfig(&RCC_ClkInitStruct,FLASH_LATENCY_2);
}

