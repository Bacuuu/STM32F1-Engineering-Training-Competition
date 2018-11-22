/*
	*库文件引入
*/
#include "stm32f10x.h"   
#include "oled.h"
#include "bsp_usart.h"
#include<math.h>
#include <stdlib.h>

/*
	*变量宏定义
*/
#define 	Dir 	GPIO_Pin_6
#define 	Step 	GPIO_Pin_7

/*
	*全局变量声明
*/
int rx_buf[1024];
unsigned int colorList ;
unsigned int qrcode;
/*
	*串口中断服务函数
*/
void DEBUG_USART_IRQHandler(void)
{	
	uint16_t num = 0;
	if(USART_GetITStatus(DEBUG_USARTx,USART_IT_RXNE)!=RESET)
	{	
		
		//接受消息，并做出相应显示
		if(USART_ReceiveData(DEBUG_USARTx))
		{
			//OLED_Clear();
			rx_buf[num] = USART_ReceiveData(DEBUG_USARTx);
			/*
				*颜色识别接收
			*/
			if(rx_buf[num]==0x30)
			{
			OLED_ShowChinese(0, 0, ren);//‘任’    
			OLED_ShowChinese(18, 0, wu);//‘务’
			OLED_ShowChinese(36, 0, xian);//‘显’
			OLED_ShowChinese(54, 0, shi);//‘示’
			OLED_ShowChar(72,0,ASCII_Colon);
			OLED_ShowChinese(0,2,hong);
			OLED_ShowChinese(18,2,lv);
			OLED_ShowChinese(36,2,lan);
			colorList = 123; 
			
			}
			
			else if(rx_buf[num]==0x31)
			{
			OLED_ShowChinese(0, 0, ren);//‘任’    
			OLED_ShowChinese(18, 0, wu);//‘务’
			OLED_ShowChinese(36, 0, xian);//‘显’
			OLED_ShowChinese(54, 0, shi);//‘示’
			OLED_ShowChar(72,0,ASCII_Colon);
			OLED_ShowChinese(0,2,hong);
			OLED_ShowChinese(18,2,lan);
			OLED_ShowChinese(36,2,lv);
			colorList = 132;
			}
			else if(rx_buf[num]==0x32)
			{
			OLED_ShowChinese(0, 0, ren);//‘任’    
			OLED_ShowChinese(18, 0, wu);//‘务’
			OLED_ShowChinese(36, 0, xian);//‘显’
			OLED_ShowChinese(54, 0, shi);//‘示’
			OLED_ShowChar(72,0,ASCII_Colon);
			OLED_ShowChinese(0,2,lan);
			OLED_ShowChinese(18,2,hong);
			OLED_ShowChinese(36,2,lv);
			colorList = 312;
			}
			else if(rx_buf[num]==0x33)
			{
			OLED_ShowChinese(0, 0, ren);//‘任’    
			OLED_ShowChinese(18, 0, wu);//‘务’
			OLED_ShowChinese(36, 0, xian);//‘显’
			OLED_ShowChinese(54, 0, shi);//‘示’
			OLED_ShowChar(72,0,ASCII_Colon);
			OLED_ShowChinese(0,2,lan);
			OLED_ShowChinese(18,2,lv);
			OLED_ShowChinese(36,2,hong);
			colorList = 321;
			}
			else if(rx_buf[num]==0x34)
			{
			OLED_ShowChinese(0, 0, ren);//‘任’    
			OLED_ShowChinese(18, 0, wu);//‘务’
			OLED_ShowChinese(36, 0, xian);//‘显’
			OLED_ShowChinese(54, 0, shi);//‘示’
			OLED_ShowChar(72,0,ASCII_Colon);
			OLED_ShowChinese(0,2,lv);
			OLED_ShowChinese(18,2,hong);
			OLED_ShowChinese(36,2,lan);
			colorList = 213;
			}
			else if(rx_buf[num]==0x35)
			{
			OLED_ShowChinese(0, 0, ren);//‘任’    
			OLED_ShowChinese(18, 0, wu);//‘务’
			OLED_ShowChinese(36, 0, xian);//‘显’
			OLED_ShowChinese(54, 0, shi);//‘示’
			OLED_ShowChar(72,0,ASCII_Colon);
			OLED_ShowChinese(0,2,lv);
			OLED_ShowChinese(18,2,lan);
			OLED_ShowChinese(36,2,hong);
			colorList = 231;
			}
			
				
			/*
				*二维码接收
			*/
			else if(rx_buf[num]==0x41)
			{
			OLED_ShowChar(0,6,_1);
			OLED_ShowChar(18,6,_2);
			OLED_ShowChar(36,6,_3);
			qrcode = 123;
			}
			
			else if(rx_buf[num]==0x42)
			{
			OLED_ShowChar(0,6,_1);
			OLED_ShowChar(18,6,_3);
			OLED_ShowChar(36,6,_2);
			qrcode = 132;
			}
			else if(rx_buf[num]==0x43)
			{
			OLED_ShowChar(0,6,_2);
			OLED_ShowChar(18,6,_1);
			OLED_ShowChar(36,6,_3);
			qrcode = 213;
			}
			else if(rx_buf[num]==0x44)
			{
			OLED_ShowChar(0,6,_2);
			OLED_ShowChar(18,6,_3);
			OLED_ShowChar(36,6,_1);
			qrcode = 231;
			}
			else if(rx_buf[num]==0x45)
			{
			OLED_ShowChar(0,6,_3);
			OLED_ShowChar(18,6,_1);
			OLED_ShowChar(36,6,_2);
			qrcode = 312;
			}
			else if(rx_buf[num]==0x46)
			{
			OLED_ShowChar(0,6,_3);
			OLED_ShowChar(18,6,_2);
			OLED_ShowChar(36,6,_1);
			qrcode = 321;
			}
			
		}
		
		
		// 当值不等时候，则继续接收下一个
		else
		{
				num ++;
		  }  
	}	 
}

