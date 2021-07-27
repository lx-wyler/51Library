#include "mpu6050.h"
#include "i2c.h"
#include "mycommon.h"



// 初始化6050，成功返回1，失败返回0
bit init_mpu6050(){
	delay(200);
	
	I2C_writedata(MPU6050Address, PWR_MGMT_1, 0x00);
	I2C_writedata(MPU6050Address, SMPLRT_DIV, 0x07);
	I2C_writedata(MPU6050Address, CONFIG, 0x06);
	I2C_writedata(MPU6050Address, GYRO_CONFIG, 0x18);
	I2C_writedata(MPU6050Address, ACCEL_CONFIG, 0x01);
	
	delay(500);
	
//	if(0x68 == I2C_readdata(SlaveAddress, WHO_AM_I))
//		return 1;
//	else
		return 0;
}


// 读X轴加速度
int read_accel_x(){
	int temp;
	
	temp = I2C_readdata(MPU6050Address, ACCEL_XOUT_H);
	temp = temp << 8;
	temp = temp | I2C_readdata(MPU6050Address, ACCEL_XOUT_L);
	
	return temp;
}


// 读y轴加速度
int read_accel_y(){
	int temp;
	
	temp = I2C_readdata(MPU6050Address, ACCEL_YOUT_H);
	temp = temp << 8;
	temp = temp | I2C_readdata(MPU6050Address, ACCEL_YOUT_L);
	
	return temp;
}


// 读z轴加速度
int read_accel_z(){
	int temp;
	
	temp = I2C_readdata(MPU6050Address, ACCEL_ZOUT_H);
	temp = temp << 8;
	temp = temp | I2C_readdata(MPU6050Address, ACCEL_ZOUT_L);
	
	return temp;
}


// 读x轴角速度
int read_gyro_x(){
	int temp;
	
	temp = I2C_readdata(MPU6050Address, GYRO_XOUT_H);
	temp = temp << 8;
	temp = temp | I2C_readdata(MPU6050Address, GYRO_XOUT_L);
	
	return temp;
}


// 读y轴角速度
int read_gyro_y(){
	int temp;
	
	temp = I2C_readdata(MPU6050Address, GYRO_YOUT_H);
	temp = temp << 8;
	temp = temp | I2C_readdata(MPU6050Address, GYRO_YOUT_L);
	
	return temp;
}


// 读z轴角速度
int read_gyro_z(){
	int temp;
	
	temp = I2C_readdata(MPU6050Address, GYRO_ZOUT_H);
	temp = temp << 8;
	temp = temp | I2C_readdata(MPU6050Address, GYRO_ZOUT_L);
	
	return temp;
}