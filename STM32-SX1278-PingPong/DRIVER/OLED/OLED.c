/******************************************************************
 * �ļ���OLED.c
 * ���ܣ�ʵ��OLED��������
 * ���ڣ�2018-03-05
 * ���ߣ�zx
 * �汾��Ver.1.0 | ����汾
 * 
 * Copyright (C) 2018 zx. All rights reserved.
*******************************************************************/
#include "stdio.h"
#include "string.h"
#include "OLED/OLED.h"
#include "OLED/FONT.h"  	 
#include "DELAY/Delay.h"
#include "IIC/IIC.h"
#include "OLED/BMP.h"
/**********************************��̬���ܺ���**************************************/
/**
 * ���ܣ�����ָ������ֵ��Ч��������
 * ������
 * 		x:x������
 * 		y:y������
 * ����ֵ��None
 */
static void setPos(unsigned char x, unsigned char y) 
{ 
	writeCommand(0xb0+y);
	writeCommand(((x&0xf0)>>4)|0x10);
	writeCommand(x&0x0f); 
} 

/**
 * ���ܣ�����ָ���������ֿ��е�λ��
 * ������
 *      str:�����Һ����ַ�����һ������Ҳ���ַ�����ռ��3�ֽڣ�
 * 		cnfont_index:�����������ֿ����������ַ
 * ����ֵ��None
 */
static u8 findCNIndex(u8* str,u8* cnfont_index)
{
	u16 cnfont_size = strlen(cnfont_index);

	u8 index = 0;
	for(index=0;index<cnfont_size/3;++index)
	{
		if(((str[0]^cnfont_index[index*3+0])||(str[1]^cnfont_index[index*3+1])||(str[2]^cnfont_index[index*3+2]))==0)//ƥ�䵽��������
		{
			return index;
		}
	}

	return 0; //û��ƥ�䵽ֱ�ӷ����ֿ��һ�������������ǡ��硱
}

/**
 * ���ܣ�д�������OLED
 * ������
 * 		cmd:����
 * ����ֵ��None
 */
static void writeCommand(unsigned char cmd)
{
	startIIC();
	sendIICByte(0x78); //���ʹӻ���ַ��дָ��λ('0')       
	waitAck();	
	sendIICByte(0x00); //д������ֽ�
	waitAck();	
	sendIICByte(cmd); 
	waitAck();	
	stopIIC();
}

/**
 * ���ܣ�д�����ݸ�OLED
 * ������
 * 		data:����
 * ����ֵ��None
 */
static void writeData(unsigned char data)
{
	startIIC();
	sendIICByte(0x78);	//���ʹӻ���ַ��дָ��λ('0')
	waitAck();	
	sendIICByte(0x40);	//д������ֽ�
	waitAck();	
	sendIICByte(data);
	waitAck();	
	stopIIC();
}
/**********************************��Ļ���ú���**************************************/
/**
 * ���ܣ�������Ļ��ɫ  
 * ������
 * 		set�����ò���   SCREEN_NORMAL,SCREEN_REVERSE��ѡ
 * ����ֵ��None
 */
void setScreenReverse(SCREEN_SHOW set)
{
	if(set==SCREEN_REVERSE)		//��Ļ��ɫ
	{
		writeCommand(0xA7);
	}else 						//��Ļ��ɫ
	{
		writeCommand(0xA6);
	}
}

/**
 * ���ܣ�������Ļ��ʾ�����������ֻ���Ļ��ת  
 * ������
 * 		set�����ò���   SCREEN_UP,SCREEN_DOWN��ѡ
 * ����ֵ��None
 */
void setScreenDir(SCREEN_DIR set)
{
	if(set==SCREEN_UP)			//��Ļ����
	{
		writeCommand(0xA1);
		writeCommand(0xC8);
	}else 						//��Ļ����
	{
		writeCommand(0xA0);
		writeCommand(0xC0);
	}
}

/**
 * ���ܣ�������Ļ�Ƿ������������ֻ�Ϣ���ͻ���
 * ������
 * 		set�����ò���   SCREEN_ON,SCREEN_OFF��ѡ
 * ����ֵ��None
 */
