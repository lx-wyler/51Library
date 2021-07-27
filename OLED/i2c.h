#ifndef __24C02_H__
#define __24C02_H__

#include "reg52.h"

#define AT24C02_WRITE_ADDRESS          0xA0//24c02��д��ַ
#define AT24C02_READ_ADDRESS           0xA1//24c02�Ķ���ַ���������һλ�Ĳ�ͬ����ɵĲ�ͬ�����һλ==1ʱΪ����      

sbit SCL=P0^0;
sbit SDA=P0^1;

/////////////////6050/////////////////
     ////����MPU6050�ڲ���ַ/////
#define	SMPLRT_DIV		0x19	//�����ǲ����ʣ�����ֵ:0x07(125Hz)
#define	CONFIG			0x1A	//��ͨ�˲�Ƶ�ʣ�����ֵ:0x06(5Hz)

#define	GYRO_CONFIG		0x1B	//�������Լ켰������Χ������ֵ:0x18(???,2000deg/s)
#define	ACCEL_CONFIG	        0x1C	//���ٶȼ��Լ졢������Χ����ͨ�˲���Χ������ֵ,???:0x01(???,2G,5Hz)
#define PWR_MGMT_1  0x6B //��Դ���������ֵ:0x00(????)
#define WHO_AM_I   0x75 //IIC��ַ�Ĵ���(Ĭ������ֵ0x68,??)
#define SlaveAddress 0xD0 //IICд��ʱ�ĵ�ַ�ֽ�����,+1Ϊ��ȡ

         //���ٶȵĺ�//
#define	ACCEL_XOUT_H	        0x3B    //a
#define	ACCEL_XOUT_L	        0x3C    //b
#define	ACCEL_YOUT_H	        0x3D    //c
#define	ACCEL_YOUT_L	        0x3E    //d
#define	ACCEL_ZOUT_H	        0x3F    //e
#define	ACCEL_ZOUT_L	        0x40    //f

         //�����ǵĺ�//
#define	GYRO_XOUT_H		0x43
#define	GYRO_XOUT_L		0x44	
#define	GYRO_YOUT_H		0x45
#define	GYRO_YOUT_L		0x46
#define	GYRO_ZOUT_H		0x47
#define	GYRO_ZOUT_L		0x48




//extern void delay7ms(void);
//extern void delay_ms(unsigned int );  //��ʱ�ĺ���
//extern void I2C_start();//��ʼ�ź�
//extern void I2C_stop();//ֹͣ�ź�
//extern void I2C_send_answer();//����������Ӧ���ź�
//extern int I2C_receive_answer();//����������Ӧ���ź�
extern void I2C_send_byte(unsigned char);//��24c02����һ���ֽ�
extern void I2C_writedata(unsigned char,unsigned char,unsigned char);//��24c02дһ��8λ����
extern unsigned char I2C_readdata(unsigned char,unsigned char);//��23c02��һ��8λ����
#endif