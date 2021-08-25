#ifndef __MYCOMMON_H__
#define __MYCOMMON_H__



typedef unsigned char 	uchar;
typedef unsigned short	ushort;
typedef unsigned int	uint;


void senddelay();  

double myabs(double x);  // 我的取绝对值函数

bit isDecimal(double x);  // 判断一个数是不是小数

long mypow(long x, int n);  // 整数专用次方

void delay(unsigned int n);

void Delay5us();

int hmd(int n);  // 判断一个整数有几位 hmd: how many digits




#endif