#include "stm32f10x.h"   

#define 	Dir 	GPIO_Pin_6
#define 	Step 	GPIO_Pin_7

void TIMInit(void);

int main(void)
{

}

void TIMInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//ʹ��TIM3����ʱ�ӣ�A��B��I/O��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;			//�����������
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	
	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	

}

void stepControl(u16 CCR_Val1,u16 CCR_Val2,u8 ForL,u8 ForR)
{
	
	
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	//1000��Ϊһ����ʱ����
	TIM_TimeBaseStructure.TIM_Period = 450;//9999
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