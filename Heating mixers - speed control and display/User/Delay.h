#ifndef __DELAY_H__
#define __DELAY_H__

/*ͷ�ļ�*/
#include "stm32f1xx.h"
/*�û��Զ������*/
#define u32 unsigned int
/*�û���������*/
void Delay_Init(u32 SYSCLK_Freq);
void Delay_us(u32 us);
void Delay_ms(u32 ms);
#endif