/*
	*函数声明
*/
void GPIOInit(void);
void stepControl(u16 period,u16 CCR_Val1,u16 CCR_Val2,u8 ForL,u8 ForR);
void delay_ms(u16 time);
void delay_us(u16 time);
u8 trackL(void);
u8 trackR(void);
void selfCorrectForward(void);
void selfCorrectBack(void);
void turnRightDoubleline(void);	
void black2Stop(void);
void turnRightSimpleline(void);
void servo(u8 angle1,u8 angle2,u8 angle3,u8 angle4,u8 angle5,u8 angle6);
void servoSmooth(u8 val1,u8 val2,u8 val3,u8 val4,u8 val5,u8 val6,u8 val7,u8 val8,u8 val9,u8 val10,u8 val11,u8 val12,u16 time);
void catchM(void);
void catchL(void);
void catchR(void);
	
//calculateAngle(180,89,servoangles+1)
/*
	*入口函数
*/

int main(void)
{
	USART_Config();	
	GPIOInit();
	OLED_Init();
	OLED_ShowChinese(0,0,ren);
	OLED_ShowChinese(18,0,wu);
	OLED_ShowChinese(36,0,xian);
	OLED_ShowChinese(54,0,shi);
	OLED_ShowChar(72,0,ASCII_Colon);
	OLED_ShowChinese(0,4,er);
	OLED_ShowChinese(18,4,wei);
	OLED_ShowChinese(36,4,ma);
	OLED_ShowChar(54,4,ASCII_Colon);

	servo(112,112,166,172,0,74);
	stepControl(900,0,0,1,1);
	
	stepControl(900,450,450,1,1);
	delay_ms(4000);

	black2Stop();
	delay_ms(300);
	selfCorrectForward();
	delay_ms(100);

	turnRightDoubleline();
	delay_ms(100);
	stepControl(900,450,450,1,1);
	black2Stop();
	
	delay_ms(100);
	selfCorrectForward();
	delay_ms(100);
	
	//二线停止检测
	stepControl(900,450,450,1,1);
	delay_ms(1000);
	black2Stop();
	selfCorrectForward();
	//三线停止检测
	stepControl(900,450,450,1,1);
	delay_ms(1000);
	black2Stop();
	selfCorrectForward();
	
	//四线停止检测
	stepControl(900,450,450,1,1);
	delay_ms(1000);
	black2Stop();
	selfCorrectForward();
	
	Usart_SendString(DEBUG_USARTx,"Sa");
	delay_ms(2000);
	
	stepControl(900,450,450,1,1);
	delay_ms(5000);
	black2Stop();
	delay_ms(1500);
	/*
		*此处之上代码由起始到二维码检验完成
		*之下开始逻辑判断并抓取
	*/
	
	stepControl(900,450,450,0,0);
	delay_ms(5000);
	black2Stop();
	delay_ms(300);
	selfCorrectBack();
	delay_ms(100);
	turnRightSimpleline();
	
	stepControl(900,450,450,1,1);
	delay_ms(1000);
	black2Stop();
	selfCorrectForward();
	
	stepControl(900,450,450,0,0);
	delay_ms(1300);
	stepControl(900,0,0,0,0);
	catchM();
	
	/*
		抓取第一个
	*/
	
	delay_ms(1000);
	
	stepControl(900,450,450,0,0);
	delay_ms(500);
	black2Stop();
	selfCorrectBack();
	stepControl(900,450,450,0,0);
	delay_ms(1000);
	black2Stop();
	selfCorrectBack();
	
	/*
		*放第一个
	*/
	
	delay_ms(1000);
	
	
	stepControl(900,450,450,1,1);
	delay_ms(1000);
	black2Stop();
	selfCorrectForward();
	stepControl(900,450,450,1,1);
	delay_ms(1000);
	black2Stop();
	selfCorrectForward();
	
	stepControl(900,450,450,0,0);
	delay_ms(1300);
	stepControl(900,0,0,0,0);
	catchL();
	/*
		抓取第二个
	*/
	
	delay_ms(1000);
	
	
	stepControl(900,450,450,0,0);
	delay_ms(1000);
	black2Stop();
	selfCorrectBack();
	stepControl(900,450,450,0,0);
	delay_ms(1000);
	black2Stop();
	selfCorrectBack();
	/*
		*放第二个
	*/
	
	delay_ms(1000);
	
	
	stepControl(900,450,450,1,1);
	delay_ms(1000);
	black2Stop();
	selfCorrectForward();
	stepControl(900,450,450,1,1);
	delay_ms(1000);
	black2Stop();
	selfCorrectForward();
	
		stepControl(900,450,450,0,0);
	delay_ms(1300);
	stepControl(900,0,0,0,0);
	catchR();
	/*
		抓取第三个
	*/
	
	delay_ms(1000);
	
	
	stepControl(900,450,450,0,0);
	delay_ms(1000);
	black2Stop();
	selfCorrectBack();
	stepControl(900,450,450,0,0);
	delay_ms(1000);
	black2Stop();
	selfCorrectBack();
	/*
		*放第三个
	*/
	
	delay_ms(1000);
	
	
	stepControl(900,450,450,1,1);
	delay_ms(1000);
	black2Stop();
	selfCorrectForward();
	
	turnRightDoubleline();
	
	//一线停止检测
	stepControl(900,450,450,1,1);
	delay_ms(1000);
	black2Stop();
	selfCorrectForward();
	//二线停止检测
	stepControl(900,450,450,1,1);
	delay_ms(1000);
	black2Stop();
	selfCorrectForward();
	
	//三线停止检测
	stepControl(900,450,450,1,1);
	delay_ms(1000);
	black2Stop();
	selfCorrectForward();
	
	//单线左转
	stepControl(900,450,450,1,1);
	delay_ms(1600);
	stepControl(900,450,450,0,1);
	delay_ms(1650);
	stepControl(900,0,0,1,1);
	delay_ms(100);
	
	stepControl(900,450,450,1,1);
	delay_ms(800);
	black2Stop();
	selfCorrectForward();
	
	stepControl(900,450,450,1,1);
	delay_ms(1700);
	stepControl(900,0,0,1,1);
}


