#include "stm32f10x.h"                  // Device header
#include "motor.h"

/***********
�����������������:  
ENA  <->   PB8   TIM4_CH3
IN1  <->   PA3	
IN2  <->   PA4

IN1 IN2 ���Ʒ���; ENA �����ٶ�

OUT1 OUT2 ���������

+12V�ӵ�Դģ��5V, GND��GND

ע�⹴ѡ ��ɫͼ�� Device -> StdPeriph Drivers -> TIM
***********/

/*********************
//�ο� main.c
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
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);//ʹ��GPIOB��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE); //ʹ��TIM4��ʱ��
	
	//GPIO����  PA4 PA5
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
	GPIO_Init(GPIOA, &GPIO_InitStructure); //���ų�ʼ��   ͨ���������
	
	//GPIO����  PB8  TIM4_CH3
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
	GPIO_Init(GPIOB, &GPIO_InitStructure); //���ų�ʼ��   �����������
	
	//TIM3�Ļ�������
	TIM_BaseInitStructure.TIM_Period = 1000;//��������  1000  1ms
	TIM_BaseInitStructure.TIM_Prescaler = 72-1;//Ԥ��Ƶ 72MHz/72 = 1000 000Hz ����һ��1us
	TIM_BaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���
	TIM_BaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;  //ʱ�ӷָ�  �����˲�
	TIM_TimeBaseInit(TIM4, &TIM_BaseInitStructure);//��ʼ��TIM3
	
	//����TIM3��ͨ��1���PWM����
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//TIM �����ȵ���ģʽ 1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//��ʱ�����ʹ��
	TIM_OCInitStructure.TIM_Pulse = 1000;//����װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//TIM ����Ƚϼ��ԣ���  �������ڵ���TIM_Pulse�����ֵ��ʱ�䣬���Ǹߵ�ƽ������ʱ�䶼�ǵͣ�	
	TIM_OC3Init(TIM4,&TIM_OCInitStructure);//��ʼ��TIM3��Channel1

	TIM_Cmd(TIM4,ENABLE);//ʹ��TIM3
	
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


