#include <reg52.h>
#include "LED.h"
#include "smg.h"
#include"ePaper.h"
#include "PinDefine.h"
#include "uart.h"
#include "keyboard.h"
#include <string.h>



unsigned char send_buff[SENDBUFFMAXSIZE] = {0};


int main(){
	int a = -588;
	float b = -3333561.134;
	
	ePaperInit();
	
	epaperClean();
	epaperRefresh();
	delay(500);
	
	
	Displaynum6_8(0, 0, a);
	Displaynum6_8(0, 1, b);
	Displaychar6_8(0, 2, '{');
	Displaychar6_8(0, 3, '}');
	Displaychar6_8(0, 4, '|');
//	epaperRefresh();
//	epaperRefresh();
//	
//	Displaynum5_8('b');
//	epaperRefresh();
	

	
	
	
	epaperSleep();
	while(1);
  return 0;
}





