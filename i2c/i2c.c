#include "i2c.h"
#include <intrins.h>
#include "PinDefine.h"
#include "mycommon.h"



#include "oled.h"
#include <stdio.h>

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int   uint;


//**************************************
//I2C起始信号
//**************************************
void i2c_start()
{
    SDA = 1;                    //拉高数据线
    SCL = 1;                    //拉高时钟线
    Delay5us();                 //延时
    SDA = 0;                    //产生下降沿
    Delay5us();                 //延时
    SCL = 0;                    //拉低时钟线
}

//**************************************
//I2C停止信号
//**************************************
void i2c_stop()
{
    SDA = 0;                    //拉低数据线
    SCL = 1;                    //拉高时钟线
    Delay5us();                 //延时
    SDA = 1;                    //产生上升沿
    Delay5us();                 //延时
}

//**************************************
// I2C发送应答信号
// 入口参数: ack(0: ACK; 1: NACK)
//**************************************
void i2c_sendack(bit ack)
{
    SDA = ack;                  //写应答信号
    SCL = 1;                    //拉高时钟线
    Delay5us();                 //延时
    SCL = 0;                    //拉低时钟线
    Delay5us();                 //延时
}

//**************************************
//I2C接收应答信号
//**************************************
bit i2c_recvack()
{
    SCL = 1;                    //拉高时钟线
    Delay5us();                 //延时
    CY = SDA;                   //读应答信号
    SCL = 0;                    //拉低时钟线
    Delay5us();                 //延时
    return CY;
}

//**************************************
// 向I2C总线发送一个字节数据
//**************************************
void i2c_send_byte(uchar dat)
{
    uchar i;
    for (i=0; i<8; i++)         //8位计数器
    {
        dat <<= 1;              //移出数据的最高位
        SDA = CY;               //送数据口
        SCL = 1;                //拉高时钟线
        Delay5us();             //延时
        SCL = 0;                //拉低时钟线
        Delay5us();             //延时
    }
    i2c_recvack();
}

//**************************************
// 从I2C总线接收一个字节数据
//**************************************
uchar i2c_recvbyte()
{
    uchar i;
    uchar dat = 0;
    SDA = 1;                    // 使能内部上拉，准备读取数据
    for (i=0; i<8; i++)         // 8位计数器
    {
        dat <<= 1;
        SCL = 1;                // 拉高时钟线
        Delay5us();             // 延时
        dat |= SDA;             // 读数据
        SCL = 0;                // 拉低时钟线
        Delay5us();             // 延时
    }
    return dat;
}

//**************************************
// 向I2C设备写入一个字节数据
//**************************************
void I2C_writedata(uchar slaveaddress, uchar reg_address,uchar reg_data)
{
    i2c_start();                  // 起始信号
    i2c_send_byte(slaveaddress);   // 发送设备地址+写信号
    i2c_send_byte(reg_address);    // 内部寄存器地址
    i2c_send_byte(reg_data);       // 内部寄存器数据
    i2c_stop();                   // 发送停止信号
}

//**************************************
// 从I2C设备读取一个字节数据
//**************************************
uchar I2C_readdata(uchar slave_address, uchar reg_address)
{
	uchar REG_data;
	
	i2c_start();                   //ÆðÊ¼ÐÅºÅ
	i2c_send_byte(slave_address);    //·¢ËÍÉè±¸µØÖ·+Ð´ÐÅºÅ
	i2c_send_byte(reg_address);     //·¢ËÍ´æ´¢µ¥ÔªµØÖ·£¬´Ó0¿ªÊ¼	
	i2c_start();                   //ÆðÊ¼ÐÅºÅ
	i2c_send_byte(slave_address+1);  //·¢ËÍÉè±¸µØÖ·+¶ÁÐÅºÅ
	REG_data=i2c_recvbyte();       //¶Á³ö¼Ä´æÆ÷Êý¾Ý
	i2c_sendack(1);                //½ÓÊÕÓ¦´ðÐÅºÅ
	i2c_stop();                    //Í£Ö¹ÐÅºÅ
	return REG_data;
}