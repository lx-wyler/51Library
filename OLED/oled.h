#ifndef __OLED_H__
#define __OLED_H__

#include "stc12c5a60s2.h"

sbit OLED_CS=P1^0; //Æ¬Ñ¡
sbit OLED_RST =P1^1;//¸´Î»
sbit OLED_DC =P1^2;//Êı¾İ/ÃüÁî¿ØÖÆ
sbit OLED_SCL=P1^3;//Ê±ÖÓ D0£¨SCLK£
sbit OLED_SDIN=P1^4;//D1£¨MOSI£© Êı¾İ

void InitOled();
void OLED_P6x8Char(unsigned char x, unsigned char y, unsigned char ch);
void OLED_P6x8Str(unsigned char x,unsigned char y,unsigned char ch[]);
void OLED_Displaynum6_8(const unsigned int x, const unsigned char y, double num);  //ÏÔÊ¾Êı×Ö
void OLED_Clear(void)  ;


void OLED_P6x8CharUL(unsigned char x, unsigned char y, unsigned char ch, bit u);  // ĞÂ¼ÓµÄ´øÏÂ»®ÏßµÄµ¥×Ö·ûÏÔÊ¾



#endif