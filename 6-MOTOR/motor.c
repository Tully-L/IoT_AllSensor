#include "stm32f10x.h"                  // Device header
#include "motor.h"

/***********
电机驱动板引脚连接:  
ENA  <->   PB8   TIM4_CH3
IN1  <->   PA3	
IN2  <->   PA4

IN1 IN2 控制方向; ENA 控制速度

OUT1 OUT2 接马达引脚

+12V接电源模块5V, GND接GND

注意勾选 绿色图标 Device -> StdPeriph Drivers -> TIM
***********/

/*********************
//参考 main.c
#include "motor.h" 

int main()
{	
	motor_init();
	motor_set_speed( MOTOR_FORWARD, 1000 );

	while(1)
	{
		
	}
}
*********************/
void motor_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	TIM_TimeBaseInitTypeDef TIM_BaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);//使能GPIOB的时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE); //使能TIM4的时钟
	
	//GPIO配置  PA4 PA5
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
	GPIO_Init(GPIOA, &GPIO_InitStructure); //引脚初始化   通用推挽输出
	
	//GPIO配置  PB8  TIM4_CH3
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
	GPIO_Init(GPIOB, &GPIO_InitStructure); //引脚初始化   复用推挽输出
	
	//TIM3的基本配置
	TIM_BaseInitStructure.TIM_Period = 1000;//计数周期  1000  1ms
	TIM_BaseInitStructure.TIM_Prescaler = 72-1;//预分频 72MHz/72 = 1000 000Hz 计数一次1us
	TIM_BaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数
	TIM_BaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;  //时钟分割  输入滤波
	TIM_TimeBaseInit(TIM4, &TIM_BaseInitStructure);//初始化TIM3
	
	//配置TIM3的通道1输出PWM脉冲
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//TIM 脉冲宽度调制模式 1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//定时器输出使能
	TIM_OCInitStructure.TIM_Pulse = 1000;//设置装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//TIM 输出比较极性：高  即周期内低于TIM_Pulse这个阈值的时间，都是高电平，其他时间都是低；	
	TIM_OC3Init(TIM4,&TIM_OCInitStructure);//初始化TIM3的Channel1

	TIM_Cmd(TIM4,ENABLE);//使能TIM3
	
	GPIO_ResetBits(GPIOA, GPIO_Pin_3 | GPIO_Pin_4);
}

//mode: MOTOR_OFF/MOTOR_FORWARD/MOTOR_REVERSAL    speed: 0~1000
void motor_set_speed(int mode, int speed)
{
	switch(mode)
	{
		case MOTOR_OFF: GPIO_ResetBits(GPIOA, GPIO_Pin_3 | GPIO_Pin_4); break;
		case MOTOR_FORWARD: GPIO_WriteBit(GPIOA, GPIO_Pin_3, Bit_SET); GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_RESET); break;
		case MOTOR_REVERSAL: GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_SET); GPIO_WriteBit(GPIOA, GPIO_Pin_3, Bit_RESET); break;
	}
	
	TIM_SetCompare3(TIM4, speed);
}


