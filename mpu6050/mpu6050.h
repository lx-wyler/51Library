#ifndef __MPU6050_H__
#define __MPU6050_H__


// 定义6050内部地址
#define	SMPLRT_DIV		0x19	// 陀螺仪采样率，典型值：0X07(125hz)
#define	CONFIG			0x1A	// 低通滤波频率，典型值：0X06(5HZ)
#define	GYRO_CONFIG		0x1B	// 陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)
#define	ACCEL_CONFIG	0x1C	// 加速计自检、测量范围及高通滤波频率，典型值：0x01(不自检，2G，5Hz)
#define PWR_MGMT_1		0x6B	// 电源管理，典型值：0x00(正常启用)
#define WHO_AM_I		0x75	// IIC地址寄存器(默认数值0x68，只读)
#define MPU6050Address	0xD0	// IIC写入时的地址字节数据，+1为读取

// 这些是加速度的宏
#define	ACCEL_XOUT_H	        0x3B    //a
#define	ACCEL_XOUT_L	        0x3C    //b
#define	ACCEL_YOUT_H	        0x3D    //c
#define	ACCEL_YOUT_L	        0x3E    //d
#define	ACCEL_ZOUT_H	        0x3F    //e
#define	ACCEL_ZOUT_L	        0x40    //f

// 这些是陀螺仪的宏
#define	GYRO_XOUT_H		0x43
#define	GYRO_XOUT_L		0x44	
#define	GYRO_YOUT_H		0x45
#define	GYRO_YOUT_L		0x46
#define	GYRO_ZOUT_H		0x47
#define	GYRO_ZOUT_L		0x48




bit init_mpu6050();  // 初始化6050，成功返回1，失败返回0
int read_accel_x();  // 读X轴加速度
int read_accel_y();  // 读y轴加速度
int read_accel_z();  // 读z轴加速度
int read_gyro_x();  // 读x轴角速度
int read_gyro_y();  // 读y轴角速度
int read_gyro_z();  // 读z轴角速度

#endif