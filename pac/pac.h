#ifndef __PAC_H__
#define __PAC_H__

//sfr CCON = 0xD8;
//sbit CCF0 = CCON^0;
//sbit CCF1 = CCON^1;
//sbit CR = CCON^6;
//sbit CF = CCON^7;
//sfr CMOD = 0xD9;
//sfr CL = 0xE9;
//sfr CH = 0xF9;
//sfr CCAPM0 = 0xDA;
//sfr CCAP0L = 0xEA;
//sfr CCAP0H = 0xFA;
//sfr CCAPM1 = 0xDB;
//sfr CCAP1L = 0xEB;
//sfr CCAP1H = 0xFB;
//sfr PCAPWM0 = 0xF2;
//sfr PCAPWM1 = 0xF3;

void init_pwm(bit pwm0, bit pwm1);  // 初始化PWM，对应位置为1时初始化，否则不初始化
void set_pwm_duty(bit pwmn, unsigned char duty);  // 设置选择的PWM占空比

#endif