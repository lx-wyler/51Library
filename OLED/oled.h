#ifndef __OLED_H__
#define __OLED_H__

#include "stc12c5a60s2.h"

sbit OLED_CS=P1^0; //片选
sbit OLED_RST =P1^1;//复位
sbit OLED_DC =P1^2;//数据/命令控制
sbit OLED_SCL=P1^3;//时钟 D0（SCLK�
sbit OLED_SDIN=P1^4;//D1（MOSI） 数据

void InitOled();
void OLED_P6x8Char(unsigned char x, unsigned char y, unsigned char ch);
void OLED_P6x8Str(unsigned char x,unsigned char y,unsigned char ch[]);
void OLED_Displaynum6_8(const unsigned int x, const unsigned char y, double num);  //显示数字
void OLED_Clear(void)  ;


void OLED_P6x8CharUL(unsigned char x, unsigned char y, unsigned char ch, bit u);  // 新加的带下划线的单字符显示



#endif