#ifndef __UART_H__
#define __UART_H__

#define START '{'
#define END   '}'
#define SENDBUFFMAXSIZE 50

extern unsigned char code send_buff[SENDBUFFMAXSIZE];


extern unsigned char cout;
extern unsigned char rbuff[30];

void UartInit();		//9600bps@11.0592MHz
void flagSendOneTime();
void sendChar(unsigned char c);


#endif