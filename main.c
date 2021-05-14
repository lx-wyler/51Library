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



int main(){
	ePaperInit();
//	InitOled();
//	OLED_Clear();
//	OLED_Displaynum6_8(0, 0, -321654);
//	OLED_P6x8Str(0, 1, "This is my nth OLED program.");
	
	epaperClean();
	epaperRefresh();
	delay(500);
	
	Displaystr6_8(0, 1, "This is my first ePaper program.");
	Displaystr6_8_2(280, 2, "This is my first ePaper program.And now alsdjfoi ajsiodfjaosi j aoispoiuwuj j2393274598 !$#%#@^ owqiejfiodaj.");
	Displaynum6_8(0, 0, -123.5);
	epaperSleep();

	
	

	while(1);
	return 0;
}