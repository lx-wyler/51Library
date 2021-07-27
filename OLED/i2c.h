#ifndef __24C02_H__
#define __24C02_H__

#include "reg52.h"

#define AT24C02_WRITE_ADDRESS          0xA0//24c02µÄĞ´µØÖ·
#define AT24C02_READ_ADDRESS           0xA1//24c02µÄ¶ÁµØÖ·£¨ÓÉÓÚ×îºóÒ»Î»µÄ²»Í¬¶øÔì³ÉµÄ²»Í¬£¬×îºóÒ»Î»==1Ê±Îª¶Á£©      

sbit SCL=P0^0;
sbit SDA=P0^1;

/////////////////6050/////////////////
     ////¶¨ÒåMPU6050ÄÚ²¿µØÖ·/////
#define	SMPLRT_DIV		0x19	//ÍÓÂİÒÇ²ÉÑùÂÊ£¬µäĞÍÖµ:0x07(125Hz)
#define	CONFIG			0x1A	//µÍÍ¨ÂË²¨ÆµÂÊ£¬µäĞÍÖµ:0x06(5Hz)

#define	GYRO_CONFIG		0x1B	//ÍÓÂİÒÇ×Ô¼ì¼°²âÁ¿·¶Î§£¬µäĞÍÖµ:0x18(???,2000deg/s)
#define	ACCEL_CONFIG	        0x1C	//¼ÓËÙ¶È¼Æ×Ô¼ì¡¢²âÁ¿·¶Î§¼°¸ßÍ¨ÂË²¨·¶Î§£¬µäĞÍÖµ,???:0x01(???,2G,5Hz)
#define PWR_MGMT_1  0x6B //µçÔ´¹ÜÀí£¬µäĞÍÊÖµ:0x00(????)
#define WHO_AM_I   0x75 //IICµØÖ·¼Ä´æÆ÷(Ä¬ÈÏÉèÊıÖµ0x68,??)
#define SlaveAddress 0xD0 //IICĞ´ÈëÊ±µÄµØÖ·×Ö½ÚÊı¾İ,+1Îª¶ÁÈ¡

         //¼ÓËÙ¶ÈµÄºê//
#define	ACCEL_XOUT_H	        0x3B    //a
#define	ACCEL_XOUT_L	        0x3C    //b
#define	ACCEL_YOUT_H	        0x3D    //c
#define	ACCEL_YOUT_L	        0x3E    //d
#define	ACCEL_ZOUT_H	        0x3F    //e
#define	ACCEL_ZOUT_L	        0x40    //f

         //ÍÓÂİÒÇµÄºê//
#define	GYRO_XOUT_H		0x43
#define	GYRO_XOUT_L		0x44	
#define	GYRO_YOUT_H		0x45
#define	GYRO_YOUT_L		0x46
#define	GYRO_ZOUT_H		0x47
#define	GYRO_ZOUT_L		0x48




//extern void delay7ms(void);
//extern void delay_ms(unsigned int );  //ÑÓÊ±µÄº¯Êı
//extern void I2C_start();//¿ªÊ¼ĞÅºÅ
//extern void I2C_stop();//Í£Ö¹ĞÅºÅ
//extern void I2C_send_answer();//Ö÷Æ÷¼ş·¢ËÍÓ¦´ğĞÅºÅ
//extern int I2C_receive_answer();//Ö÷Æ÷¼ş½ÓÊÕÓ¦´ğĞÅºÅ
extern void I2C_send_byte(unsigned char);//Ïò24c02·¢ËÍÒ»¸ö×Ö½Ú
extern void I2C_writedata(unsigned char,unsigned char,unsigned char);//Ïò24c02Ğ´Ò»¸ö8Î»Êı¾İ
extern unsigned char I2C_readdata(unsigned char,unsigned char);//´Ó23c02¶ÁÒ»¸ö8Î»Êı¾İ
#endif