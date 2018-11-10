#ifndef __OLED_H
#define __OLED_H

#include"stm32f10x.h"

/*X为1时对应GPIO端口输出高电平，X为0时对应GPIO端口输出低电平*/
#define OLED_CS(X)        X?GPIO_SetBits(GPIOD, GPIO_Pin_3):GPIO_ResetBits(GPIOD, GPIO_Pin_3)   	//CS
#define OLED_RST(X)        X?GPIO_SetBits(GPIOD, GPIO_Pin_4):GPIO_ResetBits(GPIOD, GPIO_Pin_4)    	//RST
#define OLED_DC(X)        X?GPIO_SetBits(GPIOD, GPIO_Pin_5):GPIO_ResetBits(GPIOD, GPIO_Pin_5)		//DC
#define OLED_D0(X)        X?GPIO_SetBits(GPIOD, GPIO_Pin_6):GPIO_ResetBits(GPIOD, GPIO_Pin_6)    	//CK
#define OLED_D1(X)        X?GPIO_SetBits(GPIOD, GPIO_Pin_7):GPIO_ResetBits(GPIOD, GPIO_Pin_7)    	//DI

/*定义写命令*/
#define OLED_Order 0
/*定义写数据*/
#define OLED_Data  1

/*显示字符定义*/
const unsigned char ren[]=
{
0x00,0x01,0x80,0x00,0x60,0x00,0xF8,0xFF,0x87,0x00,0x80,0x40,0x84,0x40,0x84,0x40,
0x84,0x40,0xFE,0x7F,0x82,0x40,0x83,0x40,0x82,0x40,0x80,0x40,0x80,0x00,0x00,0x00,//任0
};

const unsigned char wu[]=
{
0x00,0x01,0x00,0x01,0x90,0x80,0x88,0x42,0x4C,0x22,0x57,0x1A,0xA4,0x07,0x24,0x02,
0x54,0x42,0x54,0x82,0x8C,0x42,0x84,0x3E,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x00,//务1
};

const unsigned char xian[]=
{

0x00,0x40,0x00,0x42,0x00,0x44,0xFE,0x58,0x92,0x40,0x92,0x7F,0x92,0x40,0x92,0x40,
0x92,0x40,0x92,0x7F,0x92,0x40,0xFE,0x50,0x00,0x48,0x00,0x46,0x00,0x40,0x00,0x00,//显2
};

const unsigned char shi[]=
{
0x40,0x20,0x40,0x10,0x42,0x08,0x42,0x06,0x42,0x00,0x42,0x40,0x42,0x80,0xC2,0x7F,
0x42,0x00,0x42,0x00,0x42,0x00,0x42,0x02,0x42,0x04,0x40,0x08,0x40,0x30,0x00,0x00,//示3
};

const unsigned char ASCII_Colon[]=
{    0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0x30,
    0xC0,0x30,0x00,0x00,0x00,0x00,0x00,0x00};// :  

const unsigned char hong[]=
{
0x20,0x22,0x30,0x67,0xAC,0x22,0x63,0x12,0x20,0x12,0x18,0x12,0x00,0x40,0x04,0x40,
0x04,0x40,0x04,0x40,0xFC,0x7F,0x04,0x40,0x04,0x40,0x04,0x40,0x00,0x40,0x00,0x00,//红4
};

const unsigned char lv[]=
{
0x20,0x22,0x30,0x67,0xAC,0x22,0x63,0x12,0x30,0x12,0x00,0x00,0x80,0x22,0x92,0x14,
0x92,0x48,0x92,0x84,0x92,0x7F,0x92,0x04,0xFE,0x08,0x80,0x14,0x80,0x22,0x00,0x00,//绿5
};

const unsigned char lan[]=
{
0x04,0x40,0x04,0x40,0xE4,0x7D,0x04,0x44,0x0F,0x44,0xF4,0x7D,0x04,0x44,0x04,0x45,
0xF4,0x44,0x44,0x7C,0xCF,0x44,0x44,0x45,0x44,0x7C,0x44,0x40,0x04,0x40,0x00,0x00,//蓝6
};

/*GPIO初始化*/
void OLED_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;    
    //开启GPIOD的时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);  //光电传感器
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	GPIO_Init(GPIOE, &GPIO_InitStruct);
	
    //设置GPIO的基本参数
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;    //推挽输出
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;    //输出速度50MHz

    GPIO_Init(GPIOD, &GPIO_InitStruct);
    GPIO_SetBits(GPIOD, GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7);
	

}


void delayms(u16 time)
{    
   u16 i=0;  
   while(time--)
   {
      i=12000;  //自己定义
      while(i--) ;    
   }
}


/*        SPI写数据/命令
 *    Mode :O:写命令   1：写数据
 *    data :数据/命令
 *
*/
void SPI_Write(char data, int Mode)
{    
    int i = 0;
    if(Mode)
    {
        OLED_DC(OLED_Data);        //DC引脚输入高，表示写数据
    }
    else
    {
        OLED_DC(OLED_Order);        //DC引脚输入低，表示写命令
    }
    OLED_CS(0);            //CS引脚输入低，片选使能
    for(i = 0; i < 8; i++)
    {
        OLED_D0(0);        //D0引脚输入低
        if(data & 0x80)    //判断传输的数据最高位为1还是0
        {
            OLED_D1(1);    //D1引脚输入高
        }
        else
        {
            OLED_D1(0);    //D1引脚输入低
        }
        OLED_D0(1);        //D1引脚输入高
        data <<= 1;        //将数据左移一位
    }
    OLED_DC(0);            //DC引脚输入低
    OLED_CS(1);            //CS引脚输入高，片选失能
}