void setScreenSwtich(SCREEN_SWITCH set)
{
	if(set==SCREEN_ON)
	{
		writeCommand(0xAF);
	}else 
	{
		writeCommand(0xAE);
	}
}

/**********************************��ʾ����������**************************************/
/**
 * ���ܣ���ʼ��OLED
 * ������None
 * ����ֵ��None
 */
void initOLED(void)
{ 	 
	writeCommand(0x81); 	//��������
	writeCommand(0xFF); 	//����ֵ��� ��λĬ��0x7F
	writeCommand(0xA1);		//���ö�ӳ�䷽ʽ�������Ƿ�ˮƽ��ת A0��ʾ��ת ͨ����C0һ��ʹ��
	writeCommand(0xC8);		//����COMɨ��ģʽ�������Ƿ�ֱ��ת C0��ʾ��ת ͨ����A0һ��ʹ��	
	writeCommand(0x8D);		//��ɱ�ʹ��
	writeCommand(0x14);
	
	writeCommand(0xAF);		//����Ļ��Ĭ���ǹرյľͺ�û�ϵ�һ��������Ҫ�ֶ�����
} 

/**
 * ���ܣ���ʽ����Ļ����ʹ��0x00����0xFF������ʹ�ò�ͬ���ݿ��Բ�����ͬ������
 * ������
 * 		format_data����ʽ�����ݣ�һ���������õ�0x00����0xFF
 * ����ֵ��None
 */
void formatScreen(u8 format_data)  
{  
	u8 x,y;		    
	for(y=0;y<8;++y)  
	{  
		writeCommand(0xb0+y);    //����ҳ��ַ��0~7��
		writeCommand(0x00);      //������ʾλ�á��е͵�ַ
		writeCommand(0x10);      //������ʾλ�á��иߵ�ַ   
		for(x=0;x<128;++x)
		{
			writeData(format_data); 
		}	
	} 
}

/**
 * ���ܣ���ʾһ���ַ���OLED
 * ������
 * 		x:x������ 0-127
 * 		y:y������ 0-7
 * 		ch:����ʾ�ַ� ASCII�ַ���
 * 		f_size:�����С FONT_8_EN(0608) FONT_16_EN(0816)
 * ����ֵ��None
 */
void showChar(u8 x,u8 y,u8 ch,FONT_SIZE f_size)
{      	
		u8 index = ch-' ';	
		u8 i;
		
		if(x > 127 || y > 7) 			//�����쳣����
		{
			x = 0;
			y = 0;
		}
		if(f_size == FONT_16_EN)		//�����16*8����
		{
			setPos(x,y);	
			for(i=0;i<8;++i)			//������8*16�ĵ������ռ����ҳ��Ҫ�ֳ�д�룬��ʱд���һҳ
			{
				writeData(ANSIC0816[index][i]);
			}
			setPos(x,y+1);				//��Ϊָ����һҳ��ַ
			for(i=8;i<16;++i)			//������8*16�ĵ������ռ����ҳ��Ҫ�ֳ�д�룬��ʱд��ڶ�ҳ
			{
				writeData(ANSIC0816[index][i]);
			}
			
		}else if(f_size == FONT_8_EN)	//6*8����
		{	
			setPos(x,y);
			for(i=0;i<6;i++)			//6*8����д��һҳ����
			{
				writeData(ANSIC0608[index][i]);		
			}	
		}else 
		{
			/*�������徴���ڴ�:)*/
		}
}

/**
 * ���ܣ���ʾ�ַ�����OLED
 * ������
 * 		x:x������ 0-127
 * 		y:y������ 0-7
 * 		str:����ʾ�ַ���
 * 		f_size:�����С FONT_8_EN(0608) FONT_16_EN(0816)
 * ����ֵ��None
 */  
void showString(u8 x,u8 y,u8* str,FONT_SIZE f_size)
{
	while(*str)
	{
		showChar(x,y,*str++,f_size);	
		x += f_size;		//���Ӻ����꣬�Ƶ���һ������λ��
	}
}

