/*ͷ�ļ�*/
#include "delay.h"

/*�û��Զ������*/
u32 systick_Freq = 0;


/*�û��Զ��庯��*/
//��ʱ������ʼ��
void Delay_Init(u32 SYSCLK_Freq)
{	
	SysTick->CTRL = 0;		//ϵͳ�δ�ʱ�ӿ��ƼĴ���ȫ������
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK_DIV8);		//ϵͳ�δ�ʱ��8��Ƶ
	systick_Freq = SYSCLK_Freq/8;		//��ȡϵͳ�δ�ʱ��Ƶ��(MHz)
}

//΢�뼶��ʱ����
void Delay_us(u32 us)
{
	u32 temp = 0;
	SysTick->LOAD = us*systick_Freq;		//�Զ���װ�ؼĴ�����ֵ
	SysTick->VAL = 0;		//��ռ�����
	SysTick->CTRL |= 1<<0;	//�����δ�ʱ��
	do
	{
		temp = SysTick->CTRL;		//���δ�ʱ���Ŀ��ƼĴ���ֵ����temp
	}while((temp & 0x01)&&!(temp&(1<<16)));		//�ȴ�������ֵ��Ϊ��
	SysTick->CTRL |= !(1<<0);		//�رյδ�ʱ��
	SysTick->VAL = 0;		//���������
}
//���뼶��ʱ����
void Delay_ms(u32 ms)
{
	u32 temp = 0;
	SysTick->LOAD = ms*1000*systick_Freq;		//�Զ���װ�ؼĴ�����ֵ
	SysTick->VAL = 0;		//��ռ�����
	SysTick->CTRL |= 1<<0;	//�����δ�ʱ��
	do
	{
		temp = SysTick->CTRL;		//���δ�ʱ���Ŀ��ƼĴ���ֵ����temp
	}while((temp & 0x01)&&!(temp&(1<<16)));		//�ȴ�������ֵ��Ϊ��
	SysTick->CTRL |= !(1<<0);		//�رյδ�ʱ��
	SysTick->VAL = 0;		//���������
}






































