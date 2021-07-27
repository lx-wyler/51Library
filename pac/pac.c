#include "pac.h"



void init_pwm(bit pwm0, bit pwm1){
	CCON = 0;
	
	CL = 0;
	CH = 0;
	CMOD = 0x08;
	
	if(pwm0){
		CCAP0H = CCAP0L = 0x00;  // 占空比
		CCAPM0 = 0x42;
	}
	
	if(pwm1){
		CCAP1H = CCAP1L = 0x00;
		CCAPM1 = 0x42;
	}
	
	CR = 1;
}


void set_pwm_duty(bit pwmn, unsigned char duty){
	if(pwmn){
		CCAP1H = duty;
	}
	else{
		CCAP0H = duty;
	}
}