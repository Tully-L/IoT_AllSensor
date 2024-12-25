#ifndef __LED_H
#define __LED_H

//led_num: 
#define  RGB_OFF 	0
#define  RGB_R 		1
#define  RGB_G 		2
#define  RGB_B 		3
#define  RGB_RG 	4
#define  RGB_RB 	5
#define  RGB_GB 	6
#define  RGB_RGB 	7


void led_c13_init(void);
void led_rgb_init(void);

void led_c13_on(void);
void led_c13_off(void);

void led_rgb_set(int led_num);

#endif
