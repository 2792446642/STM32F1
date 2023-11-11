/*头文件*/
#include "OLED.h"

/*用户自定义变量*/

/*OLED控制引脚配置函数*/
void OLED_GPIO_Init(void)
{
	OLED_CLK_ENABLE;									//开启OLED控制引脚端口时钟
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;		//端口配置为推挽输出模式	
	GPIO_InitStructure.Pin = RSE|DC|CS;					//OLED控制引脚
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;	//高速输出
	HAL_GPIO_Init(OLED_Port,&GPIO_InitStructure);		//初始化GPIOA端口		
}

/*OLED写字节函数*/
void OLED_Write_Data(uint8_t Byte,uint8_t CD)
{
	if(CD == OLED_CMD)									//如果输入数据为命令类型
	{
		OLED_DC_L;										//拉低DC线电平输出
	}
	else if(CD == OLED_DATA)							//如果输入数据为数据类型
	{
		OLED_DC_H;										//拉高DC线电平输出
	}
	OLED_CS_L;											//拉低片选，选择外部从设备，准备写入数据
	SPI2_ReadWriteByte(Byte);				//单片机通过SPI模块向OLED屏幕写数据
	OLED_CS_H;											//拉高片选线，完成主机向从机的数据写入
}

/*OLED开启显示函数*/
void OLED_Display_ON(void)
{
	OLED_Write_Data(0x8d,OLED_CMD);						//设置内部DCDC命令
	OLED_Write_Data(0x14,OLED_CMD);						//开启DCDC
	OLED_Write_Data(0xaf,OLED_CMD);						//开启显示
}

/*OLED关闭显示函数*/
void OLED_Display_OFF(void)
{
	OLED_Write_Data(0x8d,OLED_CMD);						//设置内部DCDC命令
	OLED_Write_Data(0x10,OLED_CMD);						//关闭DCDC
	OLED_Write_Data(0xaf,OLED_CMD);						//关闭显示
}

/*OLED坐标设置函数(横坐标为列(共128列)，纵坐标为页(每页8行，共8页))*/
void OLED_Set_Display_Position(uint8_t x,uint8_t y)
{
	OLED_Write_Data(0xb0 + y,OLED_CMD);					//设置显示位置的页地址
	OLED_Write_Data(((x & 0xf0) >> 4) | 0x10,OLED_CMD);	//取出列地址的高四位
	OLED_Write_Data(x & 0x0f,OLED_CMD);					//取出列地址的低四位
}

/*OLED清屏函数*/
void OLED_Clear(uint8_t Color)
{
	static uint8_t i,n;
	if(Color == 1)										//OLED亮屏
	{
		for(i = 0;i < 8;i++)							//循环8页
		{
			OLED_Write_Data(0xb0+i,OLED_CMD);			//设置显示位置的页地址
			OLED_Write_Data(X_L,OLED_CMD);				//设置低四位列地址
			OLED_Write_Data(X_H,OLED_CMD);				//设置高四位列地址
			for(n = 0;n < Column_Size;n++)				//循环128列
			OLED_Write_Data(OLED_buffer[i][n],OLED_DATA);	//设置每页128列的LED灯亮
		}
	}
	else if(Color == 0)	//OLED熄屏
	{
		for(i = 0;i < 8;i++)	//循环8页
		{
			OLED_Write_Data(0xb0 + i,OLED_CMD);			//设置显示位置的页地址
			OLED_Write_Data(X_L,OLED_CMD);				//设置低四位列地址
			OLED_Write_Data(X_H,OLED_CMD);				//设置高四位列地址
			for(n = 0;n < Column_Size;n++)				//循环128列
			OLED_Write_Data(~OLED_buffer[i][n],OLED_DATA); 	//设置每页128列的LED灯灭
		}
	}
}

