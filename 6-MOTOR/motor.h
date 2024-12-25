#ifndef __MOTOR_H
#define __MOTOR_H


#define  MOTOR_OFF  0			//马达关
#define  MOTOR_FORWARD  1		//马达正转
#define  MOTOR_REVERSAL  2		//马达反转

void motor_init(void);
void motor_set_speed(int mode, int speed);


#endif

