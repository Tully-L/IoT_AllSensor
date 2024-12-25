#include "stm32f10x.h"                  // Device header
#include "usart.h"

/******************
PA9   USART1_TX  ����1��������   �Ӵ���ģ���RX
PA10  USART1_RX  ����1��������   �Ӵ���ģ���TX

ע�⹴ѡ ��ɫͼ�� Device -> StdPeriph Drivers -> USART

ע��: ʹ��printfʱ, ��Ҫ��ħ����ͼ��(options) -> target -> ��ѡ Use MicroLib
*******************/


/********************
//�ο�main.c
#include "stm32f10x.h"                  // Device header
#include "led.h"
#include "usart.h"

int main()
{
	int i= 0;
	
	led_c13_init();
	uart1_init(115200);
	
	while(1)
	{
		i++;
		uart1_send_byte('a');
		uart1_send_str("hello\r\n");
		printf("i:%d\r\n", i);
		
		if(RxFlag == 1)  //��־λ���ж�, ��������
		{
			RxFlag = 0;  //�����־λ, ������һ�ν��� 
			switch(RxData)
			{
				case 'a': led_c13_on(); break;
				case 'b': led_c13_off(); break;
			}
		}
	}
}
*********************/

void uart1_init(int BaudRate)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure; 	
	NVIC_InitTypeDef NVIC_InitStructure; 
	
	//RCC ʹ��GPIOAʱ�� + ����1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1 , ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
	GPIO_Init(GPIOA, &GPIO_InitStructure); //��ʼ��PA9 �����������ģʽ
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);  //��ʼ��PA10 ��������ģʽ
	
	USART_InitStructure.USART_BaudRate = BaudRate; //���ò����ʣ��ⲿ���� 9600 �� 115200
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; //�����ֳ�/����λ 8λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1; //����ֹͣλ 1λ
	USART_InitStructure.USART_Parity = USART_Parity_No; //����żУ��
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //��Ӳ������
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; //�����շ�ģʽ
	USART_Init(USART1, &USART_InitStructure); //��ʼ������1
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); //ʹ�ܴ��ڽ����ж�
	
	USART_Cmd(USART1, ENABLE); //ʹ�ܴ���1

	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;   //ѡ�񴮿�1�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //�����ж���ռ���ȼ�/�����ȼ� 0 ����ԽС���ȼ�Խ�� (ֻ����0)
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //�����жϴ����ȼ� 0 ����ԽС���ȼ�Խ�� (0~15)
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //�ж�ʹ��
	NVIC_Init(&NVIC_InitStructure); //�жϳ�ʼ��
}

//����1����һ���ַ� �ַ���''������   ��Ƭ��->���� �������ô��ڵ���С���ֲ鿴����
void uart1_send_byte(unsigned char data)
{
	USART_SendData(USART1, data);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}
//����1�����ַ��� �ַ�����""������  ��Ƭ��->����
void uart1_send_str(unsigned char *str)
{
	while(*str != '\0')
	{
		uart1_send_byte(*str);
		str++;
	}
}

char uart1_recv_byte(void)
{
	u16 RxData; 
	RxData = USART_ReceiveData(USART1);
	return RxData;
}

//���ض�����дfputc����  ��д�����ʹ��printf�����������
//ע��: ʹ��printfʱ, ��Ҫ��ħ����ͼ��(options) -> target -> ��ѡ Use MicroLib
int fputc(int dat, FILE * stream)
{
	uart1_send_byte(dat);
	return dat;
}

char RxData = 0, RxFlag = 0;

//����1���жϺ��� ��������
void USART1_IRQHandler(void)
{
	if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) 
	{
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
		RxData = USART_ReceiveData(USART1);  //�յ�������
		RxFlag = 1; //���ձ�־
		
		//uart_send_byte(RxData);
	}
}


