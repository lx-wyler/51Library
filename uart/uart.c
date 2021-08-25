#include "uart.h"
#include "PinDefine.h"
#include "clearrobot.h"
#include "eeprom.h"
#include "stc12c5a60s2.h"

unsigned char code send_buff[SENDBUFFMAXSIZE] = 0;
unsigned char rbuff[30] = {0};
unsigned char cout = 0;

unsigned char flag_down = 0;
unsigned char down_buff[3] = {0x5a, 0x5a, 0x24};
unsigned char down_rbuff[3] = {0};  // 这3个是自动下载用的

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


void sendChar(unsigned char c){
	SBUF = c;
	while(!TI);
	TI=0;
}

void irq_receive() interrupt 4{
	// 还没加
	rbuff[cout++] = SBUF;
	down_rbuff[flag_down] = SBUF;
	
	if(down_rbuff[flag_down] == down_buff[flag_down]){
		if(flag_down < 3){
			flag_down++;
		}
		if(flag_down == 3){
			IAP_CONTR = 0x60;
		}
	}
	else{
		flag_down = 0;
	}
	
	RI = 0;
}

// -----------------------------------
// --------- clearrobot add ----------
// -----------------------------------

void send_cto(int cto_temp){
	static bit flag_send_none = 0;
	
	if(!cto_temp){
		if(!flag_send_none){
			sendChar(cto_temp);
			sendChar(cto_temp);
			sendChar(cto_temp);
			flag_send_none = 1;
		}
	}
	else{
		sendChar(cto_temp);
		flag_send_none = 0;
	}
}