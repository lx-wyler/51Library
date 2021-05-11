#ifndef __OLED_H__
#define __OLED_H__

#include "reg52.h"

sbit OLED_CS=P1^4; //Æ¬Ñ¡
sbit OLED_RST =P1^2;//¸´Î»
sbit OLED_DC =P1^3;//Êý¾Ý/ÃüÁî¿ØÖÆ
sbit OLED_SCL=P1^0;//Ê±ÖÓ D0£¨SCLK£
sbit OLED_SDIN=P1^1;//D1£¨MOSI£© Êý¾Ý

#define OLED_CS_Clr()  OLED_CS=0
#define OLED_CS_Set()  OLED_CS=1

#define OLED_RST_Clr() OLED_RST=0
#define OLED_RST_Set() OLED_RST=1

#define OLED_DC_Clr() OLED_DC=0
#define OLED_DC_Set() OLED_DC=1

#define OLED_SCLK_Clr() OLED_SCL=0
#define OLED_SCLK_Set() OLED_SCL=1

#define OLED_SDIN_Clr() OLED_SDIN=0
#define OLED_SDIN_Set() OLED_SDIN=1;

#endif