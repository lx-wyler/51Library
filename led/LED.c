#include <PinDefine.h>
#include "mycommon.h"




void ledFlicker(unsigned char ledN, unsigned char n, unsigned int time){
  if(ledN==0){
	  for(;n>0;--n){
		  LED0=0;
			delay(time);
			LED0=1;
			delay(time);
		}
	}
	else if(ledN==1){
	  for(;n>0;--n){
		  LED1=0;
			delay(time);
			LED1=1;
			delay(time);
		}
	}
	else{
		while(1){
		  LED0=0;
			LED1=0;
			delay(time);
			LED0=1;
			LED1=1;
			delay(time);
		}
	}
}