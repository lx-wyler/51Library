#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#define USEPWHAT 2  // 2 or 0

#if USEPWHAT == 2
sbit fist_line = P2^1;
sbit second_line = P2^2;
sbit third_line = P2^3;
sbit four_line = P2^4;
sbit fist_list = P2^5;
sbit second_list = P2^6;
sbit third_list = P2^7;
#define keyboardall  P2
#else

#endif




unsigned char get_key();


#endif