/*
	*GPIO初始化
*/
void GPIOInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//使能TIM3\4\5外设时钟，A、B的I/O口时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE,ENABLE);
	
	//GPIO A0\A1 步进电机PWM 初始化
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;			//复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//GPIO A11\A12 步进电机direction 初始化
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA,&GPIO_InitStructure);	

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	//GPIOB0\B1\B6\B7\B8\B9 舵机PWM 初始化
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	//GPIO E7\E8\E9\E10 循迹传感 初始化
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOE,&GPIO_InitStructure);

}

/*
	*平滑移动舵机
	*参数	前六个为6个舵机角度初始值		后六个为6个舵机目的角度值		最后参数是整个动作运行时间
*/
void servoSmooth(u8 val1,u8 val2,u8 val3,u8 val4,u8 val5,u8 val6,u8 val7,u8 val8,u8 val9,u8 val10,u8 val11,u8 val12,u16 time)
{
	u8 pos1 = val7-val1;
	u8 pos2 = val8-val2;
	u8 pos3 = val9-val3;
	u8 pos4 = val10-val4;
	u8 pos5 = val11-val5;
	u8 pos6 = val12-val6;
	u8 pos7 = pos1>pos2?pos1:pos2;
	u8 pos8 = pos3>pos4?pos3:pos4;
	u8 pos9 = pos5>pos6?pos5:pos6;
	u8 pos10 = pos7>pos8?pos7:pos8;
	u8 maxPos = pos9>pos10?pos9:pos10;
	u8 i = maxPos;
	for(i=maxPos;i>0;i--)
	{
		servo(val7-(val7-val1)*i/maxPos,val8-(val8-val2)*i/maxPos,val9-(val9-val3)*i/maxPos,val10-(val10-val4)*i/maxPos,val11-(val11-val5)*i/maxPos,val12-(val12-val6)*i/maxPos);
		delay_ms(time/maxPos);
	}
	
}


