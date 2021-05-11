#include <reg52.h>
#include "LED.h"
#include "smg.h"
#include "ePaper.h"
#include "PinDefine.h"
#include "uart.h"
//#include "keyboard.h"
#include <string.h>
#include "mycommon.h"
#include "oled.h"




unsigned char code send_buff[SENDBUFFMAXSIZE] = {0};


int main(){
	
	
	int a = -588;
	float b = -3333561.134;
	float c = -123.2;
	

	
	ePaperInit();
	InitOled();
	OLED_Clear();
	
	epaperClean();
	epaperRefresh();
	delay(500);
	
	Displaystr6_8(0, 1, "abc");
	epaperSleep();

	
	

	while(1);
  return 0;
}





