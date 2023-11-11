/*ͷ�ļ�*/
#include "OLED.h"

/*�û��Զ������*/

/*OLED�����������ú���*/
void OLED_GPIO_Init(void)
{
	OLED_CLK_ENABLE;									//����OLED�������Ŷ˿�ʱ��
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;		//�˿�����Ϊ�������ģʽ	
	GPIO_InitStructure.Pin = RSE|DC|CS;					//OLED��������
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;	//�������
	HAL_GPIO_Init(OLED_Port,&GPIO_InitStructure);		//��ʼ��GPIOA�˿�		
}

/*OLEDд�ֽں���*/
void OLED_Write_Data(uint8_t Byte,uint8_t CD)
{
	if(CD == OLED_CMD)									//�����������Ϊ��������
	{
		OLED_DC_L;										//����DC�ߵ�ƽ���
	}
	else if(CD == OLED_DATA)							//�����������Ϊ��������
	{
		OLED_DC_H;										//����DC�ߵ�ƽ���
	}
	OLED_CS_L;											//����Ƭѡ��ѡ���ⲿ���豸��׼��д������
	SPI2_ReadWriteByte(Byte);				//��Ƭ��ͨ��SPIģ����OLED��Ļд����
	OLED_CS_H;											//����Ƭѡ�ߣ����������ӻ�������д��
}

/*OLED������ʾ����*/
void OLED_Display_ON(void)
{
	OLED_Write_Data(0x8d,OLED_CMD);						//�����ڲ�DCDC����
	OLED_Write_Data(0x14,OLED_CMD);						//����DCDC
	OLED_Write_Data(0xaf,OLED_CMD);						//������ʾ
}

/*OLED�ر���ʾ����*/
void OLED_Display_OFF(void)
{
	OLED_Write_Data(0x8d,OLED_CMD);						//�����ڲ�DCDC����
	OLED_Write_Data(0x10,OLED_CMD);						//�ر�DCDC
	OLED_Write_Data(0xaf,OLED_CMD);						//�ر���ʾ
}

/*OLED�������ú���(������Ϊ��(��128��)��������Ϊҳ(ÿҳ8�У���8ҳ))*/
void OLED_Set_Display_Position(uint8_t x,uint8_t y)
{
	OLED_Write_Data(0xb0 + y,OLED_CMD);					//������ʾλ�õ�ҳ��ַ
	OLED_Write_Data(((x & 0xf0) >> 4) | 0x10,OLED_CMD);	//ȡ���е�ַ�ĸ���λ
	OLED_Write_Data(x & 0x0f,OLED_CMD);					//ȡ���е�ַ�ĵ���λ
}

/*OLED��������*/
void OLED_Clear(uint8_t Color)
{
	static uint8_t i,n;
	if(Color == 1)										//OLED����
	{
		for(i = 0;i < 8;i++)							//ѭ��8ҳ
		{
			OLED_Write_Data(0xb0+i,OLED_CMD);			//������ʾλ�õ�ҳ��ַ
			OLED_Write_Data(X_L,OLED_CMD);				//���õ���λ�е�ַ
			OLED_Write_Data(X_H,OLED_CMD);				//���ø���λ�е�ַ
			for(n = 0;n < Column_Size;n++)				//ѭ��128��
			OLED_Write_Data(OLED_buffer[i][n],OLED_DATA);	//����ÿҳ128�е�LED����
		}
	}
	else if(Color == 0)	//OLEDϨ��
	{
		for(i = 0;i < 8;i++)	//ѭ��8ҳ
		{
			OLED_Write_Data(0xb0 + i,OLED_CMD);			//������ʾλ�õ�ҳ��ַ
			OLED_Write_Data(X_L,OLED_CMD);				//���õ���λ�е�ַ
			OLED_Write_Data(X_H,OLED_CMD);				//���ø���λ�е�ַ
			for(n = 0;n < Column_Size;n++)				//ѭ��128��
			OLED_Write_Data(~OLED_buffer[i][n],OLED_DATA); 	//����ÿҳ128�е�LED����
		}
	}
}