/*
	*6通道舵机角度控制
	*参数为	6个舵机的角度值
*/
void servo(u8 angle1,u8 angle2,u8 angle3,u8 angle4,u8 angle5,u8 angle6)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	//1000次为一个定时周期
	TIM_TimeBaseStructure.TIM_Period = 1800;//9999
	//设置预分频值，此处不分频
	TIM_TimeBaseStructure.TIM_Prescaler = 800;//7200
	//时钟分频系数
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	//计数模式
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
	
	//输出模式配置
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	//输出模式状态
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	//小于CCR_Val为高电平
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	//设置跳变值
	TIM_OCInitStructure.TIM_Pulse = angle1+45;
	TIM_OC3Init(TIM3,&TIM_OCInitStructure);
	//TIM_CRR预装载使能
	TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable);
	
	
	//TIM3_CH2
	TIM_OCInitStructure.TIM_Pulse = angle2+45;
	TIM_OC4Init(TIM3,&TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM3,TIM_OCPreload_Enable);
	
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);
	
	//TIM4_CH1
	TIM_OCInitStructure.TIM_Pulse = angle3+45;
	TIM_OC1Init(TIM4,&TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);
	
	//TIM4_CH2
	TIM_OCInitStructure.TIM_Pulse = angle4+45;
	TIM_OC2Init(TIM4,&TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);
	
	//TIM4_CH3
	TIM_OCInitStructure.TIM_Pulse = angle5+45;
	TIM_OC3Init(TIM4,&TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable);
	
	//TIM4_CH4
	TIM_OCInitStructure.TIM_Pulse = angle6+45;
	TIM_OC4Init(TIM4,&TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM3,TIM_OCPreload_Enable);
	
	//ARR使能
	TIM_ARRPreloadConfig(TIM3,ENABLE);
	TIM_Cmd(TIM3,ENABLE);
	TIM_ARRPreloadConfig(TIM4,ENABLE);
	TIM_Cmd(TIM4,ENABLE);
}

/*
	*抓取逻辑判断
*/

/*
void logic(unsigned int color,unsigned int code)
{
	u8 colorH = color/100;
	u8 colorM = color/10%10;
	u8 colorL = color%100;
	u8 codeH = code/100;
	u8 codeM = code/10%10;
	u8 codeL = code%100;
	
	
		*第一个抓取物品
	
	
	if(codeH==1)
	{
		//if()
	}
	else if(codeM ==1)
	{
		
	}
	else if(codeL ==1)
	{
		
	}
}
 */

/*
	*黑线停止
*/
void black2Stop(void)
{
	while(1){
	if(trackL()||trackR()){
		stepControl(450,0,0,1,1);
		break;
	}
}
}

/*
	*单线后退右转
*/
void turnRightSimpleline(void)
{
	stepControl(900,450,450,0,0);
	delay_ms(100);
	stepControl(900,450,450,1,0);
	delay_ms(1650);
	stepControl(900,0,0,1,1);
	
}

/*
	*双线右转
*/
void turnRightDoubleline(void){
	stepControl(900,450,450,1,1);
	delay_ms(210);
	stepControl(900,450,450,1,0);
	delay_ms(1750);
	stepControl(900,0,0,1,1);
	delay_ms(300);
}

