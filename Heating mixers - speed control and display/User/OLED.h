#ifndef __OLED_H__
#define __OLED_H__

#include "SPI2.h"
#include "BMP.h"
#include "Delay.h"

//OLED参数定义
#define Page_Size 8	    //总页�
#define Row 64	        //总行数（�页有8行，8页共64行）
#define Column_Size 128 //总列�
#define X_L 0x00	    //列低四位地址
#define X_H 0x10	    //列高四位地址
#define Y	0xb0	    //页地�（最低）

//-----OLED引脚定义-----//
#define OLED_CLK_ENABLE __HAL_RCC_GPIOB_CLK_ENABLE()
#define OLED_Port GPIOB
#define RSE GPIO_PIN_7	
#define DC  GPIO_PIN_8		
#define CS  GPIO_PIN_9		

//-----OLED命令/数据定义-----//
#define OLED_CMD 0
#define OLED_DATA 1

//-----OLED引脚操作定义-----//

#define OLED_CS_L HAL_GPIO_WritePin(OLED_Port,CS,GPIO_PIN_RESET)
#define OLED_CS_H HAL_GPIO_WritePin(OLED_Port,CS,GPIO_PIN_SET)

#define OLED_RSE_L HAL_GPIO_WritePin(OLED_Port,RSE,GPIO_PIN_RESET)
#define OLED_RSE_H HAL_GPIO_WritePin(OLED_Port,RSE,GPIO_PIN_SET)

#define OLED_DC_L HAL_GPIO_WritePin(OLED_Port,DC,GPIO_PIN_RESET)
#define OLED_DC_H HAL_GPIO_WritePin(OLED_Port,DC,GPIO_PIN_SET)

//-----OLED初始化配置函�----//
void OLED_GPIO_Init(void);
void OLED_Init(void);
void OLED_Write_Data(uint8_t Byte,uint8_t CD);
void OLED_Display_ON(void);
void OLED_Display_OFF(void);
void OLED_Set_Display_Position(uint8_t x,uint8_t y);
void OLED_Clear(uint8_t color);
void OLED_Display(void);
void OLED_Set_Position(uint8_t x,uint8_t y);

//-----OLED显示内容函数-----//
void OLED_Fill_Up(uint8_t x0,uint8_t y0,uint8_t x1,uint8_t y1,uint8_t colour);	//OLED全屏�灭显�
void OLED_ShowEString(uint8_t x,uint8_t y,uint8_t *chr,uint8_t Char_Size,uint8_t mode);	//OLED显示英文字符�
void OLED_ShowChinese(uint8_t x,uint8_t y,uint8_t hsize,uint8_t *str,uint8_t mode);	//OLED显示中文字符�
void OLED_ShowPicture(uint8_t x,uint8_t y,uint8_t width, uint8_t height, uint8_t BMP[], uint8_t mode);	//OLED显示图片

#endif
