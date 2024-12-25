#include "stm32f10x.h"                  // Device header
#include "led.h"


void led_c13_init(void)
{
	//定义变量
	GPIO_InitTypeDef GPIO_InitStructure; 
	
	//1. RCC - 开电闸 (GPIOC)
	//使能 APB2 外设时钟  GPIOC
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	//2. GPIO初始化(基本的配置) - PC13 输出模式
	/* Configure all the GPIOA in Input Floating mode */ 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;  //选择引脚 PC13
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;  //选择响应速度 中等速度
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //选择模式  推挽输出
	GPIO_Init(GPIOC, &GPIO_InitStructure); //初始化 GPIOC
	
	//3. GPIO工作 - PC13输出高电平 -灯不亮
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
	//定义变量
	GPIO_InitTypeDef GPIO_InitStructure; 
	
	//1. RCC - 开电闸 (GPIOA)
	//使能 APB2 外设时钟  GPIOA
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	//2. GPIO初始化(基本的配置) -  输出模式
	/* Configure all the GPIOA in Input Floating mode */ 	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;  //选择引脚 PA0 PA1 PA2
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;  //选择响应速度 中等速度
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //选择模式  推挽输出
	GPIO_Init(GPIOA, &GPIO_InitStructure); //初始化 GPIOA
	
	//3. GPIO工作 - PA0 PA1 PA2 输出低电平 - 灯不亮
	GPIO_ResetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2); 
}


/*********
R  -  PA0
G  -  PA1
B  -  PA2

都不亮

红灯亮
绿
蓝

红+绿
红+蓝
绿+蓝

红+绿+蓝

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

