#ifndef __OLED_H__
#define __OLED_H__

#include "reg52.h"

sbit OLED_CS=P1^4; //片选
sbit OLED_RST =P1^2;//复位
sbit OLED_DC =P1^3;//数据/命令控制
sbit OLED_SCL=P1^0;//时钟 D0（SCLK�
sbit OLED_SDIN=P1^1;//D1（MOSI） 数据

void InitOled();
void OLED_P6x8Str(unsigned char x,unsigned char y,unsigned char ch[]);
void OLED_Displaynum6_8(const unsigned int x, const unsigned char y, double num);  //显示数字
void OLED_Clear(void)  ;
#endif