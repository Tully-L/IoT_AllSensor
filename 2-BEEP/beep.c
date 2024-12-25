#include "stm32f10x.h"                  // Device header
#include "beep.h"   

/***********
����������:  I/O  PA6   TIM3_CH1

ע�⹴ѡ ��ɫͼ�� Device -> StdPeriph Drivers -> TIM
***********/


/***********************
//�ο�main.c

//���ף����տ��ָ�C������C���Ա�ʾ����(M5,50)Ϊ(����������)100��ʾΪһ������(����)��50λ�������(����)��25λ�ķ�֮һ����(����)
int music[]=  
{  
        M5,50,M5,25,M5,25, 

        M6,100,M5,100,H1,100,

        M7,100,M7,100,M5,50,M5,25,M5,25,

        M6,100,M5,100,H2,100,

        H1,100,H1,100,M5,50,M5,25,M5,25,

        H5,100,H3,100,H1,100,

        M7,100,M6,100,H4,50,H4,25,H4,25,

        H3,100,H1,100,H2,100,H1,100,H1,100

};


int main()
{
	int i = 2000;
	int length = sizeof(music)/sizeof(music[0]);//�������鳤��

	beep_init();
	
	while(1)
	{
		for(i=0; i<(length/2); i++)//ȡ��������
		{  
			beep_set(music[2*i], music[2*i]);//PWM������

			my_music_delay( 5 * music[2*i+1] );//������ʱ�䶼����5��һ��Ϊ500΢�룬��ֵ"5"�ɵ�����ֻ�ǲ��ŵ������������ѣ��е���������Ƶ����ͺ���
		}
		
		my_music_delay(2000); //2S��ʱ
	}
}
*/

void my_music_delay(int n)
{
	int  i = 0;
	while(n--)
		for(i=0; i<8050; i++);
}

void beep_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	TIM_TimeBaseInitTypeDef TIM_BaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//ʹ��GPIOA��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE); //ʹ��TIM3��ʱ��
	
	//GPIO����  PA6  TIM3_CH1
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
	GPIO_Init(GPIOA, &GPIO_InitStructure); //���ų�ʼ��   �����������
	
	//TIM3�Ļ�������
	TIM_BaseInitStructure.TIM_Period = 10000;//��������  10000  1s
	TIM_BaseInitStructure.TIM_Prescaler = 7200-1;//Ԥ��Ƶ 72MHz/7200 = 10000Hz ����һ��0.1ms
	TIM_BaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���
	TIM_BaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;  //ʱ�ӷָ�  �����˲�
	TIM_TimeBaseInit(TIM3, &TIM_BaseInitStructure);//��ʼ��TIM3
	
	//����TIM3��ͨ��1���PWM����
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//TIM �����ȵ���ģʽ 1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//��ʱ�����ʹ��
	TIM_OCInitStructure.TIM_Pulse = 0;//����װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//TIM ����Ƚϼ��ԣ���  �������ڵ���TIM_Pulse�����ֵ��ʱ�䣬���Ǹߵ�ƽ������ʱ�䶼�ǵͣ�	
	TIM_OC1Init(TIM3,&TIM_OCInitStructure);//��ʼ��TIM3��Channel1

	TIM_Cmd(TIM3,ENABLE);//ʹ��TIM3
}

void beep_set(int period, int pulse)
{
	TIM_TimeBaseInitTypeDef TIM_BaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;	
	
	//TIM3�Ļ�������
	TIM_BaseInitStructure.TIM_Period = period;//��������  10000  1s
	TIM_BaseInitStructure.TIM_Prescaler = 7200-1;//Ԥ��Ƶ
	TIM_BaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���
	TIM_BaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;  //ʱ�ӷָ�  �����˲�
	TIM_TimeBaseInit(TIM3, &TIM_BaseInitStructure);//��ʼ��TIM3
	
	//����TIM3��ͨ��1���PWM����
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//TIM �����ȵ���ģʽ 1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//��ʱ�����ʹ��
	TIM_OCInitStructure.TIM_Pulse = pulse;//����װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//TIM ����Ƚϼ��ԣ���  �������ڵ���TIM_Pulse�����ֵ��ʱ�䣬���Ǹߵ�ƽ������ʱ�䶼�ǵͣ�	
	TIM_OC1Init(TIM3,&TIM_OCInitStructure);//��ʼ��TIM3��Channel1
}

