#ifndef __OLED_H__
#define __OLED_H__

#include "reg52.h"

sbit OLED_CS=P1^4; //Æ¬Ñ¡
sbit OLED_RST =P1^2;//¸´Î»
sbit OLED_DC =P1^3;//Êı¾İ/ÃüÁî¿ØÖÆ
sbit OLED_SCL=P1^0;//Ê±ÖÓ D0£¨SCLK£
sbit OLED_SDIN=P1^1;//D1£¨MOSI£© Êı¾İ

void InitOled();
void OLED_P6x8Str(unsigned char x,unsigned char y,unsigned char ch[]);
void OLED_Displaynum6_8(const unsigned int x, const unsigned char y, double num);  //ÏÔÊ¾Êı×Ö

#endif