#ifndef __MOTOR_H
#define __MOTOR_H


#define  MOTOR_OFF  0			//����
#define  MOTOR_FORWARD  1		//�����ת
#define  MOTOR_REVERSAL  2		//��ﷴת

void motor_init(void);
void motor_set_speed(int mode, int speed);


#endif

