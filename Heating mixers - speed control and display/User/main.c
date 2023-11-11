/*头文件*/
#include "rcc.h"
#include "OLED.h"
#include "Motor.h"

/*用户自定义变量*/

/*用户自定义函数*/
int main(void)
{
	SysClk_Init();
	Delay_Init(72);
	UART1_Init(115200);
	Motor_Init();
	TIM4_Init();
	EC11_Init();
	Encoder_Init();
	SPI2_Init();
	OLED_GPIO_Init();
	OLED_Init();
	OLED_ShowPicture(0,0,128,64,BPM2,0);
	Delay_ms(1000);
	OLED_Fill_Up(0,0,Column_Size-1,Row-1,0);
	while(1)
	{
		EC11_Speed_Display();
		Encoder_Speed_Display();
		Motor_Speed_Auto_Control();	
	}
}

