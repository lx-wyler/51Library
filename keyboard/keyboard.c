#include "PinDefine.h"
#include "keyboard.h"
#include "led.h"
#include "smg.h"


// 得到按下的按键值
#if USEPWHAT == 0
unsigned char get_key(){
	unsigned char key, temp;
  unsigned char i =0;
	
	a = 0;
  fist_line = 1;
  second_line = 1;
  third_line = 1;
  four_line = 1;
  fist_list = 0;
  second_list = 0;
  third_list = 0;
	delay(10);
	
	temp = keyboardall;
	
	
//	if(temp == i){
//		LED1 = 0;
//		//delay(500);
//		while(1){
//			keyboardall = temp;
//		}
//	}
//	else
//		LED1 = 1;
//	if(i%10 == 0)
//	LED0 = ~LED0;
//	i++;
	
	fist_list = 1;
  second_list = 1;
  third_list = 1;
  fist_line = 0;
  second_line = 0;
  third_line = 0;
  four_line = 0;
	delay(10);
	
	key = keyboardall;
	key = key & temp;
	
//	if(key == i){
//		LED1 = 0;
//		while(1){
//			keyboardall = key;
//		}
//	}
//	else
//		LED1 = 1;
//	if(i%10 == 0)
//	  LED0 = ~LED0;
//	i++;
	
	
	switch(key){
		case 0x22: i = 1;break;
		case 0x42: i = 2;break;
		case 0x82: i = 3;break;
		
		case 0x24: i = 4;break;
		case 0x44: i = 5;break;
		case 0x84: i = 6;break;
		
		case 0x28: i = 7;break;
		case 0x48: i = 8;break;
		case 0x88: i = 9;break;
		
		case 0x30: i = 11;break;
		case 0x50: i = 0;break;
		case 0x90: i = 12;break;
		default : i = 255;  // 没有按键按下
	}
	
	return i;
}

#else
unsigned char get_key(){
	unsigned char key, temp;
  unsigned char i =0;
	
	SMG1 = 0;
  fist_line = 1;
  second_line = 1;
  third_line = 1;
  four_line = 1;
  fist_list = 0;
  second_list = 0;
  third_list = 0;
	delay(10);
	
	temp = keyboardall;
	
	
//	if(temp == i){
//		LED1 = 0;
//		//delay(500);
//		while(1){
//			keyboardall = temp;
//		}
//	}
//	else
//		LED1 = 1;
//	if(i%10 == 0)
//	LED0 = ~LED0;
//	i++;
	
	fist_list = 1;
  second_list = 1;
  third_list = 1;
  fist_line = 0;
  second_line = 0;
  third_line = 0;
  four_line = 0;
	delay(10);
	
	key = keyboardall;
	key = key | temp;
	
//	P0 = key;
	
//	if(key == i){
//		LED1 = 0;
//		while(1){
//			keyboardall = key;
//		}
//	}
//	else
//		LED1 = 1;
//	if(i%10 == 0)
//	  LED0 = ~LED0;
//	i++;
	
	
	switch(key){
		case 0xDC: i = 1;break;
		case 0xBC: i = 2;break;
		case 0x7C: i = 3;break;
		
		case 0xDA: i = 4;break;
		case 0xBA: i = 5;break;
		case 0x7A: i = 6;break;
		
		case 0xD6: i = 7;break;
		case 0xB6: i = 8;break;
		case 0x76: i = 9;break;
		
		case 0xCE: i = 11;break;
		case 0xAE: i = 0;break;
		case 0x6E: i = 12;break;
		default : i = 255;  // 没有按键按下
	}
	
	return i;
}
#endif


//sbit fist_line = P2^1;
//sbit second_line = P2^2;
//sbit third_line = P2^3;
//sbit four_line = P2^4;
//sbit fist_list = P2^5;
//sbit second_list = P2^6;
//sbit third_list = P2^7;