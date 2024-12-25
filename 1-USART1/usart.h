#ifndef __USART_H
#define __USART_H

#include <stdio.h>

extern char RxData;  //���յ�������
extern char RxFlag;  //0-�����޽�������  1-�����н�������

void uart1_init(int BaudRate);
void uart1_send_byte(unsigned char data);
void uart1_send_str(unsigned char *str);


#endif
