#include "stm32f10x.h"                  // Device header
#include "usart.h"

/******************
PA9   USART1_TX  串口1发送引脚   接串口模块的RX
PA10  USART1_RX  串口1接收引脚   接串口模块的TX

注意勾选 绿色图标 Device -> StdPeriph Drivers -> USART

注意: 使用printf时, 需要在魔法棒图标(options) -> target -> 勾选 Use MicroLib
*******************/


/********************
//参考main.c
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
		
		if(RxFlag == 1)  //标志位的判断, 有数据来
		{
			RxFlag = 0;  //清除标志位, 方便下一次接收 
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
	
	//RCC 使能GPIOA时钟 + 串口1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1 , ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
	GPIO_Init(GPIOA, &GPIO_InitStructure); //初始化PA9 复用推挽输出模式
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);  //初始化PA10 浮空输入模式
	
	USART_InitStructure.USART_BaudRate = BaudRate; //设置波特率，外部传入 9600 或 115200
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; //设置字长/数据位 8位
	USART_InitStructure.USART_StopBits = USART_StopBits_1; //设置停止位 1位
	USART_InitStructure.USART_Parity = USART_Parity_No; //无奇偶校验
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //无硬件流控
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; //数据收发模式
	USART_Init(USART1, &USART_InitStructure); //初始化串口1
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); //使能串口接收中断
	
	USART_Cmd(USART1, ENABLE); //使能串口1

	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;   //选择串口1中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //设置中断先占优先级/组优先级 0 数字越小优先级越高 (只能是0)
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //设置中断从优先级 0 数字越小优先级越高 (0~15)
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //中断使能
	NVIC_Init(&NVIC_InitStructure); //中断初始化
}

//串口1发送一个字符 字符用''框起来   单片机->电脑 电脑上用串口调试小助手查看数据
void uart1_send_byte(unsigned char data)
{
	USART_SendData(USART1, data);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}
//串口1发送字符串 字符串用""框起来  单片机->电脑
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

//（重定向）重写fputc函数  重写后就能使用printf函数输出数据
//注意: 使用printf时, 需要在魔法棒图标(options) -> target -> 勾选 Use MicroLib
int fputc(int dat, FILE * stream)
{
	uart1_send_byte(dat);
	return dat;
}

char RxData = 0, RxFlag = 0;

//串口1的中断函数 接收数据
void USART1_IRQHandler(void)
{
	if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) 
	{
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
		RxData = USART_ReceiveData(USART1);  //收到的数据
		RxFlag = 1; //接收标志
		
		//uart_send_byte(RxData);
	}
}


