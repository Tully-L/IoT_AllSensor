#ifndef __BEEP_H
#define __BEEP_H

#define  proport          10000 //Tclk/(psc+1)=72000000/(7199+1)   Tclk=72MHz 预分频后的频率

//根据 Tout = ((arr+1)*(psc+1))/Tclk  Tout为音调频率的倒数, 推出arr值就是define定义的值
#define  L1       ((proport/131)-1)//低调　do 的周期
#define  L2       ((proport/147)-1)//低调　re 的周期
#define  L3       ((proport/165)-1)//低调　mi 的周期
#define  L4       ((proport/176)-1)//低调　fa 的周期
#define  L5       ((proport/196)-1)//低调　sol的周期
#define  L6       ((proport/220)-1)//低调　la 的周期
#define  L7       ((proport/247)-1)//低调　si 的周期

#define  M1       ((proport/262)-1)//中调　do 的周期
#define  M2       ((proport/296)-1)//中调　re 的周期
#define  M3       ((proport/330)-1)//中调　mi 的周期
#define  M4       ((proport/349)-1)//中调　fa 的周期
#define  M5       ((proport/392)-1)//中调　sol的周期
#define  M6       ((proport/440)-1)//中调　la 的周期
#define  M7       ((proport/494)-1)//中调　si 的周期

#define  H1       ((proport/523)-1)//高调　do 的周期
#define  H2       ((proport/587)-1)//高调　re 的周期
#define  H3       ((proport/659)-1)//高调　mi 的周期
#define  H4       ((proport/699)-1)//高调　fa 的周期
#define  H5       ((proport/784)-1)//高调　sol的周期
#define  H6       ((proport/880)-1)//高调　la 的周期
#define  H7       ((proport/988)-1)//高调　si 的周期




void my_music_delay(int n);
void beep_init(void);
void beep_set(int period, int pulse);

#endif