/*OLED��ʼ������*/
void OLED_Init(void)
{
	OLED_RSE_H;											//��ʼ����λ�������ߵ�ƽ
	Delay_ms(100);										//��ʱ100����
	OLED_RSE_L;											//��λ�������͵�ƽ
	Delay_ms(100);										//��ʱ100����
	OLED_RSE_H;											//�������߸�λ���ŵ�ƽ
	/*ssd1306����оƬ��ʼ��*/
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

/*OLED��ʾ����*/
void OLED_Display(void)
{
	uint8_t i,j;
	for(i = 0;i < 8;i++)
	{
		OLED_Write_Data(Y+i,OLED_CMD);					//����ҳ��ַ
		OLED_Write_Data(X_L,OLED_CMD);					//���õ���λ�е�ַ
		OLED_Write_Data(X_H,OLED_CMD);					//���ø���λ�е�ַ
		for(j = 0;j < Column_Size;j++)	
		{
			OLED_Write_Data(OLED_buffer[i][j],OLED_DATA);	//��OLED_buffer�����ڴ�ŵ����������δӵ͵���д�뵽OLED����оƬ�Ĵ�����
		}
	}
}

/*OLED���ص����ú���*/
 void OLED_Set_Pixel(uint8_t x, uint8_t y,uint8_t Color)
{
	if(Color == 1)										//����ɫ��ʾģʽ
	{
		OLED_buffer[y/Page_Size][x] |= (1<<((y%Page_Size)))&0xff;
	}
	else if(Color == 0)									//��תɫ��ʾģʽ
	{
		OLED_buffer[y/Page_Size][x] &= ~((1<<((y%Page_Size)))&0xff);
	}
}		

/*OLED��ʾλ�����ú���*/
void OLED_Set_Position(uint8_t x,uint8_t y)
{
	OLED_Write_Data(Y+y,OLED_CMD);						//����ҳ��ַ
	OLED_Write_Data(((x&0xf0)>>4)|0x10,OLED_CMD);
	OLED_Write_Data((x&0x0f)|0x01,OLED_CMD);
}

/*OLEDȫ�������ʾ����*/
void OLED_Fill_Up(uint8_t x0,uint8_t y0,uint8_t x1,uint8_t y1,uint8_t colour)
{
	uint8_t i,j;
	unsigned width = x1-x0+1;							//�õ����Ŀ��
	unsigned height = y1-y0+1;							//�õ����ĸ߶�	
	for(i = 0;i < height;i++)
	{
		for(j = 0;j < width;j++)
		{
			OLED_Set_Pixel(x0+j,y0+i,colour);
		}
	}
	OLED_Display();
}

/*OLED����Ӣ���ַ���ʾ����*/
void OLED_ShowEChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t Char_Size,uint8_t mode)
{      	
	uint8_t c = 0,i = 0,tmp = 0,j = 0;	
	c = chr - ' ';	//�õ�ƫ�ƺ��ֵ��ÿ���ַ���ǰ�����Դ�һ���� ����		
	if(x > Column_Size - 1)
	{
		x = 0;
		y = y + 2;
	}
	if(Char_Size == 16)	//�ж��ַ��ߴ��Ƿ�Ϊ16
	{
		for(i = 0;i < 16;i++)	//ѭ��16�εõ����е����������������
		{
			if(mode == 1)	//����ɫ��ʾģʽ���ڵװ��֣�
			{
				tmp = D8X16[c][i];	//ѡ����Ҫ��ʾ�ַ����У�c�����У�i����ֵ��tmp
			}
			else if(mode != 1)	//��תɫ��ʾģʽ���׵׺��֣�
			{
				tmp = ~(D8X16[c][i]);	//ѡ����Ҫ��ʾ�ַ����У�c�����У�i����ȡ����ֵ��tmp
			}
			for(j = 0;j < 8;j++)	//һ����8�����ص㣬ѭ��8�Σ�ÿ���ж�һ�����ص���������
			{
				if(tmp & (0x01 << (8 - j)))	//�����ص�Ϊ1
				{
					OLED_Set_Pixel(x + j, y + i,1);	//������Ӧ���ص�
				}
				else		//�����ص�Ϊ0
				{
					OLED_Set_Pixel(x + j, y + i,0);	//Ϩ���Ӧ�����ص�
				}
			}
		}
	}
	else if(Char_Size == 8)	//�ж��ַ��ߴ��Ƿ�Ϊ8
	{	
		for(i = 0;i < 8;i++)
		{
			if(mode == 1)	//�ж���ʾģʽ�Ƿ�Ϊ����ɫģʽ(��)
			{
				tmp = D6x8[c][i];	//����ɫ��ʾ���ڵװ��֣�
			}
			else	//�����ʾģʽ������ɫ
			{
				tmp = ~(D6x8[c][i]);	//��תɫ��ʾ���׵׺��֣�
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

/*OLEDӢ���ַ�����ʾ����*/
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

/*OLED_16x16�ߴ纺����ʾ����*/
void OLED_ShowGB16x16(uint8_t x,uint8_t y,uint8_t *s,uint8_t mode)
{
	uint8_t i,j,k,tmp,num;
	num = sizeof(hanzi_16x16) / sizeof(GB16);	//��һ��sizeofΪ������ռ�����ֽ������ڶ���Ϊ������������ռ���ֽ���,��������ó��������������ݵ��ܸ���
  	for(i = 0;i < num;i++)
	{
		if((hanzi_16x16[i].Word_Length[0] == *s) && (hanzi_16x16[i].Word_Length[1] == *(s+1)))	//��������������ַ��ĸ�8λ�͵�8λ��ƥ��ĺ���
		{
			for(j = 0;j < 32;j++)	//ȡ��32���ַ���ʾ����
			{
				if(mode)	//�ж�ģʽ�Ƿ�Ϊ������ʾģʽ
				{
					tmp = hanzi_16x16[i].Word_Data[j];	//������ʾģʽ���ڵװ��֣�
				}
				else
				{
					tmp = ~(hanzi_16x16[i].Word_Data[j]);	//��תɫ��ʾģʽ���׵׺��֣�
				}
				for(k = 0;k < 8;k++)	//32����ʾ�����е�һ��ȡ����
				{
					if(tmp & (0x80>>k))	//8λ���ݵ�ĳλ��Ϊ1
					{
						OLED_Set_Pixel(x + (j % 2) * 8 + k, y + j / 2,1);	//������Ӧ���е�LED
					}
					else	//8λ���ݵ�ĳλ��Ϊ0
					{
						OLED_Set_Pixel(x + ( j % 2) * 8 + k, y + j / 2,0);	//Ϩ���Ӧ���е�LED
					}
				}
			}	
		}	
	}
	OLED_Display();	//�����ʾ����
}

/*OLED_24x24�ߴ纺����ʾ����*/
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

/*OLED_32x32�ߴ纺����ʾ����*/
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

/*OLED������ʾ����*/
void OLED_ShowChinese(uint8_t x,uint8_t y,uint8_t hsize,uint8_t *str,uint8_t mode)
{ 
	while(*str != '\0')	//�ж��ַ����Ƿ������
	{
		if(hsize == 16)	//������ֳߴ�Ϊ16x16
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
		x += hsize;	//ÿ����һ���ַ������¸��ַ�����ǰ�����Զ���16/24/32
		if(x > Column_Size - hsize)	//������һ���ַ���ʾʱ��Ļ��ʣ����������16/24/32
		{
			x = 0;	//��������
			y += hsize;	//����������ƫ���ַ��ߴ�
		}
		str += 2;	//uint8_t�ַ���ָ���ַ��2��ָ����һ�������͵��ַ�
	}			
}

/*OLEDͼƬ��ʾ����*/
void OLED_ShowPicture(uint8_t x,uint8_t y,uint8_t width, uint8_t height, uint8_t BMP[], uint8_t mode)
{ 	
	uint8_t i,j,k;
	static uint8_t tmp;
	for(i = 0;i < height;i++)	//�����е���������
	{
		for(j = 0;j < ( width + 7 )/8;j++)	//�����е���������
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
	OLED_Display();	//�����ʾ
}
