#include "stm32f10x.h"                  // Device header
#include "light.h"

/******************
光敏:AO引脚      PA5		ADC1_CH5

注意勾选 绿色图标 Device -> StdPeriph Drivers -> ADC
*******************/

/********************
//参考main.c
#include "stm32f10x.h"                  // Device header
#include "light.h"
#include "usart.h"

void my_delay_ms(int ms)
{
	int  i = 0;
	while(ms--)
		for(i=0; i<8050; i++);
}

int main()
{
	int light_value = 0;
	

	uart1_init(115200);
	light_init();
	
	while(1)
	{
		light_value = light_get_value();
		printf("light_value: %d\r\n", light_value);
		
		my_delay_ms(1000) ;
	}
}
*********************/

void light_init(void)
{
	ADC_InitTypeDef ADC_InitStructure;   //ADC结构体变量
	GPIO_InitTypeDef  GPIO_InitStructure;
	

	//1. 上电 使ADC能够工作
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1,ENABLE);
		
	//2.GPIO 配置	PA5    ADC12_IN5
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5  ; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;  //模拟输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA,  &GPIO_InitStructure);  //PA5初始化 模拟输入
	
	ADC_DeInit(ADC1);
	
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;//ADC1 和 ADC2 工作在独立模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;//模数转换工作在扫描模式（多通道）还是单次（单通道）模式
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;//模数转换工作在连续模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//转换由软件控制而不是外部触发启动
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;// ADC 数据向右边对齐
	ADC_InitStructure.ADC_NbrOfChannel = 1; //转换通道个数为1
	ADC_Init(ADC1, &ADC_InitStructure);  //初始化ADC
	
	//ADC1选择信道5,音序等级1,采样时间7.5个周期
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 1, ADC_SampleTime_7Cycles5);//设置指定 ADC 的规则组通道，设置它们的转化顺序和采样时间
	
	ADC_Cmd(ADC1, ENABLE);//使能ADC
	
	//开始数据转换
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);//使能  ADCx 软件启动注入组转换功能 
}

unsigned int light_get_value(void)
{
	uint16_t ResultVolt = 0;
	uint8_t i;

	for(i = 0; i<8 ;i++)
	{
		while(RESET == ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));//等待转换完成
		ResultVolt +=  ADC_GetConversionValue(ADC1);//返回最近一次 ADCx 规则组的转换结果
	}
	ResultVolt = ResultVolt / 8;//求平均值
	
	//计算对应的电压 基准电压为3.3V，12位AD对应的最大数字量为4096。所以 adcx/ResultVolt = 3.3/4096得到 adcx
	//ResultVolt = (ResultVolt * 3300) / 4096;
	
	return ResultVolt;
}


















