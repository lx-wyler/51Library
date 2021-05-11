#include <reg52.h>
#include "LED.h"
#include "smg.h"
#include "ePaper.h"
#include "PinDefine.h"
#include "uart.h"
#include "keyboard.h"
#include <string.h>
#include "mycommon.h"
#include "oled.h"




unsigned char send_buff[SENDBUFFMAXSIZE] = {0};


int main(){
	
	
	int a = -588;
	float b = -3333561.134;
	float c = -123.2;
	

	
	ePaperInit();
	InitOled();
	OLED_Clear();
	
	OLED_Displaynum6_8(0, 2, 2021.2);
	
//	epaperClean();
//	epaperRefresh();
//	delay(500);
//	
//	
//	Displaynum6_8(0, 0, a);
//	Displaynum6_8(0, 1, b);
//	Displaychar6_8(0, 2, '{');
//	Displaychar6_8(0, 3, '}');
//	Displaychar6_8(0, 4, '|');
	

	
	LED0=1;
	LED0=1;
	
//	epaperSleep();
	while(1);
  return 0;
}





