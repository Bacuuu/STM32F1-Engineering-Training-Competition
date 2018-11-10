#ifndef __OLED_H
#define __OLED_H

#include"stm32f10x.h"

/*XΪ1ʱ��ӦGPIO�˿�����ߵ�ƽ��XΪ0ʱ��ӦGPIO�˿�����͵�ƽ*/
#define OLED_CS(X)        X?GPIO_SetBits(GPIOD, GPIO_Pin_3):GPIO_ResetBits(GPIOD, GPIO_Pin_3)   	//CS
#define OLED_RST(X)        X?GPIO_SetBits(GPIOD, GPIO_Pin_4):GPIO_ResetBits(GPIOD, GPIO_Pin_4)    	//RST
#define OLED_DC(X)        X?GPIO_SetBits(GPIOD, GPIO_Pin_5):GPIO_ResetBits(GPIOD, GPIO_Pin_5)		//DC
#define OLED_D0(X)        X?GPIO_SetBits(GPIOD, GPIO_Pin_6):GPIO_ResetBits(GPIOD, GPIO_Pin_6)    	//CK
#define OLED_D1(X)        X?GPIO_SetBits(GPIOD, GPIO_Pin_7):GPIO_ResetBits(GPIOD, GPIO_Pin_7)    	//DI

/*����д����*/
#define OLED_Order 0
/*����д����*/
#define OLED_Data  1

/*��ʾ�ַ�����*/
const unsigned char ren[]=
{
0x00,0x01,0x80,0x00,0x60,0x00,0xF8,0xFF,0x87,0x00,0x80,0x40,0x84,0x40,0x84,0x40,
0x84,0x40,0xFE,0x7F,0x82,0x40,0x83,0x40,0x82,0x40,0x80,0x40,0x80,0x00,0x00,0x00,//��0
};

const unsigned char wu[]=
{
0x00,0x01,0x00,0x01,0x90,0x80,0x88,0x42,0x4C,0x22,0x57,0x1A,0xA4,0x07,0x24,0x02,
0x54,0x42,0x54,0x82,0x8C,0x42,0x84,0x3E,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x00,//��1
};

const unsigned char xian[]=
{

0x00,0x40,0x00,0x42,0x00,0x44,0xFE,0x58,0x92,0x40,0x92,0x7F,0x92,0x40,0x92,0x40,
0x92,0x40,0x92,0x7F,0x92,0x40,0xFE,0x50,0x00,0x48,0x00,0x46,0x00,0x40,0x00,0x00,//��2
};

const unsigned char shi[]=
{
0x40,0x20,0x40,0x10,0x42,0x08,0x42,0x06,0x42,0x00,0x42,0x40,0x42,0x80,0xC2,0x7F,
0x42,0x00,0x42,0x00,0x42,0x00,0x42,0x02,0x42,0x04,0x40,0x08,0x40,0x30,0x00,0x00,//ʾ3
};

const unsigned char ASCII_Colon[]=
{    0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0x30,
    0xC0,0x30,0x00,0x00,0x00,0x00,0x00,0x00};// :  

const unsigned char hong[]=
{
0x20,0x22,0x30,0x67,0xAC,0x22,0x63,0x12,0x20,0x12,0x18,0x12,0x00,0x40,0x04,0x40,
0x04,0x40,0x04,0x40,0xFC,0x7F,0x04,0x40,0x04,0x40,0x04,0x40,0x00,0x40,0x00,0x00,//��4
};

const unsigned char lv[]=
{
0x20,0x22,0x30,0x67,0xAC,0x22,0x63,0x12,0x30,0x12,0x00,0x00,0x80,0x22,0x92,0x14,
0x92,0x48,0x92,0x84,0x92,0x7F,0x92,0x04,0xFE,0x08,0x80,0x14,0x80,0x22,0x00,0x00,//��5
};

const unsigned char lan[]=
{
0x04,0x40,0x04,0x40,0xE4,0x7D,0x04,0x44,0x0F,0x44,0xF4,0x7D,0x04,0x44,0x04,0x45,
0xF4,0x44,0x44,0x7C,0xCF,0x44,0x44,0x45,0x44,0x7C,0x44,0x40,0x04,0x40,0x00,0x00,//��6
};

