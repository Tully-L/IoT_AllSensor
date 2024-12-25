#include "stm32f10x.h"                  // Device header
#include "beep.h"   

/***********
蜂鸣器引脚:  I/O  PA6   TIM3_CH1

注意勾选 绿色图标 Device -> StdPeriph Drivers -> TIM
***********/


/***********************
//参考main.c

//乐谱：生日快乐歌C调简谱C语言表示方法(M5,50)为(音调，音长)100表示为一个音长(节拍)，50位半个音长(节拍)，25位四分之一音长(节拍)
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
	int length = sizeof(music)/sizeof(music[0]);//计算数组长度

	beep_init();
	
	while(1)
	{
		for(i=0; i<(length/2); i++)//取数组数据
		{  
			beep_set(music[2*i], music[2*i]);//PWM波周期

			my_music_delay( 5 * music[2*i+1] );//音长的时间都乘以5即一拍为500微秒，此值"5"可调整，只是播放的整个快慢而已，有点类似于视频快进和后退
		}
		
		my_music_delay(2000); //2S延时
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
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能GPIOA的时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE); //使能TIM3的时钟
	
	//GPIO配置  PA6  TIM3_CH1
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
	GPIO_Init(GPIOA, &GPIO_InitStructure); //引脚初始化   复用推挽输出
	
	//TIM3的基本配置
	TIM_BaseInitStructure.TIM_Period = 10000;//计数周期  10000  1s
	TIM_BaseInitStructure.TIM_Prescaler = 7200-1;//预分频 72MHz/7200 = 10000Hz 计数一次0.1ms
	TIM_BaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数
	TIM_BaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;  //时钟分割  输入滤波
	TIM_TimeBaseInit(TIM3, &TIM_BaseInitStructure);//初始化TIM3
	
	//配置TIM3的通道1输出PWM脉冲
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//TIM 脉冲宽度调制模式 1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//定时器输出使能
	TIM_OCInitStructure.TIM_Pulse = 0;//设置装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//TIM 输出比较极性：高  即周期内低于TIM_Pulse这个阈值的时间，都是高电平，其他时间都是低；	
	TIM_OC1Init(TIM3,&TIM_OCInitStructure);//初始化TIM3的Channel1

	TIM_Cmd(TIM3,ENABLE);//使能TIM3
}

void beep_set(int period, int pulse)
{
	TIM_TimeBaseInitTypeDef TIM_BaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;	
	
	//TIM3的基本配置
	TIM_BaseInitStructure.TIM_Period = period;//计数周期  10000  1s
	TIM_BaseInitStructure.TIM_Prescaler = 7200-1;//预分频
	TIM_BaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数
	TIM_BaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;  //时钟分割  输入滤波
	TIM_TimeBaseInit(TIM3, &TIM_BaseInitStructure);//初始化TIM3
	
	//配置TIM3的通道1输出PWM脉冲
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//TIM 脉冲宽度调制模式 1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//定时器输出使能
	TIM_OCInitStructure.TIM_Pulse = pulse;//设置装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//TIM 输出比较极性：高  即周期内低于TIM_Pulse这个阈值的时间，都是高电平，其他时间都是低；	
	TIM_OC1Init(TIM3,&TIM_OCInitStructure);//初始化TIM3的Channel1
}