/*OLED初始化函数*/
void OLED_Init(void)
{
	OLED_RSE_H;											//初始化复位引脚拉高电平
	Delay_ms(100);										//延时100毫秒
	OLED_RSE_L;											//复位引脚拉低电平
	Delay_ms(100);										//延时100毫秒
	OLED_RSE_H;											//重新拉高复位引脚电平
	/*ssd1306驱动芯片初始化*/
	OLED_Write_Data(0xAE,OLED_CMD); 					/*display off*/
	OLED_Write_Data(0x00,OLED_CMD); 					/*set lower column address*/
	OLED_Write_Data(0x10,OLED_CMD); 					/*set higher column address*/
	OLED_Write_Data(0x40,OLED_CMD); 					/*set display start line*/ 
	OLED_Write_Data(0xB0,OLED_CMD); 					/*set page address*/
	OLED_Write_Data(0x81,OLED_CMD); 					/*contract control*/ 
	OLED_Write_Data(0xFF,OLED_CMD); 					/*128*/
	OLED_Write_Data(0xA1,OLED_CMD); 					/*set segment remap*/ 
	OLED_Write_Data(0xA6,OLED_CMD); 					/*normal / reverse*/
	OLED_Write_Data(0xA8,OLED_CMD); 					/*multiplex ratio*/ 
	OLED_Write_Data(0x3F,OLED_CMD); 					/*duty = 1/64*/
	OLED_Write_Data(0xC8,OLED_CMD); 					/*Com scan direction*/
	OLED_Write_Data(0xD3,OLED_CMD); 					/*set display offset*/ 
	OLED_Write_Data(0x00,OLED_CMD);
	OLED_Write_Data(0xD5,OLED_CMD); 					/*set osc division*/ 
	OLED_Write_Data(0x80,OLED_CMD);
	OLED_Write_Data(0xD9,OLED_CMD); 					/*set pre-charge period*/ 
	OLED_Write_Data(0XF1,OLED_CMD);
	OLED_Write_Data(0xDA,OLED_CMD); 					/*set COM pins*/ 
	OLED_Write_Data(0x12,OLED_CMD);
	OLED_Write_Data(0xDB,OLED_CMD); 					/*set vcomh*/ 
	OLED_Write_Data(0x30,OLED_CMD);
	OLED_Write_Data(0x8D,OLED_CMD); 					/*set charge pump disable*/ 
	OLED_Write_Data(0x14,OLED_CMD);
	OLED_Write_Data(0xAF,OLED_CMD); 					/*display ON*/
}

/*OLED显示函数*/
void OLED_Display(void)
{
	uint8_t i,j;
	for(i = 0;i < 8;i++)
	{
		OLED_Write_Data(Y+i,OLED_CMD);					//设置页地址
		OLED_Write_Data(X_L,OLED_CMD);					//设置低四位列地址
		OLED_Write_Data(X_H,OLED_CMD);					//设置高四位列地址
		for(j = 0;j < Column_Size;j++)	
		{
			OLED_Write_Data(OLED_buffer[i][j],OLED_DATA);	//将OLED_buffer数组内存放的列数据依次从低到高写入到OLED驱动芯片寄存器内
		}
	}
}

/*OLED像素点设置函数*/
 void OLED_Set_Pixel(uint8_t x, uint8_t y,uint8_t Color)
{
	if(Color == 1)										//正常色显示模式
	{
		OLED_buffer[y/Page_Size][x] |= (1<<((y%Page_Size)))&0xff;
	}
	else if(Color == 0)									//反转色显示模式
	{
		OLED_buffer[y/Page_Size][x] &= ~((1<<((y%Page_Size)))&0xff);
	}
}		

/*OLED显示位置设置函数*/
void OLED_Set_Position(uint8_t x,uint8_t y)
{
	OLED_Write_Data(Y+y,OLED_CMD);						//设置页地址
	OLED_Write_Data(((x&0xf0)>>4)|0x10,OLED_CMD);
	OLED_Write_Data((x&0x0f)|0x01,OLED_CMD);
}

/*OLED全屏填充显示函数*/
void OLED_Fill_Up(uint8_t x0,uint8_t y0,uint8_t x1,uint8_t y1,uint8_t colour)
{
	uint8_t i,j;
	unsigned width = x1-x0+1;							//得到填充的宽度
	unsigned height = y1-y0+1;							//得到填充的高度	
	for(i = 0;i < height;i++)
	{
		for(j = 0;j < width;j++)
		{
			OLED_Set_Pixel(x0+j,y0+i,colour);
		}
	}
	OLED_Display();
}