/*
	*自我修正
*/
void selfCorrectForward(void)
{
	if(trackL()==1&&trackR()==0)
	{
		stepControl(2250,1125,0,1,1);
		while(1)
		{
			if(trackR()==1)
			{
				stepControl(450,0,0,1,1);
				break;
			}
		}
	}
	if(trackL()==0&&trackR()==1)
	{
		stepControl(2250,0,1125,1,1);
		while(1)
		{				
			if(trackL()==1)
			{
				stepControl(450,0,0,1,1);
				break;
			}
		}
	}
}

void selfCorrectBack(void)
{
	if(trackL()==1&&trackR()==0)
	{
		stepControl(2250,1125,0,0,0);
		while(1)
		{
			if(trackR()==1)
			{
				stepControl(450,0,0,0,0);
				break;
			}
		}
	}
	if(trackL()==0&&trackR()==1)
	{
		stepControl(2250,0,1125,0,0);
		while(1)
		{				
			if(trackL()==1)
			{
				stepControl(450,0,0,1,1);
				break;
			}
		}
	}
}


/*
	*左右循迹
	*检测到返回1，反之为0
	*暂时只需要两个
*/
u8 trackL(void)
{
	if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7) == 0)
		return 1;
	else
		return 0;
}

u8 trackR(void)
{
	if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_9) == 0)
		return 1;
	else
		return 0;
}


/*
	*步进电机控制
	*PWM调控1	PWM调控2	direction1	direction2
*/
void stepControl(u16 period,u16 CCR_Val1,u16 CCR_Val2,u8 ForL,u8 ForR)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	
	/*
		*	ForL	ForR	GPIOA11		GPIOA12		direction1		direction2
		*	1		1		0			0			1				1
		*	1		0		0			1			0				1
	
		*	1		0		0			1			1				0
	*/
	if(ForR == 0)					
		GPIO_ResetBits(GPIOA,GPIO_Pin_11);
	else
		GPIO_SetBits(GPIOA,GPIO_Pin_11);
	
	if(ForL == 1)
		GPIO_SetBits(GPIOA,GPIO_Pin_12);
	else
		GPIO_ResetBits(GPIOA,GPIO_Pin_12);
	

	//1000次为一个定时周期
	TIM_TimeBaseStructure.TIM_Period = period;//9999
	//设置预分频值，此处不分频
	TIM_TimeBaseStructure.TIM_Prescaler = 800;//7200
	//时钟分频系数
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	//计数模式
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseStructure);
	
	//输出模式配置
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	//输出模式状态
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	//设置跳变值
	TIM_OCInitStructure.TIM_Pulse = CCR_Val1;
	//小于CCR_Val为高电平
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	TIM_OC1Init(TIM5,&TIM_OCInitStructure);
	//TIM_CRR预装载使能
	TIM_OC1PreloadConfig(TIM5,TIM_OCPreload_Enable);
	
	
	//TIM5_CH2
	TIM_OCInitStructure.TIM_Pulse = CCR_Val2;
	TIM_OC2Init(TIM5,&TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM5,TIM_OCPreload_Enable);
	
	//ARR使能
	TIM_ARRPreloadConfig(TIM5,ENABLE);
	TIM_Cmd(TIM5,ENABLE);
	
}

/*
	*延时函数
	*毫秒
	*微秒
*/

void delay_ms(u16 time)
{    
   u16 i=0;  
   while(time--)
   {
      i=8000;  //自己定义
      while(i--) ;    
   }
}
void delay_us(u16 time)
{    
   u16 i=0;  
   while(time--)
   {
      i=10;  //自己定义
      while(i--) ;    
   }
}





void catchM(void)
{
	servo(112,112,166,172,0,74);
	servoSmooth(112,112,166,172,0,74,112,112,56,86,0,74,3000);
	servoSmooth(112,112,56,86,0,74,115,112,17,108,180,98,3000);
	servoSmooth(115,112,17,108,180,98,115,112,11,106,180,98,2000);
	servoSmooth(115,112,11,106,180,98,115,126,33,88,180,98,2000);
	servoSmooth(115,126,33,88,180,98,115,126,33,88,180,9,3000);
	servo(115,126,33,88,180,0);
	delay_ms(500);
	servoSmooth(115,126,33,88,180,9,115,3,33,30,0,9,3000);
}