/*GPIO��ʼ��*/
void OLED_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;    
    //����GPIOD��ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);  //��紫����
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	GPIO_Init(GPIOE, &GPIO_InitStruct);
	
    //����GPIO�Ļ�������
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;    //�������
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;    //����ٶ�50MHz

    GPIO_Init(GPIOD, &GPIO_InitStruct);
    GPIO_SetBits(GPIOD, GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7);
	

}


void delayms(u16 time)
{    
   u16 i=0;  
   while(time--)
   {
      i=12000;  //�Լ�����
      while(i--) ;    
   }
}


/*        SPIд����/����
 *    Mode :O:д����   1��д����
 *    data :����/����
 *
*/
void SPI_Write(char data, int Mode)
{    
    int i = 0;
    if(Mode)
    {
        OLED_DC(OLED_Data);        //DC��������ߣ���ʾд����
    }
    else
    {
        OLED_DC(OLED_Order);        //DC��������ͣ���ʾд����
    }
    OLED_CS(0);            //CS��������ͣ�Ƭѡʹ��
    for(i = 0; i < 8; i++)
    {
        OLED_D0(0);        //D0���������
        if(data & 0x80)    //�жϴ�����������λΪ1����0
        {
            OLED_D1(1);    //D1���������
        }
        else
        {
            OLED_D1(0);    //D1���������
        }
        OLED_D0(1);        //D1���������
        data <<= 1;        //����������һλ
    }
    OLED_DC(0);            //DC���������
    OLED_CS(1);            //CS��������ߣ�Ƭѡʧ��
}



/*        ����OLED������ʾ����
 *  ����  X : ��ʾOLED��ˮƽ���꣨0��127��
 * ����   Y : ��ʾOLED��ҳ��0��7��
 *        
*/
void OLED_Coord(unsigned char x, unsigned char y)
{
    SPI_Write((0xb0+(y & 0x0f)),0);        //����OLED��ʾ��ҳ    
    SPI_Write((((x & 0xf0)>>4) | 0x10), 0);//����OLEDˮƽ����ĸ�4λ
    SPI_Write((x & 0x0f)|0x01, 0);                //����OLEDˮƽ����ĵ�4λ
}


/*
 *        ���OLED����ʾ
 *
 *
*/
void OLED_Clear(void)
{
    int i = 0, j = 0;
    for(i = 0; i < 8; i++)
    {
        OLED_Coord(0, i);
        for(j = 0; j < 128; j++)
        {
            SPI_Write(0x00, 1);
        }
    }
}


/*        �ر�OLED��ʾ
 *
 *
*/
void OLED_Display_Off(void)
{
    //��ɱ����ã���ʼ��ʱ����򿪣����򿴲�����ʾ��
    SPI_Write(0x8D, OLED_Order);
    SPI_Write(0x10, OLED_Order);//bit2   0���ر�        1����
    SPI_Write(0xAE, OLED_Order);//0xAE:�ر���ʾ
}

/*
 *        ����OLED��ʾ
 *
*/
void OLED_Display_On(void)
{
    //��ɱ����ã���ʼ��ʱ����򿪣����򿴲�����ʾ��
    SPI_Write(0x8D, OLED_Order);
    SPI_Write(0x14, OLED_Order);//bit2   0���ر�        1����
    SPI_Write(0xAF, OLED_Order);//0xAF:����ʾ    
}


