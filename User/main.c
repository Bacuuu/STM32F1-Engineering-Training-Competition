/*
	*���ļ�����
*/
#include "stm32f10x.h"   
#include "oled.h"
#include "bsp_usart.h"
#include<math.h>
#include <stdlib.h>

/*
	*�����궨��
*/
#define 	Dir 	GPIO_Pin_6
#define 	Step 	GPIO_Pin_7

/*
	*ȫ�ֱ�������
*/
int rx_buf[1024];
unsigned int colorList ;
unsigned int qrcode;
/*
	*�����жϷ�����
*/
void DEBUG_USART_IRQHandler(void)
{	
	uint16_t num = 0;
	if(USART_GetITStatus(DEBUG_USARTx,USART_IT_RXNE)!=RESET)
	{	
		
		//������Ϣ����������Ӧ��ʾ
		if(USART_ReceiveData(DEBUG_USARTx))
		{
			//OLED_Clear();
			rx_buf[num] = USART_ReceiveData(DEBUG_USARTx);
			/*
				*��ɫʶ�����
			*/
			if(rx_buf[num]==0x30)
			{
			OLED_ShowChinese(0, 0, ren);//���Ρ�    
			OLED_ShowChinese(18, 0, wu);//����
			OLED_ShowChinese(36, 0, xian);//���ԡ�
			OLED_ShowChinese(54, 0, shi);//��ʾ��
			OLED_ShowChar(72,0,ASCII_Colon);
			OLED_ShowChinese(0,2,hong);
			OLED_ShowChinese(18,2,lv);
			OLED_ShowChinese(36,2,lan);
			colorList = 123; 
			
			}
			
			else if(rx_buf[num]==0x31)
			{
			OLED_ShowChinese(0, 0, ren);//���Ρ�    
			OLED_ShowChinese(18, 0, wu);//����
			OLED_ShowChinese(36, 0, xian);//���ԡ�
			OLED_ShowChinese(54, 0, shi);//��ʾ��
			OLED_ShowChar(72,0,ASCII_Colon);
			OLED_ShowChinese(0,2,hong);
			OLED_ShowChinese(18,2,lan);
			OLED_ShowChinese(36,2,lv);
			colorList = 132;
			}
			else if(rx_buf[num]==0x32)
			{
			OLED_ShowChinese(0, 0, ren);//���Ρ�    
			OLED_ShowChinese(18, 0, wu);//����
			OLED_ShowChinese(36, 0, xian);//���ԡ�
			OLED_ShowChinese(54, 0, shi);//��ʾ��
			OLED_ShowChar(72,0,ASCII_Colon);
			OLED_ShowChinese(0,2,lan);
			OLED_ShowChinese(18,2,hong);
			OLED_ShowChinese(36,2,lv);
			colorList = 312;
			}
			else if(rx_buf[num]==0x33)
			{
			OLED_ShowChinese(0, 0, ren);//���Ρ�    
			OLED_ShowChinese(18, 0, wu);//����
			OLED_ShowChinese(36, 0, xian);//���ԡ�
			OLED_ShowChinese(54, 0, shi);//��ʾ��
			OLED_ShowChar(72,0,ASCII_Colon);
			OLED_ShowChinese(0,2,lan);
			OLED_ShowChinese(18,2,lv);
			OLED_ShowChinese(36,2,hong);
			colorList = 321;
			}
			else if(rx_buf[num]==0x34)
			{
			OLED_ShowChinese(0, 0, ren);//���Ρ�    
			OLED_ShowChinese(18, 0, wu);//����
			OLED_ShowChinese(36, 0, xian);//���ԡ�
			OLED_ShowChinese(54, 0, shi);//��ʾ��
			OLED_ShowChar(72,0,ASCII_Colon);
			OLED_ShowChinese(0,2,lv);
			OLED_ShowChinese(18,2,hong);
			OLED_ShowChinese(36,2,lan);
			colorList = 213;
			}
			else if(rx_buf[num]==0x35)
			{
			OLED_ShowChinese(0, 0, ren);//���Ρ�    
			OLED_ShowChinese(18, 0, wu);//����
			OLED_ShowChinese(36, 0, xian);//���ԡ�
			OLED_ShowChinese(54, 0, shi);//��ʾ��
			OLED_ShowChar(72,0,ASCII_Colon);
			OLED_ShowChinese(0,2,lv);
			OLED_ShowChinese(18,2,lan);
			OLED_ShowChinese(36,2,hong);
			colorList = 231;
			}
			
				
			/*
				*��ά�����
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
		
		
		// ��ֵ����ʱ�������������һ��
		else
		{
				num ++;
		  }  
	}	 
}

/*
	*��������
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
	*��ں���
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
	
	//����ֹͣ���
	stepControl(900,450,450,1,1);
	delay_ms(1000);
	black2Stop();
	selfCorrectForward();
	//����ֹͣ���
	stepControl(900,450,450,1,1);
	delay_ms(1000);
	black2Stop();
	selfCorrectForward();
	
	//����ֹͣ���
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
		*�˴�֮�ϴ�������ʼ����ά��������
		*֮�¿�ʼ�߼��жϲ�ץȡ
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
		ץȡ��һ��
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
		*�ŵ�һ��
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
		ץȡ�ڶ���
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
		*�ŵڶ���
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
		ץȡ������
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
		*�ŵ�����
	*/
	
	delay_ms(1000);
	
	
	stepControl(900,450,450,1,1);
	delay_ms(1000);
	black2Stop();
	selfCorrectForward();
	
	turnRightDoubleline();
	
	//һ��ֹͣ���
	stepControl(900,450,450,1,1);
	delay_ms(1000);
	black2Stop();
	selfCorrectForward();
	//����ֹͣ���
	stepControl(900,450,450,1,1);
	delay_ms(1000);
	black2Stop();
	selfCorrectForward();
	
	//����ֹͣ���
	stepControl(900,450,450,1,1);
	delay_ms(1000);
	black2Stop();
	selfCorrectForward();
	
	//������ת
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
	*GPIO��ʼ��
*/
void GPIOInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//ʹ��TIM3\4\5����ʱ�ӣ�A��B��I/O��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE,ENABLE);
	
	//GPIO A0\A1 �������PWM ��ʼ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;			//�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//GPIO A11\A12 �������direction ��ʼ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA,&GPIO_InitStructure);	

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	//GPIOB0\B1\B6\B7\B8\B9 ���PWM ��ʼ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	//GPIO E7\E8\E9\E10 ѭ������ ��ʼ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOE,&GPIO_InitStructure);

}

/*
	*ƽ���ƶ����
	*����	ǰ����Ϊ6������Ƕȳ�ʼֵ		������Ϊ6�����Ŀ�ĽǶ�ֵ		��������������������ʱ��
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
	*6ͨ������Ƕȿ���
	*����Ϊ	6������ĽǶ�ֵ
*/
void servo(u8 angle1,u8 angle2,u8 angle3,u8 angle4,u8 angle5,u8 angle6)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	//1000��Ϊһ����ʱ����
	TIM_TimeBaseStructure.TIM_Period = 1800;//9999
	//����Ԥ��Ƶֵ���˴�����Ƶ
	TIM_TimeBaseStructure.TIM_Prescaler = 800;//7200
	//ʱ�ӷ�Ƶϵ��
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	//����ģʽ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
	
	//���ģʽ����
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	//���ģʽ״̬
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	//С��CCR_ValΪ�ߵ�ƽ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	//��������ֵ
	TIM_OCInitStructure.TIM_Pulse = angle1+45;
	TIM_OC3Init(TIM3,&TIM_OCInitStructure);
	//TIM_CRRԤװ��ʹ��
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
	
	//ARRʹ��
	TIM_ARRPreloadConfig(TIM3,ENABLE);
	TIM_Cmd(TIM3,ENABLE);
	TIM_ARRPreloadConfig(TIM4,ENABLE);
	TIM_Cmd(TIM4,ENABLE);
}

/*
	*ץȡ�߼��ж�
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
	
	
		*��һ��ץȡ��Ʒ
	
	
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
	*����ֹͣ
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
	*���ߺ�����ת
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
	*˫����ת
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
	*��������
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
	*����ѭ��
	*��⵽����1����֮Ϊ0
	*��ʱֻ��Ҫ����
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
	*�����������
	*PWM����1	PWM����2	direction1	direction2
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
	

	//1000��Ϊһ����ʱ����
	TIM_TimeBaseStructure.TIM_Period = period;//9999
	//����Ԥ��Ƶֵ���˴�����Ƶ
	TIM_TimeBaseStructure.TIM_Prescaler = 800;//7200
	//ʱ�ӷ�Ƶϵ��
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	//����ģʽ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseStructure);
	
	//���ģʽ����
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	//���ģʽ״̬
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	//��������ֵ
	TIM_OCInitStructure.TIM_Pulse = CCR_Val1;
	//С��CCR_ValΪ�ߵ�ƽ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	TIM_OC1Init(TIM5,&TIM_OCInitStructure);
	//TIM_CRRԤװ��ʹ��
	TIM_OC1PreloadConfig(TIM5,TIM_OCPreload_Enable);
	
	
	//TIM5_CH2
	TIM_OCInitStructure.TIM_Pulse = CCR_Val2;
	TIM_OC2Init(TIM5,&TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM5,TIM_OCPreload_Enable);
	
	//ARRʹ��
	TIM_ARRPreloadConfig(TIM5,ENABLE);
	TIM_Cmd(TIM5,ENABLE);
	
}

/*
	*��ʱ����
	*����
	*΢��
*/

void delay_ms(u16 time)
{    
   u16 i=0;  
   while(time--)
   {
      i=8000;  //�Լ�����
      while(i--) ;    
   }
}
void delay_us(u16 time)
{    
   u16 i=0;  
   while(time--)
   {
      i=10;  //�Լ�����
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
	float angleB = acos((arm1*arm1 + arm2 * arm2 - x*x - y*y) / (2 * arm1*arm2));	//����е��֮��ļнǣ�������
	float angleA = asin(arm2*sin(angleB) / sqrt(x*x + y*y));	//��е��arm1��С��ƽ̨֮��ļнǣ�������
	float angleC = asin(arm1*sin(angleB) / sqrt(x*x + y*y));	//��е��arm2����A����B��������֮��ļнǣ�������
	servoAngle[1] = angleA * (360 / 2 * PI) + starAngle[0] - 90;	//��angleAתΪ���2��Ŀ��ǶȲ��ó�ʼ�Ƕ�У׼���Ƕ���
//	servoAngle[1] = 180 - servoAngle[0];	//�����е���ڷ��������Ļ���ȡ���Ĳ���
	servoAngle[2] = angleB * (360 / 2 * PI) - (180 - starAngle[1]);	//��angleBתΪ���3��Ŀ��ǶȲ��ó�ʼ�Ƕ�У׼���Ƕ���
//	servoAngle[2] = 180 - servoAngle[1];	//�����е���ڷ��������Ļ���ȡ���Ĳ���
	servoAngle[3] = (90 - (angleC * (360 / 2 * PI)) + atan(y / x)) - (90 - starAngle[2]);	//��angleCתΪ���4��Ŀ��ǶȲ��ó�ʼ�Ƕ�У׼���Ƕ���
//	c[2] = 180 - servoAngle[2]; //����Ƕȵı仯���򷴵Ļ���ȡ���Ĳ���
//	servoAngle[3] = 90 - servoAngle[2];	//�����е���ڷ��������Ļ���ȡ�������
}


void delay_ms(u32 i)
{
    u32 temp;
    SysTick->LOAD=9000*i;      //������װ��ֵ, 72MHZʱ
    SysTick->CTRL=0X01;        //ʹ�ܣ����������޶����������ⲿʱ��Դ
    SysTick->VAL=0;            //���������
    do
    {
        temp=SysTick->CTRL;       //��ȡ��ǰ������ֵ
    }
    while((temp&0x01)&&(!(temp&(1<<16))));    //�ȴ�ʱ�䵽��
    SysTick->CTRL=0;    //�رռ�����
    SysTick->VAL=0;        //��ռ�����
}

void delay_us(u32 i)
{
    u32 temp;
    SysTick->LOAD=9*i;         //������װ��ֵ, 72MHZʱ
    SysTick->CTRL=0X01;         //ʹ�ܣ����������޶����������ⲿʱ��Դ
    SysTick->VAL=0;                //���������
    do
    {
        temp=SysTick->CTRL;           //��ȡ��ǰ������ֵ
    }
    while((temp&0x01)&&(!(temp&(1<<16))));     //�ȴ�ʱ�䵽��
    SysTick->CTRL=0;    //�رռ�����
    SysTick->VAL=0;        //��ռ�����
}
*/
