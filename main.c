#include <reg52.h>
#include "LED.h"
#include "smg.h"
#include "ePaper.h"
#include "PinDefine.h"
#include "uart.h"
#include "keyboard.h"
#include <string.h>
#include "mycommon.h"
#include "oled.h"
#include <stdio.h>
#include "i2c.h"
#include "mpu6050.h"
#include "pac.h"



/*
int main(){
	
	unsigned int itemp = 0;
	 char ctemp = 0;
	unsigned char bufftemp[10] = {0};
	
	InitOled();
	OLED_Clear();
	
	
	while(1){
		sprintf(bufftemp, "%6d", ctemp--);
		OLED_P6x8Str(0, 0, bufftemp);
		
		itemp = ctemp;
		sprintf(bufftemp, "%6d", itemp);
		OLED_P6x8Str(0, 1, bufftemp);
		
		delay(10);
	}
	
	return 0;
}
*/



// test mpu6050 i2c

int main(){
	
	unsigned int it = 0;
	unsigned int temp = 0;
	char buff_temp[10] = {0};
	
	
	
	//UartInit();
	TESTP = 0;
	TESTRECEIVE = 0;
	InitOled();
	
	delay(200);
	
	I2C_writedata(MPU6050Address, PWR_MGMT_1, 0x00);
	delay(10);
	I2C_writedata(MPU6050Address, SMPLRT_DIV, 0x07);
	delay(10);
	I2C_writedata(MPU6050Address, CONFIG, 0x06);
	delay(10);
	I2C_writedata(MPU6050Address, GYRO_CONFIG, 0x18);
	delay(10);
	I2C_writedata(MPU6050Address, ACCEL_CONFIG, 0x01);
	
	delay(100);
	
	temp = I2C_readdata(MPU6050Address, WHO_AM_I);
	sprintf(buff_temp, "%x", temp);
	OLED_P6x8Str(0, 6, buff_temp);
	
	
	it = 0;
	
	LED0 = 1;
	while(1){
		
		it++;
		temp = read_accel_x();
		sprintf(buff_temp, "%6d", temp);
		OLED_P6x8Str(0, 0, buff_temp);
		
		temp = read_accel_y();
		sprintf(buff_temp, "%6d", temp);
		OLED_P6x8Str(36, 0, buff_temp);
		
		temp = read_accel_z();
		sprintf(buff_temp, "%6d", temp);
		OLED_P6x8Str(72, 0, buff_temp);
		
		temp = read_gyro_x();
		sprintf(buff_temp, "%6d", temp);
		OLED_P6x8Str(0, 1, buff_temp);
		
		temp = read_gyro_y();
		sprintf(buff_temp, "%6d", temp);
		OLED_P6x8Str(36, 1, buff_temp);
		
		temp = read_gyro_z();
		sprintf(buff_temp, "%6d", temp);
		OLED_P6x8Str(72, 1, buff_temp);
//		
		sprintf(buff_temp, "%6d", it);
		OLED_P6x8Str(0, 7, buff_temp);
		delay(10);
		
		
	}
	return 0;
}



