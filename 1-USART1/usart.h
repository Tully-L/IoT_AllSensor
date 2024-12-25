#ifndef __USART_H
#define __USART_H

#include <stdio.h>

extern char RxData;  //接收到的数据
extern char RxFlag;  //0-代表无接收数据  1-代表有接收数据

void uart1_init(int BaudRate);
void uart1_send_byte(unsigned char data);
void uart1_send_str(unsigned char *str);


#endif