/*OLED单个英文字符显示函数*/
void OLED_ShowEChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t Char_Size,uint8_t mode)
{      	
	uint8_t c = 0,i = 0,tmp = 0,j = 0;	
	c = chr - ' ';	//得到偏移后的值（每个字符串前都会自带一个‘ ’）		
	if(x > Column_Size - 1)
	{
		x = 0;
		y = y + 2;
	}
	if(Char_Size == 16)	//判断字符尺寸是否为16
	{
		for(i = 0;i < 16;i++)	//循环16次得到该行的所有列所存的数据
		{
			if(mode == 1)	//正常色显示模式（黑底白字）
			{
				tmp = D8X16[c][i];	//选中需要显示字符的行（c）和列（i）赋值给tmp
			}
			else if(mode != 1)	//反转色显示模式（白底黑字）
			{
				tmp = ~(D8X16[c][i]);	//选中需要显示字符的行（c）和列（i）并取反赋值给tmp
			}
			for(j = 0;j < 8;j++)	//一列有8个像素点，循环8次，每次判断一个像素点的亮灭情况
			{
				if(tmp & (0x01 << (8 - j)))	//该像素点为1
				{
					OLED_Set_Pixel(x + j, y + i,1);	//点亮对应像素点
				}
				else		//该像素点为0
				{
					OLED_Set_Pixel(x + j, y + i,0);	//熄灭对应的像素点
				}
			}
		}
	}
	else if(Char_Size == 8)	//判断字符尺寸是否为8
	{	
		for(i = 0;i < 8;i++)
		{
			if(mode == 1)	//判断显示模式是否为正常色模式(是)
			{
				tmp = D6x8[c][i];	//正常色显示（黑底白字）
			}
			else	//如果显示模式非正常色
			{
				tmp = ~(D6x8[c][i]);	//反转色显示（白底黑字）
			}
			for(j=0;j<8;j++)
			{
				if(tmp & (0x01 >> (8 - j)))
				{
					OLED_Set_Pixel(x + j, y + i,1);
				}
				else
				{
					OLED_Set_Pixel(x + j, y + i,0);
				}
			}
		}
	}
	OLED_Display();
}

/*OLED英文字符串显示函数*/
void OLED_ShowEString(uint8_t x,uint8_t y,uint8_t *chr,uint8_t Char_Size,uint8_t mode)
{
	uint8_t j = 0,Chr_size = 0;
	if(Char_Size == 16)
  	{
		Chr_size = Char_Size / 2;
	}
 	else if(Char_Size == 8)
  	{
	  	Chr_size = Char_Size / 2 + 2;
	}
	while(chr[j] != '\0')
	{		
		OLED_ShowEChar(x,y,chr[j],Char_Size,mode);
		x += Chr_size;
		if(x > 128)
		{
			x = 0;
			y += Char_Size;
		}
		j++;
	}
}

/*OLED_16x16尺寸汉字显示函数*/
void OLED_ShowGB16x16(uint8_t x,uint8_t y,uint8_t *s,uint8_t mode)
{
	uint8_t i,j,k,tmp,num;
	num = sizeof(hanzi_16x16) / sizeof(GB16);	//第一个sizeof为数组所占的总字节数，第二个为该数组类型所占的字节数,两者相除得出数组内所含数据的总个数
  	for(i = 0;i < num;i++)
	{
		if((hanzi_16x16[i].Word_Length[0] == *s) && (hanzi_16x16[i].Word_Length[1] == *(s+1)))	//在数组内找与该字符的高8位和低8位相匹配的汉字
		{
			for(j = 0;j < 32;j++)	//取出32个字符显示数据
			{
				if(mode)	//判断模式是否为正常显示模式
				{
					tmp = hanzi_16x16[i].Word_Data[j];	//正常显示模式（黑底白字）
				}
				else
				{
					tmp = ~(hanzi_16x16[i].Word_Data[j]);	//反转色显示模式（白底黑字）
				}
				for(k = 0;k < 8;k++)	//32个显示数据中的一个取出来
				{
					if(tmp & (0x80>>k))	//8位数据的某位若为1
					{
						OLED_Set_Pixel(x + (j % 2) * 8 + k, y + j / 2,1);	//点亮对应行列的LED
					}
					else	//8位数据的某位若为0
					{
						OLED_Set_Pixel(x + ( j % 2) * 8 + k, y + j / 2,0);	//熄灭对应行列的LED
					}
				}
			}	
		}	
	}
	OLED_Display();	//输出显示汉字
}

