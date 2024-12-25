#ifndef __OLED_H
#define __OLED_H

#include <stdint.h>
#include "OLED_Data.h"

/*�����궨��*********************/

/*FontSize����ȡֵ*/
/*�˲���ֵ���������жϣ��������ڼ�������ַ�ƫ�ƣ�Ĭ��ֵΪ�������ؿ��*/
#define OLED_8X16				8
#define OLED_6X8				6

/*IsFilled������ֵ*/
#define OLED_UNFILLED			0
#define OLED_FILLED				1

/*********************�����궨��*/


/*��������*********************/

/*��ʼ������*/
void OLED_Init(void);

/*���º���*/
//����ȫ��
void OLED_Update(void);
//����ָ������
void OLED_UpdateArea(int16_t X, int16_t Y, uint8_t Width, uint8_t Height);

/*�Դ���ƺ���*/
//���ȫ��
void OLED_Clear(void);
//���ָ������
void OLED_ClearArea(int16_t X, int16_t Y, uint8_t Width, uint8_t Height);
void OLED_Reverse(void);
void OLED_ReverseArea(int16_t X, int16_t Y, uint8_t Width, uint8_t Height);

/*��ʾ����*/
//��ʾһ���ַ�
void OLED_ShowChar(int16_t X, int16_t Y, char Char, uint8_t FontSize);
//��ʾ�ַ���
void OLED_ShowString(int16_t X, int16_t Y, char *String, uint8_t FontSize);
//��ʾ��������
void OLED_ShowNum(int16_t X, int16_t Y, uint32_t Number, uint8_t Length, uint8_t FontSize);
//��ʾ�з�����������
void OLED_ShowSignedNum(int16_t X, int16_t Y, int32_t Number, uint8_t Length, uint8_t FontSize);
//��ʾʮ��������������
void OLED_ShowHexNum(int16_t X, int16_t Y, uint32_t Number, uint8_t Length, uint8_t FontSize);
//��ʾ��������������
void OLED_ShowBinNum(int16_t X, int16_t Y, uint32_t Number, uint8_t Length, uint8_t FontSize);
//��ʾ����������
void OLED_ShowFloatNum(int16_t X, int16_t Y, double Number, uint8_t IntLength, uint8_t FraLength, uint8_t FontSize);
//��ʾ����
void OLED_ShowChinese(int16_t X, int16_t Y, char *Chinese);
//��ʾͼƬ
void OLED_ShowImage(int16_t X, int16_t Y, uint8_t Width, uint8_t Height, const uint8_t *Image);
//��ӡ
void OLED_Printf(int16_t X, int16_t Y, uint8_t FontSize, char *format, ...);

/*��ͼ����*/
//����һ����
void OLED_DrawPoint(int16_t X, int16_t Y);
//���ָ����λ�Ƿ����
uint8_t OLED_GetPoint(int16_t X, int16_t Y);
//��ֱ��
void OLED_DrawLine(int16_t X0, int16_t Y0, int16_t X1, int16_t Y1);
//������
void OLED_DrawRectangle(int16_t X, int16_t Y, uint8_t Width, uint8_t Height, uint8_t IsFilled);
//��������
void OLED_DrawTriangle(int16_t X0, int16_t Y0, int16_t X1, int16_t Y1, int16_t X2, int16_t Y2, uint8_t IsFilled);
//��Բ��
void OLED_DrawCircle(int16_t X, int16_t Y, uint8_t Radius, uint8_t IsFilled);
//����Բ��
void OLED_DrawEllipse(int16_t X, int16_t Y, uint8_t A, uint8_t B, uint8_t IsFilled);
//��Բ��
void OLED_DrawArc(int16_t X, int16_t Y, uint8_t Radius, int16_t StartAngle, int16_t EndAngle, uint8_t IsFilled);

/*********************��������*/

#endif