void catchL(void)
{
	servo(116,46,0,130,90,90);
	servoSmooth(116,46,0,130,90,90,     143,116,0,130,90,90,3000);
	servoSmooth(143,116,0,130,90,90,    143,139,14,140,180,90,3000);
	servoSmooth(143,139,14,140,180,90,  137,137,46,94,180,90,3000);
	servoSmooth(137,137,46,94,180,90,   132,152,72,90,180,90,3000);
	servoSmooth(132,152,72,90,180,90,   137,143,54,90,180,3,3000);
	servo(137,143,54,90,180,3);
	delay_ms(400);
	servoSmooth(137,143,54,90,180,3,    137,37,0,90,180,3,3000);
	servoSmooth(137,37,0,90,180,3,      114,37,0,127,180,3,3000);
	
}

void catchR(void)
{
	servo(116,46,0,130,90,90);
	servoSmooth(116,46,0,130,90,90,     88,116,0,130,90,90,3000);
	servoSmooth(88,116,0,130,90,90,    88,139,14,140,180,90,3000);
	servoSmooth(88,139,14,140,180,90,  88,137,46,94,180,90,3000);
	servoSmooth(88,137,46,94,180,90,   88,143,54,90,180,90,3000);
	servoSmooth(88,143,54,90,180,90,   88,143,54,90,180,3,3000);
	servo(88,143,54,90,180,3);
	delay_ms(400);
	servoSmooth(88,143,54,90,180,3,    88,37,0,90,180,3,3000);
	servoSmooth(88,37,0,90,180,3,      110,37,0,127,180,3,3000);
	
}
/*

void calculateAngle(u8 x, u8 y,float servoAngle[]) {
	float angleB = acos((arm1*arm1 + arm2 * arm2 - x*x - y*y) / (2 * arm1*arm2));	//两机械臂之间的夹角，弧度制
	float angleA = asin(arm2*sin(angleB) / sqrt(x*x + y*y));	//机械臂arm1与小车平台之间的夹角，弧度制
	float angleC = asin(arm1*sin(angleB) / sqrt(x*x + y*y));	//机械臂arm2与舵机A与舵机B轴心连线之间的夹角，弧度制
	servoAngle[1] = angleA * (360 / 2 * PI) + starAngle[0] - 90;	//将angleA转为舵机2的目标角度并用初始角度校准，角度制
//	servoAngle[1] = 180 - servoAngle[0];	//如果机械臂在反方向动作的话，取它的补角
	servoAngle[2] = angleB * (360 / 2 * PI) - (180 - starAngle[1]);	//将angleB转为舵机3的目标角度并用初始角度校准，角度制
//	servoAngle[2] = 180 - servoAngle[1];	//如果机械臂在反方向动作的话，取它的补角
	servoAngle[3] = (90 - (angleC * (360 / 2 * PI)) + atan(y / x)) - (90 - starAngle[2]);	//将angleC转为舵机4的目标角度并用初始角度校准，角度制
//	c[2] = 180 - servoAngle[2]; //如果角度的变化方向反的话，取它的补角
//	servoAngle[3] = 90 - servoAngle[2];	//如果机械臂在反方向动作的话，取它的余角
}


void delay_ms(u32 i)
{
    u32 temp;
    SysTick->LOAD=9000*i;      //设置重装数值, 72MHZ时
    SysTick->CTRL=0X01;        //使能，减到零是无动作，采用外部时钟源
    SysTick->VAL=0;            //清零计数器
    do
    {
        temp=SysTick->CTRL;       //读取当前倒计数值
    }
    while((temp&0x01)&&(!(temp&(1<<16))));    //等待时间到达
    SysTick->CTRL=0;    //关闭计数器
    SysTick->VAL=0;        //清空计数器
}

void delay_us(u32 i)
{
    u32 temp;
    SysTick->LOAD=9*i;         //设置重装数值, 72MHZ时
    SysTick->CTRL=0X01;         //使能，减到零是无动作，采用外部时钟源
    SysTick->VAL=0;                //清零计数器
    do
    {
        temp=SysTick->CTRL;           //读取当前倒计数值
    }
    while((temp&0x01)&&(!(temp&(1<<16))));     //等待时间到达
    SysTick->CTRL=0;    //关闭计数器
    SysTick->VAL=0;        //清空计数器
}
*/