/*OLED_24x24尺寸汉字显示函数*/
 void OLED_ShowGB24x24(uint8_t x,uint8_t y,uint8_t *s,uint8_t mode)
 {
 	uint8_t i,j,k,tmp;
 	uint16_t num;
 	num = sizeof(hanzi_24x24)/sizeof(GB24);
   	for(i=0;i<num;i++)
 	{
 		if((hanzi_24x24[i].Word_Length[0] == *s) && (hanzi_24x24[i].Word_Length[1] == *(s+1)))
 		{
 			for(j=0;j<72;j++)
 			{
 				if(mode)
 				{
 					tmp = hanzi_24x24[i].Word_Data[j];
 				}
 				else
 				{
 					tmp = ~(hanzi_24x24[i].Word_Data[j]);
 				}
 				for(k=0;k<8;k++)
 				{
 					if(tmp&(0x80>>k))
 					{
 						OLED_Set_Pixel(x+(j%3)*8+k, y+j/3,1);
 					}
 					else
 					{
 						OLED_Set_Pixel(x+(j%3)*8+k, y+j/3,0);
 					}
 				}
 			}	
 			break;
 		}	
 	}
 	OLED_Display();
 }

/*OLED_32x32尺寸汉字显示函数*/
void OLED_ShowGB32x32(uint8_t x,uint8_t y,uint8_t *s,uint8_t mode)
{
	uint8_t i,j,k,tmp;
	uint16_t num;
	num = sizeof(hanzi_32x32)/sizeof(GB32);
  for(i=0;i<num;i++)
	{
		if((hanzi_32x32[i].Word_Length[0] == *s) && (hanzi_32x32[i].Word_Length[1] == *(s+1)))
		{
			for(j=0;j<128;j++)
			{
				if(mode)
				{
					tmp = hanzi_32x32[i].Word_Data[j];
				}
				else
				{
					tmp = ~(hanzi_32x32[i].Word_Data[j]);
				}
				for(k=0;k<8;k++)
				{
					if(tmp&(0x80>>k))
					{
						OLED_Set_Pixel(x+(j%4)*8+k, y+j/4,1);
					}
					else
					{
						OLED_Set_Pixel(x+(j%4)*8+k, y+j/4,0);
					}
				}
			}	
		}	
	}
	OLED_Display();
}

/*OLED汉字显示函数*/
void OLED_ShowChinese(uint8_t x,uint8_t y,uint8_t hsize,uint8_t *str,uint8_t mode)
{ 
	while(*str != '\0')	//判断字符串是否传送完成
	{
		if(hsize == 16)	//如果汉字尺寸为16x16
		{
			OLED_ShowGB16x16(x,y,str,mode);
		}
		else if(hsize == 24)
		{
			OLED_ShowGB24x24(x,y,str,mode);
		}
		else if(hsize == 32)
		{
			OLED_ShowGB32x32(x,y,str,mode);
		}
		x += hsize;	//每传送一个字符，在下个字符传送前列数自动加16/24/32
		if(x > Column_Size - hsize)	//如果最后一个字符显示时屏幕所剩的列数少于16/24/32
		{
			x = 0;	//列数清零
			y += hsize;	//行数数向下偏移字符尺寸
		}
		str += 2;	//uint8_t字符串指针地址加2，指向下一个待传送的字符
	}			
}

/*OLED图片显示函数*/
void OLED_ShowPicture(uint8_t x,uint8_t y,uint8_t width, uint8_t height, uint8_t BMP[], uint8_t mode)
{ 	
	uint8_t i,j,k;
	static uint8_t tmp;
	for(i = 0;i < height;i++)	//数组中的数据行数
	{
		for(j = 0;j < ( width + 7 )/8;j++)	//数组中的数据列数
		{
			if(mode)
			{
				tmp = BMP[i * ((width+7)/8) + j];
			}
			else
			{
				tmp = ~BMP[i * ((width+7)/8) + j];
			}
			for(k = 0;k < 8;k++)
			{
				if(tmp & (0x80 >> k))
				{
					OLED_Set_Pixel(x + j*8 + k, y + i,1);
				}
				else
				{
					OLED_Set_Pixel(x + j*8 + k, y + i,0);
				}
			}
		}
	} 
	OLED_Display();	//输出显示
}
