#include "uart.h"
#include "PinDefine.h"
#include "smg.h"

unsigned char code send_buff[SENDBUFFMAXSIZE] = 0;
unsigned char rbuff[30] = {0};
unsigned char cout = 0;

void UartInit()		//9600bps@11.0592MHz
{
	TMOD = 0X20;  // 定时器1工作方式2
	TH1 = 0XFD;
	TL1 = 0XFD;
	TR1 = 1;
	SM0 = 0;
	SM1 = 1;
	REN = 1;
	EA = 1;
	ES = 1;
}

void flagSendOneTime(){
	SMG4 = ~SMG4;
	a = ~a;
}

void sendChar(unsigned char c){
	SBUF = c;
	while(!TI);
//		if(c != 0)
//		  LED0 = 0;
//		else
//			LED1 = 0;
//	if(c != 0)
//	  LED0 = 1;
//	else
//		LED1 = 1;
	TI=0;
}

void irq_receive() interrupt 4{
	// 还没加
	rbuff[cout++] = SBUF;
	RI = 0;
}