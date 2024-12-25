#include "stm32f10x.h"                  // Device header
#include "led.h"


void led_c13_init(void)
{
	//�������
	GPIO_InitTypeDef GPIO_InitStructure; 
	
	//1. RCC - ����բ (GPIOC)
	//ʹ�� APB2 ����ʱ��  GPIOC
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	//2. GPIO��ʼ��(����������) - PC13 ���ģʽ
	/* Configure all the GPIOA in Input Floating mode */ 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;  //ѡ������ PC13
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;  //ѡ����Ӧ�ٶ� �е��ٶ�
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //ѡ��ģʽ  �������
	GPIO_Init(GPIOC, &GPIO_InitStructure); //��ʼ�� GPIOC
	
	//3. GPIO���� - PC13����ߵ�ƽ -�Ʋ���
	GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
}
void led_c13_on(void)
{
	GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
}
void led_c13_off(void)
{
	GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
}


void led_rgb_init(void)
{
	//�������
	GPIO_InitTypeDef GPIO_InitStructure; 
	
	//1. RCC - ����բ (GPIOA)
	//ʹ�� APB2 ����ʱ��  GPIOA
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	//2. GPIO��ʼ��(����������) -  ���ģʽ
	/* Configure all the GPIOA in Input Floating mode */ 	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;  //ѡ������ PA0 PA1 PA2
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;  //ѡ����Ӧ�ٶ� �е��ٶ�
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //ѡ��ģʽ  �������
	GPIO_Init(GPIOA, &GPIO_InitStructure); //��ʼ�� GPIOA
	
	//3. GPIO���� - PA0 PA1 PA2 ����͵�ƽ - �Ʋ���
	GPIO_ResetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2); 
}


/*********
R  -  PA0
G  -  PA1
B  -  PA2

������

�����
��
��

��+��
��+��
��+��

��+��+��

led_num: 
#define  RGB_OFF 	0
#define  RGB_R 		1
#define  RGB_G 		2
#define  RGB_B 		3
#define  RGB_RG 	4
#define  RGB_RB 	5
#define  RGB_GB 	6
#define  RGB_RGB 	7
**********/
void led_rgb_set(int led_num)
{
	switch(led_num)
	{
		case RGB_OFF: 
			GPIO_ResetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2); 
			break;
		case RGB_R: 
			GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_SET); 
			GPIO_ResetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2);
			break;
		case RGB_G: 
			GPIO_WriteBit(GPIOA, GPIO_Pin_1, Bit_SET); 
			GPIO_ResetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_2);
			break;
		case RGB_B: 
			GPIO_WriteBit(GPIOA, GPIO_Pin_2, Bit_SET); 
			GPIO_ResetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1);
			break;
		case RGB_RG: 
			GPIO_SetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1); 
			GPIO_ResetBits(GPIOA, GPIO_Pin_2);
			break;
		case RGB_RB: 
			GPIO_SetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_2); 
			GPIO_ResetBits(GPIOA, GPIO_Pin_1);
			break;
		case RGB_GB: 
			GPIO_SetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2); 
			GPIO_ResetBits(GPIOA, GPIO_Pin_0);
			break;
		case RGB_RGB: 
			GPIO_SetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2);
			break;
	}	
}

