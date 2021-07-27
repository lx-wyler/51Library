#ifndef __pindefine_h__
#define __pindefine_h__

#include<reg52.h>

// ePaper pin define
sbit epaperBUSY=P0^0;
sbit epaperRST=P0^1;
sbit epaperDC=P0^2;
sbit epaperCS=P0^3;
sbit epaperDIN=P0^4;
sbit epaperCLK=P0^5;


// 51 LED define
sbit LED0=P1^4;
sbit LED1=P1^5;
sbit BUTTON = P1^3;
sbit FMQ = P1^6;

// test
sbit TESTP = P2^2;
sbit TESTWHILE = P2^3;
sbit TESTRECEIVE = P2^4;

#endif






