/**
 * ���ܣ��԰˽���/ʮ����/ʮ��������ʾ�������������
 * ������
 * 		x:x������ 0-127
 * 		y:y������ 0-7
 * 		number:����ʾ������֧�ָ���
 * 		radix:ѡ����ʾ���ƣ���ѡOCT/DEC/HEX
 *      ndigit:ռ�ü����ַ�
 * 		f_size:�����С FONT_8_EN(0608) FONT_16_EN(0816)
 * ����ֵ��None
 * ע�⣺
 */ 
void showNumber(u8 x,u8 y,s32 number,RADIX radix,u8 ndigit,FONT_SIZE f_size)
{
	u8 i = 0;
	u8 str[25] = {0}; 				//��������ת�ַ����Ĵ洢buffer

	if(radix==DEC) 					//��ʮ���ƴ洢
	{
		sprintf(str,"%d",number);
	}else if(radix==HEX)			//��ʮ�����ƴ洢
	{
		sprintf(str,"%X",number);
	}else if(radix==OCT)			//���˽��ƴ洢
	{
		sprintf(str,"%o",number);
	}else 
	{
		sprintf(str,"%d",number);   //�������󣬰�ʮ���ƴ���
	}

	
	for(i=strlen(str);i<ndigit;++i)
	{
		str[i] = ' ';
	}
	
	i = 0;
	while(str[i])
	{
		showChar(x,y,str[i++],f_size);	
		x += f_size;
	}	
}

/**
 * ���ܣ���ʾ16*16������
 * ������
 * 		x:x������ 0-127
 * 		y:y������ 0-7
 * 		str:����ʾ����֧�ֵ������ֺͶ������
 * 		f_size:�����С Ŀǰֻ�ṩ��16*16�����֣����Ҫ��������С�ĺ�����Ӷ�Ӧ�жϼ���
 * 			    �������иò�����Ч
 * ����ֵ��None
 */ 
void showCNString(u8 x,u8 y,u8* str,FONT_SIZE f_size)
{   
	u8 i;
	u8 cn_index;
	u8 count;
	if(x > 127 || y > 7) //�����쳣����
	{
		x = 0;
		y = 0;
	}  

	for(count=0;count<strlen(str)/3;++count)
	{
		cn_index = findCNIndex(str+count*3,CN1616_Index);
		setPos(x+16*count,y);
		for(i=0;i<16;++i)
		{
			writeData(CN1616[cn_index][i]);
		}
		setPos(x+16*count,y+1);
		for(i=16;i<32;++i)
		{
			writeData(CN1616[cn_index][i]);
		}
	} 			    
		
}


/**
 * ���ܣ����ƶ�������ʾͼƬ
 * ������
 * 		x:x������ 0-127
 * 		y:y������ 0-7
 * 		x_len:��ʾ��������곤�� 0-128
 *		y_len:��ʾ���������곤�� 0-8
 * 		image_index:ͼƬö������
 * ˵�����ú���һ��������ʾȫ��LOGO������������ÿ�����ʾPPT�л���Ч
 * 		����x_len����LOGO�ͻ����������ʾ�������÷�����
 * ����ֵ��None
 */ 
void showImage(u8 xpos, u8 ypos,u8 x_len, u8 y_len,IMAGE_INDEX  image_index)
{ 	
	u16 i,j;

	for(i=0;i<y_len;++i)					//ҳ��ַ����
	{
		setPos(xpos,ypos++);
		
		for(j=i*128+xpos;j<i*128+x_len;++j) //�е�ַ����
		{
			switch(image_index)
			{
				case FM_LOGO_ENUM        :writeData(FM_LOGO[j]);        break;
				case BRIGHTNESS_LOGO_ENUM:writeData(BRIGHTNESS_LOGO[j]);break;
				case DIRECT_LOGO_ENUM    :writeData(DIRECT_LOGO[j]);    break;
				case REVERSAL_LOGO_ENUM  :writeData(REVERSAL_LOGO[j]);  break;

				default                  :                              break;
			}
			
		}
	}
} 
					    
 





























