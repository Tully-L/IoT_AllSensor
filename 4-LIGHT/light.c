#include "stm32f10x.h"                  // Device header
#include "light.h"

/******************
����:AO����      PA5		ADC1_CH5

ע�⹴ѡ ��ɫͼ�� Device -> StdPeriph Drivers -> ADC
*******************/

/********************
//�ο�main.c
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
	ADC_InitTypeDef ADC_InitStructure;   //ADC�ṹ�����
	GPIO_InitTypeDef  GPIO_InitStructure;
	

	//1. �ϵ� ʹADC�ܹ�����
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1,ENABLE);
		
	//2.GPIO ����	PA5    ADC12_IN5
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5  ; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;  //ģ������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA,  &GPIO_InitStructure);  //PA5��ʼ�� ģ������
	
	ADC_DeInit(ADC1);
	
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;//ADC1 �� ADC2 �����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;//ģ��ת��������ɨ��ģʽ����ͨ�������ǵ��Σ���ͨ����ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;//ģ��ת������������ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//ת����������ƶ������ⲿ��������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;// ADC �������ұ߶���
	ADC_InitStructure.ADC_NbrOfChannel = 1; //ת��ͨ������Ϊ1
	ADC_Init(ADC1, &ADC_InitStructure);  //��ʼ��ADC
	
	//ADC1ѡ���ŵ�5,����ȼ�1,����ʱ��7.5������
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 1, ADC_SampleTime_7Cycles5);//����ָ�� ADC �Ĺ�����ͨ�����������ǵ�ת��˳��Ͳ���ʱ��
	
	ADC_Cmd(ADC1, ENABLE);//ʹ��ADC
	
	//��ʼ����ת��
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);//ʹ��  ADCx �������ע����ת������ 
}

unsigned int light_get_value(void)
{
	uint16_t ResultVolt = 0;
	uint8_t i;

	for(i = 0; i<8 ;i++)
	{
		while(RESET == ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));//�ȴ�ת�����
		ResultVolt +=  ADC_GetConversionValue(ADC1);//�������һ�� ADCx �������ת�����
	}
	ResultVolt = ResultVolt / 8;//��ƽ��ֵ
	
	//�����Ӧ�ĵ�ѹ ��׼��ѹΪ3.3V��12λAD��Ӧ�����������Ϊ4096������ adcx/ResultVolt = 3.3/4096�õ� adcx
	//ResultVolt = (ResultVolt * 3300) / 4096;
	
	return ResultVolt;
}


















