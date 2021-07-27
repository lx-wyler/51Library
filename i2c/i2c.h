#ifndef __24C02_H__
#define __24C02_H__

#include "reg52.h"    

typedef unsigned char i2ctype;

sbit SCL=P3^3;
sbit SDA=P3^2;


void I2C_writedata(i2ctype, i2ctype, i2ctype);  // 向I2C总线上指定设备的寄存器写一个8位数据
i2ctype I2C_readdata(i2ctype, i2ctype);  // 从I2C总线上指定设备的寄存器中读一个8位数据

#endif