/*        OLED��ʾ�����ĳ�ʼ��
 *
 *
 *
*/
void OLED_Init(void)
{
    OLED_GPIO_Init();
    
    OLED_RST(1);
    delayms(100);
    OLED_RST(0);
    delayms(100);
    OLED_RST(1);
    
    SPI_Write(0xAE, OLED_Order);//0xAE:����ʾ   
    
    SPI_Write(0x00, OLED_Order);//���õ��е�ַ
    SPI_Write(0x10, OLED_Order);//���ø��е�ַ
    
    //��������ʾ�Ŀ�ʼ��ַ(0-63)
    //40-47: (01xxxxx)
    SPI_Write(0x40, OLED_Order);
    
    //���öԱȶ�
    SPI_Write(0x81, OLED_Order);
    SPI_Write(0xff, OLED_Order);//���ֵԽ����ĻԽ��(������ָ��һ��ʹ��)(0x00-0xff)
    
    SPI_Write(0xA1, OLED_Order);//0xA1: ���ҷ��ã�  0xA0: ������ʾ��Ĭ��0xA0��
    SPI_Write(0xC8, OLED_Order);//0xC8: ���·��ã�  0xC0: ������ʾ��Ĭ��0xC0��
    
    //0xA6: ��ʾ������ʾ���������1��ʾ������0��ʾ������
    //0xA7: ��ʾ����ʾ���������0��ʾ������1��ʾ������
    SPI_Write(0xA6, OLED_Order);
    
    SPI_Write(0xA8, OLED_Order);//���ö�·�����ʣ�1-64��
    SPI_Write(0x3F, OLED_Order);//��0x01-0x3f��(Ĭ��Ϊ3f)
    
    
    //������ʾ������λӳ���ڴ������
    SPI_Write(0xD3, OLED_Order);
    SPI_Write(0x00, OLED_Order);//��0x00-0x3f��(Ĭ��Ϊ0x00)
    
    //������ʾʱ�ӷ�Ƶ����/����Ƶ��
    SPI_Write(0xD5, OLED_Order);
    //��4λ������ʾʱ��(��Ļ��ˢ��ʱ��)��Ĭ�ϣ�0000����Ƶ����= [3:0]+1
    //��4λ��������Ƶ�ʣ�Ĭ�ϣ�1000��
    SPI_Write(0x80, OLED_Order);//
    
    //ʱ��Ԥ�������
    SPI_Write(0xD9, OLED_Order);
    SPI_Write(0xF1, OLED_Order);//[3:0],PHASE 1;   [7:4] PHASE 2
    
    //����COMӲ��Ӧ������
    SPI_Write(0xDA, OLED_Order);
    SPI_Write(0x12, OLED_Order);//[5:4]  Ĭ�ϣ�01
    
    SPI_Write(0xDB, OLED_Order);//
    SPI_Write(0x40, OLED_Order);//
    
    //�����ڴ�Ѱַ��ʽ
    SPI_Write(0x20, OLED_Order);
    //00: ��ʾˮƽѰַ��ʽ
    //01: ��ʾ��ֱѰַ��ʽ
    //10: ��ʾҳѰַ��ʽ��Ĭ�Ϸ�ʽ��
    SPI_Write(0x02, OLED_Order);//    
    
    //��ɱ����ã���ʼ��ʱ����򿪣����򿴲�����ʾ��
    SPI_Write(0x8D, OLED_Order);
    SPI_Write(0x14, OLED_Order);//bit2   0���ر�        1����
    
    //�����Ƿ�ȫ����ʾ 0xA4: ��ֹȫ����ʾ
    SPI_Write(0xA4, OLED_Order);

    //0xA6: ��ʾ������ʾ���������1��ʾ������0��ʾ������
    //0xA7: ��ʾ����ʾ���������0��ʾ������1��ʾ������
    SPI_Write(0xA6, OLED_Order);//
    
    SPI_Write(0xAF, OLED_Order);//0xAF:����ʾ
    
    SPI_Write(0xAF, OLED_Order);//0xAF:����ʾ
    
    OLED_Clear();
}



/*        ��ʾ����
 *        x����ʾ��ʾ��ˮƽ����
 *        y: ��ʾ��ʾ�Ĵ�ֱ����
 *        *p: ��ʾҪ��ʾ����ģ����׵�ַ
*/
void OLED_ShowChinese(int x, int y, const unsigned char *p)
{
    int i = 0;
    OLED_Coord(x, y);
    for(i = 0; i < 32; i+=2)
    {
        SPI_Write(p[i], OLED_Data);
    }
    OLED_Coord(x, y+1);
    for(i = 1; i < 32; i+=2)
    {
        SPI_Write(p[i], OLED_Data);
    }
}


/*        ��ʾASCII
 *        x����ʾ��ʾ��ˮƽ����
 *        y: ��ʾ��ʾ�Ĵ�ֱ����
 *        *p: ��ʾҪ��ʾ����ģ����׵�ַ
*/
void OLED_ShowChar(int x, int y, const unsigned char *p)
{
    int i = 0;
    OLED_Coord(x, y);
    for(i = 0; i < 16; i+=2)
    {
        SPI_Write(p[i], OLED_Data);
    }
    OLED_Coord(x, y+1);
    for(i = 1; i < 16; i+=2)
    {
        SPI_Write(p[i], OLED_Data);
    }
}




#endif /* __OLED_H */