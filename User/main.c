#include "stm32f10x.h"   
#include "oled.h"

#define 	Dir 	GPIO_Pin_6
#define 	Step 	GPIO_Pin_7

void GPIOInit(void);
void stepControl(u16 CCR_Val1,u16 CCR_Val2,u8 ForL,u8 ForR);
void delay_ms(u32 i);
void delay_us(u32 i);
u8 trackL(void);
u8 trackR(void);
	
int main(void)
{
	
	GPIOInit();
	//OLED_Init();
	while(1)
	{
		stepControl(135,135,1,1);
		while(1){
			if(trackL())
			{
				stepControl(0,0,1,1);
				break;
			}
		}

}
}

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

	//GPIOB0\B1\B6\B7\B8\B9 舵机PWM 初始化
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	//GPIO E7\E8\E9\E10 循迹传感 初始化
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOE,&GPIO_InitStructure);

}



/*
	*左右循迹
	*检测到返回1，反之为0
	*暂时只需要两个
*/
u8 trackL(void)
{
	if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7) == 1)
		return 1;
	else
		return 0;
}

u8 trackR(void)
{
	if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8) == 1)
		return 1;
	else
		return 0;
}


/*
	*步进电机控制
	*PWM调控1	PWM调控2	direction1	direction2
*/
void stepControl(u16 CCR_Val1,u16 CCR_Val2,u8 ForL,u8 ForR)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	if(ForL == 1)
		GPIO_SetBits(GPIOA,GPIO_Pin_11);
	else
		GPIO_ResetBits(GPIOA,GPIO_Pin_11);
	
	if(ForR == 0)
		GPIO_SetBits(GPIOA,GPIO_Pin_12);
	else
		GPIO_ResetBits(GPIOA,GPIO_Pin_12);
	

	//1000次为一个定时周期
	TIM_TimeBaseStructure.TIM_Period = 270;//9999
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

/**
	*延时函数
**/
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