/*        设置OLED屏的显示坐标
 *  　　  X : 表示OLED的水平坐标（0—127）
 * 　　   Y : 表示OLED的页（0—7）
 *        
*/
void OLED_Coord(unsigned char x, unsigned char y)
{
    SPI_Write((0xb0+(y & 0x0f)),0);        //设置OLED显示的页    
    SPI_Write((((x & 0xf0)>>4) | 0x10), 0);//设置OLED水平坐标的高4位
    SPI_Write((x & 0x0f)|0x01, 0);                //设置OLED水平坐标的低4位
}


/*
 *        清除OLED的显示
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


/*        关闭OLED显示
 *
 *
*/
void OLED_Display_Off(void)
{
    //电荷泵设置（初始化时必须打开，否则看不到显示）
    SPI_Write(0x8D, OLED_Order);
    SPI_Write(0x10, OLED_Order);//bit2   0：关闭        1：打开
    SPI_Write(0xAE, OLED_Order);//0xAE:关闭显示
}

/*
 *        开启OLED显示
 *
*/
void OLED_Display_On(void)
{
    //电荷泵设置（初始化时必须打开，否则看不到显示）
    SPI_Write(0x8D, OLED_Order);
    SPI_Write(0x14, OLED_Order);//bit2   0：关闭        1：打开
    SPI_Write(0xAF, OLED_Order);//0xAF:开显示    
}


/*        OLED显示参数的初始化
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
    
    SPI_Write(0xAE, OLED_Order);//0xAE:关显示   
    
    SPI_Write(0x00, OLED_Order);//设置低列地址
    SPI_Write(0x10, OLED_Order);//设置高列地址
    
    //设置行显示的开始地址(0-63)
    //40-47: (01xxxxx)
    SPI_Write(0x40, OLED_Order);
    
    //设置对比度
    SPI_Write(0x81, OLED_Order);
    SPI_Write(0xff, OLED_Order);//这个值越大，屏幕越亮(和上条指令一起使用)(0x00-0xff)
    
    SPI_Write(0xA1, OLED_Order);//0xA1: 左右反置，  0xA0: 正常显示（默认0xA0）
    SPI_Write(0xC8, OLED_Order);//0xC8: 上下反置，  0xC0: 正常显示（默认0xC0）
    
    //0xA6: 表示正常显示（在面板上1表示点亮，0表示不亮）
    //0xA7: 表示逆显示（在面板上0表示点亮，1表示不亮）
    SPI_Write(0xA6, OLED_Order);
    
    SPI_Write(0xA8, OLED_Order);//设置多路复用率（1-64）
    SPI_Write(0x3F, OLED_Order);//（0x01-0x3f）(默认为3f)
    
    
    //设置显示抵消移位映射内存计数器
    SPI_Write(0xD3, OLED_Order);
    SPI_Write(0x00, OLED_Order);//（0x00-0x3f）(默认为0x00)
    
    //设置显示时钟分频因子/振荡器频率
    SPI_Write(0xD5, OLED_Order);
    //低4位定义显示时钟(屏幕的刷新时间)（默认：0000）分频因子= [3:0]+1
    //高4位定义振荡器频率（默认：1000）
    SPI_Write(0x80, OLED_Order);//
    
    //时钟预充电周期
    SPI_Write(0xD9, OLED_Order);
    SPI_Write(0xF1, OLED_Order);//[3:0],PHASE 1;   [7:4] PHASE 2
    
    //设置COM硬件应脚配置
    SPI_Write(0xDA, OLED_Order);
    SPI_Write(0x12, OLED_Order);//[5:4]  默认：01
    
    SPI_Write(0xDB, OLED_Order);//
    SPI_Write(0x40, OLED_Order);//
    
    //设置内存寻址方式
    SPI_Write(0x20, OLED_Order);
    //00: 表示水平寻址方式
    //01: 表示垂直寻址方式
    //10: 表示页寻址方式（默认方式）
    SPI_Write(0x02, OLED_Order);//    
    
    //电荷泵设置（初始化时必须打开，否则看不到显示）
    SPI_Write(0x8D, OLED_Order);
    SPI_Write(0x14, OLED_Order);//bit2   0：关闭        1：打开
    
    //设置是否全部显示 0xA4: 禁止全部显示
    SPI_Write(0xA4, OLED_Order);

    //0xA6: 表示正常显示（在面板上1表示点亮，0表示不亮）
    //0xA7: 表示逆显示（在面板上0表示点亮，1表示不亮）
    SPI_Write(0xA6, OLED_Order);//
    
    SPI_Write(0xAF, OLED_Order);//0xAF:开显示
    
    SPI_Write(0xAF, OLED_Order);//0xAF:开显示
    
    OLED_Clear();
}



/*        显示汉字
 *        x：表示显示的水平坐标
 *        y: 表示显示的垂直坐标
 *        *p: 表示要显示汉字模组的首地址
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


/*        显示ASCII
 *        x：表示显示的水平坐标
 *        y: 表示显示的垂直坐标
 *        *p: 表示要显示汉字模组的首地址
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
